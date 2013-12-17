#include<stdio.h>
#include<sys/socket.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERV_PORT 9000
#define SERV_ADDR "127.0.0.1"

int main(int argc, char **argv){
    int connfd = 0;
    struct sockaddr_in serveradd;

    bzero(&serveradd, sizeof(struct sockaddr_in));
    serveradd.sin_family = AF_INET;
    serveradd.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, SERV_ADDR, &serveradd.sin_addr);
    
    connfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(connfd, (struct sockaddr *)&serveradd, sizeof(struct sockaddr_in));
    write(connfd, "hello world", 20);
    
    return 0;
    
}
