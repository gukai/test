/*
#include<string.h>
char *strdup(const char *s);
function:returns a pointer to a new string which is a duplicate of the string s.  Memory for the new string is obtained with malloc(3), and can be freed with free(3).
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char *mystrdup(const char *s){
	char *temp = malloc(strlen(s) + 1);
	char *dest = temp;
	if(s == NULL) return NULL;

	while('\0' != (*temp++ = *s++));
	return dest;
	
}

/*test*/
int main(int argc, char **argv){
	char *hello = "hello world!";
	printf("%s\n", mystrdup(hello));

	return 0;
}
