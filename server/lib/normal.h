#ifndef _NORMAL_H_
#define _NORMAL_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>
#include <dirent.h> 
#include <math.h>

#define BUFFNUM 1000
#define CMDNUM 20
#define FILENAMENUM 20
#define USRNUM 20
#define PWDNUM 20
#define PATH "../data/"
#define PATHNUM 200
typedef struct transferdata
{
	int len;
	char buf[BUFFNUM];
}td,*ptd;

void send_file(int,char*,char*);
void recv_file(int,char*);
void set_init(int,char*,char*);
void send_n(int fd,char* buf,int len);
void recv_n(int fd,char* buf,int len);
int command(char* s);
void epoll_add(int epfd, int fd, int eve,  struct epoll_event* event);
void epoll_del(int epfd, int fd, int eve, struct epoll_event* event);
int filename_check(char* path, char* file);
void mycd(int rootlen, char* path,char* filepath);
void myls(char* rootpath,char* filepath,char* out);
void mypwd(char* rootpath,char* path,char* out);
void myremove(char* path,char* filename);
void send_msg(int fd,char* out);
#endif
