#include "normal.h"

int sfd;

void sig(int signum)
{
	td tdsig;
	memset(&tdsig,0,sizeof(tdsig));
	tdsig.len = 0;
	send_n(sfd,(char*)&tdsig,4+tdsig.len);
	close(sfd);
	system("clear");
	exit(0);
}

int main(int argc,char* argv[])
{
	signal(SIGINT,sig);
	if(argc != 4)
	{
	    printf("argc\n");
	    return -1;
	}

	system("clear");
	//socket
	sfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_addr.s_addr = inet_addr(argv[1]);
	ser.sin_port = htons(atoi(argv[2]));

	//connect
	connect(sfd,(struct sockaddr*)&ser,sizeof(ser));

	//发送用户名
	char usr[USRNUM] = {0}, pwd[PWDNUM] = {0};
	strcpy(usr,argv[3]);
	td tdusr;
	tdusr.len = strlen(usr);
	strcpy(tdusr.buf,usr);

	strcpy(pwd,"NULL");

	send_n(sfd,(char*)&tdusr,4+tdusr.len);


	//输入指令
	char input[INPUTNUM],cmd[CMDNUM],filename[FILENAMENUM],path[200];
	int cmdid,fileflag;
    char buf[BUFFNUM] = {0};

input_command:
	memset(input,0,sizeof(input));
	memset(cmd,0,sizeof(cmd));
	memset(filename,0,sizeof(filename));
	read(STDIN_FILENO,input,sizeof(input));
	system("clear");
	get_command(input,cmd,filename);
	cmdid = command(cmd);
	if(0 == cmdid)
	{
		goto input_command;
	}

	strcpy(path,PATH);
	if(!filename_check(path,filename))
	{
		fileflag = 0;
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
	memset(&tdcmd,0,sizeof(tdcmd));
	memset(&tdfilename,0,sizeof(tdcmd));

	memset(&buf,0,sizeof(buf));
	int len = 0;

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
		case 2:recv_n(sfd,(char*)&len,4);recv_n(sfd,buf,len);printf("%s",buf);break;
		case 3:send_file(sfd,filename);break;
		case 4:recv_file(sfd);break;
		case 5:break;
		case 6:recv_n(sfd,(char*)&len,4);recv_n(sfd,buf,len);printf("%s\n",buf);break;
		default:break;
	}

	goto input_command;

	return 0;
}
