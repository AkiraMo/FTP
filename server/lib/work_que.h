#ifndef _WORK_QUE_
#define _WORK_QUE_

#include "normal.h"

typedef struct list
{
	int new_fd;
	int sfd;
	struct list* pnext;
}node,*pnode;

typedef struct work_que
{
	pnode phead,ptail;
	pthread_mutex_t mutex;
	int size;
}que_t,*pque;

void que_init(pque);
void que_add(pque,int,int);
void que_get(pque,pnode*);

#endif

