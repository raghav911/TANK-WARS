//TANK WARS
#pragma once
//#5.
//This File Contains All The Information about Game.
//for e.g No. of Players,BulletCount,etc

bool isGameRunning = true;

Player *P1 = NULL;
Player *P2 = NULL;
bool P1Alive = true;
bool P2Alive = true;


//BOT
bool autoPlay = false;
void BotPlay(int);
unsigned int botReactionTime = 1;

string P1Score="0000";
string P2Score="0000";

Color P1color;
Color P2color;

vector<Projectile*> P1Bullet;
vector<Projectile*> P2Bullet;
vector<Obstacle*>   gameObstacles;
//Game State variables
bool isGamepaused=true;

int GameSpeed = 5;									//higher the value slower the game(FPS of the Game)
int projectileCount = 4;							//how much bullet Players can Shoot
int P1WinCount = 0;
int P2WinCount = 0;

//checking click in start button used in "canvas.h"
int xMouseClick = 0;
int yMouseClick = 0;

void ResetGame();									//defined in "global.h"
void PlayerControls(int key,ControllerState controller);	//defined in "global.h"