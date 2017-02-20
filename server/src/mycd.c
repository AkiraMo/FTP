#include "../lib/normal.h"

void mycd(char* path,char* filepath)
{
	char sprit[2] = "/";
	int i;
	if(!strcmp(filepath,".."))
	{
		for(i = strlen(path); path[i] != '/'; i--)
		{
			path[i] = '\0';
		}
	}
	else if(!filename_check(path,filepath))
	{
		strcat(path,sprit);
		strcat(path,filepath);
	}
	else
	{
		printf("路径不存在\n");
		return;
	}
	printf("%s\n",path);
}
