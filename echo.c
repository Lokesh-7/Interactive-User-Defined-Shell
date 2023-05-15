#include "headers.h"
void echo(char *args[], int n)
{
	int i;
  	if(n<2)
  	{
    		printf("\n");
		return;
  	}
  	for(i=1;i<n-1;i++)
  	{
    		if(args[i]!=NULL)
    		{
      			printf("%s ",args[i]);
    		}
  	}
  	if(args[n - 1]!=NULL)
  	{
    		printf("%s",args[n - 1]);
  	}
  	printf("\n");
}
