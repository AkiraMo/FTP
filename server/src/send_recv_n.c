#include "../lib/normal.h"

void send_n(int fd,char* buf,int len)
{
	int total = 0;
	int pos;
	while(total < len)
	{
		pos = send(fd,buf+total,len-total,0);
		total += pos;
	}
//	printf("本次发送完毕\n");
}

void recv_n(int fd,char* buf,int len)
{
	int total = 0;
	int pos;
	while(total < len)
	{
		pos = recv(fd,buf+total,len-total,0);
		total += pos;
	}
//	printf("本次接受完毕\n");
}

