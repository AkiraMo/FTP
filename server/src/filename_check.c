#include "../lib/normal.h"

int filename_check(char* path, char* file)
{
	DIR *dir;
	struct dirent *p;
	char buf[200] = {0};
	int ret = 100;
	dir = opendir(path);
	
	while((p = readdir(dir)) != NULL)
	{
		if(!strcmp(p->d_name,".") || !strcmp(p->d_name,".."))
		{
			continue;
		}
		if(!strcmp(p->d_name,file))
		{
			closedir(dir);
			return 0;
		}
		if(4 == p->d_type)
		{
			sprintf(buf,"%s/%s",path,p->d_name);
			ret = filename_check(buf,file);
			if(0 == ret)
			{
				closedir(dir);
				return 0;
			}
		}
	}
	closedir(dir);
	return -1;
}
