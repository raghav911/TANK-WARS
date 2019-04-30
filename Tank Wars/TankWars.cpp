//TANK WARS

#include "pch.h"
#include<Gl/glut.h>
#include<iostream>
#include <vector>
#include<stdlib.h>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
#include<random>
#include<ctime>
using namespace std;

#include "essentials.h"
#include "object.h"
#include "player.h"
#include "Projectile.h"
#include "Obstacle.h"
#include "GameArea.h"
#include "LevelInformation.h"
#include "GameManager.h"
#include "canvas.h"
#include "global.h"
#include "Bot.h"
void GameHelpSection();

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	Init();
	InitCallbackFunc();

	GameHelpSection();
	ResetGame();
	
	srand(time(NULL));
	glutMainLoop();
	return 0;
}

//help section of the game
void GameHelpSection()
{
	cout << "~~~~~~~~~~~~{ WELCOME TO TANK WARS }~~~~~~~~~~~~"<<endl;
	cout << "2 Players can play on the same Device" << endl;
	cout << "MOTIVE:" << endl;
	cout << "You need to destroy other Player in Arena,you can Shoot Bullets" << endl;
	cout << "to Destroy Other Player" << endl;
	cout << "" << endl;
	cout << "CONTROLS:" << endl;
	cout << "Player1:" << endl;
	cout << "w := move Up" << endl;
	cout << "s := move Down" << endl;
	cout << "a := move Left" << endl;
	cout << "d := move Right" << endl;
	cout << "space := Shoots" << endl;

	cout << "" << endl;
	cout << "Player2:" << endl;
	cout << "up_arrow    := move Up" << endl;
	cout << "down_arrow  := move Down" << endl;
	cout << "left_arrow  := move Left" << endl;
	cout << "right_arrow := move Right" << endl;
	cout << "enter       := Shoots" << endl;
	cout << "" << endl;


	cout << "p   := pause/play" << endl;
	cout << "esc := pause/play" << endl;
	cout << "When your helth drops to minimum you " << endl;
	cout << "enter rage mode in this mode your bullets become powerful " << endl;
	cout << "and fast " << endl;


}

//THANKS FOR PLAYING
//MADE BY: SHUBAM SHARMA
//TANKS DESIGNED BY : AKASH SANGWAN