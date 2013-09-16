#define _GNU_SOURCE
#include<stdio.h>
#include <string.h>
/*
YNOPSIS
       #include <string.h>

       char *strstr(const char *haystack, const char *needle);

       #define _GNU_SOURCE

       #include <string.h>

       char *strcasestr(const char *haystack, const char *needle);

DESCRIPTION
       The strstr() function finds the first occurrence of the substring needle in the string haystack.  The terminating '\0' characters are not compared.

       The strcasestr() function is like strstr(), but ignores the case of both arguments.

RETURN VALUE
       These functions return a pointer to the beginning of the substring, or NULL if the substring is not found.
*/

/*
       strcasestr与strstr()函数功能类似，但忽略大小写
       编译时出现  warning: assignment makes pointer from integer without a cast

       未经声明的函数默认返回int型。
 
       因此要在#include所有头文件之前加    #define _GNU_SOURCE  ，以此解决此问

*/

char *mystrstr(const char *haystack, const char *needle){
	char *ret = NULL;
	char *needle_temp = needle;

	while(*haystack++ != '\0'){
		ret = haystack;
		for (needle_temp = needle; *haystack++ == *needle_temp++; ){
			if (needle_temp == '\0') return ret;
		}
	}
	
	return NULL;
}



int main(int argc, char **argv){
	char *full = "hello world";
	char *part = "world", *part_p = NULL;
	char *part1 = "WorlD", *part1_p = NULL;
		

	
	if(NULL != (part_p = strstr(full, part)))
		printf("%s\n", part_p);

	if(NULL != (part_p = mystrstr(full, part)))
		printf("%s\n", part_p);

	if(NULL != (part1_p = strcasestr(full, part1)))
		printf("%s\n", part1_p);

	return 0;
	
		
}





