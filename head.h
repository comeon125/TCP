/*************************************************************************
  > File Name:    head.h
  > Author:       hczbha
  > Description:  
  > Created Time: 2023年12月01日 星期五 19时46分05秒
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>

typedef struct file
{
    char name[64];
    char cont[256];
}F;



MYSQL* msql_init();
int query_mysql(char* user, char* passwd);
int insert_mysql(char* user, char* passwd);
int update_mysql(char* user, char* passwd);
int delete_mysql(char* user);
void register_user(int cfd);
void login_user(int cfd);
void change_password(int cfd);
void log_out(int cfd);

void file_sel(int cfd);
void file_dow(int cfd);
void file_up(int cfd);

#endif //_HEAD_H
