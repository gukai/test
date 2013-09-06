#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
SYNOPSIS
       #include <string.h>
       void *memset(void *s, int c, size_t n);

DESCRIPTION
       The memset() function fills the first n bytes of the memory area pointed to by s with the constant byte c.

RETURN VALUE
       The memset() function returns a pointer to the memory area s.
*/

/*
 * 第二个参数为什么是int、难道是为了对于特殊实现的字符和char类型提供
 * 统一的接口，现在无法知晓，但是第二个参数会取其ascll码来赋值，如果
 * 把取码时写成const unsinged uc = (unsigned char *)c 则会出现大小断问题.
 */
void *(standard_memset)(void *s, int c, size_t n){
	const unsigned char uc = c;
	unsigned char *su;
	
	for(su = s; 0<n; ++su, --n)
		*su = uc;
	
	return (s)
}


/*
 * 从实现来看，memset永远是以字节赋值的，
 * 所以对于int *a赋值，读取时int *a却以4字节读取，需要注意.
 * 
 */


void *mymemset(void *s, int c, size_t n){
	int i = 0;
	char *temp = s;
	
	for(i = 0; i < n; i++) *temp++ = c;
	
	return s;
}

/*test*/
int main(int argc, char **argv){
	char *test = malloc(20);
	memset(test, 0, 20);
	char guess[5] = {'g', 'u', 'e', 's', 's'};	
	
	strcpy(test, "hello world!");
	memcpy(test, guess, 5);
	printf("%s\n", test);

	strcpy(test, "hello world!");
	memcpy(test, guess, 5);
	printf("%s\n", test);

	strcpy(test, "hello world!");
	memset(test, 0, 20);
	memcpy(test, guess, 5);
	printf("%s\n", test);

	return 0;		

}
