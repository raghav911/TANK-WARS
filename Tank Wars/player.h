//TANK WARS
#pragma once
//#3.
#include "object.h"

class Player:public GameObject
{
	double sizeReducedPerHit;
	double centreOffset=0; 
	double criticalHealth;

	void Init(int dState = UPWARD)
	{
		height              = 15;
		speed               = 2.5;
		drawState           = dState;
		state               = NEUTRAL;
		sizeReducedPerHit   = 0.9;
		centreOffset        = height;
		health              = 4;
		criticalHealth      = 1;
	}
public:
	
	Player(double x,double y, int dState)
	{
		centre.x = x;
		centre.y = y;
		Init(dState);
	}
	Player(const Vector2 &point)
	{
		centre = point;
		Init();
	}

	//unique functions
	void Move(int st);
	void StopMovement() { state = NEUTRAL; }
	void ReduceSize();
	bool RageMode()     { return health <= criticalHealth ? true : false; }
	//void Dash()			{  }
	
	//overrided func
	void Draw();
	void UpdatePos();

	//setters
	void SetState(int st)                 { this->state = st; }
	void SetColor(int r, int g, int b)    { color.SetColor(r, g, b); }
	void SetColor(const Color &c)         { color = c; }
	void SetSize(int sz)                  { this->height = sz; }
	void SetWidth(int wd)                 { this->width = wd; }
	void SetSpeed(double sp)              { this->speed = sp; }
	void SetInternalColor(const Color& c) { internal = c; }
	void IncreaseSpeed(double inc)        { speed += inc; }

	//getters
	string GetType()                      { return "player"; }
	int GetDrawState()                    { return drawState; }
	int GetState()                        { return state; }
	int GetSize()                         { return height; }
	Color GetPlayerColor()                { return color; }
	bool IsDead()                         { return health <= 0 ? true : false; }
	void RecieveDamage(double dmg)        { this->health -= dmg; }
	Vector2 GetCentre();
	//double GetDamage()                  { return this->damage; }

	//Box Colliders
	Vector2 GetTopRight();     //returns topright point of player area
	Vector2 GetBottomLeft();   //returns bottomleft point of player area
};



void Player:: Move(int st)
{
	if (st > 6) return;
	if (st == RANDOM)
		st = rand() % 4;
	
	drawState = state = st;

	
}













//---------------------~>[ Get Player Extremes POSITION ]<~---------------------
Vector2 Player:: GetBottomLeft()   //returns bottomleft point of player area
{
	Vector2 temp;
	switch (drawState)
	{
	case UPWARD:
		temp(centre.x - 7 * height / 5, centre.y - 5 * height / 4);
		break;

	case DOWNWARD:
		temp(centre.x - 7 * height / 5, centre.y - 3 * height);
		break;

	case FORWARD:
		temp(centre.x - 5 * height / 4, centre.y -7 * height / 5);
		break;

	case BACKWARD:
		temp(centre.x - 3 * height, centre.y - 7 * height / 5);
		break;
	}
	return temp;
}
Vector2 Player:: GetTopRight()   //returns bottomleft point of player area
{
	Vector2 temp;
	switch (drawState)
	{
	case UPWARD:
		 temp(centre.x + 7 * height / 5, centre.y + 3 * height);
		break;
	case DOWNWARD:
		temp(centre.x + 7 * height / 5, centre.y + 5 * height / 4);
		break;

	case FORWARD:
		temp(centre.x + 3 * height, centre.y + 7 * height / 5);
		break;

	case BACKWARD:
		temp(centre.x + 5 * height / 4, centre.y + 7 * height / 5);
		break;
	}
	return temp;
}

//---------------------~>[ UPDATE POSITION ]<~---------------------
void Player::UpdatePos()
{
	bool dashed = false;
	double x_min, y_min, x_max, y_max;

	x_min = centre.x - height / 2;
	y_min = centre.y - height / 2;
	x_max = centre.x + height / 2;
	y_max = centre.y + height / 2;

	switch(state)
	{
	case FORWARD:
		if(x_max<GAME_WIDTH)
		centre.x+=speed;
		break;
	case BACKWARD:
		if(x_min>0)
		centre.x-=speed;
		break;
	case DOWNWARD:
		if (y_min>0)
			centre.y-=speed;
		break;
	case UPWARD:
		if (y_max<GAME_HEIGHT)
			centre.y+=speed;
		break;
	}
}

//---------------------~>[ Reduce_size ]<~---------------------
void Player:: ReduceSize()
{
	if (height > 5)
	{
		height -= sizeReducedPerHit;
	}
}

//bool Player::RecieveDamage(double damage)
//{
//	health -= damage;
//	if (health <= 0) return true;
//	return false;
//}

//---------------------~>[ GET_CENTRE ]<~---------------------
Vector2 Player::GetCentre()
{
	Vector2 temp;
	switch (drawState)
	{
	case FORWARD:
		temp(centre.x+centreOffset,centre.y);
		break;

	case BACKWARD:
		temp(centre.x - centreOffset, centre.y);
		break;

	case UPWARD:
		temp(centre.x , centre.y+centreOffset);
		break;

	case DOWNWARD:
		temp(centre.x, centre.y - centreOffset);
		break;
	}
	return temp;
}

//---------------------~>[ Sharma Draw ]<~---------------------
/*void Player::Draw()
{
	this->color.SetGLColor();
	
	switch(drawState)
	{
	case FORWARD:
		DrawRectangle(centre.x, centre.y, height, height);//Draw Basic Rectangle
		glColor3f(0, 0, 0);//drawing Black Nozzle
		DrawRectangle(centre.x + height / 2, centre.y, 0.8*height, 0.1*height);//nozzle
		break;
	case BACKWARD:
		DrawRectangle(centre.x, centre.y, height, height);//Draw Basic Rectangle
		glColor3f(0, 0, 0);//drawing Black Nozzle
		DrawRectangle(centre.x - height / 2, centre.y, 0.8*height, 0.1*height);//nozzle
		break;
	case UPWARD:
		DrawRectangle(centre.x, centre.y, height, height);//Draw Basic Rectangle
		glColor3f(0, 0, 0);//drawing Black Nozzle
		DrawRectangle(centre.x, centre.y + height / 2, 0.1*height, 0.8*height);//nozzle
		break;
	case DOWNWARD:
		DrawRectangle(centre.x, centre.y, height, height);//Draw Basic Rectangle
		glColor3f(0, 0, 0);//drawing Black Nozzle
		DrawRectangle(centre.x, centre.y - height / 2, 0.1*height, 0.8*height);//nozzle
		break;
	}
}
*/
//---------------------~>[ Sangu Draw ]<~---------------------
void Player::Draw()
{
	//DRAWS COLLIDERS
	//DrawRectangleCorner(GetBottomLeft().x,GetBottomLeft().y, GetTopRight().x, GetTopRight().y);
	//DText("o", GetBottomLeft().x, GetBottomLeft().y,Color::RED(),3);
	//DText("o", GetTopRight().x, GetTopRight().y,Color::YELLOW(),3);
	
	double x, y, size;
	
	x = centre.x;
	y = centre.y;
	size = height;

	switch (drawState)
	{
	case DOWNWARD:
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(x + 7 * size / 5 - size / 5, y + size / 2);
		glVertex2d(x + 7 * size / 5 + size / 5, y + size / 2);
		glVertex2d(x + 7 * size / 5 + size / 5, y - 9 * size / 4);
		glVertex2d(x + 7 * size / 5 - size / 5, y - 9 * size / 4);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(x - 7 * size / 5 - size / 5, y + size / 2);
		glVertex2d(x - 7 * size / 5 + size / 5, y + size / 2);
		glVertex2d(x - 7 * size / 5 + size / 5, y - 9 * size / 4);
		glVertex2d(x - 7 * size / 5 - size / 5, y - 9 * size / 4);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(x - size / 2, y + 5 * size / 4);
		glVertex2d(x + size / 2, y + 5 * size / 4);
		glVertex2d(x + 7 * size / 5, y + size / 2);
		glVertex2d(x + 7 * size / 5, y - 3 * size + 3 * size / 4);
		glVertex2d(x + size / 2, y - 3 * size);
		glVertex2d(x - size / 2, y - 3 * size);
		glVertex2d(x - 7 * size / 5, y - 3 * size + 3 * size / 4);
		glVertex2d(x - 7 * size / 5, y + size / 2);
		glEnd();

		this->color.SetGLColor();

		glBegin(GL_POLYGON);
		glVertex2d(x - size / 2 + size / 7, y + 5 * size / 4 - size / 7);
		glVertex2d(x + size / 2 - size / 7, y + 5 * size / 4 - size / 7);
		glVertex2d(x + 7 * size / 5 - size / 7, y + size / 2);
		glVertex2d(x + 7 * size / 5 - size / 7, y - 3 * size + 3 * size / 4 + size / 7);
		glVertex2d(x + size / 2 - size / 7, y - 3 * size + size / 7);
		glVertex2d(x - size / 2 + size / 7, y - 3 * size + size / 7);
		glVertex2d(x - 7 * size / 5 + size / 7, y - 3 * size + 3 * size / 4 + size / 7);
		glVertex2d(x - 7 * size / 5 + size / 7, y + size / 2 - size / 7);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(x - size / 2 - size / 10, y + size - size / 2 + size / 10);
		glVertex2d(x + size / 2 + size / 10, y + size - size / 2 + size / 10);
		glVertex2d(x + size + size / 10, y + size / 2 - size / 2 + size / 10);
		glVertex2d(x + size + size / 10, y - size / 2 - size / 2 - size / 10);
		glVertex2d(x + size / 2 + size / 10, y - size - size / 2 - size / 10);
		glVertex2d(x - size / 2 - size / 10, y - size - size / 2 - size / 10);
		glVertex2d(x - size - size / 10, y - size / 2 - size / 2 - size / 10);
		glVertex2d(x - size - size / 10, y + size / 2 - size / 2 + size / 10);
		glEnd();

		this->internal.SetGLColor();
		glBegin(GL_POLYGON);
		glVertex2d(x - size / 2, y + size - size / 2);
		glVertex2d(x + size / 2, y + size - size / 2);
		glVertex2d(x + size, y + size / 2 - size / 2);
		glVertex2d(x + size, y - size / 2 - size / 2);
		glVertex2d(x + size / 2, y - size - size / 2);
		glVertex2d(x - size / 2, y - size - size / 2);
		glVertex2d(x - size, y - size / 2 - size / 2);
		glVertex2d(x - size, y + size / 2 - size / 2);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(x - size / 2, y - size - size / 2);
		glVertex2d(x - size / 2, y - size - size / 5 - size / 2);
		glVertex2d(x + size / 2, y - size - size / 5 - size / 2);
		glVertex2d(x + size / 2, y - size - size / 2);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(x - size / 8, y - 6 * size / 5 - size / 2);
		glVertex2d(x - size / 8, y - 6 * size / 4 - 2 * size - size / 2);
		glVertex2d(x + size / 8, y - 6 * size / 4 - 2 * size - size / 2);
		glVertex2d(x + size / 8, y - 6 * size / 5 - size / 2);
		glEnd();
		break;

	case FORWARD:
		swap(x, y);
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(y - size / 2, x + 7 * size / 5 - size / 5);
		glVertex2d(y - size / 2, x + 7 * size / 5 + size / 5);
		glVertex2d(y + 9 * size / 4, x + 7 * size / 5 + size / 5);
		glVertex2d(y + 9 * size / 4, x + 7 * size / 5 - size / 5);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(y - size / 2, x - 7 * size / 5 - size / 5);
		glVertex2d(y - size / 2, x - 7 * size / 5 + size / 5);
		glVertex2d(y + 9 * size / 4, x - 7 * size / 5 + size / 5);
		glVertex2d(y + 9 * size / 4, x - 7 * size / 5 - size / 5);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(y - 5 * size / 4, x - size / 2);
		glVertex2d(y - 5 * size / 4, x + size / 2);
		glVertex2d(y - size / 2, x + 7 * size / 5);
		glVertex2d(y + 3 * size - 3 * size / 4, x + 7 * size / 5);
		glVertex2d(y + 3 * size, x + size / 2);
		glVertex2d(y + 3 * size, x - size / 2);
		glVertex2d(y + 3 * size - 3 * size / 4, x - 7 * size / 5);
		glVertex2d(y - size / 2, x - 7 * size / 5);
		glEnd();

		this->color.SetGLColor();

		glBegin(GL_POLYGON);
		glVertex2d(y - 5 * size / 4 + size / 7, x - size / 2 + size / 7);
		glVertex2d(y - 5 * size / 4 + size / 7, x + size / 2 - size / 7);
		glVertex2d(y - size / 2, x + 7 * size / 5 - size / 7);
		glVertex2d(y + 3 * size - 3 * size / 4 - size / 7, x + 7 * size / 5 - size / 7);
		glVertex2d(y + 3 * size - size / 7, x + size / 2 - size / 7);
		glVertex2d(y + 3 * size - size / 7, x - size / 2 + size / 7);
		glVertex2d(y + 3 * size - 3 * size / 4 - size / 7, x - 7 * size / 5 + size / 7);
		glVertex2d(y - size / 2 + size / 7, x - 7 * size / 5 + size / 7);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(y - size + size / 2 - size / 10, x - size / 2 - size / 10);
		glVertex2d(y - size + size / 2 - size / 10, x + size / 2 + size / 10);
		glVertex2d(y - size / 2 + size / 2 - size / 10, x + size + size / 10);
		glVertex2d(y + size / 2 + size / 2 + size / 10, x + size + size / 10);
		glVertex2d(y + size + size / 2 + size / 10, x + size / 2 + size / 10);
		glVertex2d(y + size + size / 2 + size / 10, x - size / 2 - size / 10);
		glVertex2d(y + size / 2 + size / 2 + size / 10, x - size - size / 10);
		glVertex2d(y - size / 2 + size / 2 - size / 10, x - size - size / 10);
		glEnd();

		this->internal.SetGLColor();

		glBegin(GL_POLYGON);
		glVertex2d(y - size + size / 2, x - size / 2);
		glVertex2d(y - size + size / 2, x + size / 2);
		glVertex2d(y - size / 2 + size / 2, x + size);
		glVertex2d(y + size / 2 + size / 2, x + size);
		glVertex2d(y + size + size / 2, x + size / 2);
		glVertex2d(y + size + size / 2, x - size / 2);
		glVertex2d(y + size / 2 + size / 2, x - size);
		glVertex2d(y - size / 2 + size / 2, x - size);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(y + size + size / 2, x - size / 2);
		glVertex2d(y + size + size / 5 + size / 2, x - size / 2);
		glVertex2d(y + size + size / 5 + size / 2, x + size / 2);
		glVertex2d(y + size + size / 2, x + size / 2);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(y + 6 * size / 5 + size / 2, x - size / 8);
		glVertex2d(y + 6 * size / 4 + 2 * size + size / 2, x - size / 8);
		glVertex2d(y + 6 * size / 4 + 2 * size + size / 2, x + size / 8);
		glVertex2d(y + 6 * size / 5 + size / 2, x + size / 8);
		glEnd();
		break;

	case UPWARD:
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(x + 7 * size / 5 - size / 5, y - size / 2);
		glVertex2d(x + 7 * size / 5 + size / 5, y - size / 2);
		glVertex2d(x + 7 * size / 5 + size / 5, y + 9 * size / 4);
		glVertex2d(x + 7 * size / 5 - size / 5, y + 9 * size / 4);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(x - 7 * size / 5 - size / 5, y - size / 2);
		glVertex2d(x - 7 * size / 5 + size / 5, y - size / 2);
		glVertex2d(x - 7 * size / 5 + size / 5, y + 9 * size / 4);
		glVertex2d(x - 7 * size / 5 - size / 5, y + 9 * size / 4);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(x - size / 2, y - 5 * size / 4);
		glVertex2d(x + size / 2, y - 5 * size / 4);
		glVertex2d(x + 7 * size / 5, y - size / 2);
		glVertex2d(x + 7 * size / 5, y + 3 * size - 3 * size / 4);
		glVertex2d(x + size / 2, y + 3 * size);
		glVertex2d(x - size / 2, y + 3 * size);
		glVertex2d(x - 7 * size / 5, y + 3 * size - 3 * size / 4);
		glVertex2d(x - 7 * size / 5, y - size / 2);
		glEnd();

		this->color.SetGLColor();

		glBegin(GL_POLYGON);
		glVertex2d(x - size / 2 + size / 7, y - 5 * size / 4 + size / 7);
		glVertex2d(x + size / 2 - size / 7, y - 5 * size / 4 + size / 7);
		glVertex2d(x + 7 * size / 5 - size / 7, y - size / 2);
		glVertex2d(x + 7 * size / 5 - size / 7, y + 3 * size - 3 * size / 4 - size / 7);
		glVertex2d(x + size / 2 - size / 7, y + 3 * size - size / 7);
		glVertex2d(x - size / 2 + size / 7, y + 3 * size - size / 7);
		glVertex2d(x - 7 * size / 5 + size / 7, y + 3 * size - 3 * size / 4 - size / 7);
		glVertex2d(x - 7 * size / 5 + size / 7, y - size / 2 + size / 7);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(x - size / 2 - size / 10, y - size + size / 2 - size / 10);
		glVertex2d(x + size / 2 + size / 10, y - size + size / 2 - size / 10);
		glVertex2d(x + size + size / 10, y - size / 2 + size / 2 - size / 10);
		glVertex2d(x + size + size / 10, y + size / 2 + size / 2 + size / 10);
		glVertex2d(x + size / 2 + size / 10, y + size + size / 2 + size / 10);
		glVertex2d(x - size / 2 - size / 10, y + size + size / 2 + size / 10);
		glVertex2d(x - size - size / 10, y + size / 2 + size / 2 + size / 10);
		glVertex2d(x - size - size / 10, y - size / 2 + size / 2 - size / 10);
		glEnd();

		this->internal.SetGLColor();

		glBegin(GL_POLYGON);
		glVertex2d(x - size / 2, y - size + size / 2);
		glVertex2d(x + size / 2, y - size + size / 2);
		glVertex2d(x + size, y - size / 2 + size / 2);
		glVertex2d(x + size, y + size / 2 + size / 2);
		glVertex2d(x + size / 2, y + size + size / 2);
		glVertex2d(x - size / 2, y + size + size / 2);
		glVertex2d(x - size, y + size / 2 + size / 2);
		glVertex2d(x - size, y - size / 2 + size / 2);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(x - size / 2, y + size + size / 2);
		glVertex2d(x - size / 2, y + size + size / 5 + size / 2);
		glVertex2d(x + size / 2, y + size + size / 5 + size / 2);
		glVertex2d(x + size / 2, y + size + size / 2);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(x - size / 8, y + 6 * size / 5 + size / 2);
		glVertex2d(x - size / 8, y + 6 * size / 4 + 2 * size + size / 2);
		glVertex2d(x + size / 8, y + 6 * size / 4 + 2 * size + size / 2);
		glVertex2d(x + size / 8, y + 6 * size / 5 + size / 2);
		glEnd();
		break;
	case BACKWARD:
		swap(x, y);
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(y + size / 2, x + 7 * size / 5 - size / 5);
		glVertex2d(y + size / 2, x + 7 * size / 5 + size / 5);
		glVertex2d(y - 9 * size / 4, x + 7 * size / 5 + size / 5);
		glVertex2d(y - 9 * size / 4, x + 7 * size / 5 - size / 5);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(y + size / 2, x - 7 * size / 5 - size / 5);
		glVertex2d(y + size / 2, x - 7 * size / 5 + size / 5);
		glVertex2d(y - 9 * size / 4, x - 7 * size / 5 + size / 5);
		glVertex2d(y - 9 * size / 4, x - 7 * size / 5 - size / 5);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(y + 5 * size / 4, x - size / 2);
		glVertex2d(y + 5 * size / 4, x + size / 2);
		glVertex2d(y + size / 2, x + 7 * size / 5);
		glVertex2d(y - 3 * size + 3 * size / 4, x + 7 * size / 5);
		glVertex2d(y - 3 * size, x + size / 2);
		glVertex2d(y - 3 * size, x - size / 2);
		glVertex2d(y - 3 * size + 3 * size / 4, x - 7 * size / 5);
		glVertex2d(y + size / 2, x - 7 * size / 5);
		glEnd();

		this->color.SetGLColor();

		glBegin(GL_POLYGON);
		glVertex2d(y + 5 * size / 4 - size / 7, x - size / 2 + size / 7);
		glVertex2d(y + 5 * size / 4 - size / 7, x + size / 2 - size / 7);
		glVertex2d(y + size / 2, x + 7 * size / 5 - size / 7);
		glVertex2d(y - 3 * size + 3 * size / 4 + size / 7, x + 7 * size / 5 - size / 7);
		glVertex2d(y - 3 * size + size / 7, x + size / 2 - size / 7);
		glVertex2d(y - 3 * size + size / 7, x - size / 2 + size / 7);
		glVertex2d(y - 3 * size + 3 * size / 4 + size / 7, x - 7 * size / 5 + size / 7);
		glVertex2d(y + size / 2 - size / 7, x - 7 * size / 5 + size / 7);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(y + size - size / 2 + size / 10, x - size / 2 - size / 10);
		glVertex2d(y + size - size / 2 + size / 10, x + size / 2 + size / 10);
		glVertex2d(y + size / 2 - size / 2 + size / 10, x + size + size / 10);
		glVertex2d(y - size / 2 - size / 2 - size / 10, x + size + size / 10);
		glVertex2d(y - size - size / 2 - size / 10, x + size / 2 + size / 10);
		glVertex2d(y - size - size / 2 - size / 10, x - size / 2 - size / 10);
		glVertex2d(y - size / 2 - size / 2 - size / 10, x - size - size / 10);
		glVertex2d(y + size / 2 - size / 2 + size / 10, x - size - size / 10);
		glEnd();

		this->internal.SetGLColor();

		glBegin(GL_POLYGON);
		glVertex2d(y + size - size / 2, x - size / 2);
		glVertex2d(y + size - size / 2, x + size / 2);
		glVertex2d(y + size / 2 - size / 2, x + size);
		glVertex2d(y - size / 2 - size / 2, x + size);
		glVertex2d(y - size - size / 2, x + size / 2);
		glVertex2d(y - size - size / 2, x - size / 2);
		glVertex2d(y - size / 2 - size / 2, x - size);
		glVertex2d(y + size / 2 - size / 2, x - size);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(y - size - size / 2, x - size / 2);
		glVertex2d(y - size - size / 5 - size / 2, x - size / 2);
		glVertex2d(y - size - size / 5 - size / 2, x + size / 2);
		glVertex2d(y - size - size / 2, x + size / 2);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2d(y - 6 * size / 5 - size / 2, x - size / 8);
		glVertex2d(y - 6 * size / 4 - 2 * size - size / 2, x - size / 8);
		glVertex2d(y - 6 * size / 4 - 2 * size - size / 2, x + size / 8);
		glVertex2d(y - 6 * size / 5 - size / 2, x + size / 8);
		glEnd();
		break;
	}
}