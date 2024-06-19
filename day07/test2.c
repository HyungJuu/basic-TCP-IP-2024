
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 1024
#define SMALL_BUF 100

void* request_handler(void* arg);
void send_html(FILE* fp);
void send_image(FILE* fp, char* file_name);
char* content_type(char* file);
void send_error(FILE* fp);
void error_handling(char *message);

const char webpage[] = "HTTP/1.1 200 OK\r\n"
                       "Server: Linux Web Server\r\n"
                       "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                       "<!DOCTYPE html>\r\n"
                       "<html><head><title>My Web Page</title>\r\n"
                       "<style>body {background-color: #FFFF00; }</style></head>\r\n"
                       "<body><center><h1>Hello world!</h1><br>\r\n"
                       "<img src=\"web.jpeg\"></center></body></html>\r\n";

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    int clnt_adr_size;
    pthread_t t_id;
    if(argc != 2) {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));
    if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    if(listen(serv_sock, 20) == -1)
        error_handling("listen() error");

    while(1)
    {
        clnt_adr_size = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_adr, &clnt_adr_size);
        printf("Connection Request : %s:%d \n", inet_ntoa(clnt_adr.sin_addr), ntohs(clnt_adr.sin_port));
        pthread_create(&t_id, NULL, request_handler, &clnt_sock);
        pthread_detach(t_id);
    }
    close(serv_sock);
    return 0;
}

void* request_handler(void *arg)
{
    int clnt_sock = *((int*)arg);
    char req_line[SMALL_BUF];
    FILE* clnt_read;
    FILE* clnt_write;

    char method[10];
    char ct[15];
    char file_name[30];

    clnt_read = fdopen(clnt_sock, "r");
    clnt_write = fdopen(dup(clnt_sock), "w");
    fgets(req_line, SMALL_BUF, clnt_read);
    if(strstr(req_line, "HTTP/") == NULL)
    {
        send_error(clnt_write);
        fclose(clnt_read);
        fclose(clnt_write);
        return NULL;
    }

    strcpy(method, strtok(req_line, " /"));
    strcpy(file_name, strtok(NULL, " /"));
    strcpy(ct, content_type(file_name));
    if(strcmp(method, "GET") != 0)
    {
        send_error(clnt_write);
        fclose(clnt_read);
        fclose(clnt_write);
        return NULL;
    }

    fclose(clnt_read);
    if (strcmp(file_name, "") == 0 || strcmp(file_name, "index.html") == 0) {
        send_html(clnt_write);
    } else if (strcmp(file_name, "web.jpeg") == 0) {
        send_image(clnt_write, file_name);
    } else {
        send_error(clnt_write);
    }
    return NULL;
}

void send_html(FILE* fp)
{
    fputs(webpage, fp);
    fflush(fp);
    fclose(fp);
}

void send_image(FILE* fp, char* file_name)
{
    char protocol[] = "HTTP/1.1 200 OK\r\n";
    char server[] = "Server: Linux Web Server\r\n";
    char cnt_len[SMALL_BUF];
    char cnt_type[] = "Content-Type: image/jpeg\r\n\r\n";
    int file_fd;
    struct stat st;

    file_fd = open(file_name, O_RDONLY);
    if(file_fd == -1) {
        send_error(fp);
        return;
    }

    fstat(file_fd, &st);
    sprintf(cnt_len, "Content-Length: %ld\r\n", st.st_size);

    fputs(protocol, fp);
    fputs(server, fp);
    fputs(cnt_len, fp);
    fputs(cnt_type, fp);
    fflush(fp);

    sendfile(fileno(fp), file_fd, NULL, st.st_size);
    close(file_fd);
    fclose(fp);
}

char* content_type(char* file)
{
    char extension[SMALL_BUF];
    char file_name[SMALL_BUF];
    strcpy(file_name, file);
    strtok(file_name, ".");
    strcpy(extension, strtok(NULL, "."));

    if(!strcmp(extension, "html") || !strcmp(extension, "htm"))
        return "text/html";
    else if(!strcmp(extension, "jpeg") || !strcmp(extension, "jpg"))
        return "image/jpeg";
    else
        return "text/plain";
}

void send_error(FILE* fp)
{
    char protocol[] = "HTTP/1.0 400 Bad Request\r\n";
    char server[] = "Server: Linux Web Server\r\n";
    char cnt_type[] = "Content-Type: text/html\r\n\r\n";
    char content[] = "<html><head><title>NETWORK</title></head>"
                     "<body><font size=+5><br>요청 파일은 찾을 수 없습니다!</font></body></html>";

    fputs(protocol, fp);
    fputs(server, fp);
    fputs(cnt_type, fp);
    fputs(content, fp);
    fflush(fp);
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
