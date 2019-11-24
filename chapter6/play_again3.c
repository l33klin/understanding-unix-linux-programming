/* play_again3.c
 * purpose: ask if user wants another transaction
 * method: set tty into char-by-char mode,
 *         set tty into no-delay mode
 *         read char, return result
 * returns: 0=>yes, 1=>no
 * better: reset terminal mode no Interrupt
 * authors: klin
 * create at: 2019-11-24
 */


#include <stdio.h>
#include <termios.h>
#include <fcntl.h>      // control
#include <string.h>

#define QUESTION "Do you want another transaction"
#define TRIES 3
#define SLEEPTIME 2
#define BEEP putchar('\a')

int main() {
    int response;
    tty_mode(0);                                /* save tty mode */
    set_cr_noecho_mode();                       /* set chr-by-chr mode */
    set_nodelay_mode();                         /* set no delay mode */
    response = get_response(QUESTION, TRIES);   /* get some answer */
    tty_mode(1);                                /* restore tty mode */
    return response;
}

int get_response(char *question, int maxtries) {
    int input;
    printf("%s (y/n)?", question);
    fflush(stdout);
    while(1){
        sleep(SLEEPTIME);
        input = tolower(get_ok_char());
        if(input == 'y')
            return 0;
        if(input == 'n')
            return 1;
        if(maxtries-- == 0)
            return 2;
        BEEP;
    }
}

get_ok_char()
{
    int c;
    while((c = getchar()) != EOF && strchr("yYnN", c) == NULL);
    return c;
}

set_cr_noecho_mode()
/*
 * purpose: put file description 0 (i.e. stdin) into chr-by-chr and no echo mode
 * method: use bits in termios
 */
{
    struct termios tty_state;
    tcgetattr(0, &tty_state);            /* read curr. settings */
    tty_state.c_lflag &= ~ICANON;        /* no buff */
    tty_state.c_lflag &= ~ECHO;          /* no echo either */
    tty_state.c_cc[VMIN] = 1;            /* get 1 char at a time */
    tcsetattr(0, TCSANOW, &tty_state);   /* install settings*/
}

set_nodelay_mode()
/*
 * purpose: put file description 0 into no-delay mode
 * method: use fctnl to set bits
 * notes: tcsetattr will do something similar, but it is complicated
 */
{
    int termflags;
    termflags = fcntl(0, F_GETFL);      /* read curr. settings */
    termflags |= O_NDELAY;              /* flip on no delay bit */
    fcntl(0, F_SETFL, termflags);       /* and install settings */
}

int tty_mode(int how)
/* how==0 => save current mode, how==1 => restore mode*/
{
    static struct termios original_mode;
    static int original_flags;
    if (how == 0) {
        tcgetattr(0, &original_mode);
        original_flags = fcntl(0, F_GETFL);
    } else {
        tcsetattr(0, TCSANOW, &original_mode);
        fcntl(0, F_SETFL, original_flags);
    }
}

