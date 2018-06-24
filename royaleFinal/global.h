#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <vector>

#define font_size 12
#define grid_width 40
#define grid_height 40

#define window_width 1500
#define window_height 900
#define field_width 1500
#define field_height 700

enum {up = 0, left, down, right};
enum {EDWARD = 0, MOMO, ACC, ZHENGYEN, CGHG, JACKY};
enum TowerType{SMALLBLUE = 0, SMALLRED, BIGBLUE, BIGRED}; // Tower
enum {leftup = 0, centre};

extern int dir_mov[4][2];
extern int TowerWidth[];
extern int TowerHeight[];
extern int TowerRadius[];

extern int cmRadius[6];
extern int cmAttack[6];
extern int cmHealth[6];
extern int cmVelocity[6];

#endif // GLOBAL_H_INCLUDED
