#include "../lib/work_que.h"

void que_init(pque q)
{
	memset(q,0,sizeof(que_t));
	pthread_mutex_init(&q->mutex,NULL);
	printf("队列初始化完成\n");
}

void que_add(pque q,int new_fd, int sfd)
{
	pnode pnew = (pnode)calloc(1,sizeof(node));
	pnew->new_fd = new_fd;
	pnew->sfd = sfd;
	pthread_mutex_lock(&q->mutex);
	if(q->phead == q->ptail)
	{
		q->phead = pnew;
		q->ptail = pnew;
	}
	else
	{
		q->ptail->pnext = pnew;
		q->ptail = pnew;
	}
	(q->size)++;
	pthread_mutex_unlock(&q->mutex);
}

void que_get(pque q,pnode* p)
{
	*p = q->phead;
	q->phead = q->phead->pnext;
	if(q->phead == NULL)
	{
		q->ptail = NULL;
	}
	(q->size)--;
}
