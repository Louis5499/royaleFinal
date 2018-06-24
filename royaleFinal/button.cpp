#include "button.h"

button::button(const char *name, int x, int y, int w, int h, int f): x(x), y(y), width(w), height(h), type(f)
{
    int i;
    char buffer[50];
    for(i=0; i<50; i++) buffer[i] = name[i];
    
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
        printf("* x: %d, y: %d, mousex: %d, mousey: %d, d: %d, r: %d\n", x, y, mouseX, mouseY, (x - mouseX)*(x - mouseX) + (y - mouseY)*(y - mouseY), width*width);
        return true;
    }
    printf("type: %d, x: %d, mousex: %d, dest: %d, r: %d\n", type, x, mouseX, (x - mouseX)*(x - mouseX) + (y - mouseY)*(y - mouseY), width*width);
    notHover();
    return false;
}

void
button::draw()
{
    al_draw_bitmap(drawImg, x - width, y - height, 0);
}
