#include<stdio.h>
#include<stdlib.h>
#include<libvirt/libvirt.h>

int main(int argc, char **argv){
	virConnectPtr conn;
	
	conn = virConnectOpenAuth("qemu+ssh://root@10.12.28.63/system", virConnectAuthPtrDefault, 0);
	if(conn == NULL){
		fprintf(stderr, "Failed to open connect to quem");
		return 1;
	}

	printf("virConnectGetType's return value is %s\n", virConnectGetType(conn));
	virConnectClose(conn);
	return 0;
}
