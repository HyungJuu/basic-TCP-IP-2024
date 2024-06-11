# basic-TCP-IP-2024
부경대 2024 IoT 개발자과정 TCP/IP 학습 리포지토리

## 1일차(24.06.11)
- tcp/ip : cmd &rarr; ipconfig
    - IP : 컴퓨터 주소
    - **IPv4** | IPv6 : 총 4개의 바이트(byte)로 구성(현재 사용됨) | IPv4의 할당량이 부족할 때 대체 아이피 주소
    - 기본 게이트웨이 : 컴퓨터로 들어오는 출입문(1번). IP와 3byte까지는 동일함

- 전송방식 차이
    - TCP(Transmission Control Protocol) : 데이터를 잃어버리면 안될 때 사용 
        - ex) 압축파일
    - UDP(User Datagram Protocol) : 데이터를 한두개 잃어버려도 문제가 없을 때 사용. 보안,신뢰성 < 전송속도, 효율성
        - ex) 비디오 재생

- 네트워크 프로그래밍 연결과정 : **소말리아**
    - 소켓(socket) &rarr; 소
    - 바인더(bind) &rarr; 말
    - 리슨(listen) &rarr; 리
    - 엑셉트(accept) &rarr; 아

    ``` cpp
    #include <sys/socket.h>
    // 소켓 생성 -> socket 함수 호출
    int socket(int domain, int type, int protocol); // 성공 시 파일 디스크립터, 실패 시 -1 반환
    // IP 주소와 PORT번호 할당 -> bind 함수 호출
    int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen); // 성공 시 0, 실패 시 -1 반환
    // 연결요청 가능상태로 변경 -> listen 함수 호출
    int listen(int sockfd, int backlog); // 성공 시 0, 실패 시 -1 반환
    // 연결요청에 대한 수랑 -> accept 함수 호출
    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); // 성공 시 파일 디스크립터, 실패 시 -1 반환
    ```