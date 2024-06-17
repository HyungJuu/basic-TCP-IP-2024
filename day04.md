## 4일차(24.06.14) ~ p.285
- 멀티프로세스 기반의 서버구현
    - 좀비 프로세스
        - 좀비 프로세스 소멸 : wait(), waitpid()
            - wait 함수
            
                ```c
                #include <sys/wait.h>

                pid_t wait(int * statloc);
                // 성공 시 종료된 자식 프로세스의 ID, 실패 시 -1 반환
                ```
            
                - 매크로함수
                    - WIFEXITED : 자식 프로세스가 정상 종료한 경우 참(true) 반환
                    - WEXITSTATUS : 자식 프로세스의 전달값을 반환

                    ```c
                    if(WIFEXITED(status)) // 정상 종료되었는가
                    {
                        puts("Normal termination!");
                        printf("Child pass num : %d", WEXITSTATUS(status)); // 그렇다면 반환값은?
                    }
                    ```

            - waitpid 함수

                ```c
                #include <sys/wait.h>

                pid_t waitpid(pid_t pid, int * statloc, int options);
                // 성공 시 종료된 자식 프로세스의 ID(또는 O), 실패 시 -1 반환
                ```

    - 시그널 핸들링



- IO 멀티플렉싱
    - IO 멀티플렉싱 기반 서버
        - 멀티프로세스 서버
            - 단점
                - 빈번한 프로세스 생성 &rarr; 성능 저하
                - 흐름을 고려하여 구현해야 함(쉽지않음)
                - 프로세스간 통신이 필요한 경우, 서버의 구현이 더 복잡해짐
            - 대안
                - 하나의 프로세스 &rarr; 다수의 클라이언트 에게 서비스 할 수 있도록
                - 하나의 프로세스가 여러개의 소켓을 핸들링할 수 있는 방법 &rarr; IO 멀티플렉싱

    - select 함수의 이해와 서버구현
        - select 함수 기능