/** psh1.c
 * purpose: prompting shell version 1
 * Prompts for the command and its arguments
 * Use execvp(), and never returns
 * authors: klin
 * create at: 2019-12-15
 */

#include <stdio.h>
#include <signal.h>
#include <string.h>

#define MAXARGS     20
#define ARGLEN      100

int main()
{
    char    *arglist[MAXARGS + 1];
    int     numargs;
    char    argbuf[ARGLEN];
    char    *makestring();          /* malloc etc */
    numargs = 0;
    while (numargs < MAXARGS)
    {
        printf("Arg[%d]?", numargs);
        if(fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n')
            arglist[numargs++] = makestring(argbuf);
        else
        {
            if(numargs > 0){
                arglist[numargs] = NULL;
                execute(arglist);
                numargs = 0;
            }
        }
    }
    return 0;
}

int execute(char * arglist[])
/**
 * use execvp to do it
 */
{
    execvp(arglist[0], arglist);
    perror("execvp failed");
    exit(1);
}

char * makestring(char * buf)
/**
 * trim off newline and create storage for the string
 */
{
    char *cp, *malloc();
    buf[strlen(buf) - 1] = '\0';
    cp = malloc(strlen(buf) + 1);
    if (cp == NULL) {
        fprintf(stderr, "no memory\n");
        exit(1);
    }
    strcpy(cp, buf);
    return cp;
}