#include "headers.h"
void cd(char *args[],int n)
{
	char loc[FILENAME_MAX]="";
    	if(n==1)  
	{
		strcpy(loc,tild);
	}
    	else if(args[1][0]=='~')   
    	{
        	strcpy(loc,tild);
        	strcat(loc,&args[1][1]);
    	}
    	else 
	{
		strcpy(loc,args[1]);
	}
    	if(n>2) 
	{
		fprintf(stderr,"Mainshell: Error: Too many arguments: cd\n");
	}
    	else if(chdir(loc))
	{
        	perror("cd");
    	}
}
