#ifndef classmates_h
#define classmates_h

#include <string.h>
#include "global.h"
#include "Object.h"

class Classmates : public Object
{
public:
    Classmates(std::string);
    virtual ~Classmates(){};
    
    void change_dir(int d){dir = d;};
    void move();
    void draw();
    
    // functions that return informations of monster
    int getDir() { return dir; }
    int getHealthPoint() { return HealthPoint; }
    
    bool Subtract_HP(int);
    
protected:
    ALLEGRO_BITMAP *img[4][3];
    std::string name;
    int vel = 5;
    int dir = up;
    int pos[2];
    int whichImg;
    int moveSpeed;
    
    int HealthPoint = 20;
    int speed = 1;
    char class_name[20];
};


#endif /* classmates_h */
