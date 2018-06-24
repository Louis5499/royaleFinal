#ifndef button_h
#define button_h

#include <string.h>
#include "global.h"

class button
{
public:
    button(const char *name, int x, int y, int w, int h, int f);
    virtual ~button(){};
    
    bool isHovered(int, int);
    void hover(){drawImg = hoveredImg;};
    void notHover(){drawImg = img;};
    void draw();
    
protected:
    ALLEGRO_BITMAP *img = NULL, *hoveredImg = NULL, *drawImg = NULL;
    
    int x = 0, y = 0; //center
    int width = 0, height = 0;
    int type = 0;
    bool hovered = false;
};


#endif /* button_h */
