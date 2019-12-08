/** bounce_async.c
 * purpose: animation with user control, using aio_read() etc
 * notes:   set_ticker() sends SIGALRM, handler does animation
 *          keyboard sends SIGIO, man only calls pause()
 * compile: gcc bounce_aio.c set_ticker.c -l curses -o bounce_aio.o
 * authors: klin
 * create at: 2019-12-08
 */


#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <fcntl.h>
#include <aio.h>

/* The state of the game */

#define MESSAGE "hello"
#define BLANK   "     "

int row     = 10;
int col     = 0;
int dir     = 1;
int delay   = 200;
int done    = 0;

struct aiocb kbcbuf;

void main()
{
    void on_alarm(int);
    void on_input(int);
    void setup_aio_buffer();

    initscr();
    crmode();
    noecho();
    clear();

    signal(SIGIO, on_input);
    setup_aio_buffer();
    aio_read(&kbcbuf);

    signal(SIGALRM, on_alarm);
    set_ticker(delay);

    mvaddstr(row, col, MESSAGE);

    while (! done)
        pause();

    endwin();
}

void on_input(int signum) {
    int c;

    char *cp = (char *) kbcbuf.aio_buf;

    if (aio_error(&kbcbuf) != 0)
        perror("reading failed");
    else
        if (aio_return(&kbcbuf) == 1) {
            c = *cp;
            if (c == 'Q' || c == EOF)
                done = 1;
            else if (c == ' ')
                dir = -dir;
        }
    aio_read(&kbcbuf);
}

void on_alarm(int signum) {
    signal(SIGALRM, on_alarm);
    mvaddstr(row, col, BLANK);
    col += dir;
    mvaddstr(row, col, MESSAGE);
    refresh();

    /**
     * now handle borders
     */
    if ( dir == -1 && col <= 0)
        dir = 1;
    else if (dir == 1 && col + strlen(MESSAGE) >= COLS)
        dir = -1;
}

void setup_aio_buffer() {
    static char input[1];

    kbcbuf.aio_fildes   = 0;
    kbcbuf.aio_buf      = input;
    kbcbuf.aio_nbytes   = 1;
    kbcbuf.aio_offset   = 0;

    kbcbuf.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    kbcbuf.aio_sigevent.sigev_signo = SIGIO;
}
