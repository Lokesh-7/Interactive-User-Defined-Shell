#include "headers.h"
void bg(char *args[], int n)
{
    	if(n!=2)
    	{
       		fprintf(stderr,"Mainshell: kjob: Exactly one argument required\n");
        	return;
    	}
    	int index=0,flag=0,i;
    	for(i=0;i<pidcnt;i++)
    	{
        	if(pids[i].status==1)
        	{
            		index=index+1;
            		if(index==atol(args[1]))
            		{
                		if(kill(pids[i].pid,SIGTTIN)<0)
                		{
                    			perror("Error in kill");
                    			return;
                		}
                		if(kill(pids[i].pid, SIGCONT)>=0)
                		{
					flag=1;
				}
                    		else
				{	perror("Error in kill");
                    			return;
                		}
            		}
        	}
    	}
    	if(flag==0)
	{
        	fprintf(stderr,"Mainnshell: No such process\n");
	}
}
void fg(char *args[], int n)
{
    	if(n!=2)
    	{
        	fprintf(stderr,"Mainshell: kjob: Exactly one argument required\n");
        	return;
    	}
    	int index=0,flag=0,i;
    	for(i=0;i<pidcnt;i++)
    	{
        	if(pids[i].status==1)
        	{
            		index=index+1;
            		if(index==atol(args[1]))
            		{
                		if(kill(pids[i].pid, SIGCONT)<0)
                		{
                    			perror("Error in kill");
                		}
                		pids[i].status=0;
                		fore.pid=pids[i].pid;
                		strcpy(fore.name, pids[i].name);
                		fore.status=1;
                		flag=1;
                		actives=actives-1;
                		waitpid(-1,NULL,WUNTRACED);
                		break;
            		}
        	}
    	}
    	if(flag==0)
        {
		fprintf(stderr,"Mainshell: No background process with given background number\n");
	}
}
void ctrlzhandler(int sig_num)
{
    	if(getpid()!=shellPID)
	{
        	return;
	}
    	if(fore.status==1)
    	{
        	if(kill(fore.pid,SIGTTIN)<0)
        	{
            		perror("Error in kill");
            		return;
        	}
        	if(kill(fore.pid,SIGTSTP)<0)
        	{
            		perror("Error in kill");
            		return;
        	}
        	printf("[%d] %d\n",++actives,fore.pid);
        	pids[pidcnt].pid=fore.pid;
        	pids[pidcnt].status=1;
        	strcpy(pids[pidcnt++].name, fore.name);
        	fore.status=0;
        	return;
    	}
	signal(SIGTSTP,ctrlzhandler);
}
void ctrlchandler(int sig_num)
{
    	if (getpid()!=shellPID)
        {
		return;
	}
    	if(fore.status!=1)
    	{
        	fprintf(stderr,"\nMainshell: No foreground process\n");
        	fflush(stdout);
        	tildconvertedpwd();
    	}
    	else
    	{
		if(kill(fore.pid,SIGINT)<0)
        	{
        	    perror("Error in kill");
        	    printf("%s",fore.name);
        	}
        	fore.status=0;
    	}
    	signal(SIGINT,ctrlchandler);   
    	fflush(stdout);
	return;
}
