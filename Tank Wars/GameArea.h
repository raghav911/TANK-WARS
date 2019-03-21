#pragma once
//#5.
//This File Contains All The Information about Game.
//for e.g No. of Players,BulletCount,etc

bool isGameRunning = true;

Player *P1 = NULL;
Player *P2 = NULL;
bool P1Alive = true;
bool P2Alive = true;

vector<Projectile*> P1Bullet;
vector<Projectile*> P2Bullet;

int projectileCount = 4;//how much bullet Players can Shoot
int maxHit = 3;
int P1HitTaken=0;
int P2HitTaken=0;

void ResetGame();//defined in "global.h"
void PlayerControls(int key,int controllerType);//defined in "global.h"

