/*********************************************************************
Program : miniShell Version : 1.3
--------------------------------------------------------------------
skeleton code for linix/unix/minix command line interpreter
--------------------------------------------------------------------
File : minishell.c
Compiler/System : gcc/linux
********************************************************************/

/**************************************************************
 * Modify that minishell to do the following:

put commands ended by an “&”  into background mode and report when they finish. 
properly interpret the shell cd command
include an appropriate perror statement after each and every system call.
fix the minishell so that if the exec system call fails, the child process is correctly terminated
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * **********************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#define NV 20 /* max number of command tokens */
#define NL 100 /* input buffer size */
char line[NL]; /* command input buffer */
char *background_names[NV]; /* array to store background process names */

/*
shell prompt
*/
void prompt(void)
{
	//fprintf(stdout, "\n msh> ");
	fflush(stdout);
}
int main(int argk, char *argv[], char *envp[])
/* argk - number of arguments */
/* argv - argument vector from command line */
/* envp - environment pointer */
{
	int frkRtnVal; /* value returned by fork sys call */
	int wpid; /* value returned by wait */
	char *v[NV]; /* array of pointers to command line tokens */
	char *sep = " \t\n";/* command line token separators */
	int i; /* parse index */
	int backgroundCount = 1;
	/* prompt for and process one command line at a time */
	while (1) { /* do Forever */
		prompt();
		fgets(line, NL, stdin);
		fflush(stdin);
		if (feof(stdin)) { /* non-zero on EOF */
			/*fprintf(stderr, "EOF pid %d feof %d ferror %d\n", getpid(),
			feof(stdin), ferror(stdin));*/
			exit(0);
		}
		if (line[0] == '#' || line[0] == '\n' || line[0] == '\000')
			continue; /* to prompt */
		

		int background = 0;
		
		//printf("show????:%c",line[strlen(line)-2]);
		if (line[strlen(line) - 2] == '&') {
		    
		    background = 1;
		    line[strlen(line) - 2] = '\0';
		}

		v[0] = strtok(line, sep); //
		for (i = 1; i < NV; i++) {
			v[i] = strtok(NULL, sep);
			if (v[i] == NULL)
				break;
		}

		//printf("show me background:%i",background);
        if (strcmp(v[0], "cd") == 0) {
            if (v[1] == NULL) {
                fprintf(stderr, "Usage: cd <directory>\n");
            } else if (chdir(v[1]) == -1) {
                perror("chdir");
            }
            continue; 
        }

		/* assert i is number of tokens + 1 */
		/* fork a child process to exec the command in v[0] */
		switch (frkRtnVal = fork()) {
			case -1: /* fork returns error to parent process */
			{
				perror("fork");
				break;
			}
			case 0: /* code executed only by child process */
			{
				if (execvp(v[0], v) == -1) {
                    perror("execvp");
                    exit(EXIT_FAILURE);
                }
			}
			default:
                if (background) {
                    printf("[%d] %d\n", backgroundCount, frkRtnVal);
                    background_names[backgroundCount] = strdup(v[0]);
                    for (int j = 1; j < i; j++) {
                        background_names[backgroundCount] = strcat(background_names[backgroundCount], " ");
                        background_names[backgroundCount] = strcat(background_names[backgroundCount], v[j]);
                    }
                    backgroundCount++;
                } else {
                    wpid = wait(0);
                    if (wpid == -1) {
                        perror("wait");
                    } else {
                        for (int j = 1; j < backgroundCount; j++) {
                            if (waitpid(-1, NULL, WNOHANG) == wpid) {
                                printf("[%d]+ Done\t\t\t%s\n", j, background_names[j]);
                                break;
                            }
                        }
                    }
                }

                // Print Done messages for completed background processes
                for (int j = 1; j < backgroundCount; j++) {
                    if (waitpid(0, NULL, WNOHANG) == atoi(background_names[j])) {
                        printf("[%d]+ Done\t\t\t%s\n", j, background_names[j]);
                    }
                }

                break;
			} /* switch */
		} /* while */
} /* main */