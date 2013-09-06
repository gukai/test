#include<stdio.h>
#include<string.h>
/*
char *strncpy(char *dest, const char *src, size_t n);

 The  strncpy()  function is similar, except that at most n bytes of src
 are copied.  Warning: If there is no null byte among the first n  bytes
of src, the string placed in dest will not be null-terminated.

If  the  length of src is less than n, strncpy() writes additional null
bytes to dest to ensure that a total of n bytes are written.
*/

char *mystrncpy(char *dest, const char *src, size_t n){
	char *temp = dest;
	for(;n > 0 && (*temp++ = *src++) != '\0'; n--)
		;
	if(n > 0){
		for(;n>0;n--){
			*temp++ = '\0';
		}
	}

	return dest;
}

int main(int argc, char **argv){
	char *a = "hello world!";
	char b[20];
	
	mystrncpy(b,a,20);
	printf(" 20 %s\n", b);
	memset(b,0,20);
	mystrncpy(b,a,3);
	printf("3 %s\n",b);

	return 0;


}
