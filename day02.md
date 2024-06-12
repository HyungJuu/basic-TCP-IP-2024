## 2일차 (24.06.12)
- 주소체계와 데이터 정렬
    - 인터넷 주소의 초기화와 할당
        - inet_addr
            - 32비트 정수형태로 IP주소를 변환
            - 유효하지 않은 IP주소에 대한 오류검출
            - 네트워크 바이트 순서(빅 엔디안)로 정렬
        
        - inet_aton
            - 기능상 inet_addr 함수와 동일
            - 차이점 : 구조체 변수 in_addr를 이용 &rarr; 변환 결과가 저장됨
        
        - inet_ntoa
            - inet_aton 함수의 반대기능
            - 네트워크 바이트 순서로 정렬된 정수형 IP주소정보를 문자열 형태로 변환하여, 변환된 문자열의 주소 값을 반환
            - 반환형 : char형 포인터
            - 함수 재호출 전까지만 반환된 문자열의 주소값이 유효 &rarr; 문자열 정보를 유지해야 한다면 별도의 메모리 공간에 복사


        - 인터넷 주소 초기화
            - 일반적인 인터넷 주소의 초기화 과정

                ```c
                struct sockaddr_in addr;
                char *serv_ip = "211.217.168.13";   // IP주소 문자열 선언
                char *serv_port = "9190";   // PORT번호 문자열 선언
                memset(&addr, 0, sizeof(addr)); // 구조체 변수 addr의 모든 멤버 0으로 초기화
                addr.sin_family = AF_INET;  // 주소체계 지정
                addr.sin_addr.s_addr = inet_addr(serv_ip);  // 문자열 기반의 IP주소 초기화
                addr.sin_port = htons(atoi(serv_port)); // 문자열 기반의 PORT번호 초기화
                ```
            
            - memset 함수 : 동일한 값으로 바이트단위 초기화를 할때 호출

        - INADDR_ANY
            - 현재 실행 중인 컴퓨터의 IP를 소켓에 부여할 때 사용
            - 주로 서버 프로그램 구현에 사용

                ```c
                struct sockaddr_in addr;
                char *serv_port = "9190";
                memset(&addr, 0, sizeof(addr));
                addr.sin_family = AF_INET;
                addr.sin_addr.s_addr = htonl(INADDR_ANY);
                addr.sin_port = htons(atoi(serv_port));
                ```

- TCP 기반 서버/클라이언트
    - TCP / UDP에 대한 이해
        - TCP/IP 프로토콜 스택
        
