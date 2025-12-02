#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

// Base64 인코딩을 위한 문자 테이블
static const char base64_table[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Base64 인코딩 함수
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

    // 패딩 처리
    int mod = length % 3;
    if (mod == 1) {
        encoded[output_length - 1] = '=';
        encoded[output_length - 2] = '=';
    } else if (mod == 2) {
        encoded[output_length - 1] = '=';
    }

    encoded[output_length] = '\0';
    return encoded;
}

// SHA3-512 해시 생성 함수
int generate_sha3_hash(const char *password, const char *salt,
                       unsigned char *hash_output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned int hash_len;

    // SHA3-512 알고리즘 선택
    md = EVP_sha3_512();
    if (md == NULL) {
        fprintf(stderr, "SHA3-512 not supported\n");
        return -1;
    }

    // 컨텍스트 생성
    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        fprintf(stderr, "Failed to create EVP_MD_CTX\n");
        return -1;
    }

    // 해시 초기화
    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1) {
        fprintf(stderr, "DigestInit failed\n");
        EVP_MD_CTX_free(mdctx);
        return -1;
    }

    // Salt 추가
    if (EVP_DigestUpdate(mdctx, salt, strlen(salt)) != 1) {
        fprintf(stderr, "DigestUpdate (salt) failed\n");
        EVP_MD_CTX_free(mdctx);
        return -1;
    }

    // Password 추가
    if (EVP_DigestUpdate(mdctx, password, strlen(password)) != 1) {
        fprintf(stderr, "DigestUpdate (password) failed\n");
        EVP_MD_CTX_free(mdctx);
        return -1;
    }

    // 최종 해시 계산
    if (EVP_DigestFinal_ex(mdctx, hash_output, &hash_len) != 1) {
        fprintf(stderr, "DigestFinal failed\n");
        EVP_MD_CTX_free(mdctx);
        return -1;
    }

    EVP_MD_CTX_free(mdctx);
    return hash_len;
}

// Shadow 파일 생성 및 출력
int write_shadow_file(const char *username, const char *salt,
                      const unsigned char *hash, int hash_len) {
    char *encoded_hash = base64_encode(hash, hash_len);

    if (encoded_hash == NULL) {
        fprintf(stderr, "Base64 encoding failed\n");
        return -1;
    }

    // shadow 파일 생성 (현재 디렉토리에 생성)
    FILE *shadow_file = fopen("shadow", "a");
    if (shadow_file == NULL) {
        fprintf(stderr, "Failed to open shadow file\n");
        free(encoded_hash);
        return -1;
    }

    // Shadow 파일 형식: username:$id$salt$hash:lastchanged:min:max:warn:inactive:expire:
    fprintf(shadow_file, "%s:$sha3-512$%s$%s:18900:0:99999:7:::\n",
            username, salt, encoded_hash);

    fclose(shadow_file);

    // 화면 출력
    printf("\n=== Shadow File Entry Created ===\n");
    printf("File: ./shadow\n");
    printf("Entry: %s:$sha3-512$%s$%s:18900:0:99999:7:::\n",
           username, salt, encoded_hash);

    printf("\n=== Details ===\n");
    printf("Username: %s\n", username);
    printf("Algorithm: SHA3-512\n");
    printf("Salt: %s\n", salt);
    printf("Hash (Base64): %s\n", encoded_hash);
    printf("Hash Length: %d bytes\n", hash_len);

    // 16진수 형식으로도 출력
    printf("Hash (Hex): ");
    for (int i = 0; i < hash_len; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    free(encoded_hash);
    return 0;
}

int main(int argc, char *argv[]) {
    char username[256];
    char password[256];
    char salt[256];
    unsigned char hash[EVP_MAX_MD_SIZE];
    int hash_len;

    printf("=== Shadow File Generator (SHA3-512) ===\n\n");

    // 사용자 입력
    if (argc == 4) {
        // 커맨드 라인 인자로 받은 경우
        strncpy(username, argv[1], sizeof(username) - 1);
        strncpy(password, argv[2], sizeof(password) - 1);
        strncpy(salt, argv[3], sizeof(salt) - 1);
    } else {
        // 대화형 입력
        printf("Enter username: ");
        if (fgets(username, sizeof(username), stdin) == NULL) {
            fprintf(stderr, "Failed to read username\n");
            return 1;
        }
        username[strcspn(username, "\n")] = 0;

        printf("Enter password: ");
        if (fgets(password, sizeof(password), stdin) == NULL) {
            fprintf(stderr, "Failed to read password\n");
            return 1;
        }
        password[strcspn(password, "\n")] = 0;

        printf("Enter salt: ");
        if (fgets(salt, sizeof(salt), stdin) == NULL) {
            fprintf(stderr, "Failed to read salt\n");
            return 1;
        }
        salt[strcspn(salt, "\n")] = 0;
    }

    // 입력 검증
    if (strlen(password) == 0) {
        fprintf(stderr, "Password cannot be empty\n");
        return 1;
    }

    if (strlen(salt) == 0) {
        fprintf(stderr, "Salt cannot be empty\n");
        return 1;
    }

    // SHA3-512 해시 생성
    hash_len = generate_sha3_hash(password, salt, hash);
    if (hash_len < 0) {
        fprintf(stderr, "Hash generation failed\n");
        return 1;
    }

    // Shadow 파일 생성 및 출력
    if (write_shadow_file(username, salt, hash, hash_len) < 0) {
        fprintf(stderr, "Failed to write shadow file\n");
        return 1;
    }

    printf("\n✓ Shadow file successfully created/updated!\n");
    printf("✓ You can view it with: cat shadow\n");

    return 0;
}
