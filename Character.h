#ifndef CHARACTER_H
#define CHARACTER_H

#include<iostream>
#include"Proyectile.h"
#include"GameManager.h"

//clase comun de todos los personajes jugables
class PlayableChar{
    protected:
        int MaxHealth;
        int health;
        float burstCharge;
        int superMeter;
        int frames2Wait; 
        float superCharge;
        int maxFreeCancels;
        void TakeDamage(int dmg);
        void Move(float x, float y);
        float yMomentum;
        float xMomentum;

    public:
        void Dash();
        void SuperDash();
        void Jump(float xForce, float yForce); 
        Hitbox hitbox;

};

class Robot:PlayableChar{
    private:
        float fuel;
        int loic;
        void LOIC(PlayableChar *target, int x);
    
    public:
        Robot();
        void Start(); 
        void Dash();
        void SuperDash();
        void Jump(float xForce, float yForce);
        void Punch(PlayableChar *target);
        void Grab(PlayableChar *target);
        void TryCatch(PlayableChar *target);
        void Bounds(PlayableChar *target);
        void LOICRequest(PlayableChar *target, int x);
        Hitbox hitbox;
};

class Wizzard:PlayableChar{
    private:
        float gravity;
        void Orb(PlayableChar *target);

    public:
        Wizzard();
        void Start();
        void Dash();
        void SuperDash();
        void Jump(float xForce, float yForce);
        void TomeSlap(PlayableChar *target);
        void SummonMagicDart(PlayableChar *target, float xForce, float yForce);
        void Geyser(PlayableChar *target, float xDir, float yDir);
        void MissileForm(float xDir, float yDir, PlayableChar *target);
        void OrbRequest(PlayableChar *target);
        Hitbox hitbox;
};

Robot::Robot(): hitbox(2, 3){
    MaxHealth = 110;
    health = MaxHealth;
    burstCharge = 0;
    superMeter = 0;
    frames2Wait = 0;
    superCharge = 0;
    maxFreeCancels = 2;
    fuel = 100;
    loic = 0;
    xMomentum = 0;
    yMomentum = 0;


}

void Robot::Dash(){ //por terminar cuando el Game Manager este listo :)
    frames2Wait = 12;
    xMomentum = 10;
}

void Robot::SuperDash(){ //por terminar cuando el Game Manager este listo :)
    frames2Wait = 15;
    xMomentum = 15;
    yMomentum = 5;
}

void Robot::Jump(float xForce, float yForce){
    if(sqrt(xForce*xForce + yForce*yForce) < 1){
        frames2Wait = 8;
    }else{
        frames2Wait = 11;
    }

    yMomentum = yForce;
    xMomentum = xForce;
}

Wizzard::Wizzard(): hitbox(2, 3){
    MaxHealth = 110;
    health = MaxHealth;
    burstCharge = 0;
    superMeter = 0;
    frames2Wait = 0;
    superCharge = 0;
    maxFreeCancels = 2;
    gravity = 100.0f;
    xMomentum = 0;
    yMomentum = 0;
}

void Wizzard::Dash(){ //por terminar cuando el Game Manager este listo :)
    frames2Wait = 11;
    xMomentum = 12;
}

void Wizzard::SuperDash(){ //por terminar cuando el Game Manager este listo :)
    frames2Wait = 15;
    xMomentum = 20;
    yMomentum = 5;
}

void Wizzard::Jump(float xForce, float yForce){
    if(sqrt(xForce*xForce + yForce*yForce) < 1){
        frames2Wait = 8;
    }else{
        frames2Wait = 11;
    }

    yMomentum = yForce;
    xMomentum = xForce;
}
#endif