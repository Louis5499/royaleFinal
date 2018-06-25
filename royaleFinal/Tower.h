#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED

class Classmates;
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Object.h"
#include "Attack.h"
#include "Circle.h"
#include "Classmates.h"
#include "global.h"
#include <vector>

class Tower : public Object
{
public:
    Tower(int, int, int, int, int);
    virtual ~Tower();
    
    // override virtual function "Object::Draw"
    void draw();
    void resetAttackCounter() { attack_counter = 0; }
    void ToggleClicked() { isClicked = !isClicked; }
    int getHealthPoint() { return HealthPoint; }
    
    // update whole attack set
    // if any attack goes out of the range of tower, delete it
    void UpdateAttack();
    // detect if tower needs to attack some monster
    bool DetectAttack(Classmates*);
    // process if some of attack in set touches monster
    bool TriggerAttack(Classmates*);
    
    virtual int getWidth() { return 40; }
    virtual int getHeight() { return 40; }
    
    // show selected tower image on cursor position
    static void SelectedTower(int, int, int);
    
    bool Subtract_HP(int);
    
    int whichSide = 0; // 0->blue , 1->red
    int type;
    std::vector<Attack*> attack_set;
    
protected:
    // setting of attack
    int attack_frequency = 20;
    int attack_counter = 0;
    int attack_harm_point = 5;
    int attack_velocity = 10;
    
    int img_posX;
    int img_posY;
    ALLEGRO_BITMAP *attack_img = al_load_bitmap("./meteor.png");
    
    // information of tower
    
    bool isClicked = false;
    Classmates *a = NULL;
    ALLEGRO_BITMAP *img;
    
    int HealthPoint = 100;
    
    int num=0;
    
};

#endif // TOWER_H_INCLUDED
