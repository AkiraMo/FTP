#include "../lib/normal.h"

void delDir(char* path)
{
	DIR *dir;
	char buf[PATHNUM];
	struct dirent *p;

	dir = opendir(path);
	while((p = readdir(dir)) != NULL)
	{
		memset(&buf,0,sizeof(buf));
		if(!strcmp(p->d_name,".") || !strcmp(p->d_name,".."))
		{
			continue;
		}
		sprintf(buf,"%s/%s",path,p->d_name);
		if(4 == p->d_type)
		{
			delDir(buf);
		}
		else
		{
			unlink(buf);
		}
	}
	closedir(dir);
	rmdir(path);
}

void myremove(char* path,char* filename)
{
	char pathbuf[PATHNUM] = {0};
	struct stat buf;
	int i,ret;
	mode_t mode;
	double type;
	char b_mode[16];

	sprintf(pathbuf,"%s/%s",path,filename);
	ret = stat(pathbuf,&buf);
	if(-1 == ret)
	{
		perror("stat");
		return;
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

	if(4 == type)
	{
		delDir(pathbuf);
	}
	else
	{
		unlink(pathbuf);
	}

}
