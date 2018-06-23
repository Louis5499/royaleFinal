#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#define font_size 12
#define grid_width 40
#define grid_height 40

#define window_width 800
#define window_height 600
#define field_width 600
#define field_height 600

enum {up = 0, left, down, right};
enum {EDWARD = 0, MOMO, ACC, ZHENGYEN, CGHG, JACKY};

extern int dir_mov[4][2];

#endif // GLOBAL_H_INCLUDED
