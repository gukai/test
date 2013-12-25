#include<error.h>
#include <string.h>
#include <stdio.h>

/*
  不分等级写标准输出,将日志和标准输出重合.
  errnum:程序出错时返回的全局错误码errno.
*/
WriteLogErr(char *log, int errnum){
    char *errstr = strerror(errmum);
    char *errlog = strcat(log, errstr);
    write(STDOUT_FILENO, errlog, strlen(errlog));
}


WriteLog(char *log){
    write(STDOUT_FILENO, log, strlen(log));
}



/*
 严重出错需要程序退出的处理
 errnum:程序出错时返回的全局错误码errno.
*/
ExitError(char *log, int errnum){
   WriteLogErr(int errmum);
   exit(1);
}


/***********************************************************************************************************************************************************/
/*慢系统调用accept、read和write被信号中断时应该重试。connect虽然也会阻塞，但是被信号中断时不能立刻重试。对于accept，如果errno是ECONNABORTED，也应该重试。*/


/*
 参数和返回值全部采用标准，只是增加了信号中断的重试。
 Goto可以用while代替
*/
ssize_t Read(int fd, void *ptr, size_t nbytes){
    ssize_t n = -1;

again:
    if ( (n = read(fd, ptr, nbytes) == -1 ){
        if (errno = EINTR){
            goto again;
        }else{
            ExitError(errno);
        }
    }
    
    return n; 
}



/*
 参数和返回值全部采用标准，只是增加了信号中断的重试。
 Goto可以用while代替
*/
ssize_t Write(int fd, ptr, nbytes){
    ssize_t n = -1;

again:
    if ( (n = write(fd, ptr, nbytes) == -1 ){
        if (errno = EINTR){
            goto again;
        }else{
            ExitError(errno);
        }
    }
    
    return n; 
}

/*
 socket套接字本是阻塞的，但是read在读完缓冲区内无论读取字节是否达到规定字节都会直接返回，在读socket更像是非阻塞的。
 该方法保证能够读取的字节数就是自己请求的字节数，一直循环去读，直到读到足够的个数为止。
*/
ssize_t Readn(int fd, void *ptr, size_t nbytes){
    size_t nleft = nbytes;
    ssize curread = 0;
    char *curptr = ptr;

    while(nleft > 0){
        if((curread = read(fd, curptr, nleft)) == -1){
            if(error == EINTR){
                curread = 0;
            }else{
                WriteLog("Readn Error");
                return -1; 
            }
        }else{
            nleft -= curread;
            curptr ++ curread;
       }
    }

    return nbytes - nleft;
  
}






