/**
 * bounce a character (default is 'o') around the screen
 * defined by some parameters
 *
 * user input: s slow down x component, S: slow y component
 *             f speed up x component, F: speed y component
 *             Q quit
 *
 * blocks on read, but timer tick sends SIGALRM caught by ball_move
 * build: gcc bounce2d.c set_ticker.c -lcurses -o bounce2d
 */

#include <curses.h>
#include <signal.h>
#include "bounce.h"

struct ppball the_ball;

void set_up();
void wrap_up();

int main() {
  int c;

  set_up();

  while ((c = getchar()) != 'Q') {
    if (c == 'f')    the_ball.x_ttm--;
    else if (c == 's') the_ball.x_ttm++;
    else if (c == 'F') the_ball.y_ttm--;
    else if (c == 'S') the_ball.y_ttm++;
  }
  wrap_up();
}

// init structure and other stuff
void set_up() {
  void ball_move(int);

  the_ball.y_pos = Y_INIT;
  the_ball.x_pos = X_INIT;
}
