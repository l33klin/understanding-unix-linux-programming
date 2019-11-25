/* ticker_demo.c
 * purpose: demonstrates use of interval to generate regular
 *          signals, which are in turn caught and use to count down
 * method:
 * returns: 
 * authors: klin
 * create at: 2019-11-26
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>

int main()
{
    void countdown(int);

    signal(SIGALRM, countdown);
    if (set_ticker(500) == -1)
        perror("set_ticker");
    else
        while (1)
            pause();
    return 0;
}

void countdown(int signum)
{
    static int num = 10;
    printf("%d..", num --);
    fflush(stdout);
    if (num < 0){
        printf("Done!\n");
        exit(0);
    }
}

int set_ticker(int n_msecs)
/**
 *
 * @param n_msecs
 * @return
 */
{
    struct itimerval new_timeset;
    long n_secs, n_usecs;

    n_secs = n_msecs / 1000;
    n_usecs = (n_msecs % 1000) * 1000L;

    new_timeset.it_interval.tv_sec = n_secs;
    new_timeset.it_interval.tv_usec = n_usecs;

    new_timeset.it_value.tv_sec = n_secs;
    new_timeset.it_value.tv_usec = n_usecs;

    return setitimer(ITIMER_REAL, &new_timeset, NULL);
}