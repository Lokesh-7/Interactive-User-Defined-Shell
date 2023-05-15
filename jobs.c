#include "headers.h"
void jobs(char *args[], int n)
{
	if(n>1)
    	{
        	fprintf(stderr,"Mainshell: jobs: Too many arguments");
    	}
    	int index=0,i;
    	for(i=0;i<pidcnt;i++)
    	{
        	if(pids[i].status==1)
        	{
            		index=index+1;
            		char stats[FILENAME_MAX];
            		sprintf(stats,"/proc/%d/stat",pids[i].pid);
            		FILE *fd=fopen(stats, "r");
            		if(fd)
            		{
				char statchar;
                		unsigned long mem;
                		fscanf(fd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &statchar, &mem);
                		fclose(fd);
                		char state[100]="Running";
                		if(statchar=='T' || statchar=='t')
				{
                    			strcpy(state,"Stopped");
				}
                		printf("[%d] %s %s[%d]%c\n",index,state,pids[i].name,pids[i].pid,statchar);
            		}
            		else
            		{
                		pids[i].status=0;
            		}
        	}
    	}
}
void overkill(char *args[], int n)
{
    	if(n>1)
    	{
        	fprintf(stderr,"Mainshell: jobs: Too many arguments");
        	return;
    	}
	int i;
    	for(i=0;i<pidcnt;i++)
    	{
        	if(pids[i].status==1)
        	{
            		if(kill(pids[i].pid,SIGKILL)>=0)
            		{
                		pids[i].status=0;
                		actives=actives-1;
            		}
            		else
            		{
				perror("Error in kill");
            		}
        	}
    	}
}
void kjob(char *args[], int n)
{
    	if (n!=3)
    	{
        	fprintf(stderr,"Mainshell: kjob: Exactly two arguments required\n");
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
                		if(kill(pids[i].pid, atol(args[2]))>=0)
                		{
                    			flag=1;
                    			pids[i].status=0;
                    			actives=actives-1;
                		}
                		else
                		{
					perror("Error in kill");
                    			return;
                		}
                		break;
            		}
        	}
    	}
    	if(flag==0)
    	{
        	fprintf(stderr,"Mainshell: No such process\n");
    	}
}
