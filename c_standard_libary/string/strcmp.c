/*
YNOPSIS
       #include <string.h>

       int strcmp(const char *s1, const char *s2);
	   int strncmp(const char *s1, const char *s2, size_t n);

DESCRIPTION
		The  strcmp()  function  compares  the two strings s1 and s2.  
		It returns an integer less than, equal to, or greater
		than zero if s1 is found, respectively, to be less than, to
		 match, or greater than s2.

		The strncmp() function is similar, except it only compares the first (at most) n bytes of
		s1 and s2.

RETURN VALUE
		The strcmp() and strncmp() functions return an integer less than, equal to,
	    or greater than zero if s1 (or the first n bytes thereof) is found, respectively, 
		to be less than, to  match,  or be greater than s2.

*/

#include<stdio.h>

int mystrcmp(const char *s1, const char *s2){
	do{
		if (*s1 > *s2){
			return 1;
		}else if(*s1 < *s2){
			return -1;
		}
		s2++;
	}while(*s1++ != '\0');
	
	if(*s1 == *s2) return 0;
	return -1;
}

int main(int argc, char **argv){
	char *a = "hello";
	char *b = "helloa";
	char *c = "abcdefgh";

	printf("hello and helloa is %d\n", mystrcmp(a,b));
	printf("helloa and hello is %d\n", mystrcmp(b,a));
	printf("hello and abcdefgh is %d\n", mystrcmp(a,c));
	printf("hello and hello is %d\n", mystrcmp(a,a));

	return 0;

}











