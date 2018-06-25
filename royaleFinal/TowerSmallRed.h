#include "Tower.h"

class TowerSmallRed : public Tower
{
public:
    TowerSmallRed(int mouse_x, int mouse_y)
    : Tower(mouse_x, mouse_y,TowerWidth[SMALLRED]/2,TowerHeight[SMALLRED]/2,1)
    {
        type = SMALLRED;
        
        circle->r = 70;
        attack_frequency = 20;
        attack_velocity = 8;
        attack_harm_point = 5;
        img = al_load_bitmap("./tower_small_red.png");
    }
    
    int getWidth() override { return TowerWidth[SMALLRED]; }
    int getHeight() override { return TowerHeight[SMALLRED]; }
};
