# Interactive-User-Defined-Shell
A project to design &amp; implement a Interactive User Defined Shell, consisting commands like cd, echo, pwd, ls, pinfo, setenv, unsetenv, fg, bg, kjo, CTRL+C, CTRL+Z etc.
## How to compile and run
- compile : make 
- run : ./main
## How to exit from the shell
- exit : type 'exit' to exit from the shell
## shell loop
- in mainshell.c
## Built-In Commands
### cd 
- in cd.c
- The cd command changes directory to the directory specified.(path may be relative or absolute)
- "cd .." : goes to previous directory
- "cd ." : Nothing happens. Goes to the present directory
- "cd ~" : changes directory to the home directory 
### echo 
- in echo.c
- "echo" : prints empty line
- "echo text" : prints the text as it is
### pwd
- in pwd.c
- Show present working directory.
## ls
- in ls.c	
- "ls" : prints/lists all files and directories in current working directory in order
- "ls -a" : displays hidden files
- "ls -l" : long list
- "ls -al"/"ls -la"/"ls -l -a"/"ls -a -l" : long list including hidden files
## pinfo
- in pinfo.c
- At most one argument can be provided
- If no argument provided, takes pid of the current process and displays info about it
- If pid is provided in argument, displays info about that pid
## history
- in history.c
- Displays the last 'number' commands (If number is provided and also number can be less than or equal to 10)
- If 'number'>10, prints last 10 commands
- same command continuosly will be printed only once
- If no number is provide as argument, it prints last 10 commands
## headers.h
- Contains all the required header files, global variables and function declarations
## history.txt
- a file to store the past commands(Stores 20 commands at max)
## setenv
- in env.c
- Sets value of environment variable 'var' to 'value'
- If 'value' is not given then sets 'value' to empty string
- Accepts one or two arguments only
## unsetenv 
- in env.c
- Destroys all environment variables 'var1','var2' etc given as argument
- At least one argument
## fg
- in fgbg.c
- Brings running or stopped background job to foreground with the given job number
## bg
- in fgbg.c
- Changes stopped background job to running background job
## overkill
- in jobs.c
- Kills all background process
## jobs
- in jobs.c
- Prints list of all currently running jobs along with pid, in particular, background jobs, in order of their creation along with their state
## kjob 
- in jobs.c
- Takes job id of a running job and sends signal value to that process
## CTRL-C 
- in ctrl+(c)(z).c
- It changes status of currently running job to stop, and pushes it into background process.
## CTRL-Z
- in ctrl+(c)(z).c
- It causes SIGINT signal to be sent to current foreground job of shell
## pipe.c
## redir.c
