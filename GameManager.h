#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include<iostream>
#include"Proyectile.h"

class GameScene{
    private:
        int winner;
        int framesLft; //cada frame representa 0.1 segundos(estimacion), las partidas duran un maximo de 50 frames
        int ySize, xSize;
        int xBorder, yBorder;
        bool gameRunning;

    public:
        GameScene();
        PlayableChar *players[2];
        Proyectile *p1Proy[6];
        Proyectile *p2Proy[6];
        void Update(); //Actualizacion de un solo frame, manda a llamar otros Updates
        void CheckColAll(Proyectile *proy); //Checar todas las colisiones posibles para un proyectil
        void CheckColAll(PlayableChar *character); //Checar todas las colisiones posibles para un personaje, se omiten los proyectiles pues esos se evaluan primero

        //getters
        bool IsGameRunning(); 
        int GetWinner();


};

class GameManager{
    private:
        int playerCharacter;
        int AnalyseChoice(std::string in);
    public:
        GameScene game;
        GameManager();
        void Menu();
        void StartGame();
        void GameLoop();
};

GameScene::GameScene(){
    winner = 0;
    framesLft = 3600;
    xSize = 200;
    ySize = 150;
    xBorder = xSize/2;
    yBorder = ySize;
}

void GameScene::Update(){

    if (players[0]->GetHealth() <= 0){
        gameRunning = 0;
        winner = 2;
    }
    if (players[1]->GetHealth() <=0){
        gameRunning = 0;
        winner = 1;
    }
}

bool GameScene::IsGameRunning(){ return gameRunning; }
int GameScene::GetWinner(){ return winner; }

GameManager::GameManager() : game(){

}
void GameManager::Menu(){
    std::string input;

    while (true){
        std::cout << "Selecciona a tu personaje:\n 1. Robot \n 2. Wizzard\n";
        std::cin >> input;

        if (input == "1" || input == "Robot"){
            game.players[0] = new Robot(1);
            playerCharacter = 1;
            break;
        }else if (input == "2" || input == "Wizzard"){
            game.players[0] = new Wizzard(1);
            playerCharacter = 2;
            break;
        }else{
            std::cout << "Seleccion invalida, solo se aceptan numeros del 1 al 2 o nombres de personajes definidos\n";
        }

    }

    while (true){
        std::cout << "Selecciona a tu enemigo:\n 1. Robot \n 2. Wizzard\n";
        std::cin >> input;

        if (input == "1" || input == "Robot"){
            game.players[1] = new Robot(2);
            break;
        }else if (input == "2" || input == "Wizzard"){
            game.players[1] = new Wizzard(2);
            break;
        }else{
            std::cout << "Seleccion invalida, solo se aceptan numeros del 1 al 2 o nombres de personajes definidos\n";
        }

    }
}

void GameManager::StartGame(){
    std::cout <<"la wea inutil;";
}

void GameManager::GameLoop(){
    std::string input;
    int userInt;

    while (game.IsGameRunning()){
        game.players[0]->PlayerChoice();
        std::cin >> input;
        userInt = AnalyseChoice(input);
        game.players[0]->Do(userInt, game.players[1]);

        game.Update();
        break;
    }

    std::cout <<"Juego terminado, gana el jugador " << game.GetWinner();
}

int GameManager::AnalyseChoice(std::string in){
    int value = 0;

    if (playerCharacter == 1){
        if ( in == "Wait") value = DOWAIT;
        else if (in == "Jump") value = DOJUMP;
        else if (in == "Dash") value = DODASH;
        else if (in == "Super Dash") value = DOSDASH;
        else if (in == "Block") value = DOBLOCK;
        else if (in == "Bounds Check") value = ROBDOBOUNDS;
        else if (in == "Grab") value = ROBDOGRAB;
        else if (in == "LOIC") value = ROBDOLOIC;
        else if (in == "Punch") value = ROBDOPUNCH;
        else if (in == "Try Catch") value = ROBDOTRYCATCH;

    }else if(playerCharacter = 2){
        if ( in == "Wait") value = DOWAIT;
        else if (in == "Jump") value = DOJUMP;
        else if (in == "Dash") value = DODASH;
        else if (in == "Super Dash") value = DOSDASH;
        else if (in == "Block") value = DOBLOCK;
        else if (in == "Magic Dart") value = WIZDODART;
        else if (in == "Geyser") value = WIZDOGEYSER;
        else if (in == "Missile Form") value = WIZDOMISSILE;
        else if (in == "Orb") value = WIZDOORB;
        else if (in == "Tome Slap") value = WIZDOTSLAP;
    }

    return value;
}
  
#endif