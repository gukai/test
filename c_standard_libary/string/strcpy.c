#include<stdio.h>
/*
 SYNOPSIS
        #include <string.h>
		char *strcpy(char *dest, const char *src);
		char *strncpy(char *dest, const char *src, size_t n);

DESCRIPTION
		The  strcpy()  function copies the string pointed to by src, including the terminating null byte ('\0'), to the buffe
		pointed to by dest.  The strings may not overlap, and the destination string dest must be large enough to receive  The
		copy.  Beware of buffer overruns!  (See BUGS.)

		The  strncpy()  function is similar, except that at most n bytes of src are copied.  Warning: If there is no null byte
		among the first n bytes of src, the string placed in dest will not be null-terminated.

		If the length of src is less than n, strncpy() writes additional null bytes to dest to ensure that a total of n  bytes
		are written.
 */

/* 内存重叠和拷贝效率的问题可以参考mymemcpy4 
 * 指针有效性检查啥的,面试题干的事情,调用者保证即可
 * */
char *mystrcpy(char *dest, const char *src){
	char *temp = dest;
	while('\0' != (*temp++ = *src++));
	return dest;

}

int main(int argc, char **argv){
	char *sayhi = "hello world!";
	char temp[20];
	printf("%s\n", mystrcpy(temp, sayhi));
	return 0;
}

