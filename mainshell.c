#include "headers.h"
int splitter(char *tokens[], char *line, char *delim)
{
  	int num=0;
  	tokens[num]=strtok(line, delim);
  	while(tokens[num]!=NULL)
  	{
    		tokens[++num]=strtok(NULL, delim);
  	}
  	tokens[num]=NULL;
  	return num;
}
int checkredir(char word[], char ops[5][5])
{
  	int c=0,i;
  	for(i=0;i<strlen(word);i++)
  	{
    		if(word[i]=='>'&&(i+1)<strlen(word) && word[i+1]=='>')
    		{
      			strcpy(&ops[c++][0], ">>");
      			i=i+1;
    		}
    		else if(word[i]=='>')
		{
      			strcpy(&ops[c++][0],">");
		}
		else if(word[i]=='<')
		{
      			strcpy(&ops[c++][0],"<");
		}
  	}
  	return c;
}
int checkpipe(char word[])
{
  	int c=0,i;
  	for(i=0;i<strlen(word);i++)
  	{
    		if(word[i]=='|')
		{
      			c++;
		}
  	}
  	return c;
}
int execbuiltin(char word[])
{
  	char *args[100];
  	int n=splitter(args, word, " \n\r\t");
  	if(n<1)
	{
    		return 0;
	}
  	else if(strcmp("cd",args[0])==0)
  	{
    		if(strcmp("&",args[n-1])==0)
		{
      			n=n-1;
		}
		cd(args, n);
  	}
  	else if(strcmp("pwd",args[0])==0)
  	{
    		if(strcmp("&",args[n-1])==0)
		{
      			n=n-1;
		}
    		pwd(n);
  	}
  	else if(strcmp("echo",args[0])==0)
  	{
    		if(strcmp("&",args[n-1])==0)
		{
      			n=n-1;
		}
    		echo(args,n);
  	}
  	else if(strcmp("ls",args[0])==0)
  	{
    		if(strcmp("&",args[n-1])==0)
		{
      			n=n-1;
		}
    		ls(args,n);
  	}
  	else if(strcmp("pinfo",args[0])==0)
  	{
    		if(strcmp("&",args[n-1])==0)
		{
      			n=n-1;
		}
    		pinfo(args,n);
  	}
  	else if(strcmp("history",args[0])==0)
  	{
    		if(strcmp("&",args[n-1])==0)
		{
      			n=n-1;
		}
    		historydisp(args,n);
  	}
	else if(strcmp("exit",args[0])==0 || strcmp("quit",args[0])==0 )
  	{
    		if(strcmp("&",args[n-1])==0)
		{
      			n=n-1;
		}
    		if(n>1)
		{
      			printf("Mainshell : exit: Too many arguments\n");
		}
    		else
    		{
      			overkill(NULL,1);
     	 		return 1;
    		}
  	}
  	else if(strcmp("setenv",args[0])==0)
  	{
    		if(strcmp("&",args[n-1])==0)
		{
      			n=n-1;
		}
    		senv(args,n);
  	}
  	else if(strcmp("jobs",args[0])==0)
  	{
    		if(strcmp("&",args[n-1])==0)
		{
      			n=n-1;
		}
    		jobs(args,n);
  	}
  	else if(strcmp("unsetenv",args[0])==0)
  	{
    		if(strcmp("&",args[n-1])==0)
		{ 
			n=n-1;
		}
    		unsenv(args,n);
  	}
  	else if(strcmp("overkill",args[0])==0)
  	{
    		if(strcmp("&",args[n-1])==0)
		{
      			n=n-1;
		}
    		overkill(args,n);
  	}
  	else if(strcmp("kjob",args[0])==0)
  	{
    		if(strcmp("&",args[n-1])==0)
		{
			n=n-1;
		}
    		kjob(args,n);
  	}
  	else if(strcmp("fg",args[0])==0)
  	{
    		if(strcmp("&",args[n-1])==0)
		{
			n=n-1;
		}
    		fg(args,n);
  	}
  	else if(strcmp("bg",args[0])==0)
  	{
    		if(strcmp("&",args[n-1])==0)
		{ 
			n=n-1;
		}
    		bg(args,n);
  	}
  	else if(strcmp("&",args[n-1])==0)
  	{
    		n=n-1;
    		backgrnd(args,n);
  	}
  	else
  	{
    		foregrnd(args,n);
  	}
  	return 0;
}
void mainloop()
{
  	while (1)
  	{
    		signal(SIGCHLD,child_sig);
    		signal(SIGTSTP,ctrlzhandler);
    		signal(SIGINT,ctrlchandler);
    		tildconvertedpwd(tild);
    		char *line=NULL;
    		size_t bufsize=0;
    		getline(&line,&bufsize,stdin);
    		char *tokens[100];
    		int now,num=splitter(tokens,line,";");
    		for(now=0;now<num;now++)
    		{
      			historyadd(tokens[now]);
      			int p=checkpipe(tokens[now]);
      			if(p!=0)
      			{
        			piping(tokens[now]);
        			continue;
      			}
      			char ops[5][5];
      			int c=checkredir(tokens[now],ops);
      			if(c!=0)
      			{
        			redirect(tokens[now],ops,c);
        			continue;
      			}
      			if(execbuiltin(tokens[now])==1)
      			{
        			free(line);
        			return;
      			}
    		}
    		free(line);
  	}
}
int main(int argc, char **argv)
{
  	pidcnt=0;
  	actives=0;
  	shellPID=getpid();
  	fore.status=0;
  	getcwd(tild,FILENAME_MAX);
  	strcat(tild,&argv[0][1]);
  	tild[strlen(tild)-5]='\0';
  	if(gethostname(hostbuffer,sizeof(hostbuffer))!=0)
  	{
    		printf("Mainshell : Unable to get hostname\n");
    		strcpy(hostbuffer,"HOSTNAME");
  	}
  	if(getlogin_r(namebuffer,sizeof(namebuffer))!=0)
  	{
    		printf("Mainshell : Unable to get username\n");
    		strcpy(namebuffer,"USERNAME");
  	}
  	historyinit();
  	mainloop();
  	historyexit();
	return 0;
}
