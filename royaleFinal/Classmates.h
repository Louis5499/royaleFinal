#ifndef classmates_h
#define classmates_h

#include <stdio.h>
#include <string.h>
//#include <allegro5/allegro.h>
//#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_font.h>
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_primitives.h>
#include "global.h"

class Classmates
{
public:
    Classmates(std::string);
    virtual ~Classmates(){};
    
    void change_dir(int d){dir = d;};
    void move();
    void draw();
    
protected:
    ALLEGRO_BITMAP *img[4][3];
    std::string name;
    int vel = 5;
    int dir = up;
    int pos[2];
    int whichImg;
};


#endif /* classmates_h */