#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include<unistd.h>
#include <string.h>

#define XMLPATH "/home/workspace/mylibvirt/xp-1.xml"

char *readxml(char *path){
	char *xml = NULL;
	int readfd = 0, writefd=0;	
	int readlen = 0;	

	xml = (char *)malloc(10240);
	readfd = open(path, O_RDONLY);
	if((readlen=read(readfd, xml, 10240)) >= 10000){
		printf("it is not over man!");
		exit(1);
	}

	printf("readlen= %d, sizeofxml= %d, strlenxml= %d", readlen, sizeof(xml), strlen(xml));
//	#writefd=("/home/workspace/mylibvirt/answter.log", readlen, sizeof(xml), strlen(xml));
//	#write()
	return xml;
}

int main(int argc, char **argv){
	printf("\n%s\n", readxml(XMLPATH));
	/*you'd better to release the readxml mau*/
	return 0;
}
