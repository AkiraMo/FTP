#include "fun.h"

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		printf("argc\n");
		return -1;
	}
	
	//socket
	int sfd;
	sfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_addr.s_addr = inet_addr(argv[1]);
	ser.sin_port = htons(atoi(argv[2]));

	//connect
	int ret;
	ret = connect(sfd,(struct sockaddr*)&ser,sizeof(ser));

	char buf[BUFFNUM] = {0};
	int len;
	recv_n(sfd,(char*)&len,4);
	printf("file name len = %d\n",len);
	recv_n(sfd,buf,len);
	printf("file name = %s\n",buf);

	int fd;
	fd = open(buf,O_RDWR|O_CREAT,0666);
	if(-1 == fd)
	{
		perror("open");
		return -1;
	}
	
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
	close(sfd);
	return 0;
}
