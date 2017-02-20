#include "../lib/normal.h"

void printfls(char* path)
{
	DIR *dir;
	struct dirent *p;
	struct stat buf;
	mode_t mode;
	double type;
	int b_mode[16],i;

	dir = opendir(path);
	if(NULL == dir)
	{
		printf("opendir\n");
		return;
	}

	while((p = readdir(dir)) != NULL)
	{
		memset(&buf,0,sizeof(buf));
		stat(p->d_name,&buf);
		if(!strcmp(p->d_name,".") || !strcmp(p->d_name,".."))
		{
			continue;
		}
		mode = buf.st_mode;
		for(i = 0; i < 16; i++)
		{
			b_mode[15 - i] = mode % 2;
			mode /= 2;
		}
		type = 0;
		for(i = 0; i < 4; i++)
		{
			type += b_mode[i] * pow(2,i+1);
		}
		printf("%d	%s	%ld\n",(int)type,p->d_name,buf.st_size);
	}
}

void myls(char* rootpath,char* filepath)
{
	char path[PATHNUM] = {0};
	if(!strcmp(filepath,"NULL"))
	{
		strcpy(path,".");
	}
	else if(!filename_check(rootpath,filepath))
	{
		sprintf(path,"%s/%s",rootpath,filepath);
	}
	else
	{
		printf("路径不存在\n");
		return;
	}
	printfls(path);
}