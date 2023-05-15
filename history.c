#include "headers.h"
void historyinit()
{
    	char fname[20];
    	histptr=0;
    	FILE *fptr=NULL;
    	fptr=fopen("history.txt","r");
    	while(fgets(hists[histptr],4096,fptr))
    	{
        	hists[histptr][strlen(hists[histptr])-1]='\0';
        	strcat(hists[histptr],"\n");
        	histptr=histptr+1;
        	if(histptr>19)
		{
            		break;
		}
    	}
    	histptr%=20;
    	histcnt=histptr;
    	fclose(fptr);
}
void historyadd(char cmnd[])
{   
    	if(strcmp(hists[(histptr-1+20)%20],cmnd)!=0)
    	{
		strcpy(hists[histptr], cmnd);
        	histptr=(histptr+1)%20;
        	if(histcnt<20)
		{
            		histcnt=histcnt+1;
		}
    	}
    	else
    	{
        	return;
    	}
}
void historydisp(char *args[], int n)
{
    	int num,i;
    	if(n==1)
    	{
        	num=10;
    	}
    	else if(n==2)
    	{
        	sscanf(args[1],"%d",&num);
    	}
    	else
    	{
        	fprintf(stderr,"Mainshell: history: Too many arguments\n");
    	}		
    	if(num>10)
	{
        	num=10;
	}
    	if(num>histcnt)
	{
        	num=histcnt;
	}
    	for(i=num;i>0;i--)
    	{
        	printf("%s",hists[(histptr-i+20)%20]);
    	}
}
void historyexit()
{
    	FILE *fp;
    	int i;
    	fp=fopen("history.txt","w");
    	for(i=histcnt;i>0;i--)
    	{
        	fputs(hists[(histptr-i+20)%20],fp);
    	}
    	fclose(fp);
    	return;
}
