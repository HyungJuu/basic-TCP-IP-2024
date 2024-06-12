## 2일차 (24.06.12)
- 인터넷 주소 초기화

    ```c
    struct sockaddr_in addr;
    char *serv_ip = "211.217.168.13";   // IP주소 문자열 선언
    char *serv_port = "9190";   // PORT번호 문자열 선언
    memset(&addr, 0, sizeof(addr)); // 구조체 변수 addr의 모든 멤버 0으로 초기화
    addr.sin_family = AF_INET;  // 주소체계 지정
    addr.sin_addr.s_addr = inet_addr(serv_ip);  // 문자열 기반의 IP주소 초기화
    addr.sin_port = htons(atoi(serv_port)); // 문자열 기반의 PORT번호 초기화
    ```