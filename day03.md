## 3일차(24.06.13) ~ p.229
- UDP 기반 서버 / 클라이언트
    - UDP 데이터 송수신 특성과 connect 함수호출
        - UDP
            - 데이터의 경계가 존재하는 프로토콜
            - 경계가 존재하기 때문에 하나의 패킷이 하나의 데이터로 간주됨 &rarr; 데이터그램 이라고 표현
            - 입력함수의 호출횟수와 출력함수의 호출횟수가 완벽하게 일치해야 송수신 데이터를 전부 수신할 수 있다
        
        - unconnected 소켓 : 목적지 정보가 등록되어 있지 않은 소켓(기본)
        - connected 소켓 : 목적지 정보가 등록되어 있는 소켓
        
        - connected 소켓 생성방법
            - UDP 소켓을 대상으로 connected 함수 호출
            
                ```c
                sock = socked(PF_INET, SOCK_DGRAM, 0); // SOCK_DGRAM : UDP 소켓 생성
                memset(&adr, 0, sizeof(adr));
                adr.sin_family = AF_INET;
                adr.sin_addr.s_addr = . . . .
                adr.sin_port = . . . .
                connect(sock, (struct sockaddr*)&adr, sizeof(adr));
                // connect 함수를 호출했다고 해서 목적지의 UDP 소켓과 연결과정을 거친것은 아님
                // 다만, UDP 소켓에 목적지의 IP와 PORT정보가 등록
                ```

            - sendto함수 호출 시 &rarr; 데이터 전송과정만 거침
            - 송수신 대상이 정해졌기 때문에 sendto, recvfrom 함수가 아닌 write, read 함수의 호출로도 데이터 송수신 가능

- 소켓 연결 종료과정
    - close 함수
        - 완전종료를 의미
        - 한쪽에서 close함수를 호출할 경우 `일방적`으로 연결이 종료됨
        - 즉, 데이터의 송수신 모두 불가능한 상황
    
    - **Half-close**
        - 일방적인 연결종료의 문제점을 해결하기 위해 데이터의 송수신에 사용되는 스트림의 일부만 종료하는 방법
            |  | 송신 | 수신 |
            | :--: | :--: | :--: |
            | 1 | 가능 | 불가능 |
            | 2 | 불가능 | 가능 |

    - 소켓과 스트림
        - 소켓을 통해 두 호스트가 연결 &rarr; 상호간 데이터의 송수신 가능 상태 = 스트림이 형성된 상태
        
        - 스트림(물의 흐름)
            - 한방향으로만 데이터의 이동이 가능
            - 양방향 통신을 위해서는 두개의 스트림이 필요!
                - 입력 스트림
                - 출력 스트림

    - Half-close에 사용되는 함수
        - shutdown 함수

            ```c
            #include <sys/socket.h>

            int shutdown(int sock, int howto);
            // 성공시 0, 실패시 -1 반환
            // sock : 종료할 소켓의 파일 디스크립터 전달
            // howto : 종료방법에 대한 정보 전달
            ```

            | 종료방법 | |
            | :-- | :-- |
            | `SHUT_RD` | 입력 스트림 종료 |
            | `SHUT_WR` | 출력 스트림 종료 <br><small> (단, 출력 버퍼에 전송되지 못한 상태의 데이터가 존재할 경우, <br> 해당 데이터는 목적지로 전송됨) </small> |
            | `SHUT_RDWR` | 입출력 스트림 종료 <br><small> (shutdown 함수의 인자를 각각 SHUT_RD, SHUT_WR로 두번 호출한 것과 같음) </small> |


---
* sudo raspi-config -> 6 -> A1
---

- DNS (Domain Name System)
    - 도메인 이름 : 기억하고 표현하기 좋은 형태의 이름을 IP주소에 부여하여, IP주소 대신 사용
    - 도메인 이름의 IP주소 확인하고 싶으면... 콘솔창 입력  
    &rarr; ping 도메인명  
    ex) ping www.naver.com

    ... 작성중
        
