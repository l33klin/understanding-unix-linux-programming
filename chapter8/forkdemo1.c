/** forkdemo1.c
 * purpose: shows how fork creates two processes, distinguishable
 * by the different return values from fork
 * returns: 
 * authors: klin
 * create at: 2019-12-15
 */

#include <stdio.h>

main()
{
    int ret_from_fork, mypid;
    mypid = getpid();
    printf("Before: my pid is %d\n", mypid);

    ret_from_fork = fork();

    sleep(1);
    printf("After fork: my pid is %d, fork() said %d\n",
            getpid(), ret_from_fork);
}