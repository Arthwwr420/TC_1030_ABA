#ifndef HITBOX_H
#define HITBOX_H

#include<cmath>

const int HIT_CHARACTER = 0;
const int HIT_PROYECTILE = 1;
//clase para manejar colisiones en forma rectangular
class Hitbox{
    private:
        float posX;
        float posY;
        int width;
        int height;
        int type;
    public:
        Hitbox(int w, int h);
        void MoveTo(float x, float y);  //Reemplaza los valores de la posicion por los dados
        void MoveTowards(float x, float y); //Añade los valores dados a la posicion
        float GetPosX();
        float GetPosY();

        //Funciones para Checar colisiones con circulo y otro recatngulo
        bool CheckCol(Hitbox *target);

};

//Clase para manejar colisiones en forma circular
class HitCircle{
    private:
        int radius;
        int type;
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

void Hitbox::MoveTo(float x, float y){
    posX = x;
    posY = y;
}

void Hitbox::MoveTowards(float x, float y){
    posX += x;
    posY += y;
}
float Hitbox::GetPosX(){
    return posX;
}

float Hitbox::GetPosY(){
    return posY;
}

bool Hitbox::CheckCol(Hitbox *target){
    return false;
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