#ifndef CHARACTER_H
#define CHARACTER_H

#include<iostream>
#include"Hitbox.h"

const int DOWAIT = 0;
const int DOJUMP = 1;
const int DODASH = 2;
const int DOSDASH = 3;
const int DOBLOCK = 4;

const int ROBDOPUNCH = 5;
const int ROBDOGRAB = 6;
const int ROBDOTRYCATCH = 7;
const int ROBDOBOUNDS = 8;
const int ROBDOLOIC = 9;

const int WIZDOTSLAP = 5;
const int WIZDODART = 6;
const int WIZDOGEYSER = 7;
const int WIZDOMISSILE = 8;
const int WIZDOORB = 9;

//clase comun de todos los personajes jugables
class PlayableChar{
    protected:
        int playerNum;
        int MaxHealth;
        int health;
        float burstCharge;
        int superMeter;
        int frames2Wait; 
        float superCharge;
        int maxFreeCancels;
        int maxAirOptions;
        int airOptions;
        bool blocking;

        bool OnGround();

        float yMomentum;
        float xMomentum;
        PlayableChar(): hitbox(2, 3){};

    
    public:
        Hitbox hitbox;
        void TakeDamage(int dmg);
        void Wait();
        virtual void PlayerChoice() = 0;
        virtual void Do(int choice, PlayableChar *target) = 0;
        virtual void Dash() = 0;
        virtual void SuperDash() = 0;
        virtual void Jump(float xForce, float yForce) = 0; 
        void JumpRequest();
        void Block();
        void Update();
        int GetHealth();

};

class Robot : public PlayableChar{
    private:
        float fuel;
        int loic;
        void LOIC(PlayableChar *target, int x);
    
    public:
        Robot(int player);
        void PlayerChoice();
        void Do(int choice, PlayableChar *target);
        void Dash();
        void SuperDash();
        void Jump(float xForce, float yForce);
        void Punch(PlayableChar *target);
        void Grab(PlayableChar *target);
        void TryCatch(PlayableChar *target);
        void Bounds(PlayableChar *target);
        void LOICRequest(PlayableChar *target, int x);
};

class Wizzard: public PlayableChar{
    private:
        float gravity;
        void Orb(PlayableChar *target);

    public:
        Wizzard(int player);
        void PlayerChoice();
        void Do(int choice, PlayableChar *target);
        void Dash();
        void SuperDash();
        void Jump(float xForce, float yForce);
        void TomeSlap(PlayableChar *target);
        void SummonMagicDart(PlayableChar *target, float xForce, float yForce);
        void Geyser(PlayableChar *target, float xDir, float yDir);
        void MissileForm(float xDir, float yDir, PlayableChar *target);
        void OrbRequest(PlayableChar *target);
};

void PlayableChar::TakeDamage(int dmg){
    health-= dmg;
}

void PlayableChar::Wait(){
    frames2Wait = 5;
}

void PlayableChar::Block(){
    frames2Wait = 6;
    blocking = true;
}

void PlayableChar::JumpRequest(){
    std::string input;
    std::cout << "Introducir magnitud de la direccion en y (0 <= y <= 1)\n";
    std::getline(std::cin, input);
    float y = std::stof(input);
    if (y < 0 || y > 1) y = 0;

    std::cout << "Introducir magnitud de la direccion en x (0 <= x <= 1)\n";
    std::getline(std::cin, input);
    float x = std::stof(input);
    if (x < 0 || x > 1) x = 0;

    float m = sqrt(x*x + y*y);

    Jump(x/m, y/m);

}

int PlayableChar::GetHealth() { return health; }
bool PlayableChar::OnGround(){ return (hitbox.GetPosY() <= 1.5f); }


Robot::Robot(int player){
    MaxHealth = 110;
    playerNum = player;
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
    maxAirOptions = 0;

    if(player == 1){
        hitbox.MoveTo(-5, 1.5);
    }else if (player == 2)
        hitbox.MoveTo(5, 1.5);

    std::cout << "Creado personaje Robot para jugador "<< player << "\n";
}

void Robot::PlayerChoice(){
    blocking = 0;
    std::cout << "Opciones disponibles:\n";
    if ( OnGround() )
        std::cout << "Jump\nDash\nSuperDash\nTryCatch\n";
    std::cout<<"Block\nPunch\nGrab\nBoundsCheck\n";
    if (superMeter >= 3){
        std::cout << "LOIC\n";
    }
    
    
}

void Robot::Do(int choice, PlayableChar *target){
    switch (choice)
    {
    case DOWAIT:
        Wait();
        break;
    case DOJUMP:
        JumpRequest();
        break;
    case DODASH:
        Dash();
        break;
    case DOSDASH:
        SuperDash();
        break;
    case DOBLOCK:
        Block();
        break;
    case ROBDOPUNCH:
        Punch(target);
        break;        
    
    default:
    std::cout << "Ups, no he implementado esa accion, la reemplazare por Wait por mientras\n";
        Wait();
        break;
    }
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

void Robot::Punch(PlayableChar *target){
    target->TakeDamage(10000);
}


Wizzard::Wizzard(int player){
    MaxHealth = 110;
    playerNum = player;
    health = MaxHealth;
    burstCharge = 0;
    superMeter = 0;
    frames2Wait = 0;
    superCharge = 0;
    maxFreeCancels = 2;
    gravity = 100.0f;
    xMomentum = 0;
    yMomentum = 0;
    maxAirOptions = 2;
    airOptions = maxAirOptions;

    if(player == 1){
        hitbox.MoveTo(-5, 3);
    }else if (player == 2)
        hitbox.MoveTo(5, 1.5);

    std::cout << "Creado personaje Wizzard para jugador "<< player << "\n";
}

void Wizzard::PlayerChoice(){
    blocking = 0;
    std::cout << "Opciones disponibles:\n";
    if (OnGround())
        std::cout << "SuperDash\n";
    if ( OnGround() || airOptions >= 1)
        std::cout << "Jump\nDash\nMissile Form\n";
    std::cout<<"Block\nTomeSlap\nMagic Dart\nGeyser\n";
    if (superMeter >= 3){
        std::cout << "Orb\n";
    }
}

void Wizzard::Do(int choice, PlayableChar *target){

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