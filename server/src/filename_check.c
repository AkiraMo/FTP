#include "../lib/normal.h"

int filename_check(char* path, char* file)
{
	DIR *dir;
	struct dirent *p;

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
	}
	closedir(dir);
	return -1;
}
