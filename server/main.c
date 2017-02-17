#include "factory.h"

void console(pnode p)
{
	int cmdid;
	int len;
	char cmd[CMDNUM],filename[FILENAMENUM];

	memset(&cmd,0,sizeof(cmd));
	memset(&filename,0,sizeof(filename));
	recv_n(p->new_fd,(char*)&len,4);
	recv_n(p->new_fd,cmd,len);
	recv_n(p->new_fd,(char*)&len,4);
	recv_n(p->new_fd,filename,len);
	printf("%s %s\n",p->cmd,p->filename);	
	cmdid = command(p->cmd);
	switch(cmdid)
	{
		case 1:printf("cd %s\n",p->filename);break;
		case 2:printf("ls %s\n",p->filename);break;
		case 3:printf("puts %s\n",p->filename);break;
		case 4:printf("gets %s\n",p->filename);break;
		case 5:printf("remove %s\n",p->filename);break;
		case 6:printf("pwd %s\n",p->filename);break;
		default:break;
	}
}

void* threadfunc(void* p)
{
	printf("子线程正在运行\n");
	pfac pf = (pfac)p;
	pque pq = &pf->que;
	pnode pn;
	int epfd,ret;
	//epoll
	epfd = epoll_create(1);
	struct epoll_event event;
	memset(&event,0,sizeof(event));
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
		epoll_add(epfd,pn->new_fd,EPOLLIN,&event);
		ret = epoll_wait(epfd,&event,1,-1);
		if(-1 == ret)
		{
			perror("epoll_wait");
			return NULL;
		}
		printf("%d",ret);
		if(ret > 0)
		{
			console(pn);	
		}
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
		que_add(&f.que,new_fd);
		pthread_cond_signal(&f.cond);
	}
	
	close(sfd);
	return 0;	
}
