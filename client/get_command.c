#include "normal.h"

void get_command(char* s,char* s1,char* s2)
{
	int i,j;
	int flag = 0;
	for (i = 0; s[i] != '\n'; i++)
	{
		if(' ' == s[i])
		{
			flag = 1;
			break;
		}
		s1[i] = s[i];
	}

	if(flag)
	{
		strcpy(s2,s+i+1);
		s2[strlen(s)+1] = '\0';
	}
	else
	{
		s2 = NULL;
	}
	
}
