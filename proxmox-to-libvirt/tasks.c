#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<libvirt/libvirt.h>
#include "basic.h"

struct time{
        long time;
        long localtime;
        char timezone[64];
};



/*Must free by caller*/
char *AplinfoGet(void){
	return ReadShell("rpm -qai");
}

void ApinfoPost(char *app){
	char cmd[128];
	strcpy(cmd, "yum install -y ");
	strcat(cmd, app);
	system(cmd);
}

char * BootLogGet(void){
	int logfd = 0;
	char *debian_log = "/var/log/boot";
	char *rhel_log = "/var/log/boot.log";
	char *logbuf = (char *)malloc(1024*8);
	
	memset(logbuf,0,1024*8);

	if(! access(debian_log, R_OK)){
		logfd = open(debian_log,O_RDONLY);
	}else if(! access(rhel_log, R_OK)){
		logfd = open(rhel_log,O_RDONLY);
	}else{
		fprintf(stderr, "%s\n", "failed to open log.");
	}

	read(logfd,logbuf,1024*8);

	return logbuf;
}

char *ReadDNS(void){
	int dnsfd = 0;
	char *dns_path = "/etc/resolv.conf";
	char *dns_buf = (char *)malloc(1024);
	memset(dns_buf,0,1024);

	if(! access(dns_path, R_OK)){
		dnsfd = open(dns_path, O_RDONLY);
	}else{
		fprintf(stderr,"open dns failed.\n");
		return NULL;
	}

	read(dnsfd,dns_buf,1024);

	return dns_buf;
}

void SetHostname(char *hostname){
	char cmd[128];
	char option[128];
	
	memset(cmd,0,128);
	strcpy(cmd,"hostname ");
	strcat(cmd,hostname);
	system(cmd);

	memset(option,0,128);
	strcpy(option,"HOSTNAME=");
	strcat(option,hostname);
	AddOrAltConfig("/etc/sysconfig/network", "HOSTNAME", option);
}



char *ReadSyslog(char *sys_path){
	int sysfd = 0;
	char *sys_buf = (char *)malloc(1024*8);
	memset(sys_buf,0,1024*8);

	if(! access(sys_path, R_OK)){
		sysfd = open(sys_path, O_RDONLY);
	}else{
		fprintf(stderr,"open syslog failed.\n");
		return NULL;
	}

	read(sysfd,sys_buf,1024*8);

	return sys_buf;
}


int DomainStartAll(virConnectPtr conn){
	virDomainPtr *domains = NULL;
	int flags = VIR_CONNECT_LIST_DOMAINS_INACTIVE;
	int ret = 0, i = 0;
	
	ret = virConnectListAllDomains(conn, &domains, flags);
	for(i = 0; i < ret; i++){
	    virDomainCreate(domains[i]);
	    virDomainFree(domains[i]);
	}

	return 0;
	
}

int DomainStopAll(virConnectPtr conn){
	virDomainPtr *domains = NULL;
	int flags = VIR_CONNECT_LIST_DOMAINS_ACTIVE;
	int ret = 0, i = 0;
	
	ret = virConnectListAllDomains(conn, &domains, flags);
	for(i = 0; i < ret; i++){
	    virDomainDestroy(domains[i]);
	    virDomainFree(domains[i]);
	}

	return 0;
	
}

void FenceHost1(char *ip,char *type){
	char cmd[128];
	memset(cmd,0,128);

	strcpy(cmd,"ssh ");
	strcat(cmd, ip);
	strcat(cmd, " ");
	strcat(cmd,type);

	system(cmd);
}


/*Must free by caller.*/
struct time *gettime(void){
        struct time *now = (struct time *)malloc(sizeof(struct time));
        time_t timep;
        struct tm *localtemp;
        long seconds = 0, localseconds = 0;

        seconds = time(&timep);
        now->time = seconds;

        localtemp = localtime(&timep);
        strcpy(now->timezone,localtemp->tm_zone);

        localseconds = mktime(localtemp);
        now->localtime = localseconds;

        return now;
}

int main(int argc, char **argv){
        virConnectPtr conn;
//	SetHostname("gukai");
//	FenceHost1("172.23.178.61","reboot");

	
//	printf("%s\n", BootLogGet());
//	AplinfoGet();
//	printf("%s\n", ReadDNS());
//	char *p = AplinfoGet();
//	printf("%s", p);
//	free(p);

        conn = virConnectOpenAuth("qemu+ssh://root@10.12.28.59/system", virConnectAuthPtrDefault, 0);
        if(conn == NULL){
                fprintf(stderr, "Failed to open conection");
                return 1;
        }


/*
int	virNodeGetInfo			(virConnectPtr conn,
					 virNodeInfoPtr info)
*/
/*
struct virNodeInfoPtr nodeinfo = (struct virNodeInfoPtr)malloc(sizeof(virNodeInfo));
virNodeGetInfo(conn, nodeinfo);
*/




/**************/
/* works */
//DomainStopAll(conn);
//sleep(20);
//DomainStartAll(conn);
/*************/

//	printf("%s\n", virConnectGetCapabilities(conn));
//	printf("%s\n", virConnectGetSysinfo(conn, 0));
//	AplinfoGet();
//	ApinfoPost("vim");
	virConnectClose(conn);

        return 0;
}
