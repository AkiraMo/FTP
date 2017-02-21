#include "../lib/normal.h"

void send_msg(int fd,char* out)
{
	td t;
	memset(&t,0,sizeof(t));
	t.len = strlen(out);
	strcpy(t.buf,out);
	send_n(fd,(char*)&t,4+t.len);
}
