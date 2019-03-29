//TANK WARS

#include "pch.h"
#include<Gl/glut.h>
#include<iostream>
#include <vector>
#include<stdlib.h>
#include<sstream>
#define _USE_MATH_DEFINES
#include<math.h>
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

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	Init();
	InitCallbackFunc();

	ResetGame();

	glutMainLoop();
	return 0;
}




//THANKS FOR PLAYING
//MADE BY: SHUBAM SHARMA