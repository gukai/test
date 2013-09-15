#include<stdio.h>
#include<stdlib.h>
#include<libvirt/libvirt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include <string.h>



/*gcc connet.c -Wall -o connet -lvirt*/
#define XMLPATH "/home/workspace/mylibvirt/centos6.4-1.xml"
char *readxml(char *path){
        char *xml = NULL;
        int readfd = 0, writefd=0;
        int readlen = 0;

        xml = (char *)malloc(10240);
	memset(xml, 10240, 10240);
        readfd = open(path, O_RDONLY);
        if((readlen=read(readfd, xml, 10240)) >= 10000){
                printf("it is not over man!");
                exit(1);
        }

//        printf("readlen= %d, sizeofxml= %d, strlenxml= %d", readlen, sizeof(xml), strlen(xml));
//      #writefd=("/home/workspace/mylibvirt/answter.log", readlen, sizeof(xml), strlen(xml));
//      #write()
        return xml;
}


int main(int argc, char **argv){
	virConnectPtr conn;
	
	conn = virConnectOpenAuth("qemu+ssh://root@10.12.28.63/system", virConnectAuthPtrDefault, 0);
	if(conn == NULL){
		fprintf(stderr, "Failed to open conection");
		return 1;
	}

	/*Test APIs here*/
	printf("virConnectGetType's return value is %s\n", virConnectGetType(conn));


	/*
	char * virConnectGetSysinfo (virConnectPtr conn,
      		unsigned int flags)
	*/
	printf("virConnectGetSysinfo's return value is %s", virConnectGetSysinfo(conn, 0));

	/*
	int virConnectGetMaxVcpus (virConnectPtr conn,
      		const char * type)
	*/
	printf("qemu's %d\n", virConnectGetMaxVcpus(conn, "qemu"));
	/*Must use in lxc connection*/
	// printf("lxc's %d\n", virConnectGetMaxVcpus(conn, "lxc"));
	
	/*
	char *	virConnectGetHostname		(virConnectPtr conn)
	*/
	char *hostname = NULL;
	printf("virConneccGetHostname's return vaule is %s\n", hostname = virConnectGetHostname(conn));
	free(hostname);

	/*
	char *	virConnectGetCapabilities	(virConnectPtr conn)
	*/
	char *cap = NULL;
	printf("virConnectGetCapabilities's return value is %s\n", cap = virConnectGetCapabilities(conn));
	free(cap);


	/*
	int	virConnectListAllDomains	(virConnectPtr conn,
					 virDomainPtr ** domains,
					 unsigned int flags	
	*/
	virDomainPtr *domains = NULL;
	int flags = VIR_CONNECT_LIST_DOMAINS_RUNNING;
	int ret = 0, i=0;
	
	ret = virConnectListAllDomains(conn, &domains, flags); 
	for (i = 0; i < ret; i++) {
		/*const char *virDomainGetName (virDomainPtr domain)*/
		printf("%s\n", virDomainGetName(domains[i]));
		virDomainFree(domains[i]); 
	} 
	free(domains);


	/*
	int virConnectListAllInterfaces (virConnectPtr conn,
            virInterfacePtr ** ifaces,
            unsigned int flags)
	*/
	virInterfacePtr *ifaces;
	int if_flags = VIR_CONNECT_LIST_INTERFACES_ACTIVE;
	int if_ret = 0, if_i = 0;

	if_ret = virConnectListAllInterfaces(conn, &ifaces, if_flags);
	for(if_i = 0; if_i < if_ret; if_i ++){
		/* const char *	virInterfaceGetName	(virInterfacePtr iface) */
		printf("%s\n", virInterfaceGetName(ifaces[if_i]));
		virInterfaceFree(ifaces[if_i]);
	}
	free(ifaces);

	/*
	int virConnectListAllNetworks (virConnectPtr conn,
            virNetworkPtr ** nets,
            unsigned int flags)
	*/
	virNetworkPtr *nets = NULL;
	int nw_flags = VIR_CONNECT_LIST_NETWORKS_ACTIVE;
	int nw_ret = 0, nw_i = 0;
	
	nw_ret = virConnectListAllNetworks(conn, &nets, nw_flags);
	for(nw_i = 0; nw_i < nw_ret; nw_i ++){
		/*const char *	virNetworkGetName	(virNetworkPtr network)*/
		printf("Network is %s\n", virNetworkGetName(nets[nw_i]));
		virNetworkFree(nets[nw_i]);
	}
	free(nets);


	/*
	char *	virConnectDomainXMLToNative	(virConnectPtr conn,
					 const char * nativeFormat,
					 const char * domainXml,
					 unsigned int flags)
	*/
	char *myxml = readxml(XMLPATH);
	printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&7");
	
	//		printf("%s", myxml);
		printf("\n\n\n%s", virConnectDomainXMLToNative(conn, "qemu-argv", myxml, 0));	

	free(myxml);

	printf("Network APIS!\n");
	printf("***************************************************************************\n");
	/*
	int   virConnectListAllInterfaces
                                  (virConnectPtr conn, virInterfacePtr ** ifaces, 
                                                                                    unsigned int flags)
	*/
	/*
	int i_if = 0;
	virInterfacePtr *ifacess = NULL;
	int list_all_if = virConnectListAllInterfaces(conn, &ifacess, VIR_CONNECT_LIST_INTERFACES_ACTIVE);
	for(i_if = 0; i_if < list_all_if; i_if ++){
		printf("the %d inface is %s\n", i_if,  virInterfaceGetName(ifacess[i_if]));
	}
	*/
	int i_if = 0;
	char **names, max_names=0;
	int list_all_if = virConnectListDefinedInterfaces(conn, names, max_names);
	for(i_if = 0; i_if < list_all_if; i_if ++){
		printf("the %d inface is %s\n", i_if,  names[i_if]);

	}
/*	
	virInterfaceDestroy(virInterfaceLookupByName(conn, "eth1"),0);
	sleep(20);
	virInterfaceCreate(virInterfaceLookupByName(conn, "eth1"),0);
	int ret_1 = virInterfaceChangeBegin(conn,0);
	if(ret_1 == 0) printf("save inface success!\n");
	printf("destroy eht1\n");
	sleep(20);
	virInterfaceChangeRollback(conn, 0);
	printf("rollback eht1\n");
*/
		
	int i_nf = 0;
	virNWFilterPtr *filters = NULL;
	int list_all_nf = virConnectListAllNWFilters(conn, &filters, 0);
	for(i_nf = 0; i_nf < list_all_nf; i_nf ++){
		printf("the %d fliter is %s\n", i_nf,  virNWFilterGetName(filters[i_nf]));
	}

	virNWFilterPtr hehe = virNWFilterLookupByName(conn, "no-ip-multicast");
	unsigned char *uuid = malloc(100);
	memset(uuid,0,100);
	virNWFilterGetUUIDString(hehe,uuid);
	//virNWFilterGetUUID(hehe,uuid);
	printf("%s\n", uuid);

	
	/**************/
	virConnectClose(conn);
	
	return 0;
}
