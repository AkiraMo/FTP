#include "../lib/normal.h"

int command(char* s)
{
	if(0 == strcmp(s,"cd"))
	{
		return 1;
	}
	if(0 == strcmp(s,"ls"))
	{
		return 2;
	}
	if(0 == strcmp(s,"puts"))
	{
		return 3;
	}
	if(0 == strcmp(s,"gets"))
	{
		return 4;
	}
	if(0 == strcmp(s,"remove"))
	{
		return 5;
	}
	if(0 == strcmp(s,"pwd"))
	{
		return 6;
	}
	return 0;
}
