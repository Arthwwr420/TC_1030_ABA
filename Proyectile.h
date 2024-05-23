#ifndef PROYECTILE_H
#define PROYECTILE_H

#include "Character.h"
#include "GameManager.h"

//Clase proyectil, hecha para ser heredada
class Proyectile{
    protected:
        int damage;
        float speed;
        float dirX;
        float dirY;
        float dist2Target;
        PlayableChar *target;
        void OnHit(); //Que hace el proyectil al chocar con algo

};

//el orbe dispara al enemigo cada cierto tiempo, puede estar quieto en un lugar o seguir al jugador
class Orb:Proyectile{
    private: 
        bool lock; //Decide si sigue el jugador
        int cooldown; //Frames restantes para volver a disparar
        HitCircle Hitbox; //hitbox

    public:
        Orb(float x, float y, PlayableChar *targ);
        void Shoot();
        void OnHit(auto *object);
};

//el dardo magico sigue al su objetivo
class MagicDart:Proyectile{
    private:
        float accel; //el dardo se acelera en direccion al jugador, estra es la maganitud de la aceracion
        float speedX, speedY;
        HitCircle Hitbox; //Hitbox

    public:
        MagicDart(float x, float y, PlayableChar *targ); 
        void Update(); //funcion para actualizar las fisicas cada frame
        void OnHit(auto object);
};

Orb::Orb(float x, float y, PlayableChar *targ): Hitbox(1){
    damage = 1;
    speed = 0;
    target = targ;
    lock = 0;
    cooldown = 10;

    Hitbox.Move(x, y);
    dist2Target = sqrt(powf((target->hitbox.GetPosX()- Hitbox.GetPosX()), 2)
                    + powf((target->hitbox.GetPosY()- Hitbox.GetPosY()), 2));
    dirY = (target->hitbox.GetPosY()- Hitbox.GetPosY())/dist2Target;
    dirX = (target->hitbox.GetPosX()- Hitbox.GetPosX())/dist2Target;
}

void Orb::OnHit(auto *object){ //Por terminar cuando el GameManager este listo (es q si ta complicado)
    if (object == target){
        target->TakeDamage(damage);
    }
}

MagicDart::MagicDart(float x, float y, PlayableChar *targ): Hitbox(1){
    damage = 1;
    speed = 1;
    target = targ;
    accel = 0.1f;

    Hitbox.Move(x, y);
    dist2Target = sqrt(powf((target->hitbox.GetPosX()- Hitbox.GetPosX()), 2)
                    + powf((target->hitbox.GetPosY()- Hitbox.GetPosY()), 2));
    dirY = (target->hitbox.GetPosY()- Hitbox.GetPosY())/dist2Target;
    dirX = (target->hitbox.GetPosX()- Hitbox.GetPosX())/dist2Target;

    speedX = dirX;
    speedY = dirY;
}

void MagicDart::Update(){
    dist2Target = sqrt(powf((target->hitbox.GetPosX()- Hitbox.GetPosX()), 2)
                    + powf((target->hitbox.GetPosY()- Hitbox.GetPosY()), 2));
    dirY = (target->hitbox.GetPosY()- Hitbox.GetPosY())/dist2Target;
    dirX = (target->hitbox.GetPosX()- Hitbox.GetPosX())/dist2Target;

    if(sqrt(speedX*speedX + speedY*speedY) < speed){
        speedX += accel*dirX;
        speedY += accel*dirY;
    }
}

void MagicDart::OnHit(auto object){ //Por terminar cuando el GameManager este listo (es q si ta complicado)
    if (object == target){
        target->TakeDamage(damage);
    }
}   

#endif