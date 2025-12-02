#include "common.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <IP> <PORT>\n", argv[0]);
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        perror("Connection failed");
        return 1;
    }

    printf("Connected to server.\n");

    // 1. DH 파라미터 수신 (g, p, gs)
    Packet pkt;
    if (recv_packet(sock, &pkt) < 0 || pkt.type != MSG_DH_PARAMS) {
        printf("Protocol Error: No DH Params\n");
        return 1;
    }

    // 파싱 "p:g:gs"
    char *p_str = strtok(pkt.payload, ":");
    char *g_str = strtok(NULL, ":");
    char *gs_str = strtok(NULL, ":");

    BIGNUM *p = BN_new(); BN_hex2bn(&p, p_str);
    BIGNUM *g = BN_new(); BN_hex2bn(&g, g_str);
    BIGNUM *gs = BN_new(); BN_hex2bn(&gs, gs_str); // 서버 공개키

    // 2. 클라이언트 키 생성 (c, gc)
    BIGNUM *c = BN_new();
    BIGNUM *gc = BN_new();
    BN_CTX *ctx = BN_CTX_new();

    BN_rand(c, 256, -1, 0);         // 클라이언트 개인키
    BN_mod_exp(gc, g, c, p, ctx);   // 클라이언트 공개키 g^c mod p

    // gc 전송
    char *gc_str = BN_bn2hex(gc);
    send_packet(sock, MSG_DH_PUBLIC, gc_str, strlen(gc_str) + 1);
    OPENSSL_free(gc_str);

    // 3. 공통 비밀키 생성 gsc = (gs)^c mod p
    BIGNUM *gsc = BN_new();
    BN_mod_exp(gsc, gs, c, p, ctx);

    // 대칭키 도출
    unsigned char shared_secret[32];
    unsigned char iv[IV_SIZE] = {0}; // Handshake용 IV
    char *gsc_hex = BN_bn2hex(gsc);
    SHA256((unsigned char*)gsc_hex, strlen(gsc_hex), shared_secret);
    OPENSSL_free(gsc_hex);

    BN_free(p); BN_free(g); BN_free(c); BN_free(gs); BN_free(gc); BN_free(gsc); BN_CTX_free(ctx);
    printf("DH Key Exchange Completed.\n");

    // 4. 인증 (로그인)
    unsigned char current_key[KEY_SIZE];
    memcpy(current_key, shared_secret, KEY_SIZE);

    while (1) {
        char user[100], pass[100];
        printf("Username: "); scanf("%s", user);
        printf("Password: "); scanf("%s", pass);

        char creds[256];
        sprintf(creds, "%s:%s", user, pass);

        // 암호화 후 전송
        unsigned char encrypted_creds[BUFFER_SIZE];
        int enc_len = encrypt_aes((unsigned char*)creds, strlen(creds), current_key, iv, encrypted_creds);
        send_packet(sock, MSG_AUTH, encrypted_creds, enc_len);

        // 결과 수신
        recv_packet(sock, &pkt);
        if (strncmp(pkt.payload, "SUCCESS", 7) == 0) {
            printf("Login Successful!\n");
            break;
        } else {
            printf("Login Failed. Try again.\n");
        }
    }

    // 5. 세션 키 생성 및 전송 (과제 요구사항: 클라이언트가 생성하여 서버로 전송)
    unsigned char session_key[KEY_SIZE];
    unsigned char session_iv[IV_SIZE];
    RAND_bytes(session_key, KEY_SIZE);
    RAND_bytes(session_iv, IV_SIZE);

    // [SessionKey + SessionIV]를 DH Shared Key로 암호화
    unsigned char key_data[KEY_SIZE + IV_SIZE];
    memcpy(key_data, session_key, KEY_SIZE);
    memcpy(key_data + KEY_SIZE, session_iv, IV_SIZE);

    unsigned char encrypted_sess_key[BUFFER_SIZE];
    int esk_len = encrypt_aes(key_data, KEY_SIZE + IV_SIZE, current_key, iv, encrypted_sess_key);

    send_packet(sock, MSG_SESS_KEY, encrypted_sess_key, esk_len);
    printf("Session Key Sent to Server securely.\n");

    // 이제부터 세션 키 사용
    // 버퍼 비우기 (scanf 후 남은 개행문자 처리)
    int c_dummy; while ((c_dummy = getchar()) != '\n' && c_dummy != EOF);

    // 6. 명령 루프
    while (1) {
        printf("Sec-FTP> ");
        char cmd_line[256];
        if (fgets(cmd_line, sizeof(cmd_line), stdin) == NULL) break;
        cmd_line[strcspn(cmd_line, "\n")] = 0; // Remove newline

        if (strlen(cmd_line) == 0) continue;

        // 명령 암호화하여 전송
        unsigned char enc_cmd[BUFFER_SIZE];
        int cmd_len = encrypt_aes((unsigned char*)cmd_line, strlen(cmd_line), session_key, session_iv, enc_cmd);
        send_packet(sock, MSG_COMMAND, enc_cmd, cmd_len);

        // 로컬 파싱
        char type[10], p1[256], p2[256];
        int args = sscanf(cmd_line, "%s %s %s", type, p1, p2);

        if (strcmp(type, "quit") == 0) {
            break;
        }
        else if (strcmp(type, "send") == 0) {
            // send local remote -> Client reads local, sends to server
            if (args < 3) continue;

            FILE *fp = fopen(p1, "rb");
            if (!fp) {
                printf("File not found: %s\n", p1);
                // 서버가 이미 COMMAND를 받고 대기중이므로 EOF를 보내서 끊어줘야 함
                send_packet(sock, MSG_FILE_END, "ERR", 3);
                continue;
            }

            unsigned char fbuf[1024];
            int n;
            printf("Sending file %s...\n", p1);
            while ((n = fread(fbuf, 1, sizeof(fbuf), fp)) > 0) {
                unsigned char enc[BUFFER_SIZE];
                int enc_len = encrypt_aes(fbuf, n, session_key, session_iv, enc);
                send_packet(sock, MSG_FILE_DATA, enc, enc_len);
            }
            fclose(fp);
            send_packet(sock, MSG_FILE_END, "EOF", 3);
            printf("Transfer complete.\n");

        }
        else if (strcmp(type, "recv") == 0) {
            // recv local remote -> Server sends, Client saves to local (p1)
            // 주의: 과제 명세 "recv path1/file1 path2/file2" -> p1: local, p2: remote
            if (args < 3) continue;

            FILE *fp = fopen(p1, "wb");
            if (!fp) { printf("Cannot write to %s\n", p1); continue; }

            printf("Receiving file from %s...\n", p2);
            while(1) {
                Packet data_pkt;
                recv_packet(sock, &data_pkt);

                if (data_pkt.type == MSG_ERROR) {
                    printf("Server Error: %s\n", data_pkt.payload);
                    break;
                }
                if (data_pkt.type == MSG_FILE_END) break;

                if (data_pkt.type == MSG_FILE_DATA) {
                    unsigned char plain[BUFFER_SIZE];
                    int p_len = decrypt_aes((unsigned char*)data_pkt.payload, data_pkt.payload_len, session_key, session_iv, plain);
                    if (p_len > 0) fwrite(plain, 1, p_len, fp);
                }
            }
            fclose(fp);
            printf("Download complete.\n");
        }
    }

    close(sock);
    return 0;
}
