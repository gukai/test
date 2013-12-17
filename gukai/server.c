#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>


#define SERV_PORT 9000
#define MAX_LEN 128


int main(int argc, char **argv){
    struct sockaddr_in serveradd, acceptadd;
    socklen_t serveradd_len = sizeof(serveradd), clientadd_len;
    int listen_fd = 0, accept_fd = 0;
    int i = 0, n = 0;
    char buf[MAX_LEN];
    char clientaddr_char[INET_ADDRSTRLEN];
 
    bzero(&buf,MAX_LEN);

    bzero(&serveradd, sizeof(serveradd));
    serveradd.sin_port = htons(SERV_PORT);
    serveradd.sin_family = AF_INET;
    serveradd.sin_addr.s_addr = htonl(INADDR_ANY);

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bind(listen_fd, (struct sockaddr *)&serveradd, serveradd_len);
    listen(listen_fd, 20);
    while(1){
        accept_fd = accept(listen_fd, (struct sockaddr *)&acceptadd, &clientadd_len);
        n = read(accept_fd, buf, MAX_LEN);
        printf("Recived from %s at %d\n", inet_ntop(AF_INET,&acceptadd.sin_addr,clientaddr_char,sizeof(clientaddr_char)), ntohs(acceptadd.sin_port));       
 
        for(i = 0; i < n; i++){
	    buf[i] = toupper(buf[i]);
	}
	write(accept_fd, buf, n);
	close(accept_fd);
    }

    return 0;
}
