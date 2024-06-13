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
        Hitbox();
        Hitbox(int w, int h);
        void ChangeDim(int w, int h);
        void MoveTo(float x, float y);  //Reemplaza los valores de la posicion por los dados
        void MoveTowards(float x, float y); //Añade los valores dados a la posicion
        float GetPosX();
        float GetPosY();
        int GetWidth();
        int GetHeight();

        //Funciones para Checar colisiones con circulo y otro recatngulo
        bool CheckCol(Hitbox *target);

};

Hitbox::Hitbox(){
    height = 0;
    width = 0;
    posX = 0;
    posY = 0;

}

Hitbox::Hitbox(int w, int h){
    height = h;
    width = w;
    posX = 0;
    posY = 0;
}

void Hitbox::ChangeDim(int w, int h){
    width = w;
    height = h;
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

int Hitbox::GetWidth(){ return width; }
int Hitbox::GetHeight(){ return height; }

bool Hitbox::CheckCol(Hitbox *target){
    bool hasCol;

    float distX = abs(target->GetPosX() - posX);
    float distY = abs((target->GetPosY() - posY));

    hasCol = (distX <= width/2.0f + target->GetWidth()/2.0f) && (distY <= height/2.0f + target->GetHeight()/2.0f);

    return hasCol;
}
#endif