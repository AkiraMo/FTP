#include "../lib/normal.h"

void printfls(char* path,char* out)
{
	DIR *dir;
	struct dirent *p;
	struct stat buf;
	mode_t  mode;
	double type;
	int b_mode[16],i,ret;
	char outbuf[PATHNUM];
	char pathbuf[PATHNUM];

	dir = opendir(path);
	if(NULL == dir)
	{
		printf("opendir\n");
		return;
	}

	while((p = readdir(dir)) != NULL)
	{
		memset(&buf,0,sizeof(buf));
		memset(&pathbuf,0,sizeof(pathbuf));
		sprintf(pathbuf,"%s/%s",path,p->d_name);
		ret = stat(pathbuf,&buf);
		if(-1 == ret)
		{
			perror("stat");
			return;
		}
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
		memset(outbuf,0,sizeof(outbuf));
		sprintf(outbuf,"%d	%s	%ld\n",(int)type,p->d_name,buf.st_size);
		strcat(out,outbuf);
	}
	closedir(dir);
}

void myls(char* rootpath,char* filepath,char* out)
{
	char path[PATHNUM] = {0};
	if(!strcmp(filepath,"NULL"))
	{
		strcpy(path,rootpath);
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
	printfls(path,out);
}
