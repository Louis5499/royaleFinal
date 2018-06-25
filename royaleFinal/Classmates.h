#ifndef classmates_h
#define classmates_h

class Tower;
#include <string.h>
#include "Object.h"
#include <vector>
#include "Attack.h"
#include "global.h"
#include "Tower.h"



class Classmates : public Object
{
public:
    Classmates(std::string,int,int,int);
    virtual ~Classmates(){};
    
    void change_dir(int d){dir = d;};
    void move();
    void draw();
    
    // functions that return informations of monster
    int getDir() { return dir; }
    int getHealthPoint() { return HealthPoint; }
    
    // update whole attack set
    // if any attack goes out of the range of tower, delete it
    void UpdateAttack();
    // detect if tower needs to attack some monster
    bool DetectAttack(Classmates*);
    bool DetectAttackTower(Tower *tower);
    // process if some of attack in set touches monster
    bool TriggerAttack(Classmates*);
    bool TriggerAttackTower(Tower *tower);
    
    bool Subtract_HP(int);
    
    int attack_harm_point = 5;
    
    bool isPlayer = true; // 是電腦還是我們
    bool attacking = false;
    std::vector<Attack*> attack_set;
        
protected:
    ALLEGRO_BITMAP *img[4][3];
    std::string name;
    double vel = 0.8;
    int dir = up;
    double pos[2];
    double calcPos[2]; //leg coordinate
    int whichImg;
    
    int imgWidth = 80;
    int imgHeight = 106;
    
    // moveRelated
    int upRouteY[2] = {220,270};
    int downRouteY[2] = {650,670};
    
    // setting of attack
    int attack_frequency = 20;
    int attack_counter = 0;
    
    int attack_velocity = 10;
    ALLEGRO_BITMAP *attack_img = al_load_bitmap("./meteor.png");
    
    
    int HealthPoint = 200;
    char class_name[20];
};


#endif /* classmates_h */
