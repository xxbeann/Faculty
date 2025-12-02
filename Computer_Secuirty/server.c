#include "common.h"

// shadow generator 로직 복사 (Base64 Table)
static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Base64 인코딩 (Shadow 파일 비교용)
char* base64_encode(const unsigned char *input, int length) {
    int output_length = 4 * ((length + 2) / 3);
    char *encoded = malloc(output_length + 1);
    if (encoded == NULL) return NULL;
    int i, j;
    for (i = 0, j = 0; i < length;) {
        uint32_t octet_a = i < length ? input[i++] : 0;
        uint32_t octet_b = i < length ? input[i++] : 0;
        uint32_t octet_c = i < length ? input[i++] : 0;
        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;
        encoded[j++] = base64_table[(triple >> 18) & 0x3F];
        encoded[j++] = base64_table[(triple >> 12) & 0x3F];
        encoded[j++] = base64_table[(triple >> 6) & 0x3F];
        encoded[j++] = base64_table[triple & 0x3F];
    }
    int mod = length % 3;
    if (mod == 1) { encoded[output_length - 1] = '='; encoded[output_length - 2] = '='; }
    else if (mod == 2) { encoded[output_length - 1] = '='; }
    encoded[output_length] = '\0';
    return encoded;
}

// SHA3-512 해시 생성
int generate_sha3_hash(const char *password, const char *salt, unsigned char *hash_output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha3_512();
    unsigned int hash_len;
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, salt, strlen(salt));
    EVP_DigestUpdate(mdctx, password, strlen(password));
    EVP_DigestFinal_ex(mdctx, hash_output, &hash_len);
    EVP_MD_CTX_free(mdctx);
    return hash_len;
}

// 클라이언트 핸들링 구조체
typedef struct {
    int sock;
    struct sockaddr_in addr;
} ClientInfo;

// 전역 대칭키 (스레드별로 관리해야 하나, 간단히 로컬 변수로 처리)
// 패스워드 검증 함수
int verify_password(const char *username, const char *password) {
    FILE *fp = fopen("password.txt", "r");
    if (!fp) return 0;

    char line[512];
    int auth_success = 0;

    while (fgets(line, sizeof(line), fp)) {
        // 포맷: username:$sha3-512$salt$hash...
        // 파싱을 위해 strtok 사용
        char *entry_user = strtok(line, ":");
        if (!entry_user) continue;

        if (strcmp(entry_user, username) == 0) {
            // 사용자 발견
            char *algo = strtok(NULL, "$"); // sha3-512 건너뜀
            if (!algo) break;

            char *salt = strtok(NULL, "$");
            char *stored_hash = strtok(NULL, ":"); // 해시 뒤에 :가 옴

            if (salt && stored_hash) {
                unsigned char hash_out[EVP_MAX_MD_SIZE];
                int len = generate_sha3_hash(password, salt, hash_out);
                char *encoded_try = base64_encode(hash_out, len);

                if (strcmp(encoded_try, stored_hash) == 0) {
                    auth_success = 1;
                }
                free(encoded_try);
            }
            break;
        }
    }
    fclose(fp);
    return auth_success;
}

void *client_handler(void *arg) {
    ClientInfo *info = (ClientInfo *)arg;
    int sock = info->sock;
    free(info);

    printf("Client connected.\n");

    // 1. DH 파라미터 생성 및 전송 (g, p, gs)
    BIGNUM *p = BN_get_rfc2409_prime_1024(NULL); // 1024비트 소수 (표준)
    BIGNUM *g = BN_new(); BN_set_word(g, 2);     // 생성자
    BIGNUM *s = BN_new();                        // 서버 개인키
    BIGNUM *gs = BN_new();                       // 공개키 g^s mod p
    BN_CTX *ctx = BN_CTX_new();

    BN_rand(s, 256, -1, 0); // 랜덤 개인키 생성
    BN_mod_exp(gs, g, s, p, ctx); // gs = g^s mod p

    // BigNumber를 문자열로 변환하여 전송 (간편함을 위해 Hex String)
    char *p_str = BN_bn2hex(p);
    char *g_str = BN_bn2hex(g);
    char *gs_str = BN_bn2hex(gs);

    char dh_payload[BUFFER_SIZE];
    sprintf(dh_payload, "%s:%s:%s", p_str, g_str, gs_str);
    send_packet(sock, MSG_DH_PARAMS, dh_payload, strlen(dh_payload) + 1);

    OPENSSL_free(p_str); OPENSSL_free(g_str); OPENSSL_free(gs_str);

    // 2. 클라이언트로부터 공개키(gc) 수신
    Packet pkt;
    if (recv_packet(sock, &pkt) < 0 || pkt.type != MSG_DH_PUBLIC) {
        printf("Handshake failed.\n");
        close(sock); return NULL;
    }

    BIGNUM *gc = BN_new();
    BN_hex2bn(&gc, pkt.payload);

    // 3. 공통 비밀키(shared secret) 생성: gsc = (gc)^s mod p
    BIGNUM *gsc = BN_new();
    BN_mod_exp(gsc, gc, s, p, ctx);

    // 공통 비밀키를 AES 키로 변환 (SHA256 해싱)
    unsigned char shared_secret[32]; // 256bit
    unsigned char iv[IV_SIZE] = {0}; // 초기 IV는 0으로 약속 (핸드셰이크 중)
    char *gsc_str = BN_bn2hex(gsc);
    SHA256((unsigned char*)gsc_str, strlen(gsc_str), shared_secret);
    OPENSSL_free(gsc_str);

    // 키 정리
    BN_free(p); BN_free(g); BN_free(s); BN_free(gs); BN_free(gc); BN_free(gsc); BN_CTX_free(ctx);

    printf("DH Key Exchange Completed.\n");

    // 4. 인증 단계
    unsigned char current_key[KEY_SIZE];
    memcpy(current_key, shared_secret, KEY_SIZE); // 초기에는 DH 키 사용

    int authenticated = 0;
    while (!authenticated) {
        if (recv_packet(sock, &pkt) < 0 || pkt.type != MSG_AUTH) break;

        char decrypted[BUFFER_SIZE];
        if (decrypt_aes((unsigned char*)pkt.payload, pkt.payload_len, current_key, iv, (unsigned char*)decrypted) < 0) {
            send_packet(sock, MSG_AUTH_RES, "FAIL", 4);
            continue;
        }

        char *user = strtok(decrypted, ":");
        char *pass = strtok(NULL, ":");

        if (user && pass && verify_password(user, pass)) {
            send_packet(sock, MSG_AUTH_RES, "SUCCESS", 7);
            authenticated = 1;
            printf("User %s logged in.\n", user);
        } else {
            send_packet(sock, MSG_AUTH_RES, "FAIL", 4);
        }
    }

    if (!authenticated) {
        close(sock);
        return NULL;
    }

    // 5. 세션 키 수신 (클라이언트 생성 -> 공개키(DH키)로 암호화 -> 서버 전송)
    // 문제 요구사항: "성공인 경우 클라이언트로부터 온 암호화된 대칭키 값을 수신한 후 복호화"
    if (recv_packet(sock, &pkt) < 0 || pkt.type != MSG_SESS_KEY) {
        close(sock); return NULL;
    }

    unsigned char session_key_payload[BUFFER_SIZE];
    int sk_len = decrypt_aes((unsigned char*)pkt.payload, pkt.payload_len, current_key, iv, session_key_payload);

    // 복호화된 페이로드는 [NewKey(32 bytes) + NewIV(16 bytes)] 구조라고 가정
    unsigned char session_key[KEY_SIZE];
    unsigned char session_iv[IV_SIZE];

    if (sk_len >= KEY_SIZE + IV_SIZE) {
        memcpy(session_key, session_key_payload, KEY_SIZE);
        memcpy(session_iv, session_key_payload + KEY_SIZE, IV_SIZE);
        printf("Session Key Established.\n");
    } else {
        printf("Invalid Session Key format.\n");
        close(sock); return NULL;
    }

    // 6. 명령 루프 (send, recv, quit)
    while (1) {
        if (recv_packet(sock, &pkt) < 0) break;

        if (pkt.type == MSG_COMMAND) {
            // 명령 복호화
            char command_buf[BUFFER_SIZE];
            decrypt_aes((unsigned char*)pkt.payload, pkt.payload_len, session_key, session_iv, (unsigned char*)command_buf);

            printf("Received Command: %s\n", command_buf);

            char type[10], p1[256], p2[256];
            int args = sscanf(command_buf, "%s %s %s", type, p1, p2);

            if (strcmp(type, "quit") == 0) {
                printf("Client requested quit.\n");
                break;
            } else if (strcmp(type, "send") == 0) {
                // Client sends file (Server receives)
                // p1: local(client), p2: remote(server) -> save to p2
                FILE *fp = fopen(p2, "wb");
                if (!fp) {
                     printf("Cannot open file for writing: %s\n", p2);
                     continue;
                }

                // 파일 데이터 수신 루프
                while(1) {
                    Packet data_pkt;
                    recv_packet(sock, &data_pkt);
                    if (data_pkt.type == MSG_FILE_END) break;

                    if (data_pkt.type == MSG_FILE_DATA) {
                        unsigned char plain[BUFFER_SIZE];
                        int p_len = decrypt_aes((unsigned char*)data_pkt.payload, data_pkt.payload_len, session_key, session_iv, plain);
                        if (p_len > 0) fwrite(plain, 1, p_len, fp);
                    }
                }
                fclose(fp);
                printf("File received: %s\n", p2);

            } else if (strcmp(type, "recv") == 0) {
                // Client receives file (Server sends)
                // p1: local(client), p2: remote(server) -> read from p2
                FILE *fp = fopen(p2, "rb");
                if (!fp) {
                    send_packet(sock, MSG_ERROR, "File not found", 14);
                    continue;
                }

                unsigned char fbuf[1024]; // Plain chunks
                int n;
                while ((n = fread(fbuf, 1, sizeof(fbuf), fp)) > 0) {
                    unsigned char enc[BUFFER_SIZE];
                    int enc_len = encrypt_aes(fbuf, n, session_key, session_iv, enc);
                    send_packet(sock, MSG_FILE_DATA, enc, enc_len);
                }
                fclose(fp);
                send_packet(sock, MSG_FILE_END, "EOF", 3);
                printf("File sent: %s\n", p2);
            }
        }
    }

    close(sock);
    return NULL;
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        perror("Bind failed");
        exit(1);
    }

    if (listen(server_sock, 10) != 0) {
        perror("Listen failed");
        exit(1);
    }

    printf("Sec-FTP Server listening on port %d...\n", PORT);

    while (1) {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);

        ClientInfo *info = malloc(sizeof(ClientInfo));
        info->sock = client_sock;
        info->addr = client_addr;

        pthread_t tid;
        pthread_create(&tid, NULL, client_handler, info);
        pthread_detach(tid);
    }

    return 0;
}
