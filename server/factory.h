#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "normal.h"
#include "work_que.h"

typedef void* (*pthfunc)(void*);

typedef struct factory
{
	pthread_t *pth;
	int tnum;
	pthfunc entry;
	pthread_cond_t cond;
	int capibility;
	que_t que;
	int start;
}fac,*pfac;

void factory_init(pfac,pthfunc);
void factory_start(pfac);

#endif
