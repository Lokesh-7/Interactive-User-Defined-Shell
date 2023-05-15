#include "headers.h"
void pwd(int n)
{
  	if(n>1)
  	{
    		fprintf(stderr,"mainshell: pwd: too many arguments\n");
    		return;
  	}
  	char buffer[FILENAME_MAX];
  	getcwd(buffer,FILENAME_MAX);
  	printf("%s\n",buffer);
}
void tildconvertedpwd()
{
  	char converted[FILENAME_MAX];
  	char current[FILENAME_MAX];
  	getcwd(current,FILENAME_MAX);
  	tildconverter(converted,current);
  	printf("<%s%s@%s%s:%s%s%s> ","\x1B[1;31m",namebuffer,hostbuffer,"\x1B[0m","\x1B[1;33m",converted,"\x1B[0m");
}
void tildconverter(char converted[], char current[])
{
  	int flag=0,i;
  	if(strlen(current)<strlen(tild))
  	{
		flag=1;
	}
	else
	{
    		for(i=0;i<strlen(tild);i++)
    		{
     	 		if(current[i]!=tild[i])
      			{
        			flag=1;
        			break;
      			}
    		}	
  	}
  	strcpy(converted,"~");
  	if (flag!=0)
  	{
		strcpy(converted,current);
	}
	else
	{
    		strcat(converted,&current[strlen(tild)]);
  	}
}
