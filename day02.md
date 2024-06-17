## 2일차 (24.06.12) ~ p.157
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
                // 상수 INADDR_ANY를 통해 서버의 IP주소를 할당
                addr.sin_port = htons(atoi(serv_port));
                ```

- TCP 기반 서버/클라이언트
    - TCP / UDP에 대한 이해
        - TCP/IP 프로토콜 스택

            ![TCP/IP 프로토콜 스택](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp007.png)

        - LINK 계층
            - 물리적인 영역의 표준화 결과
            - 가장 기본이 되는 영역
            - LAN, WAN, MAN과 같은 물리적인 네트워크 표준과 관련된 프로토콜을 정의하는 영역

        - IP 계층
            - 데이터를 전송하기 위한 경로 선택의 문제를 해결
            - IP(Internet protocol)
                - 비연결지향적이며 신뢰할 수 없는 프로토콜
                - 데이터 전송 시 경로를 선택해 주지만, 일정치 않음
                - 데이터 전송 도중 경로상 문제가 발생하면 다른 경로를 선택하는데, 이 과정에서 발생하는 문제를 해결해주지 않음
                - 오류 발생에 대한 대비 x
                
        
        - TCP/UDP 계층(= 전송(Transport) 계층)
            - 실제 데이터의 송수신과 관련있는 계층
                | TCP | UDP|
                | :--- | :--- |
                | 데이터 전송을 보장하는 프로토콜 | 데이터 전송을 보장하지 않는 프로토콜 |
                | 신뢰성 보장 o | 신뢰성 보장 x |
                | 복잡 | 간단 |
                | 기반 프로토콜: IP |  |

                - IP만을 이용하여 데이터를 전송 시
                    - IP는 오로지 하나의 데이터 패킷(데이터 전송 기본단위)이 전송되는 과정에만 중심을 두고 설계됨
                    - 여러개의 데이터 패킷을 전송해도 IP에 의해 진행 &rarr; 전송순서와 전송 그 자체를 신뢰할 수 없음
                
                - TCP 프로토콜 추가 시
                    - 데이터를 주고받는 과정에서 서로 데이털를 주고받음을 확인
                    - 분실된 데이터에 대해서 재전송 &rarr; 신뢰 가능

        - APPLICATION 계층
            - 프로그래머에 의해서 완성되는 계층
                - 응용 프로그램의 프로토콜을 구성하는 계층
                - 소켓을 기반으로 완성
                - 소켓 생성시 LINK, IP, TCP/UDP계층에 대한 내용은 숨겨짐 &rarr; APPLICATION 계층의 완성에 집중

    - TCP 기반 서버, 클라이언트 구현
        - TCP 서버의 기본 함수호출 순서
            
            ![서버 함수호출 순서](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp008.png)

        - TCP 클라이언트 기본 함수호출 순서

            ![클라이언트 함수호출 순서](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp009.png)

        - TCP 기반 서버, 클라이언트 함수호출 관계

            ![함수호출 관계](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp010.png)

    - lterative 기반 서버, 클라이언트 구현
        - lterative 서버의 함수호출 순서

            ![함수호출 순서](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp011.png)

* 서버-클라이언트
    - 검색창(192.168.0.1) &rarr; 공유기 관리자모드 접속 &rarr; 포트포워드 설정 &rarr; 내부 ip주소, 외부포트
    
