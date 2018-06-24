#ifndef classmates_h
#define classmates_h

#include <string.h>
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
