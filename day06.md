## 6일차(24.06.18) ~ p.427
- epoll
    - select 함수
        - 운영체제의 커널에 의해서가 아닌, 순수하게 함수에 의해서 완성되는 기능  
        &rarr; 운영체제 레벨에서 멀티플렉싱 기능을 지원해야 함 = 리눅스의 `epoll`

    - select의 단점과 대응되는 epoll 장점
        | `select` 단점 | `epoll` 장점 |
        | :---: | :---: |
        | 함수호출 이후, 모든 파일 디스크립터를 대상으로 하는 반복문이 항상 등장 | 상태변화의 확인을 위한, 전체 파일 디스크립터를 대상으로 하는 반복문 필요x |
        | 함수호출시 관찰대상에 대한 정보를 인자로 매번 전달해야함 | epoll_wait 함수호출 시, 관찰대상에 대한 정보를 매번 전달할 필요x |  

        \* epoll의 장점은 다른 운영체제에서 제공하는 모든 멀티플렉싱 서버의 장점과 동일 \*

    - select 방식이 사용되기 위한 조건
        - 서버의 접속자 수가 많지 않다
        - 다양한 운영체제에서 운영이 가능해야 한다
    
    - epoll 구현에 필요한 함수와 구조체
        | 함수 | |
        |:--- | :--- |
        | `epoll_create` | epoll 파일 디스크립터 저장소 생성 |
        | `epoll_ctl` | 저장소에 파일 디스크립터 등록 및 삭제 |
        | `epoll_wait` | select 함수와 마찬가지로 파일 디스크립터의 변화를 대기 |

    - epoll_create
        - 운영체제가 관리하는, epoll 인스턴스라 불리는 파일 디스크립터의 저장소를 생성

            ```c
            #include <sys/epoll.h>

            int epoll_create(int size);
            // 성공시 epoll 파일 디스크립터, 실패시 -1 반환
            // size : epoll 인스턴스의 크기정보
            ```
    - epoll_ctl
        - epoll_create로 생성된 epoll 인스턴스에 관찰대상을 저장 및 삭제하는 함수

            ```c
            #include <sys/epoll.h>

            int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
            // 성공시 0, 실패시 -1 반환
            /*
                epfd : 관찰대상을 등록할 epoll 인스턴스의 파일 디스크립터
                op : 관찰대상의 추가, 삭제 또는 변경여부 지정
                fd : 등록할 관찰대상의 파일 디스크립터
                event : 관찰대상의 관찰 이벤트 유형
            */
            ```

            - 두번째 전달인자
                | 인자 |  |
                | :---: | :--- |
                | `EPOLL_CTL_ADD` | 파일 디스크립터를 epoll 인스턴스에 등록 |
                | `EPOLL_CTL_DEL` | 파일 디스크립터를 epoll 인스턴스에서 삭제 |
                | `EPOLL_CTL_MOD` | 등록된 파일 디스크립터의 이벤트 발생상황을 변경 |

            - epoll_event 구조체
                - 이벤트의 유형등록에 사용
                - 이벤트 발생시 발생된 이벤트의 정보로 사용
                    ```c
                    struct epoll_event event;
                    . . . . .
                    event.events = EPOLLIN;
                    event.data.fd = sockfd;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
                    . . . . .
                    ```
                    - events 멤버에 저장가능한 상수와 이벤트 유형 &rarr; 비트 OR 언산을 통해 둘 이상 등록 가능
                        | 상수 | 이벤트 유형 |
                        | --- | --- |
                        | `EPOLLIN` | 수신할 데이터가 존재하는 상황 |
                        | `EPOLLOUT` | 출력버퍼가 비워져서 당장 데이터를 전송할 수 있는 상황 |
                        | `EPOLLPRI` | OOB 데이터가 수신된 상황 |
                        | `EPOLLRDHUP` | 연결이 종료되거나 Half-close가 진행된 상황<br>엣지 트리거 방식에서 유용하게 사용가능 |
                        | `EPOLLERR` | 에러가 발생한 상황 |
                        | `EPOLLET` | 이벤트의 감지를 엣지 트리거 방식으로 동작 |
                        | `EPOLLONESHOT` | 이벤트가 한번 감지되면 해당 파일 디스크립터를 더이상 이벤트를 발생시키지 않음 <br> &rarr; epoll_ctl 함수의 두번째 인자로 EPOLL_CTL_MOD을 전달해서 이벤트 재설정 필요 |

    - epoll_wait
        - epoll 인스턴스에 등록된 파일 디스크립터를 대상으로 이벤트의 발생 유무를 확인하는 함수
            ```c
            #include <sys/epoll.h>

            int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
            // 성공시 이벤트가 발생한 파일 디스크립터 수, 실패시 -1 반환
            /*
                epfd : 이벤트 발생의 관찰영역인 epoll 인스턴스의 파일 디스크립터
                event : 이벤트가 발생한 파일 디스크립터가 채워질 버퍼의 주소값
                maxevents : 두번째 인자로 전달된 주소값의 버퍼에 등록 가능한 최대 이벤트 수
                timeout : 1/1000초 단위의 대기시간, -1 전달시, 이벤트가 발생할 때까지 무한 대기
            */
            ```
    
    - 레벨트리거(Level Trigger)와 엣지트리거(Edge Trigger)

- 멀티스레드 서버   

... 작성중