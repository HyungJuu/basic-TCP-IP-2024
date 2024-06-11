## 1일차(24.06.11) ~p.79
- tcp/ip : cmd &rarr; ipconfig
    - IP : 외부에서 해당 컴퓨터를 찾아오는데 필요한 주소
    - IPv4 | IPv6 &rarr; 버전차이
        - IPv4 : 총 4개의 바이트(byte)로 구성(현재 사용됨)
        - IPv6 : IPv4의 할당량이 부족할 때 대체 아이피 주소
        - ex) 192.168.5.2
    - 기본 게이트웨이 : 컴퓨터로 들어오는 출입문(1번). IP와 3byte까지는 동일함
        - ex) 192.168.5.1
    - 서브넷마스크

- 전송방식 차이
    - TCP(Transmission Control Protocol) : 정확한 데이터 전송. 데이터를 잃어버리면 안될 때 사용 
        - ex) 압축파일
    - UDP(User Datagram Protocol) : 데이터가 한두개 유실되어도 문제가 없을 때 사용. 보안,신뢰성 < 전송속도, 효율성
        - ex) 비디오 재생, 미디어 전송

- 네트워크 프로세스 : **소말리아**
    - 소 &rarr; 소켓(socket) : 휴대폰
    - 말 &rarr; 바인더(bind) : 전화번호 할당
    - 리 &rarr; 리슨(listen) : 개통
    - 아 &rarr; 엑셉트(accept) : 통화기능

    ``` c
    #include <sys/socket.h>
    // 소켓 생성 -> socket 함수 호출
    int socket(int domain, int type, int protocol); // 성공 시 파일 디스크립터, 실패 시 -1 반환
    // IP 주소와 PORT번호 할당 -> bind 함수 호출
    int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen); // 성공 시 0, 실패 시 -1 반환
    // 연결요청 가능상태로 변경 -> listen 함수 호출
    int listen(int sockfd, int backlog); // 성공 시 0, 실패 시 -1 반환
    // 연결요청에 대한 수락 -> accept 함수 호출
    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); // 성공 시 파일 디스크립터, 실패 시 -1 반환
    ```

- 리눅스 기반
    - 파일 조작
        - 파일 열기 : open()
        - 파일 닫기 : close()
        - 파일 쓰기 : write() &rarr; 데이터를 출력(전송)하는 함수

    - unsigned : 양수
    - ssize-t 등 앞에 붙는 s는 signed를 의미

- 프로토콜 (Protocol) 
    - 약속의 의미
    - 컴퓨터 간의 데이터 송수신에 필요한 통신규약
    - 소켓 생성시 기본적인 프로토콜 지정필요

- 프로토콜 체계

    ![프로토콜 체계](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp001.png)
    
- 소켓 타입
    - 연결지향형 소켓(SOCK_STREAM) : TCP
        - 중간에 데이터 소멸 x
        - 전송 순서대로 데이터 수신
        - 데이터의 경계가 존재 x
        - 소켓 대 소켓의 연결 : 반드시 1 대 1 구조

    - 비 연결지향형 소켓(SOCK_DGRAM) : UDP
        - 전송순서에 상관없이 빠른 속도의 전송 지향
        - 데이터 손실 및 파손의 우려 o
        - 데이터의 경계가 존재
        - 한번에 전송가능한 데이터 크기가 제한

- 소켓 IP주소 / PORT번호
    - 인터넷 주소(Internet Address)

        ![IPv4 인터넷 주소 체계](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp003.png)

    - 클래스별 네트워크 주소, 호스트 주소 경계

        <!-- ![클래스](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp002.png) -->
        <img src="https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp002.png" width="700" alt="클래스">

    - PORT 번호
        - 소켓을 구분하는 용도로 사용
        - 하나의 프로그램 내에 둘 이상의 소켓이 존재할 수 있음 &rarr; 둘 이상의 포트가 하나의 프록그램에 의해 할당 가능
        - 16비트로 표현 (0 ~ 65535)

- 바이트 순서와 네트워크 바이트 순서
    - CPU가 데이터를 메모리에 저장하는 방식
        - **빅 엔디안(Big Endian) : 상위 바이트의 값을 작은 번지수에 저장**
        - 리틀 엔디안(Little Endian) : 상위 바이트의 값을 큰 번지수에 저장

            ![CPU 데이터 저장방식](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp004.png)

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