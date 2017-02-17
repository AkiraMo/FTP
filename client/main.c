#include "normal.h"

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

	//输入指令
	char input[INPUTNUM] = {0};
	char cmd[CMDNUM] = {0};
	char* filename = (char*)calloc(FILENAMENUM,sizeof(char));
	int cmdid;
input_command:
	read(STDIN_FILENO,input,sizeof(input));
	get_command(input,cmd,filename);
	cmdid = command(cmd);
	if(0 == cmdid)
	{
		goto input_command;
	}

	//发送指令
	send(sfd,cmd,strlen(cmd),0);
	//接收响应
	
	switch(cmdid)
	{
		case 1:break;
		case 2:break;
		case 3:break;
		case 4:break;
		case 5:break;
		case 6:break;
	}

	close(sfd);
	return 0;
}
