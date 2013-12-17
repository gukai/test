#include<stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERV_PORT 9000
#define MAX_LEN 128
#define SERV_ADDR "127.0.0.1"

int main(int argc, char **argv){
    int connfd = 0;
    struct sockaddr_in serveradd;
    char *comu_msg;  
    int write_len = 0;
    char buf[MAX_LEN];

    if (argc != 2){
        printf("argc must be two!\n");
        exit(1);
    }
    comu_msg = argv[1];
    bzero(&buf,MAX_LEN);
    

    bzero(&serveradd, sizeof(struct sockaddr_in));
    serveradd.sin_family = AF_INET;
    serveradd.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, SERV_ADDR, &serveradd.sin_addr);
    
    connfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(connfd, (struct sockaddr *)&serveradd, sizeof(struct sockaddr_in));

    printf("write:%s to server. \n", comu_msg);
    write_len = write(connfd, comu_msg, strlen(comu_msg));
    read(connfd, buf, write_len);
    printf("Recive from the Server\n");   

    write(STDOUT_FILENO, buf, write_len);
    printf("\n");
    close(connfd);
    return 0;
    
}
