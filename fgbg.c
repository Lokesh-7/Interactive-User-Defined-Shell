#include "headers.h"
void child_sig()
{
	pid_t pid;
	int stat,i;
    	pid=waitpid(-1, &stat, WNOHANG | WUNTRACED);
    	for(i=0;i<pidcnt;i++)
    	{
        	if(pid==pids[i].pid)
        	{
            		if (WIFEXITED(stat))
            		{
                		int exit_status=WEXITSTATUS(stat);
                		if(exit_status==0)
                		{
					fprintf(stderr, "\rProcess %s with pid %d exited with exit status %d\n", pids[i].name, pid, exit_status);
                		}
                		else
                		{
                    			fprintf(stderr, "\rProcess %s with pid %d exited normally\n", pids[i].name, pid);
                		}
                		pids[i].status=0;
                		tildconvertedpwd();
                		fflush(stdout);
                		actives=actives-1;
                		break;
            		}
        	}
    	}
}
void foregrnd(char *args[], int n)
{
	pid_t pid;
	int i;
	pid=fork();
	if(pid==0)
   	{
		setpgid(0,0);
        	if (execvp(args[0],args)<0)
        	{
            		printf("Mainshell: Error: execvp failed\n");
            		exit(EXIT_FAILURE);
        	}
    	}
    	else if(pid>0)
    	{
		fore.pid=pid;
        	char send[100]="";
        	for (i=0;i<n-1;i++)
        	{
            		strcat(send,args[i]);
            		strcat(send," ");
        	}
        	strcat(send,args[n - 1]);
        	strcpy(fore.name,send);
        	fore.status=1;
        	waitpid(-1,NULL,WUNTRACED);
    	}
    	else
    	{
        	printf("Mainshell: Error: Forking failed\n");
    	}
}
void backgrnd(char *args[], int n)
{
    	pid_t pid;
    	pid=fork();
	int i;
    	setpgid(0,0);
    	if(pid==0)
    	{
		if(execvp(args[0],args)<0)
		{
        	    	fprintf(stderr, "Error: execvp failed");
		}
        	exit(0);
    	}
    	else if(pid>0)
    	{
        	printf("[%d] %d\n",++actives,pid);
        	pids[pidcnt].pid=pid;
        	pids[pidcnt].status=1;
        	char send[100]="";
        	for(i=0;i<n-1;i++)
        	{
        		    strcat(send,args[i]);
        		    strcat(send," ");
        	}
        	strcat(send,args[n - 1]);
        	strcpy(pids[pidcnt++].name,send);	
    	}
    	else
    	{
		fprintf(stderr, "Error: Forking failed");
    	}	
}
