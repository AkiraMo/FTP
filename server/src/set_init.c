#include "../lib/normal.h"

void set_init(int sfd,char* IP,char* port)
{
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_addr.s_addr = inet_addr(IP);
	ser.sin_port = htons(atoi(port));
	bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
}
