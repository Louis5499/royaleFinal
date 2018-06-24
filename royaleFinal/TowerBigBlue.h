#include "Tower.h"

class TowerBigBlue : public Tower
{
public:
    TowerBigBlue(int mouse_x, int mouse_y)
    : Tower(mouse_x, mouse_y,TowerWidth[BIGBLUE]/2,TowerHeight[BIGBLUE]/2)
    {
        type = BIGBLUE;
        
        circle->r = 150;
        attack_frequency = 20;
        attack_velocity = 8;
        attack_harm_point = 5;
        img = al_load_bitmap("./tower_big_blue.png");
    }
    
    int getWidth() override { return TowerWidth[BIGBLUE]; }
    int getHeight() override { return TowerHeight[BIGBLUE]; }
};

