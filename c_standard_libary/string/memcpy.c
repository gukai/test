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
void *mymemcpy3(void *dest, const void *src, size_t n);
void *mymemcpy4(void *dest, const void *src, size_t n);

/*Test*/
int
main(int argc, char **argv){
	char abc[15] = "abcde";
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
	printf("**********************************\n");
	memset(abc, 0, 10);
	memcpy(abc, "abcdefghi", 9);	
	printf("abc value is %s at the start point.\n", abc);
	char hello[10];	
	mymemcpy3(hello, abc, 9);
	printf("hello is %s\n", hello); 
	mymemcpy3(abc_next, abc, 9);
	printf("abc_next  value is %s after copied.\n", abc_next); 
	printf("abc value is %s after copied.\n", abc); 
	printf("**********************************\n");
	memset(abc, 0, 10);
	memcpy(abc, "abcdefghi", 9);	
	printf("abc value is %s at the start point.\n", abc);
	char world[10];	
	mymemcpy4(world, abc, 9);
	printf("world is %s\n", world); 
	mymemcpy4(abc_next, abc, 9);
	printf("abc_next  value is %s after copied.\n", abc_next); 
	printf("abc value is %s after copied.\n", abc); 


	return 0;
}
/*解决内存重叠有两种方法
  1.反向拷贝	2.利用buf
 但是这些方法都只是解决dest最后的正确，无法避免src最终还是要被污染.
*/
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

/*要解决拷贝速度问题.*/
void *mymemcpy3(void *dest, const void *src, size_t n){
	void *temp = (void *)dest;
	int cpu_size = sizeof(char *);
	int word = n/cpu_size;
	int word_left = n%cpu_size;

	while(word > 0){
		if(8 == cpu_size){
			*(long *)temp = *(long *)src;
		}else if(4 == cpu_size){
			*(int *)temp = *(int *)src;
		}else{
			return NULL;
		}

		temp += cpu_size;
		src += cpu_size;
		word --;
	}

	while(word_left > 0){
		*(char *)temp++ = *(char *)src++;
		word_left --;
	}

	return (void *)dest;
}

/*利用反向拷贝解决内存重叠，利用字长拷贝解决拷贝速度.*/
void *mymemcpy4(void *dest, const void *src, size_t n){
	char *dest_left_p = (char *)dest;
	int cpu_size = sizeof(char *);
	int word = n/cpu_size;
	int word_left = n%cpu_size;
	char *dest_word_p = dest_left_p + word_left;
	char *src_word_p = (char *)src + word_left;
		

	while(word > 0){
		if(8 == cpu_size){
			*(((long *)dest_word_p) + word - 1) = *(((long *)src_word_p) + word - 1);
		}else if(4 == cpu_size){
			*(((int *)dest_word_p) + word - 1) = *(((int *)src_word_p) + word - 1);
		}else{
			return NULL;
		}
		word--;
	}
	
	while(word_left > 0){
		*(dest_left_p + word_left -1) = *((char *)src + word_left -1);
		word_left--;
	}

	return (void *)dest;
}
