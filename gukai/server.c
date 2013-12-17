#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERV_PORT 9000
#define MAX_LEN 128


int main(int argc, char **argv){
    struct sockaddr_in serveradd, acceptadd;
    socklen_t serveradd_len = sizeof(serveradd), clientadd_len;
    int listen_fd = 0, accept_fd = 0;
    int i = 0, n = 0;
    char buf[MAX_LEN];
 
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
        
        for(i = 0; i < n; i++){
	    printf("%c", buf[i]);
	}
        printf("\n");
	close(accept_fd);
    }

    return 0;
}
