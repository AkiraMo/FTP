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

#define BUFFNUM 1000
#define CMDNUM 50
#define FILENAMENUM 50

typedef struct transferdata
{
	int len;
	char buf[BUFFNUM];
}td,*ptd;

void send_file(int);
void set_init(int,char*,char*);
void send_n(int fd,char* buf,int len);
void recv_n(int fd,char* buf,int len);
int command(char* s);
void epoll_add(int epfd, int fd, int eve,  struct epoll_event* event);
void epoll_del(int epfd, int fd, int eve, struct epoll_event* event);

#endif
