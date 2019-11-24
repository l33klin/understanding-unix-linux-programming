/* sleep1.c
 * purpose: show how alarm works
 * method:
 * returns: 
 * authors: klin
 * create at: 2019-11-24
 */

#include <stdio.h>
#include <signal.h>

#define SHHHH

main()
{
    void wakeup();

    printf("about to sleep for 4 seconds\n");
    signal(SIGALRM, wakeup);
    alarm(4);
    pause();                        /* freeze here util some signal */
    printf("Morning so soon?\n");
}

void wakeup(int signum)
{
#ifdef SHHHH
    printf("Alarm received from kernel\n");
#endif
}