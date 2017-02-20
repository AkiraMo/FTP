#include "normal.h"

int main(int argc,char* argv[])
{
	if(argc != 4)
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

	//发送用户名
	char usr[USRNUM] = {0}, pwd[PWDNUM] = {0};
	strcpy(usr,argv[3]);
	td tdusr;
	tdusr.len = strlen(usr);
	strcpy(tdusr.buf,usr);

	strcpy(pwd,"NULL");

	send_n(sfd,(char*)&tdusr,4+tdusr.len);


	//输入指令
	char input[INPUTNUM],cmd[CMDNUM],filename[FILENAMENUM];
	int cmdid;
input_command:
	memset(input,0,sizeof(input));
	memset(cmd,0,sizeof(cmd));
	memset(filename,0,sizeof(filename));
	read(STDIN_FILENO,input,sizeof(input));
	get_command(input,cmd,filename);
	cmdid = command(cmd);
	if(0 == cmdid)
	{
		goto input_command;
	}
	char path[] = ".";
	int ret1;
	ret1 = filename_check(path,filename);
	if(0 == ret1)
	{
		printf("文件存在\n");
	}
	else
	{
		printf("文件不存在\n");
	}
	//发送指令
	td tdcmd;
	tdcmd.len = 1;
	strcpy(tdcmd.buf,(char*)&cmdid);
	send_n(sfd,(char*)&tdcmd,4+tdcmd.len);

	td tdfilename;
	char tmp[] = "NULL";
	if(filename[0] != '\0' && filename[0] != ' ')
	{
		tdfilename.len = strlen(filename);
		strcpy(tdfilename.buf,filename);
	}
	else
	{
		tdfilename.len = strlen(tmp);
		strcpy(tdfilename.buf,tmp);
	}
	send_n(sfd,(char*)&tdfilename,4+tdfilename.len);
	printf("已成功发送%d %s\n",cmdid,tdfilename.buf);
	memset(&tdcmd,0,sizeof(tdcmd));
	memset(&tdfilename,0,sizeof(tdcmd));

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
		default:break;
	}

	goto input_command;

	close(sfd);
	return 0;
}
