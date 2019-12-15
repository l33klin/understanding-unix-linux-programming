/** 8.10.c
 * purpose: practice for 8.10
 *  accept a integer argument as number of child process
 *  sleep 5 seconds in each child then exit
 *  set a handler for SIGCHLD signal, to wait and count child number
 *  if count reach to the number of created processes then quit main process
 * authors: klin
 * create at: 2019-12-15
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define DELAY 5

int child_num;

void sig_child_handler(int);

int main(int argc, char **argv)
{
    printf("argc: %d\n", argc);
    for (int j = 0; j < argc; ++j) {
        printf("argc[%d]: %s\n", j, argv[j]);
    }

    void child_code(int);

    signal(SIGCHLD, sig_child_handler);

    if (argc > 2) {
        printf("too many arguments: %d\n", argc);
        exit(2);
    }

    child_num = strtol(argv[1],NULL,0);     //Ref: https://en.cppreference.com/w/c/string/byte/strtol

    printf("will create %d child soon.\n", child_num);

    int fork_rv;
    for (int i = 0; i < child_num; ++i) {
        fork_rv = fork();
        switch (fork_rv){
            case -1:
                perror("fork failed");
                exit(1);
            case 0:
                child_code(DELAY);
            default:
                printf("create child pid: %d\n", fork_rv);
                break;
        }
    }
    while (1)
        pause();
}

/**
 * new process takes a nap and then exits
 */
void child_code(int delay)
{
    printf("child %d here. will sleep for %d seconds\n", getpid(), delay);
    sleep(delay);
    printf("child done. about to exit\n");
    exit(17);
}

/**
 *
 */
void sig_child_handler(int sig)
{
    signal(SIGCHLD, sig_child_handler);
    static int child_count;
    child_count++;
    printf("receive SIGCHLD signal, child count: %d\n", child_count);

    int exit_status, wait_rv;
    wait_rv = wait(&exit_status);
    if (wait_rv == -1) {
        printf("no alive child to wait.\n");
        exit(1);
    }else
        printf("child %d exit with signals %d, %d\n",
                wait_rv, exit_status >> 8, exit_status & 0x7F);
    if(child_count == child_num)
        exit(0);
}