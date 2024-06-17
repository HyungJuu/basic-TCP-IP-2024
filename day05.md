## 5일차(24.06.17) ~ p.
- 입출력 함수
    - send 함수 &rarr; 윈도우 기반에서의 함수와 동일
    - recv 함수 &rarr; 윈도우 기반에서의 함수와 동일

        ![옵션&의미](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp014.png)

        - MSG_OOB
            - 긴급으로 전송해야 할 메시지가 있어 전송방법 및 경로를 달리하고자 할 때 사용
            - 데이터를 수신하는 대상에게 데이터의 처리를 독촉
            - TCP 전송특성(전송순서가 그대로 유지된다) 유지  
          
            &rarr; MSG_OOB 메시지라고 더 빨리 전송되지 않는다(긴급상황의 발생을 알릴 뿐, 우리가 생각하는 긴급과 다름)  
            &rarr; 긴급으로 보낸 메시지의 양에 상관없이 1바이트만 반환된다


    - wirtev 함수 : 여러 버퍼에 나뉘어 저장되어 있는 데이터를 한번에 전송할 수 있다

        ```c
        #include <sys/uin.h>

        ssize_t writev(int filedes, const struct iovec * iov, int iovcnt);
        // 성공 시 전송된 바이트 수, 실패 시 -1 반환

        struct iovec {
            void * iov_base;    // 버퍼의 주소 정보
            size_t iov_len; // 버퍼의 크기 정보
        }
        ```

        ![writev](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp015.png)

        - 장점
            - (단순하게) 함수의 호출횟수를 줄일 수 있다
            - 잘게 나뉜 데이터들을 출력버퍼에 한번에 밀어넣기 때문에 하나의 패킷으로 구성되어 전송될 확률이 높아진다 &rarr; 전송속도의 향상


    - readv 함수 : 데이터를 여러 버퍼에 나눠서 수신할 수 있다

        ```c
        #include <sys/uio.h>

        ssize_t readv(int filedes, const struct iovec * iov, int iovcnt);
        // 성공 시 수신된 바이트 수, 실패 시 -1 반환
        ```

        ![readv](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp016.png)

- 표준 입출력 함수
    - 장점  
    &rarr; 이식성이 좋다  
    &rarr; 버퍼링을 통한 성능의 향상에 도움이 된다

        ![표준입출력함수](https://raw.githubusercontent.com/HyungJuu/basic-TCP-IP-2024/main/images/tcp017.png)
