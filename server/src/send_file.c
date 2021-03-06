#include "../lib/normal.h"

void send_file(int new_fd,char* filename,char* path)
{
	td t;
	memset(&t,0,sizeof(t));
	t.len = strlen(filename);
	strcpy(t.buf,filename);
	send_n(new_fd,(char*)&t,4+t.len);
	int fd;
	char pathbuf[PATHNUM];
	strcpy(pathbuf,path);
	strcat(pathbuf,"/");
	strcat(pathbuf,filename);
	fd = open(pathbuf,O_RDONLY);

	while(memset(&t,0,sizeof(t)),(t.len = read(fd,t.buf,sizeof(t.buf))) > 0)
	{
		send_n(new_fd,(char*)&t,4+t.len);
	}
	t.len = 0;
	send_n(new_fd,(char*)&t.len,4);
	printf("文件传输完成\n");
}
