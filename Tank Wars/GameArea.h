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

string P1Score="0000";
string P2Score="0000";

Color P1color;
Color P2color;

vector<Projectile*> P1Bullet;
vector<Projectile*> P2Bullet;
vector<Obstacle*>   gameObstacles;
//Game State variables
bool isGamepaused=true;

int GameSpeed = 5;									//higher the value slower the game
int projectileCount = 4;							//how much bullet Players can Shoot
int maxHit = 3;
int P1HitTaken=0;
int P2HitTaken=0;
int P1WinCount = 0;
int P2WinCount = 0;

int xMouseClick = 0;
int yMouseClick = 0;

void ResetGame();									//defined in "global.h"
void PlayerControls(int key,int controllerType);	//defined in "global.h"