#include<stdio.h>
/*
SYNOPSIS
       #include <string.h>

       char *strchr(const char *s, int c);

       char *strrchr(const char *s, int c);

       #define _GNU_SOURCE
       #include <string.h>

       char *strchrnul(const char *s, int c);

DESCRIPTION
       The strchr() function returns a pointer to the first occurrence of the character c in the string s.

       The strrchr() function returns a pointer to the last occurrence of the character c in the string s.

       The  strchrnul()  function  is like strchr() except that if c is not found in s, then it returns a pointer to
       the null byte at the end of s, rather than NULL.

       Here "character" means "byte"; these functions do not work with wide or multi-byte characters.

RETURN VALUE
       The strchr() and strrchr() functions return a pointer to the matched character or NULL if  the  character  is
       not found.

       The strchrnul() function returns a pointer to the matched character, or a pointer to the null byte at the end
       of s (i.e., s+strlen(s)) if the character is not found.
*/

char *mystrchr(const char *s, int c){
	char *ret = NULL;

	for(;*s!= '\0' && *s != c; s++);
	if(*s == c) ret = s;
	
	return ret;
}

char *mystrrchr(const char *s, int c){
	char *ret = NULL;

	for(;*s != '\0';s++){
		if(*s == c) ret =s;
	}
	
	return ret;
}

int main(int argc, char **argv){
	char *hello = "gogogo";
	int c = 'g';
	printf("%s\n", mystrchr(hello,c));
	printf("%s\n", mystrrchr(hello,c));

	return 0;
}
