#include "../lib/factory.h"

void factory_init(pfac f,pthfunc entry)
{
	f->pth = (pthread_t*)calloc(f->tnum,sizeof(pthread_t));
	f->entry = entry;
	pthread_cond_init(&f->cond,NULL);
	que_init(&f->que);
	f->start = 0;
	printf("线程池初始化完成\n");
}

void factory_start(pfac f)
{
	int i,ret;
	if(0 == f->start)
	{
		for(i = 0; i < f->tnum; i++)
		{
			ret = pthread_create(&f->pth[i],NULL,f->entry,f);
			usleep(1);
			if(ret != 0)
			{
				perror("pthread_create");
				return;
			}
			printf("创建子线程\n");
		}
		f->start = 1;
	}
	else
	{
		printf("线程池已经启动\n");
	}
	printf("线程池启动完毕\n");
}
