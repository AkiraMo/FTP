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

#define BUFFNUM 1000

//子进程结构体
typedef struct childdata
{
	pid_t pid;
	int fdw;
	int busy;
}cd,*pcd;

typedef struct transferdata
{
	int len;
	char buf[BUFFNUM];
}td,*ptd;

void recv_n(int fd,char* buf,int len);


