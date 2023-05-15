#include "headers.h"
void piping(char word[])
{
	char *tokens[100];
	int num=splitter(tokens,word,"|");
    	int in=0,i,out=1;
    	for(i=0;i<num;i++)
    	{
        	int p[2];
       		pipe(p);
        	pid_t pid=fork();
        	if(pid==0)
		{
            		dup2(in,0);
            		if(i!=num - 1)
			{
                		dup2(p[1],1);
			}
            		close(p[0]);
            		char ops[5][5];
            		int c=checkredir(tokens[i],ops);
            		if(c!=0)
            		{
                		redirect(tokens[i],ops,c); 
            		}
            		else execbuiltin(tokens[i]);
            		exit(1);	
        	}
		else if(pid>0)
        	{
			wait(NULL);
            		close(p[1]);
            		out=p[1];
            		in=p[0];
        	}
        	else
        	{
            		fprintf(stderr, "Error in forking");
        	}
    	}
}
