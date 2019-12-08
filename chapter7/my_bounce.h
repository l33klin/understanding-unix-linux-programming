//
// Created by Klin on 2019-12-08.
//

// some setting for the game
#ifndef BOUNCE_H
#define BOUNCE_H
#define BLANK        ' '
#define DFL_SYMBOL   'O'
#define TOP_ROW       5
#define BOT_ROW       20
#define LEFT_EDGE     10
#define RIGHT_EDGE    70
#define X_INIT        10
#define Y_INIT        10
#define TICKS_PER_SEC 50

#define DAM_INIT_POS  10
#define DAM_LEN       5
#define DAM_FILL_SYM  ACS_VLINE

#define X_TTM         3
#define Y_TTM         4

// the ping pong ball

struct ppball {
    int y_pos, x_pos,
            y_ttm, x_ttm,
            y_ttg, x_ttg,
            y_dir, x_dir;
    char symbol;
};

struct dam_board {
    int y_pos, x_pos, len;
};

#endif
