#include "../lib/normal.h"

void epoll_add(int epfd, int fd, int eve,  struct epoll_event* event)
{
	int ret;
	(*event).events = eve;
	(*event).data.fd = fd;
	ret = epoll_ctl(epfd,EPOLL_CTL_ADD,fd,event);
	if(-1 == ret)
	{
		perror("epoll_ctl");
		return;
	}
}

void epoll_del(int epfd, int fd, int eve, struct epoll_event* event)
{
	(*event).events = eve;
	(*event).data.fd = fd;
	epoll_ctl(epfd,EPOLL_CTL_DEL,fd,event);
}


