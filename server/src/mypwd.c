#include "../lib/normal.h"

void mypwd(char* rootpath,char* path)
{
	char buf[PATHNUM] = {0};
	int i;
	i = strlen(path) - strlen(rootpath);
	strcpy(buf,path+(strlen(path) - i));
	printf("%s\n",buf);
}
