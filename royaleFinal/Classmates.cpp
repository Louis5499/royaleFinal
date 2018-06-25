#include "Classmates.h"

Classmates::Classmates(std::string str,int posX,int posY,int _isPlayer): name(str) {
    int i, j;
    char s[50], path[80];
    calcPos[0] = posX; calcPos[1] = posY;
    pos[0] = calcPos[0]; pos[1] = calcPos[1] - 106;
    isPlayer = _isPlayer;
    whichImg = 0;
    for(i=0; i<50; i++) s[i] = str[i];
    
    for(i=0; i<4; i++) for(j=0; j<3; j++) {
        sprintf(path, "./%s_%d_%d.png", s, i, j);
        img[i][j] = al_load_bitmap(path);
    }
    
    this->circle = new Circle(posX+imgWidth/2,posY+imgHeight/2, 70);
}

void Classmates::move() {
//    if((dir == up && pos[1] < 20) || (dir == left && pos[0] < 20) || (dir == down && pos[1] > 400) || (dir == right && pos[0] > 400)) dir = (dir+1)%4;
//    pos[0] += vel*dir_mov[dir][0];
//    pos[1] += vel*dir_mov[dir][1];
    

    if(calcPos[1] <= upRouteY[0])
        dir = 2;
    else if(calcPos[1] > upRouteY[1] && calcPos[1] < window_height/2)
        dir = 0;
    else if(calcPos[1] >= window_height/2 && calcPos[1] < downRouteY[0])
        dir = 2;
    else if(calcPos[1] >= downRouteY[1])
        dir = 0;
    else dir = 1; // fake
    
    if( (isPlayer && calcPos[0] > 1145)
       || (!isPlayer && calcPos[0] < 440)) {
        if(calcPos[1] < window_height/2) dir = 2;
        else dir = 0;
    }
    
    if(dir != 0 && dir != 2) {
        // On route
        if(isPlayer) dir = 3;
        else dir = 1;
    }
    
    std::cout << "HP :" << HealthPoint << std::endl;
    std::cout << "attacking :" << attacking << std::endl;
    std::cout << "x:" << pos[0] << " y:" << pos[1] << std::endl;
    if(!attacking) {
        pos[0] += vel*dir_mov[dir][0];
        pos[1] += vel*dir_mov[dir][1];
        calcPos[0] = pos[0];
        calcPos[1] = pos[1] + 105;
        
        circle->x = pos[0] + imgWidth/2;
        circle->y = pos[1] + imgHeight/2;
    }
    
}

void Classmates::draw() {
    int num = (whichImg == 3) ? 1 : whichImg;
    if(step < 10) step++;
    else step = 0;
    if(step == 0) whichImg = (whichImg+1)%4;
    al_draw_bitmap(img[dir][num], pos[0], pos[1], 0);
    
    attack_counter = (attack_counter + 1) % attack_frequency;
    
    for(unsigned int i=0; i<this->attack_set.size(); i++)
        this->attack_set[i]->draw();
}


bool Classmates::Subtract_HP(int harm_point)
{
    HealthPoint -= harm_point;
    
    return (HealthPoint <= 0);
}

bool
Classmates::DetectAttack(Classmates *mate)
{
    bool willAttack = false;
    Attack *attack;
    
    if(Circle::isOverlap(this->circle, mate->getCircle())  && (mate->isPlayer) != this->isPlayer)
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
    }
    attacking = willAttack;
    
    return willAttack;
}

bool
Classmates::DetectAttackTower(Tower *tower)
{
    bool willAttack = false;
    Attack *attack;

    if(Circle::isOverlap(this->circle,tower->getCircle()) && (this->isPlayer) == tower->whichSide)
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
                            tower->getCircle(),
                            this->attack_harm_point,
                            this->attack_velocity,
                            this->attack_img
                            );

        this->attack_set.push_back(attack);
        willAttack = true;
    }
    
    return willAttack;
}


bool
Classmates::TriggerAttack(Classmates *mate)
{
    bool isDestroyed = false;
    
    for(unsigned int i = 0; i < this->attack_set.size(); i++)
    {
        if(Circle::isOverlap(attack_set[i]->getCircle(), mate->getCircle()) && (mate->isPlayer) != this->isPlayer)
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

bool
Classmates::TriggerAttackTower(Tower *tower)
{
    bool isDestroyed = false;
    
    for(unsigned int i = 0; i < this->attack_set.size(); i++)
    {
        if(Circle::isOverlap(attack_set[i]->getCircle(), tower->getCircle()) && (this->isPlayer) == tower->whichSide)
        {
            /*TODO:*/
            /*1. Reduce the monster HP by the harm point*/
            /*2. Erase and delete the attack from attack set*/
            /*3. Return true if the monster's HP is reduced to zero*/
            tower->Subtract_HP(attack_harm_point);
            attack_set[i]->~Attack();
            attack_set.erase(attack_set.begin() + i);
            i--;
            if(tower->getHealthPoint() <= 0) return true;
        }
    }
    return false;
}

void
Classmates::UpdateAttack()
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

