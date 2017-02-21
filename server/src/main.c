#include "../lib/factory.h"

void console(pnode p)
{
	int len,ret,fileflag;
	//接收用户名并创建对应路径
	char usr[USRNUM] = {0};
	recv_n(p->new_fd,(char*)&len,4);
	if(len > 0)
	{
		recv_n(p->new_fd,usr,len);
	}
	printf("用户名 %s\n",usr);
	
	//创建独立文件夹
	struct stat file_stat;
	char path[PATHNUM] = PATH;
	strcat(path,usr);
	char rootpath[strlen(path)];
	strcpy(rootpath,path);
	ret = stat(path,&file_stat);
	if(ret < 0)
	{
		if(errno == ENOENT)
		{
			ret = mkdir(path,0755);
			if(ret < 0)
			{
				perror("mkdir");
				return;
			}
			printf("创建文件夹成功\n");
		}
	}

	//接收指令
	char filename[FILENAMENUM],out[BUFFNUM];
	int cmdid;
recv:
	memset(filename,0,sizeof(filename));
	cmdid = 0;
	len = 0;

	recv_n(p->new_fd,(char*)&len,4);
	if(len > 0)
	{
		recv_n(p->new_fd,(char*)&cmdid,len);
	}
	else if(0 == len)
	{
		goto exit;
	}
	if(cmdid < 1 && cmdid > 6)
	{
		goto recv;
	}
	
	recv_n(p->new_fd,(char*)&len,4);
	if(len > 0)
	{
		recv_n(p->new_fd,filename,len);
	}
	if(!strcmp(filename,"NULL"))
	{
		fileflag = -1;
	}
	else
	{
		fileflag = 0;
	}
	printf("完成接收%d %s\n",cmdid,filename);

	memset(&out,0,sizeof(out));
	switch(cmdid)
	{
		case 1:mycd(strlen(rootpath),path,filename);break;
		case 2:myls(path,filename,out);send_msg(p->new_fd,out);break;
		case 3:printf("puts %s\n",filename);break;
		case 4:printf("gets %s\n",filename);break;
		case 5:printf("remove %s\n",filename);break;
		case 6:mypwd(rootpath,path,out);send_msg(p->new_fd,out);break;
		default:break;
	}

	goto recv;
exit:
	printf("客户端断开连接\n");
}

void* threadfunc(void* p)
{
	printf("子线程创建成功\n");
	pfac pf = (pfac)p;
	pque pq = &pf->que;
	pnode pn;

	while(1)
	{
		pthread_mutex_lock(&pq->mutex);
		if(0 == pq->size)
		{
			pthread_cond_wait(&pf->cond,&pq->mutex);
		}
		que_get(pq,&pn);
		pthread_mutex_unlock(&pq->mutex);
		printf("子线程已醒来\n");
		console(pn);
		free(pn);
	}
}

int main(int argc,char* argv[])
{
	if(argc != 5)
	{
		printf("argc\n");
		return -1;
	}

	fac f;
	memset(&f,0,sizeof(f));
	f.tnum = atoi(argv[3]);
	f.capibility = atoi(argv[4]);
	factory_init(&f,threadfunc);
	factory_start(&f);
	
	int sfd;
	sfd = socket(AF_INET,SOCK_STREAM,0);
	set_init(sfd,argv[1],argv[2]);
	listen(sfd,f.capibility);
	int new_fd;
	while(1)
	{
		new_fd = accept(sfd,NULL,NULL);
		que_add(&f.que,new_fd,sfd);
		pthread_cond_signal(&f.cond);
	}
	
	close(sfd);
	return 0;	
}
