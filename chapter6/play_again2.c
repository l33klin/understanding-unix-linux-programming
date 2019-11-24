/* play_again2.c
 * purpose: ask if user wants another transaction
 * method: set tty into char-by-char mode, read char, return result
 * returns: 0=>yes, 1=>no
 * better: timeout if user walks away
 * authors: klin
 * create at: 2019-11-24
 */


#include <stdio.h>
#include <termios.h>

#define QUESTION "Do you want another transaction"

int main() {
    int response;
    tty_mode(0);                        /* save tty mode */
    set_cr_noecho_mode();                       /* set chr-by-chr mode */
    response = get_response(QUESTION);  /* get some answer */
    tty_mode(1);                        /* restore tty mode */
    return response;
}

int get_response(char *question) {
    int input;
    printf("%s (y/n)?", question);
    while(1){
        switch( input = getchar()){
            case 'y':
            case 'Y':
                return 0;
            case 'n':
            case 'N':
            case EOF:
                return 1;
        }
    }
}

set_cr_noecho_mode()
/*
 * purpose: put file description 0 (i.e. stdin) into chr-by-chr and no echo mode
 * method: use bits in termios
 */
{
    struct termios ttystate;
    tcgetattr(0, &ttystate);            /* read curr. settings */
    ttystate.c_lflag &= ~ICANON;        /* no buff */
    ttystate.c_lflag &= ~ECHO;          /* no echo either */
    ttystate.c_cc[VMIN] = 1;            /* get 1 char at a time */
    tcsetattr(0, TCSANOW, &ttystate);   /* install settings*/
}

int tty_mode(int how)
/* how==0 => save current mode, how==1 => restore mode*/
{
    static struct termios original_mode;
    if (how == 0) {
        tcgetattr(0, &original_mode);
    } else {
        return tcsetattr(0, TCSANOW, &original_mode);
    }
}

