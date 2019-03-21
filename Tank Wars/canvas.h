#pragma once
//#6.
//This File is Responsible For Drawing on The Screen.

class Canvas
{
	static bool flag;
private:
	static void DrawPlayers();
	static void Clear();
	static void CheckBulletCollision();
	static void CheckPlayerCollision();
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

	if (!isGameRunning) flag = true;//to display one last frame before Freezing
	else        		flag = false;
	
	Canvas::Clear();

	DrawPlayers();
	
	CheckBulletCollision();
	CheckPlayerCollision();

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
}

//---------------------~>[ Bullet Collision ]<~---------------------
void Canvas:: CheckBulletCollision()
{
	if (P1 == NULL || P2 == NULL) return;//defence
	Vector2 bPoint;//bullet Point
	int bSize;

	Vector2 p1Point = P1->GetCentre();
	int p1Size = P1->GetSize();

	Vector2 p2Point = P2->GetCentre();
	int p2Size = P2->GetSize();

	int P1BulletCount = P1Bullet.size();
	int P2BulletCount = P2Bullet.size();

	for (int i = 0; i < P1BulletCount; i++)//player 1 bullets
	{
		bPoint = P1Bullet[i]->GetCentre();
		bSize = P1Bullet[i]->GetSize();

		//check whether i bullet hit the P2 player
		bool hit = false;
		int bState = P1Bullet[i]->GetState();
		int x_inc = 0, y_inc = 0;
		
		switch (bState)//bulletState
		{
		case FORWARD:
			x_inc = bSize / 2;
			break;
		case BACKWARD:
			x_inc = -bSize / 2;
			break;
		case UPWARD:
			y_inc = bSize / 2;
			break;
		case DOWNWARD:
			y_inc = -bSize / 2;
			break;
		}

		int x = bPoint.x + x_inc;
		int y = bPoint.y + y_inc;

		if (y > (p2Point.y - p2Size) && y < (p2Point.y + p2Size))//bullet y is in range of P2
		{
			if (x > (p2Point.x - p2Size) && x<(p2Point.x+p2Size))
			{
				hit = true;
				P2->ReduceSize();
			}
		}

		if (x > width || y > height || x < 0 || y < 0 || hit)
		{
			P1Bullet.erase(P1Bullet.begin() + i);
			P1BulletCount--;
		}

		if (hit && ++P2HitTaken >= maxHit)//P2 Loses
		{
			cout << "P1 WINS" << endl;

			P2Alive = false;
			P2Bullet.clear();
			P2 = NULL;
			isGameRunning = false;
			return;
		}
	}//P1 Wins Or not

	for (int i = 0; i < P2BulletCount; i++)//player 2 bullets
	{
		bPoint = P2Bullet[i]->GetCentre();
		bSize = P2Bullet[i]->GetSize();

		//check whether i bullet hit the P2 player
		bool hit = false;
		int bState = P2Bullet[i]->GetState();
		int x_inc = 0, y_inc = 0;

		switch (bState)//bulletState
		{
		case FORWARD:
			x_inc = bSize / 2;
			break;
		case BACKWARD:
			x_inc = -bSize / 2;
			break;
		case UPWARD:
			y_inc = bSize / 2;
			break;
		case DOWNWARD:
			y_inc = -bSize / 2;
			break;
		}

		int x = bPoint.x + x_inc;
		int y = bPoint.y + y_inc;

		if (y > (p1Point.y - p1Size) && y < (p1Point.y + p1Size))//bullet y is in range of P2
		{
			if (x < (p1Point.x + p1Size) && x>(p1Point.x-p1Size))
			{
				hit = true;
				P1->ReduceSize();
			}
		}
		if (x >width ||y>height||x<0||y<0|| hit)//to vanish unused bullets of P2
		{
			P2Bullet.erase(P2Bullet.begin() + i);
			P2BulletCount--;
		}

		//p1 loses and p2 wins
		if (hit && ++P1HitTaken >= maxHit)//P1 loses
		{
			cout << "P2 WINS" << endl;

			P1Alive = false;
			P1 = NULL;
			P1Bullet.clear();
			isGameRunning = false;
			return;
		}

	}//P2 Wins Or Not
}

//---------------------~>[ Player Collision ]<~---------------------
void Canvas::CheckPlayerCollision()
{
	if (P1 == NULL || P2 == NULL) return;//defence


}