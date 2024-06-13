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
const int WIZDOGEYSER = 7;
const int WIZDOMISSILE = 8;

//clase comun de todos los personajes jugables
class PlayableChar{
    protected:
        int playerNum;
        int MaxHealth;
        int health; 
        int frames2Wait; //numero de frames a esperar antes de poder tener un turno
        int ignoreFric; //numero de frames en los que se ignora la friccion
        float superCharge;
        int superMeter;
        int maxAirOptions;
        int airOptions; //numero de acciones de movimiento que se pueden hacer en el aire
        int dirMultiplier; //solo 1 o -1, dirige el ataque hacie el enemigo en el eje x

        bool blocking;
        bool OnGround();
        bool isAttacking;
        int AtkFrames; //numero de frames en los que la accion actual puede hacer daño
        int currDmg; //cantidad de daño actual

        float yMomentum;
        float xMomentum;

        PlayableChar *currentTar;

        PlayableChar(): hitbox(2, 3){};

    
    public:
        Hitbox hitbox;
        Hitbox atkHbox;
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
        int GetWaitFrames();

};

class Robot : public PlayableChar{
    private:
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
        void LOICRequest(PlayableChar *target);
};

class Wizzard: public PlayableChar{
    private:
        float gravity;

    public:
        Wizzard(int player);
        void PlayerChoice();
        void Do(int choice, PlayableChar *target);
        void Dash();
        void SuperDash();
        void Jump(float xForce, float yForce);
        void TomeSlap(PlayableChar *target);
        void Geyser(PlayableChar *target, float xDir, float yDir);
        void MissileFormRequest(PlayableChar *target);
        void MissileForm(float xDir, float yDir, PlayableChar *target);
};

void PlayableChar::TakeDamage(int dmg){
    if (blocking){
        std::cout << "Jugador "<< playerNum<< " bloqueo "<< dmg<< " daño \n";
    }else{
        health-= dmg;
        frames2Wait = 0;
        std::cout << "Jugador "<< playerNum<< " recibio "<< dmg<< " daño \n";
    }
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
    std::cin >> input;
    float y = std::stof(input);
    if (y <= 0 || y > 1) y = 0.1;

    std::cout << "Introducir magnitud de la direccion en x (-1 <= x <= 1)\n";
    std::cin >> input;
    float x = std::stof(input);
    if (x < -1 || x > 1) x = 0;

    float m = sqrt(x*x + y*y);

    Jump(x/m, y/m);

}

void PlayableChar::Update(){
    if (isAttacking){
        if ( frames2Wait <= AtkFrames && AtkFrames > 0){
            if (atkHbox.CheckCol(&currentTar->hitbox)){
                currentTar->TakeDamage(currDmg);
                frames2Wait = 0;
                AtkFrames = 0;
            }else{
                AtkFrames --;
            }
        }
    }

    if(OnGround()){
        if(yMomentum <  0) yMomentum = 0;
        if(ignoreFric <= 0) {
            if (xMomentum < 0)
                if(xMomentum + 1 > 0) xMomentum = 0;
                else xMomentum += 1;
            else if (xMomentum > 0) 
                if (xMomentum - 1 < 0) xMomentum = 0;
                else xMomentum -= 1;

        }
            

    }else{
        yMomentum -= 0.5; 
    }
    if(ignoreFric > 0) ignoreFric --;

    hitbox.MoveTowards(xMomentum*0.1, yMomentum*0.1);
    atkHbox.MoveTowards(xMomentum*0.1, yMomentum*0.1);

    if (OnGround()){
        hitbox.MoveTo(hitbox.GetPosX(), 1.5f);
        airOptions = maxAirOptions;
    } 



    superCharge += 0.05;
    if(superMeter >= 9)
        superCharge = 0;

    if (superCharge >= 1){
        superMeter++;
        superCharge = 0;
    }

    frames2Wait -=1;

}

int PlayableChar::GetHealth() { return health; }
int PlayableChar::GetWaitFrames() { return frames2Wait; }
bool PlayableChar::OnGround(){ return (hitbox.GetPosY() <= 1.5f); }


Robot::Robot(int player){
    MaxHealth = 110;
    playerNum = player;
    health = MaxHealth;
    superMeter = 0;
    frames2Wait = 0;
    superCharge = 0;
    loic = 0;
    xMomentum = 0;
    yMomentum = 0;
    maxAirOptions = 0;
    isAttacking = 0;

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
    currentTar = nullptr;
    dirMultiplier = (target->hitbox.GetPosX() < hitbox.GetPosX()) ? -1 : 1;
    blocking = 0;
    isAttacking = 0;
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
    case ROBDOBOUNDS:
        Bounds(target);
        break; 
    case ROBDOGRAB:
        Grab(target);
        break;
    case ROBDOTRYCATCH:
        TryCatch(target);
        break;
    case ROBDOLOIC:
        LOICRequest(target);
        break;      
    
    default:
    std::cout << "Ups, no he implementado esa accion, la reemplazare por Wait por mientras\n";
        Wait();
        break;
    }
}

void Robot::Dash(){ 
    frames2Wait = 8;
    xMomentum = 10*dirMultiplier;
    ignoreFric = 6;
}

void Robot::SuperDash(){ 
    frames2Wait = 10;
    xMomentum = 10*dirMultiplier;
    yMomentum = 5;
    
}

void Robot::Jump(float xForce, float yForce){
    if(sqrt(xForce*xForce + yForce*yForce) < 1){
        frames2Wait = 8;
    }else{
        frames2Wait = 11;
    }

    yMomentum = 6.25f*yForce;
    xMomentum = 6.25f*xForce;
}

void Robot::Punch(PlayableChar *target){
    isAttacking = 1;
    currentTar = target;
    currDmg = 90;
    atkHbox.ChangeDim(4, 1);
    atkHbox.MoveTo(hitbox.GetPosX() + 5*dirMultiplier, hitbox.GetPosY());
    frames2Wait = 3;
    AtkFrames = 3;
}

void Robot::Bounds(PlayableChar *target){
    isAttacking = 1;
    currentTar = target;
    currDmg = 20;
    atkHbox.ChangeDim(4, 3);
    atkHbox.MoveTo(hitbox.GetPosX() + 1*dirMultiplier, hitbox.GetPosY());
    frames2Wait = 10;
    AtkFrames = 9;
    xMomentum += 10*dirMultiplier;
}

void Robot::Grab(PlayableChar *target){
    isAttacking = 1;
    currentTar = target;
    currDmg = 30;
    atkHbox.ChangeDim(9, 2);
    atkHbox.MoveTo(hitbox.GetPosX() + 4.5f*dirMultiplier, hitbox.GetPosY() + 0.5f);
    frames2Wait = 7;
    AtkFrames = 4;
}

void Robot::TryCatch(PlayableChar *target){
    isAttacking = 1;
    currentTar = target;
    currDmg = 30;
    atkHbox.ChangeDim(5, 3);
    atkHbox.MoveTo(hitbox.GetPosX() + 3.5f*dirMultiplier, hitbox.GetPosY() + 3.1f);
    frames2Wait = 7;
    AtkFrames = 5;
}

void Robot::LOICRequest(PlayableChar *target){
    if (superMeter < 3){
        std::cout << "No hay suficiente SuperCarga, esperando\n";
        Wait();
    }else{
        std::string input;
        std::cout<<"Introduce coordenadas en x para el LOIC: ";
        std::cin >> input;
        int x = std::stof(input);
        if (x < -100) x = -100;
        else if (x > 100) x = 100;

        superMeter -= 3;
        LOIC(target, x);
    }

}

void Robot::LOIC(PlayableChar *target, int x){
    isAttacking = 1;
    currentTar = target;
    currDmg = 50;
    atkHbox.ChangeDim(5, 100);
    atkHbox.MoveTo(x, 50);
    frames2Wait = 20;
    AtkFrames = 10;
}

Wizzard::Wizzard(int player){
    MaxHealth = 100;
    playerNum = player;
    health = MaxHealth;
    superMeter = 0;
    frames2Wait = 0;
    superCharge = 0;
    gravity = 100.0f;
    xMomentum = 0;
    yMomentum = 0;
    maxAirOptions = 2;
    airOptions = maxAirOptions;
    isAttacking = 0;

    if(player == 1){
        hitbox.MoveTo(-5, 1.5);
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
        std::cout << "Jump\nDash\nMissileForm\n";
    std::cout<<"Block\nTomeSlap\nGeyser\n";
}

void Wizzard::Do(int choice, PlayableChar *target){
    currentTar = nullptr;
    dirMultiplier = (target->hitbox.GetPosX() < hitbox.GetPosX()) ? -1 : 1;
    blocking = 0;
    isAttacking = 0;

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
    case WIZDOTSLAP:
        TomeSlap(target);
        break; 
    case WIZDOMISSILE:
        MissileFormRequest(target);
        break; 
    case WIZDOGEYSER:
        Geyser(target, 1, 0);
        break;
 
    default:
        std::cout << "Ups, no he implementado esa accion, la reemplazare por Wait por mientras\n";
        Wait();
        break;
    }
}

void Wizzard::Dash(){
    if(!OnGround()){
        if(airOptions > 0 && gravity>0){
            airOptions --;
            gravity -= 10;
        }else{
            Wait();
            return;
        }
    }
    frames2Wait = 8;
    xMomentum = 12*dirMultiplier;
    ignoreFric = 8;
}

void Wizzard::SuperDash(){ 
    frames2Wait = 15;
    xMomentum = 12*dirMultiplier;
    yMomentum = 5;
    ignoreFric = 1;
}

void Wizzard::Jump(float xForce, float yForce){
    if(!OnGround()){
        if(airOptions > 0 && gravity>0){
            airOptions --;
            gravity -= 10;
            std::cout <<"Accion fallida, no hay suficiente gravedad u Opciones Aereas\n";

        }else{
            Wait();
            return;
        }
    }
    if(sqrt(xForce*xForce + yForce*yForce) < 1){
        frames2Wait = 8;
    }else{
        frames2Wait = 11;
    }

    yMomentum = 5*yForce;
    xMomentum = 5*xForce;
}

void Wizzard::TomeSlap(PlayableChar *target){
    isAttacking = 1;
    currentTar = target;
    currDmg = 15;
    atkHbox.ChangeDim(2, 2);
    atkHbox.MoveTo(hitbox.GetPosX() + 3.0f*dirMultiplier, hitbox.GetPosY() + 0.5f);
    frames2Wait = 8;
    AtkFrames = 3;
    xMomentum += 1*dirMultiplier;
}

void Wizzard::Geyser(PlayableChar *target, float dirX, float dirY){
    isAttacking = 1;
    currentTar = target;
    currDmg = 30;
    atkHbox.ChangeDim(20, 3);
    atkHbox.MoveTo(hitbox.GetPosX() + 11.0f*dirMultiplier, hitbox.GetPosY());
    frames2Wait = 12;
    AtkFrames = 4;
}

void Wizzard::MissileFormRequest(PlayableChar *target){
    std::string input;
    std::cout << "Introducir magnitud de la direccion en y (-1 <= y <= 1)\n";
    std::cin >> input;
    float y = std::stof(input);
    if (y < -1 || y > 1) y = 0;

    std::cout << "Introducir magnitud de la direccion en x (-1 <= x <= 1)\n";
    std::cin >> input;
    float x = std::stof(input);
    if (x < -1 || x > 1) x = 0;

    float m = sqrt(x*x + y*y);

    MissileForm(x/m, y/m, target);
}

void Wizzard::MissileForm(float xDir, float yDir, PlayableChar *target){
    if(!OnGround()){
        if(airOptions > 0 && gravity>0){
            airOptions --;
            gravity -= 10;
        }else{
            std::cout <<"Accion fallida, no hay suficiente gravedad u Opciones Aereas\n";
            Wait();
            return;
        }
    }
    isAttacking = 1;
    currentTar = target;
    currDmg = 20;
    atkHbox.ChangeDim(4, 5);
    atkHbox.MoveTo(hitbox.GetPosX(), hitbox.GetPosY());
    frames2Wait = 8;
    AtkFrames = 1;
    xMomentum = 8*xDir;
    yMomentum = 8*yDir;
}

#endif