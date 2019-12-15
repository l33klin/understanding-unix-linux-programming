/** forkdemo2.c
 * purpose: shows how child processes pick up at the return
 *          from fork() and can execute any code they like,
 *          even fork(), Predict number of lines of output.
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
    printf("After fork 1 times: my pid is %d, fork() said %d\n",
           getpid(), ret_from_fork);

    ret_from_fork = fork();
    printf("After fork 2 times: my pid is %d, fork() said %d\n",
           getpid(), ret_from_fork);

    ret_from_fork = fork();
    printf("After fork 3 times: my pid is %d, fork() said %d\n",
           getpid(), ret_from_fork);
}