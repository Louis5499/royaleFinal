#include "Tower.h"

class TowerSmallBlue : public Tower
{
public:
    TowerSmallBlue(int mouse_x, int mouse_y)
    : Tower(mouse_x, mouse_y,TowerWidth[SMALLBLUE]/2,TowerHeight[SMALLBLUE]/2,0)
    {
        type = SMALLBLUE;
        
        circle->r = 70;
        attack_frequency = 20;
        attack_velocity = 8;
        attack_harm_point = 5;
        img = al_load_bitmap("./tower_small_blue.png");
    }
    
    int getWidth() override { return TowerWidth[SMALLBLUE]; }
    int getHeight() override { return TowerHeight[SMALLBLUE]; }
};

