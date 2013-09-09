#include<stdio.h>
/*
YNOPSIS
       #include <string.h>
       char *strcat(char *dest, const char *src);
CRIPTION
       The  strcat() function appends the src string to the dest string, overwriting the null byte ('\0') at the end
       of dest, and then adds a terminating null byte.  The strings may not overlap, and the dest string  must  have
       enough space for the result.

*/

char *strcat(char *dest, const char *src){
	char *temp = dest;

	while(*temp++ != '\0')
		;
	temp--;
	while('\0' != (*temp++ = *src++))
		;
	return dest;
}

int main(int argc, char **argv){
	char a[20] = "hello";
	char *b = "world!";

	printf("%s\n", strcat(a,b));

	return 0;
}


