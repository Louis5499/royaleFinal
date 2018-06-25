#include "Tower.h"
#include <iostream>

Tower::Tower(int _img_posX,int _img_posY,int _offsetX,int _offsetY,int _whichSide)
{
    this->circle = new Circle(_img_posX+_offsetX,_img_posY+_offsetY, 70);
    img_posX = _img_posX;
    img_posY = _img_posY;
    
    whichSide = _whichSide;
}

Tower::~Tower()
{
    delete circle;
    
    al_destroy_bitmap(img);
    al_destroy_bitmap(attack_img);
    
    for(auto&& child : this->attack_set) {
        delete child;
    }
    this->attack_set.clear();
}

void
Tower::draw()
{
    int draw_x = img_posX;
    int draw_y = img_posY;
    
    
    al_draw_bitmap(img, draw_x, draw_y, 0);
    attack_counter = (attack_counter + 1) % attack_frequency;
    
    for(unsigned int i=0; i<this->attack_set.size(); i++)
        this->attack_set[i]->draw();
}

bool
Tower::DetectAttack(Classmates *mate)
{
    bool willAttack = false;
    Attack *attack;
    
    printf("x:%d y:%d  X:%d y:%d\n",circle->x,circle->y,mate->getCircle()->x,mate->getCircle()->y);
    
    if(Circle::isOverlap(this->circle, mate->getCircle()) && (mate->isPlayer) == this->whichSide)
    {
        /*
         * TODO:
         *   Don't allow tower make new attack over and over again.
         *   Only when the counter reaches "0" can tower trigger new attack.
         *
         */
        if(attack_counter > 0) return false;
        
        attack = new Attack(
                            this->circle,
                            mate->getCircle(),
                            this->attack_harm_point,
                            this->attack_velocity,
                            this->attack_img
                            );
        this->attack_set.push_back(attack);
        
        
        willAttack = true;
        mate->attacking = true;
    }
    
    return willAttack;
}

bool
Tower::TriggerAttack(Classmates *mate)
{
    bool isDestroyed = false;
    
    for(unsigned int i = 0; i < this->attack_set.size(); i++)
    {
        if(Circle::isOverlap(attack_set[i]->getCircle(), mate->getCircle()) && (mate->isPlayer) == this->whichSide)
        {
            /*TODO:*/
            /*1. Reduce the monster HP by the harm point*/
            /*2. Erase and delete the attack from attack set*/
            /*3. Return true if the monster's HP is reduced to zero*/
            mate->Subtract_HP(attack_harm_point);
            attack_set[i]->~Attack();
            attack_set.erase(attack_set.begin() + i);
            i--;
            if(mate->getHealthPoint() <= 0) return true;
        }
    }
    return false;
}

void
Tower::UpdateAttack()
{
    for(unsigned int i=0; i < this->attack_set.size(); i++)
    {
        if(!Circle::isOverlap(this->attack_set[i]->getCircle(), this->circle))
        {
            Attack *attack = this->attack_set[i];
            
            this->attack_set.erase(this->attack_set.begin() + i);
            i--;
            delete attack;
        }
    }
}

bool Tower::Subtract_HP(int harm_point)
{
    HealthPoint -= harm_point;
    
    return (HealthPoint <= 0);
}

