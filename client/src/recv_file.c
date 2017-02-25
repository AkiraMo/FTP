#include "../lib/normal.h"
void recv_file(int sfd)
{
	char buf[BUFFNUM] = {0};
	int len;
	recv_n(sfd,(char*)&len,4);
	recv_n(sfd,buf,len);
	char pathbuf[PATHNUM] = "../data/";
	strcat(pathbuf,buf);
	int fd;
	fd = open(pathbuf,O_RDWR|O_CREAT,0666);

	while(1)
	{
		recv_n(sfd,(char*)&len,4);
		memset(buf,0,sizeof(buf));
		if(len > 0)
		{
			recv_n(sfd,buf,len);
			write(fd,buf,len);
		}
		else
		{
			break;
		}
	}
	printf("文件接收完成\n");
}
