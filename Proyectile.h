#ifndef PROYECTILE_H
#define PROYECTILE_H

#include "Character.h"
#include "Hitbox.h"

//Clase proyectil, hecha para ser heredada
class Proyectile{
    private:
        bool isActive;
    protected:
        int damage;       
        float speed;
        float dirX;
        float dirY;
        float dist2Target;
        PlayableChar *target;
        virtual void OnHit() = 0; //Que hace el proyectil al chocar con algo
        virtual void Update() = 0;

};

//el orbe dispara al enemigo cada cierto tiempo, puede estar quieto en un lugar o seguir al jugador
class Orb: public Proyectile{
    private: 
        bool lock; //Decide si sigue el jugador
        int cooldown; //Frames restantes para volver a disparar
        HitCircle hitbox; //hitbox

    public:
        Orb(float x, float y, PlayableChar *targ);
        void Update();
        void Shoot();
        void OnHit(PlayableChar *object);
};

//el dardo magico sigue al su objetivo
class MagicDart: public Proyectile{
    private:
        float accel; //el dardo se acelera en direccion al jugador, estra es la maganitud de la aceracion
        float speedX, speedY;
        HitCircle Hitbox; //Hitbox

    public:
        MagicDart(float x, float y, PlayableChar *targ); 
        void Update(); //funcion para actualizar las fisicas cada frame
        void OnHit(PlayableChar *object);
};


Orb::Orb(float x, float y, PlayableChar *targ): hitbox(1){
    damage = 1;
    speed = 0;
    target = targ;
    lock = 0;
    cooldown = 10;

    hitbox.Move(x, y);
    dist2Target = sqrt(powf((target->hitbox.GetPosX()- hitbox.GetPosX()), 2)
                    + powf((target->hitbox.GetPosY()- hitbox.GetPosY()), 2));
    dirY = (target->hitbox.GetPosY()- hitbox.GetPosY())/dist2Target;
    dirX = (target->hitbox.GetPosX()- hitbox.GetPosX())/dist2Target;
}

void Orb::OnHit(PlayableChar *object){ //Por terminar cuando el GameManager este listo (es q si ta complicado)
    if (object == target){
        object->TakeDamage(damage);
    }
}

void Orb::Update(){
    
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

    Hitbox.Move(Hitbox.GetPosX() + speedX, Hitbox.GetPosY() + speedY);
}

void MagicDart::OnHit(PlayableChar *object){ //Por terminar cuando el GameManager este listo (es q si ta complicado)
    if (object == target){
        object->TakeDamage(damage);
    }
}   

#endif