/** my_bounce2d.c
 * purpose: inherit from bounce2d and add follow features:
 *      1. add boundaries
 *      2. add dam-board
 *      3. ball lose check
 *      4. damper move
 *      5. scoring
 * method:
 * build: gcc my_bounce2d.c set_ticker.c -lcurses -o my_bounce2d
 *        if build failed, it may cause by duplicate build 'set_ticker.c', just remove 'set_ticker.c'
 * authors: klin
 * create at: 2019-12-08
 */

#include <curses.h>
#include <signal.h>
#include "my_bounce.h"
#include "set_ticker.c"

struct ppball the_ball;
struct dam_board the_dam;

int score = 0;

void set_up();
void wrap_up();
void print_prompt();
void move_dam(int);
void draw_dam(struct dam_board *);
void draw_boundaries();
void refresh_score();
int calc_score();
int bounce_or_lose(struct ppball *);

int main() {
    int c;

    set_up();

    while ((c = getchar()) != 'Q') {
        if (c == 'f')    the_ball.x_ttm--;
        else if (c == 's') the_ball.x_ttm++;
        else if (c == 'F') the_ball.y_ttm--;
        else if (c == 'S') the_ball.y_ttm++;
        else if (c == 'u') move_dam(1);
        else if (c == 'd') move_dam(-1);
    }
    wrap_up();
}

// init structure and other stuff
void set_up() {
    void ball_move(int);

    // init ball
    the_ball.y_pos = Y_INIT;
    the_ball.x_pos = X_INIT;
    the_ball.y_ttg = the_ball.y_ttm = Y_TTM;
    the_ball.x_ttg = the_ball.x_ttm = X_TTM;
    the_ball.y_dir = the_ball.x_dir = 1;
    the_ball.symbol = DFL_SYMBOL;

    // init dam
    the_dam.y_pos = DAM_INIT_POS;
    the_dam.x_pos = RIGHT_EDGE + 1;
    the_dam.len = DAM_LEN;

    initscr();
    noecho();
    crmode();
    print_prompt();
    draw_dam(&the_dam);
    draw_boundaries();
    refresh_score();

    signal(SIGINT, SIG_IGN);
    mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
    refresh();

    signal(SIGALRM, ball_move);
    set_ticker(1000 / TICKS_PER_SEC);
}

void wrap_up() {
    set_ticker(0);
    endwin();
}

void print_prompt() {
    move(0, LEFT_EDGE);
    addstr("Ping-Pong Game");
    move(1, LEFT_EDGE);
    addstr("press 'u' to move dam-board UP");
    move(2, LEFT_EDGE);
    addstr("press 'd' to move dam-board DOWN");
    move(3, LEFT_EDGE);
    addstr("press 'Q' to Quit game");
    move(3, RIGHT_EDGE - 18);
    addstr("Your score: ");
    refresh();
}

void ball_move(int signum) {
    int y_cur, x_cur, moved;

    signal(SIGALRM, SIG_IGN);
    y_cur = the_ball.y_pos;
    x_cur = the_ball.x_pos;
    moved = 0;

    if (the_ball.y_ttm > 0 & the_ball.y_ttg-- == 1) {
        the_ball.y_pos += the_ball.y_dir;
        the_ball.y_ttg = the_ball.y_ttm;
        moved = 1;
    }

    if (the_ball.x_ttm > 0 && the_ball.x_ttg-- == 1) {
        the_ball.x_pos += the_ball.x_dir;
        the_ball.x_ttg = the_ball.x_ttm;
        moved = 1;
    }

    if (moved) {
        mvaddch(y_cur, x_cur, BLANK);
        mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
        int b_or_l = bounce_or_lose(&the_ball);
        if (b_or_l < 0) {
            // TO_DO: warning and quit game
            exit(-1);
        }
        move(LINES - 1, COLS - 1);
        refresh();
    }
    signal(SIGALRM, ball_move);
}

void draw_dam(struct dam_board *dam) {
    for (int i = dam->y_pos; i < dam->y_pos + dam->len; ++i) {
        mvaddch(i, dam->x_pos, DAM_FILL_SYM);
    }
    refresh();
}

/**
 * move dam-board
 * @param direction     1  = up
 *                      -1 = down
 *                      0  = default
 */
void move_dam(int direction) {
    switch (direction) {
        case 1:
            if (the_dam.y_pos <= TOP_ROW) {
                break;
            }
            the_dam.y_pos--;
            mvaddch(the_dam.y_pos + the_dam.len, the_dam.x_pos, BLANK);
            mvaddch(the_dam.y_pos, the_dam.x_pos, DAM_FILL_SYM);
            refresh();
            break;
        case -1:
            if ( the_dam.y_pos + the_dam.len > BOT_ROW) {
                break;
            }
            the_dam.y_pos++;
            mvaddch(the_dam.y_pos - 1, the_dam.x_pos, BLANK);
            mvaddch(the_dam.y_pos + the_dam.len - 1, the_dam.x_pos, DAM_FILL_SYM);
            refresh();
            break;
    }
}

int bounce_or_lose(struct ppball *bp) {
    int return_val = 0;
    if (bp->y_pos == TOP_ROW) {
        bp->y_dir = 1;
        return_val = 1;
    } else if (bp->y_pos == BOT_ROW) {
        bp->y_dir = -1;
        return_val = 1;
    }

    if (bp->x_pos == LEFT_EDGE) {
        bp->x_dir = 1;
        return_val = 1;
    } else if (bp->x_pos == RIGHT_EDGE) {
        if (bp->y_pos < the_dam.y_pos || bp->y_pos >= the_dam.y_pos + the_dam.len) {
            return_val = -1;
        } else {
            bp->x_dir = -1;
            return_val = 1;
            calc_score();
            refresh_score();
        }
    }

    return return_val;
}

void draw_boundaries() {
    mvaddch(TOP_ROW - 1, LEFT_EDGE - 1, ACS_ULCORNER);
//    mvaddch(TOP_ROW - 1, RIGHT_EDGE + 1, ACS_URCORNER);
    mvaddch(BOT_ROW + 1, LEFT_EDGE - 1, ACS_LLCORNER);
//    mvaddch(BOT_ROW + 1, RIGHT_EDGE + 1, ACS_LRCORNER);
    // draw top and bottom
    for (int i = LEFT_EDGE; i < RIGHT_EDGE + 1; ++i) {
        mvaddch(TOP_ROW - 1, i, ACS_HLINE);       // top
        mvaddch(BOT_ROW + 1, i, ACS_HLINE);       // bottom
    }
    // draw left and right
    for (int j = TOP_ROW; j < BOT_ROW + 1; ++j) {
        mvaddch(j, LEFT_EDGE - 1, ACS_VLINE);     // left
//        mvaddch(j, RIGHT_EDGE + 1, ACS_VLINE);    // right
    }
    refresh();
}

void refresh_score() {
    char scr_str[10];
    sprintf(scr_str, "%d", score);
    move(3, RIGHT_EDGE - 6);
    addstr(scr_str);
    refresh();
}

int calc_score() {
    if (the_ball.y_pos == the_dam.y_pos || the_ball.y_pos == the_dam.y_pos + the_dam.len - 1) {
        score += 1;
    } else if (the_ball.y_pos == the_dam.y_pos + the_dam.len / 2) {
        score += 4;
    } else {
        score += 2;
    }

    return score;
}