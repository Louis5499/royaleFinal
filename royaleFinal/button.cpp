#include "button.h"

button::button(const char *name, int x, int y, int w, int h, int f): x(x), y(y), width(w), height(h), type(f)
{
    int i;
    char buffer[50];
    for(i=0; i<50; i++) { buffer[i] = name[i]; n[i] = name[i];}
    
    sprintf(buffer, "./%s.png", name);
    img = al_load_bitmap(buffer);
    sprintf(buffer, "./hovered_%s.png", name);
    hoveredImg = al_load_bitmap(buffer);
    drawImg = img;
}

bool
button::isHovered(int mouseX, int mouseY)
{
    if((type == square && mouseX >= x - width/2 && mouseX <= x + width/2 && mouseY >= y - height/2 && mouseY <= y + height/2) || (type == roundType && ((x - mouseX)*(x - mouseX) + (y - mouseY)*(y - mouseY) <= width*width))) {
            hover();
        return true;
    }
    return false;
}

void
button::draw()
{
    if(type == square) al_draw_bitmap(drawImg, x - width/2, y - height/2, 0);
    else al_draw_bitmap(drawImg, x - width, y - height, 0);
}
