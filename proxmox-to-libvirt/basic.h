#ifndef __BASIC_H__
#define	__BASIC_H__

char *ReadShell(char *cmd);
int ReadConfig(char *conf_path,char *conf_name,char *config_buff);
int AddOrAltConfig(char *conf_path,char *conf_name,char *config_buff);
int DeleteConfig(char *conf_path,char *conf_name);

#endif
