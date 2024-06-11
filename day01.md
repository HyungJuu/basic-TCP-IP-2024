## 1일차(24.06.11) ~p.79
- Windows IP 구성 확인 : cmd &rarr; ipconfig
- TCP/IP
    - IP : 외부에서 해당 컴퓨터를 찾아오는데 필요한 주소
    - IPv4 | IPv6 &rarr; 버전차이
        - IPv4 : 총 4개의 바이트(byte)로 구성(현재 사용됨)
        - IPv6 : IPv4로 할당할 수 있는 인터넷 주소가 부족할 때 대체할 아이피 주소
        - ex) 192.168.10.10
    - 기본 게이트웨이 : 컴퓨터로 들어오는 출입문(1). IP와 3byte까지는 동일함
        - ex) 192.168.10.1
    - 서브넷마스크

- 전송방식 (TCP / UDP)
    - TCP(Transmission Control Protocol) : 전송 제어 프로토콜
        - 정확한 데이터 전송. 데이터를 잃어버리면 안될 때 사용 
        - ex) HTTP 통신, 이메일, 압축파일 전송
    - UDP(User Datagram Protocol) : 사용자 데이터그램 프로토콜
        - 데이터가 조금 누락되어도 문제가 없을 때 사용
        - 보안, 신뢰성 << 전송속도, 효율성
        - ex) 비디오 재생, 미디어 전송, 실시간 동영상서비스(브로드캐스팅)

- 네트워크 프로그래밍(소켓 프로그래밍) 이해 
    - **소말리아** ★★
        - 소 &rarr; 소켓(socket) : 휴대폰 기기
        - 말 &rarr; 바인드(bind) : 전화번호 할당
        - 리 &rarr; 리슨(listen) : 개통 완료
        - 아 &rarr; 엑셉트(accept) : 통화 기능


    - 서버 소켓, 리스닝 소켓
        - 서버 프로그램에서 생성한 소켓
            - 서버(Server) : 연결 요청을 수락(허용)하는 프로그램
                - 연결을 요청하는 클라이언트보다 먼서 실행되어야 함
                - 복잡한 실행과정

            ``` c
            #include <sys/socket.h>
            // 소켓 생성 -> socket 함수 호출
            int socket(int domain, int type, int protocol); // 성공 시 파일 디스크립터, 실패 시 -1 반환
            // IP와 PORT번호 할당 -> bind 함수 호출
            int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen); // 성공 시 0, 실패 시 -1 반환
            // 연결요청 가능상태로 변경 -> listen 함수 호출
            int listen(int sockfd, int backlog); // 성공 시 0, 실패 시 -1 반환
            // 연결요청에 대한 수락 -> accept 함수 호출
            int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); // 성공 시 파일 디스크립터, 실패 시 -1 반환
            // accept 함수 호출 이후에 데이터 송수신이 가능하다. 단, 연결요청이 있을 때만 함수가 반환을 한다.
            ```

    - 클라이언트 소켓
        - 연결 요청을 진행하는 소켓
            - socket 함수호출(소켓 생성) + connect 함수호출(서버로 연결요청)
            - 상대적으로 간단한 실행과정

            ```c
            #include <sys/socket.h>
            int connect(int sockfd, struct sockaddr *serv_addr, socklen_t addrlen);
            // 성공 시 0, 실패 시 -1 반환
            ```

- 리눅스 기반 파일 조작
    - 파일 디스크립터 (File Desciptor)
        - 운영체제가 만든 파일 또는 소켓을 구분하기 위한 일종의 숫자
        - 파일과 소켓은 생성과정을 거쳐야 파일 디스크립터가 할당 (일반적)
        - 리눅스에서 제공하는 함수
            - 별도의 생성과정 필요x, 프로그램 실행 시 자동할당되는 파일 디스크립터

                ![리눅스 파일 디스크립터](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp005.png)

    - 파일 조작
        - 파일 열기
            - open(파일의 이름 및 경로 정보, 파일 오픈모드) &rarr; 인자 2개

                ```c
                #include <sys/types.h>
                #include <sys/stat.h>
                #include <fcntl.h>

                int open(const char *path, int flag);
                // 성공 시 파일 디스크립터, 실패 시 -1 반환

                /*
                    첫번째 인자 : 파일 이름을 나타내는 문자열의 주소 값
                    두번째 인자 : 파일의 오픈모드 정보
                */
                ```

            - 파일 오픈모드
                | **오픈모드** | **의미** |
                | :------: | :------ |
                | O_CREAT | 필요하면 파일을 생성 |
                | O_TRUNC | 기존 데이터 전부 삭제 |
                | O_APPEND | 기존 데이터를 보존하고, 뒤에 이어서 저장 |
                | O_RDONLY | 읽기 전용으로 파일 오픈 |
                | O_WRONLY | 쓰기 전용으로 파일 오픈 |
                | O_RDWR | 읽기, 쓰기 겸용으로 파일 오픈 |

        - 파일 닫기 
            - close(파일 디스크립터) &rarr; 인자 1개

                ```c
                #include <unistd.h>

                int close(int fd);
                // 성공 시 0, 실패 시 -1 반환

                /* 인자 : 닫고자하는 파일(소켓)의 파일 디스크립터 */
                ```

        - 파일 쓰기
            - 데이터를 출력(전송)하는 함수
            - write(파일 디스크립터, 버퍼, 데이터 바이트 수) &rarr; 인자 3개

                ```c
                #include <unistd.h>

                ssize_t wirte(int fd, const void *buf, size_t nbytes);
                // 성공 시 전달한 바이트 수, 실패 시 -1 반환
                /* 
                    첫번째 인자 : 데이터 전송 대상을 나타내는 파일 디스크립터
                    두번째 인자 : 전송할 데이터가 저장된 버퍼의 주소 값
                    세번째 인자 : 전송할 데이터의 바이트 수 
                */
                ```

        - 파일 읽기
            - 데이터를 입력(수신)하는 함수
            - read(파일 디스크립터, 버퍼, 데이터 바이트 수) &rarr; 인자 3개

                ```c
                #include <unistd.h>

                ssize_t read(int fd, void *buf, size_t nbytes);
                // 성공 시 수신한 바이트 수(단 파일의 끝을 만나면 0), 실패 시 -1 반환
                /*
                    첫번째 인자 : 데이터 수신 대상을 나타내는 파일 디스크립터
                    두번째 인자 : 수신한 데이터를 저장할 버퍼의 주소 값
                    세번째 인자 : 수신할 최대 바이트 수 
                */
                ```
        - unsigned : 양수
        - ssize-t 등 앞에 붙는 s는 signed를 의미

- 소켓의 프로토콜
    - 프로토콜 (Protocol) 
        - 약속의 의미
        - 컴퓨터 간의 데이터 송수신에 필요한 통신규약
        - 소켓 생성시 기본적인 프로토콜 지정 필요

    - 프로토콜 체계
        | **이름** | **프로토콜 체계 (Protocol Family)** |
        | :------: | :--- |
        | PF_INET | IPv4 인터넷 프로토콜 체계 |
        | PF_INET6 | IPv6 인터넷 프로토콜 체계 |
        | PF_LOCAL | 로컬 통신을 위한 UNIX 프로토콜 체계 |
        | PF_PACKET | Low Level 소켓을 위한 프로토콜 체계 |
        | PF_IPX | IPX 노벨 프로토콜 체계 |

        <!-- ![프로토콜 체계](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp001.png) -->
    
    - 소켓 타입
        - 연결지향형 소켓(SOCK_STREAM) : TCP
            - 중간에 데이터 소멸 x
            - 전송 순서대로 데이터 수신
            - 데이터의 경계가 존재 x
            - 소켓 대 소켓의 연결 : 반드시 1 대 1 구조

        - 비연결지향형 소켓(SOCK_DGRAM) : UDP
            - 전송순서에 상관없이 빠른 속도의 전송 지향
            - 데이터 손실 및 파손의 우려 o
            - 데이터의 경계가 존재
            - 한번에 전송가능한 데이터 크기가 제한

- IP주소와 PORT번호
    - IP주소
        - IPv4 : 4바이트 주소체계 [1Byte] [1Byte] [1Byte] [1Byte]
        - IPv6 : 16바이트 주소체계 [4Byte] [4Byte] [4Byte] [4Byte]
            
            ![IPv4 인터넷 주소체계](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp003.png)
            
    - 클래스별 네트워크 주소, 호스트 주소 경계

        <!-- ![클래스](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp002.png) -->
        <img src="https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp002.png" width="650" alt="클래스">

    - PORT번호
        - 소켓을 구분하는 용도로 사용
        - 하나의 프로그램 내에 둘 이상의 소켓이 존재할 수 있음 &rarr; 둘 이상의 포트가 하나의 프로그램에 의해 할당 가능
        - 16비트로 표현 (0 ~ 65535)

- 주소정보의 표현
    - IPv4 기반 주소표현 구조체

        ```c
        struct sockaddr_in
            {
                sa_family_t     sin_family;     // 주소체계
                unit16_t        sin_port;       // 16비트 TCP/UDP PORT번호 -> 네트워크 바이트 순서로 저장
                struct in_addr  sin_addr;       // 32비트 IP주소 -> 네트워크 바이트 순서로 저장
                char            sin_zero[8];    // 사용되지 않음
            }

            struct in_addr
            {
                in_addr_t       s_addr;         // 32비트 IPv4 인터넷 주소
            }
        ```

        <!-- - POSIX(Portable Operating System Interface) : 유닉스 계열의 운영체제에 적용하기위한 표준
            | 자료형 이름 | 자료형에 담길 정보 | 선언된 헤더파일 |
            | :---------: | :----------------- | :-------------- |
            | int8_t | | | -->

- 네트워크 바이트 순서와 인터넷 주소 변환
    - 바이트 순서 & 네트워크 바이트 순서
        - CPU가 데이터를 메모리에 저장하는 방식
            - 빅 엔디안(Big Endian)
                - 상위 바이트의 값을 작은 번지수에 저장
            - 리틀 엔디안(Little Endian)
                - 상위 바이트의 값을 큰 번지수에 저장

            ![CPU 데이터 저장방식](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp006.png)

        - 호스트 바이트 순서(Host Byte Order) : CPU의 데이터 저장방식
            - 인텔계열 CPU : 리틀 엔디안 방식으로 데이터를 저장함

        - 네트워크 바이트 순서(Network Byte Order) : 빅 엔디안 방식으로 통일!
            - 모든 컴퓨터는 수신된 데이터가 네트워크 바이트 순서로 정렬되어있음
            - 리틀 엔디안 시스템에서는 데이터 전송하기에 앞서 빅 엔디안 정렬방식으로 데이터를 재정렬

        - 바이트 순서 변환(Endian Conversions)
            - h : 호스트(host) 바이트 순서
            - n : 네트워크(network) 바이트 순서
            - s : short(2바이트) &rarr; 주로 PORT번호의 변환에 사용
                - htons : short형 데이터를 호스트 바이트 순서 &rarr; 네트워크 바이트 순서로 변환
                - ntohs : short형 데이터를 네트워크 바이트 순서 &rarr; 호스트 바이트 순서로 변환

            - l : long(4바이트) &rarr; 주로 IP주소의 변환에 사용
                - htonl : long형 데이터를 호스트 바이트 순서 &rarr; 네트워크 바이트 순서로 변환
                - ntohl : long형 데이터를 네트워크 바이트 순서 &rarr; 호스트 바이트 순서로 변환

                ``` c
                // 예제(p.74) endian_conv.c
                #include <stdio.h>
                #include <arpa/inet.h>
                
                int main(int argc, char *argv[])
                {
                    unsigned short host_port = 0x1234;
                    unsigned short net_port;
                    unsigned long host_addr = 0x12345678;
                    unsigned long net_addr;

                // 바이트 순서 변환
                net_port = htons(host_port); // short형 데이터 : 호스트 -> 네트워크
                net_addr = htonl(host_addr); // long형 데이터 : 호스트 -> 네트워크

                printf("Host ordered prot : %#x \n", host_port);
                printf("Network ordered port : %#x \n", net_port);
                printf("Host ordered address : %#lx \n", host_addr);
                printf("Network ordered address : %#lx \n", net_addr);
                return 0;
                }
                ```

                ``` c
                // 리틀 엔디안 기준으로 정렬하는 CPU에서의 실행결과
                Host ordered prot : 0x1234
                Network ordered port : 0x3412
                Host ordered address : 0x12345678
                Network ordered address : 0x78563412

                // 빅 엔디안 기준으로 정렬하는 CPU 상에서 실행할 경우, 변환 이후에도 값이 달라지지 않는다.
                // 인텔, AMD 계열의 CPU -> 리틀 엔디안 기준으로 정렬
                ```