#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#define TRY_MSG "try again.\n"
#define TIMEOUT_MSG "timeout\n"

int term_block_read(void *buf, size_t n){
    int m = read(STDIN_FILENO, buf, n);
    if ( m < 0 ) {
        perror("read STDIN_FILENO");
        exit(1);
    }
    return m;
}

int term_noblock_read(void *buf, size_t n){
    int alrm = 0;
    int fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
    int m = -1;

    while(alrm < 10){
        m = read(fd, buf, n);
        if ( m >= 0 ) break;
        if ( errno != EAGAIN ) {
            perror("read STDIN_FILENO");
            exit(1);
        }
        alrm++;
	sleep(1);
        write(STDOUT_FILENO, TRY_MSG, strlen(TRY_MSG));
    }
    if ( alrm >=10 ){
        write(STDOUT_FILENO, TIMEOUT_MSG, strlen(TIMEOUT_MSG));
        exit(1);
    }

    return m;
}

int main(void){
	char buf[10];
	int n = -1;
	
	// block read
	//n = term_block_read(buf, 10);
	// noblock read	
	n = term_noblock_read(buf, 10);	
	write(STDOUT_FILENO, buf, n);
	return 0;
}
