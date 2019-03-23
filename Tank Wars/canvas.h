//TANK WARS
#pragma once
//#7.
//This File is Responsible For Drawing on The Screen.
#include "GameManager.h"

class Canvas
{
	static bool flag;
private:
	static void DrawPlayers();
	static void DrawObstacles();
	static void Clear();
	static void GameOver();
	static void UpdateScore();
	static void ShowGameName();
public:
	static void DisplayText(string test,int,int,const Color&,int);
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
void Canvas::DisplayText(string text, int x, int y,const Color& c=Color::RED(),int font=5)
{
	//selecting the font
	void *p=NULL;
	if(font<8 && font>0)	p = ((void *)font);
	else				    font = 5;

	Color textColor = c;
	textColor.SetGLColor();
	
	glRasterPos2f(x, y);
	size_t len = text.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(p, (int)text[i]);
}

//---------------------~>[ UPDATE ]<~---------------------
void  Canvas::Update(int time=100)
{
	if (isGamepaused) return;
	if (!isGameRunning && flag)
	{
		GameOver();
		glFlush();
		return; 
	}

	if (!isGameRunning) flag = true;				//to display one last frame before Freezing
	else        		flag = false;
	
	Canvas::Clear();

	
	GameManager::CheckGameObjectObstacleCollision();
	GameManager::CheckPlayerPlayerCollision();
	GameManager::CheckBulletBulletCollision();
	GameManager::CheckBulletPlayerCollision();

	DrawObstacles();
	DrawPlayers();									//order matters this call should be below Physics2D
	UpdateScore();
	ShowGameName();


	glutSwapBuffers();
	glutTimerFunc(GameSpeed,Update,0);					   //controls FramePerSec of the game
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

//---------------------~>[ DrawObstacles ]<~---------------------
void Canvas::DrawObstacles()
{
	//cache size;
	unsigned int oSize= gameObstacles.size();
	for (int i = 0; i < oSize; ++i)
	{
		//map design helpers
		//gameObstacles[i]->UpdatePos();
		//helpers ends

		gameObstacles[i]->Draw();
	}
}

//---------------------~>[ GameOver ]<~---------------------
void Canvas::GameOver()
{
	Color winColor(0, 0, 0);
	
	//Updating Score
	stringstream ss1;
	ss1 << P1WinCount;
	P1Score = ss1.str();

	stringstream ss2;
	ss2 << P2WinCount;
	P2Score = ss2.str();

	if (P1Alive)
	{
		winColor = P1->GetPlayerColor();
		DisplayText("P1 WINS", GAME_WIDTH / 2 - 60 - 1, GAME_HEIGHT / 2 + 50, Color::TEAL());
		DisplayText("P1 WINS", GAME_WIDTH / 2 - 60, GAME_HEIGHT / 2 + 50, Color::TEAL());
	}
	else
	{
		winColor = P2->GetPlayerColor();
		DisplayText("P2 WINS", GAME_WIDTH / 2 - 60 - 1, GAME_HEIGHT / 2 + 50, Color::TEAL());
		DisplayText("P2 WINS", GAME_WIDTH / 2 - 60, GAME_HEIGHT / 2 + 50, Color::TEAL());
	}
	DisplayText("PRESS 'r' to Restart", GAME_WIDTH / 2 - 120 - 1, GAME_HEIGHT / 2, winColor);
	DisplayText("PRESS 'r' to Restart", GAME_WIDTH / 2 - 120, GAME_HEIGHT / 2, winColor);

	//system("clear");				// for linux users
	system("CLS");					//for window users
	cout << "P1 WINS:" << P1WinCount << endl;
	cout << "P2 WINS:" << P2WinCount << endl;
}

//---------------------~>[ GameOver ]<~---------------------
void Canvas::UpdateScore()
{
	DisplayText("P1 SCORE", 15, GAME_HEIGHT-25,P1color);
	DisplayText(P1Score,15,GAME_HEIGHT-50,P1color);

	DisplayText("P2 SCORE", GAME_WIDTH-120, GAME_HEIGHT - 25, P2color);
	DisplayText(P2Score, GAME_WIDTH-120, GAME_HEIGHT - 50, P2color);
}

void Canvas:: ShowGameName()
{
	DisplayText("BATTLE TANKS",GAME_WIDTH/2-100,GAME_HEIGHT-GAME_MENU_AREA/2,Color::SPRINGGREEN());
	DisplayText("BATTLE TANKS",GAME_WIDTH/2-100,GAME_HEIGHT-GAME_MENU_AREA/2-1,Color::SPRINGGREEN());
}
