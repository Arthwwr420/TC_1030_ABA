#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include<iostream>
#include<cmath>

class GameScene{
    private:
        int framesLft;
        int ySize, xSize;
    public:


};

//clase para manejar colisiones en forma rectangular
class Hitbox{
    private:
        float posX;
        float posY;
        int width;
        int height;
    public:
        Hitbox(int w, int h);
        float GetPosX();
        float GetPosY();

        //Funciones para Checar colisiones con circulo y otro recatngulo
        bool CheckCol(Hitbox *target);
        bool CheckCol(HitCircle *target);

};

//Clase para manejar colisiones en forma circular
class HitCircle{
    private:
        int radius;
        float posX, posY;
    public:
        HitCircle(int radius);
        int GetRadius();
        float GetPosX();
        float GetPosY();
        bool CheckCol(Hitbox *target);
        bool CheckCol(HitCircle *target);
        void Move(float x, float y);
};

Hitbox::Hitbox(int w, int h){
    height = h;
    width = w;
    posX = 0;
    posY = 0;
}

float Hitbox::GetPosX(){
    return posX;
}

float Hitbox::GetPosY(){
    return posY;
}

bool Hitbox::CheckCol(Hitbox *target){

}

HitCircle::HitCircle(int rad){
    radius = rad;
    posX = 0;
    posY = 0;
}

int HitCircle::GetRadius(){
    return radius;
}

float HitCircle::GetPosX(){
    return posX;
}

float HitCircle::GetPosY(){
    return posY;
}

bool HitCircle::CheckCol(HitCircle *target){
    float distX = (target->GetPosX() - posX);
    float distY = (target->GetPosY() - posY);
    float dist = sqrt((distX*distX)+(distY*distY));

    bool hasCol = dist <= radius + target->GetRadius();

    return hasCol;
}

void HitCircle::Move(float x, float y){
    posX = x;
    posY = y;
}
#endif