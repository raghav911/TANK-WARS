#pragma once
//#7.
//This File is Responsible For Drawing on The Screen.
#include "GameManager.h"

class Canvas
{
	static bool flag;
private:
	static void DrawPlayers();
	static void Clear();
	static void GameOver();
public:
	static void DisplayText(const char*,int,int,const Color&);
	static void Update(int);
};
bool Canvas::flag = false;

//---------------------~>[ CLEAR ]<~---------------------
void Canvas:: Clear()
{
	glClearColor((double)57 / 255, (double)64 / 255, (double)62 / 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

//---------------------~>[ Display TEXT ]<~---------------------
void Canvas::DisplayText(const char* text, int x, int y,const Color& c=Color::RED())
{
	Color textColor = c;
	textColor.SetGLColor();

	glRasterPos2f(x, y);
	size_t len = strlen(text);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
}

//---------------------~>[ UPDATE ]<~---------------------
void  Canvas::Update(int time=100)
{
	if (!isGameRunning && flag)
	{
		GameOver();
		glFlush();
		return; 
	}

	if (!isGameRunning) flag = true;				//to display one last frame before Freezing
	else        		flag = false;
	
	Canvas::Clear();

	
	GameManager::CheckBulletPlayerCollision();
	GameManager::CheckPlayerPlayerCollision();

	DrawPlayers();									//order matters this call should be below Physics2D
	
	glutSwapBuffers();
	glutTimerFunc(5,Update,0);					   //controls FramePerSec of the game
}

//---------------------~>[ Drawplayers ]<~---------------------
void Canvas:: DrawPlayers()
{
	if (P1)//Player 1 is Alive
	{
		P1->UpdatePos();
		P1->Draw();

		for (int i = 0; i < P1Bullet.size(); i++)	//player 1 bullets
		{
			P1Bullet[i]->UpdatePos();
			P1Bullet[i]->Draw();
		}
	}

	if (P2)//Player 2 is Alive
	{
		P2->UpdatePos();
		P2->Draw();

		for (int i = 0; i < P2Bullet.size(); i++)//player 2 bullets
		{
			P2Bullet[i]->UpdatePos();
			P2Bullet[i]->Draw();
		}
	}
}

//---------------------~>[ GameOver ]<~---------------------
void Canvas::GameOver()
{
	Color winColor(0, 0, 0);
	if (P1Alive)
	{
		winColor = P1->GetPlayerColor();
		DisplayText("P1 WINS", width / 2 - 60 - 1, height / 2 + 50, Color::TEAL());
		DisplayText("P1 WINS", width / 2 - 60, height / 2 + 50, Color::TEAL());
	}
	else
	{
		winColor = P2->GetPlayerColor();
		DisplayText("P2 WINS", width / 2 - 60 - 1, height / 2 + 50, Color::TEAL());
		DisplayText("P2 WINS", width / 2 - 60, height / 2 + 50, Color::TEAL());
	}
	DisplayText("PRESS 'r' to Restart", width / 2 - 120 - 1, height / 2, winColor);
	DisplayText("PRESS 'r' to Restart", width / 2 - 120, height / 2, winColor);

	cout << "P1 WINS:" << P1WinCount << endl;
	cout << "P2 WINS:" << P2WinCount << endl;
}
