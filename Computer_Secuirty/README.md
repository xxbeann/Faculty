# Sec-FTP: OpenSSL 기반 보안 파일 전송 프로그램
Sec-FTP는 신뢰할 수 없는 네트워크상에서 안전하게 파일을 송수신하기 위해 설계된 클라이언트-서버 프로그램입니다. 표준 FTP의 취약점인 평문 전송 문제를 해결하기 위해 Diffie-Hellman 키 교환과 AES-256 대칭키 암호화를 사용하여 SSH와 유사한 보안 아키텍처를 구현하였습니다.

## 🔐 주요 기능 및 보안 기술 (Security Features)

본 프로젝트는 기밀성(Confidentiality), 무결성(Integrity), 인증(Authentication)을 보장하기 위해 다음과 같은 암호학적 기법을 적용했습니다.

### 1. 안전한 키 교환 (Key Exchange)

- Diffie-Hellman 알고리즘을 사용하여, Sniffing이 가능한 환경에서도 서버와 클라이언트가 안전하게 Shared Secret을 생성합니다.
- RFC 2409 Group 2 표준 소수를 사용하여 수학적 안전성을 확보했습니다.

### 2. 강력한 암호화 (Encryption)

- AES-256-CBC 모드를 사용하여 모든 데이터(ID/PW, 명령어, 파일 내용)를 암호화합니다.
- OpenSSL EVP 라이브러리를 활용하여 표준 호환성을 유지했습니다.

### 3. 사용자 인증 (Authentication)

- Linux의 Shadow 파일 포맷을 호환하는 인증 시스템을 구현했습니다.
- SHA3-512 해시 알고리즘과 Salt를 사용하여 Rainbow Table 공격을 방어합니다.

### 4. 세션 보안 (Session Security)

- PFS(Perfect Forward Secrecy) 개념을 적용하여, 로그인 직후 임시 세션 키를 새로 생성하고 교체합니다.
- 이를 통해 장기 비밀키가 노출되더라도 과거의 통신 내용이 복호화되는 것을 방지합니다.

## 🛠️ 시스템 아키텍처 (Architecture)

Sec-FTP의 통신 프로세스는 SSH 프로토콜의 축소판과 유사하게 동작합니다.

<img width="1828" height="2496" alt="image" src="https://github.com/user-attachments/assets/31739619-fd32-4c25-89bc-aafea7e80967" />


## 💻 빌드 및 실행 방법 (Usage)

### 1. 필수 라이브러리 설치

OpenSSL 개발 라이브러리가 필요합니다.

- **Ubuntu/Linux:**
    
    ```bash
    sudo apt-get update
    sudo apt-get install libssl-dev
    ```
    
- **macOS:**
    
    ```bash
    brew install openssl
    ```
    

### 2. 컴파일 (Build)

```bash
gcc -o server server.c -lssl -lcrypto -lpthread
```

> 실행 파일 server, client, shadow_gen에 대해서 수행합니다.
> 

### 3. 사용자 계정 생성 (Setup)

서버에서 사용할 계정 정보를 담은 `password.txt` 파일을 생성해야 합니다.

1. 섀도우 생성기 실행:
    
    ```bash
    ./shadow_gen <username> <password> <salt>
    # 예시: ./shadow_gen bean 1234 mysalt
    ```
    
2. 생성된 `shadow` 파일을 `password.txt`로 이름 변경:
    
    ```bash
    mv shadow password.txt
    ```
    

### 4. 서버 실행 (Server)

```bash
./server
```

> 서버는 기본적으로 8080 포트에서 열리게 설정했습니다.
> 

### 5. 클라이언트 실행 (Client)

서버의 IP 주소와 포트 번호를 인자로 입력하여 실행합니다.

```bash
# 로컬 테스트
./client 127.0.0.1 8080
```

## 🎮 명령어 가이드 (Command)

로그인 성공 후 다음과 같은 명령어를 사용할 수 있습니다.

| **명령어** | **형식** | **설명** |
| **파일 전송** | `send <local_path> <remote_path>` | 클라이언트의 파일을 서버로 업로드합니다. |
| **파일 수신** | `recv <local_path> <remote_path>` | 서버의 파일을 클라이언트로 다운로드합니다. |
| **종료** | `quit` | 보안 연결을 종료하고 프로그램을 끝냅니다. |

**사용 예시:**

```
Sec-FTP> send my_data.txt backup/data.txt
Sec-FTP> recv downloaded_img.png server_images/photo.png
Sec-FTP> quit

```

## 🌐 네트워크 구성 (Network Setup)

본 프로그램은 소켓 프로그래밍을 통해 구현되어 다양한 네트워크 환경을 지원합니다.

1. **로컬 환경 (Localhost):** 단일 PC 내에서 `127.0.0.1`로 통신 가능.
2. **동일 네트워크 (LAN):** 같은 와이파이/공유기 내에서 사설 IP로 통신 가능.

## 📂 파일 구조

- `server.c`: 서버 메인 로직, 스레드 관리, 암호화 처리.
- `client.c`: 클라이언트 UI, 키 교환 및 파일 전송 로직.
- `common.h`: 프로토콜 정의, OpenSSL 래퍼 함수, 공통 헤더.
- `shadow_generator.c`: SHA3-512 기반 패스워드 해시 생성 도구.

## ⚠️ 주의사항 (Disclaimer)

이 프로젝트는 교육 및 과제 제출 목적으로 작성되었습니다. 실제 상용 환경에서 사용하기 위해서는 SSL/TLS 인증서 검증(MITM 방지) 및 추가적인 에러 처리가 필요할 수 있습니다.
