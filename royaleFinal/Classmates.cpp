#include "Classmates.h"

Classmates::Classmates(std::string str): name(str) {
    int i, j;
    char s[50], path[80];
    pos[0] = 200; pos[1] = 0;
    whichImg = 0;
    for(i=0; i<50; i++) s[i] = str[i];
    
    for(i=0; i<4; i++) for(j=0; j<3; j++) {
        sprintf(path, "./%s_%d_%d.png", s, i, j);
        img[i][j] = al_load_bitmap(path);
    }
}

void Classmates::move() {
    if((dir == up && pos[1] < 20) || (dir == left && pos[0] < 20) || (dir == down && pos[1] > 400) || (dir == right && pos[0] > 400)) dir = (dir+1)%4;
    pos[0] += vel*dir_mov[dir][0];
    pos[1] += vel*dir_mov[dir][1];
}

void Classmates::draw() {
    int num = (whichImg == 3) ? 1 : whichImg;
    al_draw_bitmap(img[dir][num], pos[0], pos[1], 0);
    whichImg = (whichImg+1)%4;
}
