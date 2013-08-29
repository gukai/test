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
void *(memset)(void *s, int c, size_t n){
	const unsigned char uc = c;
	unsigned char *su;
	
	for(su = s; 0<n; ++su, --n)
		*su = uc;
	
	return (s)
}


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
