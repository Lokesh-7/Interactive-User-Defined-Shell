#include "headers.h"
void senv(char *args[], int n)
{
	if(n==1)
	{
        	fprintf(stderr,"Mainshell: setenv: Too few arguments\n");
    	}
    	else if(n==2)
    	{
    		if(setenv(args[1],"",1)<0)
    	        {
			perror("Error in setenv");
		}	
    	}
    	else if(n==3)
    	{
	        if(setenv(args[1],args[2],1)<0)
      	        { 
			 perror("Error in setenv");
		}	
        }
	else
	{
        	fprintf(stderr,"Mainshell: setenv: Too many arguments");
	}
}
void unsenv(char *args[], int n)
{
	int i;
    	if(n!=1)
	{
		for(i=1;i<n;i++)
        	{
	                if(unsetenv(args[i])<0)
			{
	                	perror("Error in unsetenv");
			}
	        }
    	}
	else
    	{
        	fprintf(stderr,"Mainshell: unsetenv: Too few arguments\n");
	}
}
