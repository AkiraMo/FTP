#include "../lib/normal.h"

void send_file(int new_fd,char* filename)
{
	td t;
	memset(&t,0,sizeof(t));
	t.len = strlen(filename);
	strcpy(t.buf,filename);
	send_n(new_fd,(char*)&t,4+t.len);
	int fd;
	fd = open(filename,O_RDONLY);
	if(-1 == fd)
	{
		perror("open");
		return;
	}
	while(memset(&t,0,sizeof(t)),(t.len = read(fd,t.buf,sizeof(t.buf))) > 0)
	{
		send_n(new_fd,(char*)&t,4+t.len);
	}
	t.len = 0;
	send_n(new_fd,(char*)&t.len,4);
	printf("文件传输完成\n");
}
