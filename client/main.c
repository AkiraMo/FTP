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
	td tdcmd;
	tdcmd.len = strlen(cmd);
	strcpy(tdcmd.buf,cmd);
	send_n(sfd,(char*)&tdcmd,4+tdcmd.len);

	td tdfilename;
	char tmp[] = "NULL";
	if(filename != NULL)
	{
		tdfilename.len = strlen(filename);
		strcpy(tdfilename.buf,filename);
		send_n(sfd,(char*)&tdfilename,4+tdfilename.len);
	}
	else
	{
		send_n(sfd,(char*)8,4);
		send_n(sfd,tmp,8);
	}
	
	while(1);
	//接收响应
	char buf[BUFFNUM] = {0};
	memset(&buf,0,sizeof(buf));

	//功能
	//1.cd 进入对应目录
	//2.ls 列出相应的目录文件
	//3.puts 将本地文件上传至服务器
	//4.gets 文件名 下载服务器文件到本地
	//5.remove 删除服务器上的文件
	//6.pwd 显示目前所在路径
	//其余命令不响应
	switch(cmdid)
	{
		case 1:break;
		case 2:break;
		case 3:break;
		case 4:break;
		case 5:break;
		case 6:break;
		default:goto input_command;break;
	}

	close(sfd);
	return 0;
}
