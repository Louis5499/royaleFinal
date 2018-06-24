#ifndef button_h
#define button_h

#include <string.h>
#include "global.h"

class button
{
public:
    button(ALLEGRO_BITMAP *img1, ALLEGRO_BITMAP *img2, int x, int y, int w, int h, int f)
    : x(x), y(y), width(w), height(h), type(f) {};
    virtual ~button(){};
    
//    void change_dir(int d){dir = d;};
//    void move();
//    void draw();
    
protected:
    ALLEGRO_BITMAP *img = NULL, *hoveredImg = NULL;
    int x = 0, y = 0;
    int width = 0, height = 0;
    int type = 0;
};


#endif /* classmates_h */
