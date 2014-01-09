#include<stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERV_PORT 1202
#define MAX_LEN 128

int main(int argc, char **argv){
    int connfd = 0;
    struct sockaddr_in serveradd;
    char *comu_msg;  
    int write_len = 0;
    char buf[MAX_LEN];
	int ret = -1;

    if (argc != 3){
        printf("./client <Server IP> <Message>\n");
        exit(1);
    }
    comu_msg = argv[2];
    bzero(&buf,MAX_LEN);
    

    bzero(&serveradd, sizeof(struct sockaddr_in));
    serveradd.sin_family = AF_INET;
    serveradd.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &serveradd.sin_addr);
    
    connfd = socket(AF_INET, SOCK_STREAM, 0);
    ret = connect(connfd, (struct sockaddr *)&serveradd, sizeof(struct sockaddr_in));
    if(ret != 0 ){
		printf("connection error, exit!\n");
		exit(1);
	}

    printf("write:%s to server. \n", comu_msg);
    write_len = write(connfd, comu_msg, strlen(comu_msg));
    read(connfd, buf, write_len);
    printf("Recive from the Server\n");   

    write(STDOUT_FILENO, buf, write_len);
    printf("\n");
    close(connfd);
    return 0;
    
}
