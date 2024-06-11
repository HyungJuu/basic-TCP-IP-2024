## 1일차(24.06.11)
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

        ![클래스](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp002.png)
