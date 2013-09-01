#include <stdio.h>
#include<string.h>
/*
SYNOPSIS
       #include <string.h>
       size_t strlen(const char *s);

DESCRIPTION
       The strlen() function calculates the length of the string s, not including the terminating '\0' character.

RETURN VALUE
       The strlen() function returns the number of characters in s.
*/

size_t mystrlen(const char *s){
	int ret = 0;
	while(*s++ != '\0') ret++;
	return ret;
}

/*for test*/
int main(int argc, char **argv){
	char *sayhi = "hello world!";
//	printf("say hi len value from strlen is %d\n", strlen(sayhi));
	printf("say hi len value from strlen is %lu\n", strlen(sayhi));
	printf("say hi len value from mystrlen is %lu\n", mystrlen(sayhi));
	
	return 0;
}





/*
size_t格式在/usr/include/linux/types.h定义，32位系统下为 unsigned int，64位系统下为 long unsigned int
	typedef _kernel_size_t size_t
这个为什么不定义更长或更短的类型，比如讲size_t 32位下定义为unsigned long 或 int?
*/
