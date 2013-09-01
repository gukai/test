#include<stdio.h>
#include<string.h>
/*
SYNOPSIS
       #include <string.h>
       void *memcpy(void *dest, const void *src, size_t n);
DESCRIPTION
       The  memcpy()  function  copies n bytes from memory area src to memory area dest.  The memory areas should not
       overlap.  Use memmove(3) if the memory areas do overlap.
RETURN VALUE
       The memcpy() function returns a pointer to dest.
*/
void *mymemcpy(void *dest, const void *src, size_t n);
void *mymemcpy2(void *dest, const void *src, size_t n);

/*Test*/
int
main(int argc, char **argv){
	char abc[10] = "abcde";
	char *abc_next = abc + 2;
	char right_abc[10];
	
	printf("right abc is %s\n", (char *)mymemcpy(right_abc, abc, 5));

	
	printf("abc value is %s at the start point.\n", abc); 
	memcpy(abc_next, abc, 5);
	printf("abc_next  value is %s after copied.\n", abc_next); 
	printf("abc value is %s after copied.\n", abc); 
	
	printf("**********************************\n");
	memset(abc, 0, 10);
	memcpy(abc, "abcde", 5);	
	printf("abc value is %s at the start point.\n", abc); 
	mymemcpy(abc_next, abc, 5);
	printf("abc_next  value is %s after copied.\n", abc_next); 
	printf("abc value is %s after copied.\n", abc); 
	printf("**********************************\n");
	memset(abc, 0, 10);
	memcpy(abc, "abcde", 5);	
	printf("abc value is %s at the start point.\n", abc); 
	mymemcpy2(abc_next, abc, 5);
	printf("abc_next  value is %s after copied.\n", abc_next); 
	printf("abc value is %s after copied.\n", abc); 
	

	return 0;
}

void *mymemcpy(void *dest, const void *src, size_t n){
	for(;n > 0; --n){
		*((char *)dest + n - 1) = *((char *)src + n - 1);
	}
	return dest;
}

void *mymemcpy2(void *dest, const void *src, size_t n){
	int i = 0;
	char *temp = dest;
	while(i < n){
		*(char *)temp++ = *(char *)src++;
		i++;
	}
	return dest;

}

