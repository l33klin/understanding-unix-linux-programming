//
// Created by Klin on 2019-11-17.
//


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>

int main()
{
    struct termios info;
    int rv;

    rv = tcgetattr(STDIN_FILENO, &info);
    if (rv == -1){
      perror("tcgetattr");
      exit(1);
    }
    if(info.c_lflag & ECHO)
      printf("echo is ON\n");
    else
      printf("echo is OFF\n");
}
