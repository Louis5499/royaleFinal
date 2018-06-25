
#include "Tower.h"

class TowerBigRed : public Tower
{
public:
    TowerBigRed(int mouse_x, int mouse_y)
    : Tower(mouse_x, mouse_y,TowerWidth[BIGRED]/2,TowerHeight[BIGRED]/2,1)
    {
        type = BIGRED;
        
        circle->r = 150;
        attack_frequency = 20;
        attack_velocity = 8;
        attack_harm_point = 5;
        img = al_load_bitmap("./tower_big_red.png");
    }
    
    int getWidth() override { return TowerWidth[BIGRED]; }
    int getHeight() override { return TowerHeight[BIGRED]; }
};

