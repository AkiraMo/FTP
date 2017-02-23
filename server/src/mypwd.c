#include "../lib/normal.h"

void mypwd(char* rootpath,char* path,char* out)
{
	strcpy(out,"/");
	int i;
	i = strlen(path) - strlen(rootpath) - 1;
	strcat(out,path+(strlen(path) - i));
}
