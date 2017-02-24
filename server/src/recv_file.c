#include "../lib/normal.h"
void recv_file(int sfd,char* path)
{
	char buf[BUFFNUM] = {0};
	int len;
	recv_n(sfd,(char*)&len,4);
	recv_n(sfd,buf,len);

	int fd;
	char pathbuf[PATHNUM];
	strcpy(pathbuf,path);
	strcat(pathbuf,"/");
	strcat(pathbuf,buf);
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
	close(fd);
	printf("文件接收完成\n");
}
