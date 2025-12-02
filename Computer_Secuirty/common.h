#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <openssl/bn.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/err.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define KEY_SIZE 32 // AES-256
#define IV_SIZE 16

// 메시지 타입 정의
#define MSG_DH_PARAMS 1   // Server -> Client: p, g, g^s
#define MSG_DH_PUBLIC 2   // Client -> Server: g^c
#define MSG_AUTH      3   // Client -> Server: Encrypted Creds
#define MSG_AUTH_RES  4   // Server -> Client: Result
#define MSG_SESS_KEY  5   // Client -> Server: Encrypted Session Key
#define MSG_COMMAND   6   // Encrypted Command
#define MSG_FILE_DATA 7   // Encrypted File Chunk
#define MSG_FILE_END  8   // End of File Transfer
#define MSG_ERROR     9

typedef struct {
    int type;
    int payload_len;
    char payload[BUFFER_SIZE];
} Packet;

// OpenSSL 에러 출력
void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

// AES-256-CBC 암호화
int encrypt_aes(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                unsigned char *iv, unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) handleErrors();

    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) handleErrors();
    ciphertext_len = len;

    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}

// AES-256-CBC 복호화
int decrypt_aes(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
                unsigned char *iv, unsigned char *plaintext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;

    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) handleErrors();

    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) handleErrors();
    plaintext_len = len;

    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
        // 복호화 실패 (패딩 오류 등)
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    // Null terminate for convenience if string
    plaintext[plaintext_len] = '\0';
    return plaintext_len;
}

// 소켓 유틸리티
void send_packet(int sock, int type, const void* data, int len) {
    Packet p;
    p.type = type;
    p.payload_len = len;
    if (len > BUFFER_SIZE) {
        fprintf(stderr, "Error: Payload too large\n");
        return;
    }
    memcpy(p.payload, data, len);
    if (send(sock, &p, sizeof(p), 0) < 0) {
        perror("Send failed");
    }
}

int recv_packet(int sock, Packet *p) {
    int read_len = recv(sock, p, sizeof(Packet), 0);
    if (read_len <= 0) return -1;
    return 0;
}

#endif
