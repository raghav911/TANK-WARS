#pragma once
//#6.
//This File is Responsible For Drawing on The Screen.

class Canvas
{
	static bool flag;
private:
	static void DrawPlayers();
	static void Clear();
	static void CheckWin();
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
		return; 
	}

	if (!isGameRunning) flag = true;//to display one last frame before Freezing
	else        		flag = false;
	
	Canvas::Clear();

	DrawPlayers();

	glutSwapBuffers();
	glutTimerFunc(5,Update,0);
}

//---------------------~>[ Drawplayers ]<~---------------------
void Canvas:: DrawPlayers()
{
	if (P1)//Player 1 is Alive
	{
		P1->UpdatePos();
		P1->Draw();

		for (int i = 0; i < P1Bullet.size(); i++)//player 1 bullets
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
	DisplayText("GAMEOVER MAN GO HOME",width/2-100,height/2);
}