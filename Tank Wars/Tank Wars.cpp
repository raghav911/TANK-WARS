#include "pch.h"
#include<Gl/glut.h>
#include<iostream>
#include <vector>
#include<stdlib.h>

using namespace std;

#include "essentials.h"
#include "object.h"
#include "player.h"
#include "projectile.h"
#include "GameArea.h"
#include "GameManager.h"
#include "canvas.h"
#include "global.h"

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	Init();

	ResetGame();

	glutMainLoop();
	return 0;
}
