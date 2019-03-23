//TANK WARS
#pragma once
//#3.
#include "object.h"

class Player:public GameObject
{
	void Init(int dState = UPWARD)
	{
		height = 40;
		speed = 1.7;
		drawState = dState;
		state = NEUTRAL;
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

	void MoveForward()  { drawState = state = FORWARD; }
	void MoveBackward() { drawState = state = BACKWARD; }
	void MoveUpward()   { drawState = state = UPWARD; }
	void MoveDownward() { drawState = state = DOWNWARD; }
	void Dash()			{  }
	void StopMovement() { state = NEUTRAL; }

	void ReduceSize();
	
    //overrided func
	void Draw();
	void UpdatePos();
	Vector2 GetTopRight();    //returns topright point of player area
	Vector2 GetBottomLeft();   //returns bottomleft point of player area
};

//---------------------~>[ Get Player Extremes POSITION ]<~---------------------
Vector2 Player:: GetBottomLeft()   //returns bottomleft point of player area
{
	Vector2 temp(centre.x-height/2.0,centre.y-height/2.0);
	return temp;
}
Vector2 Player:: GetTopRight()   //returns bottomleft point of player area
{
	Vector2 temp(centre.x+height/2.0,centre.y+height/2.0);
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
		height -= 2;
	}
}


//---------------------~>[ Sharma Draw ]<~---------------------
void Player::Draw()
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

//---------------------~>[ Sangu Draw ]<~---------------------
/*
void Player::Draw()
{
	double x, y, size;

	x = centre.x;
	y = centre.y;
	size = height;

	double angle = 0;
	double r = M_PI / 180.0*(angle - 90);

	

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d((x + 7 * size / 5 - size / 5)*cos(r) - (y - size / 2)*sin(r), (x + 7 * size / 5 - size / 5)*sin(r) + (y - size / 2)*cos(r));
	glVertex2d((x + 7 * size / 5 + size / 5)*cos(r) - (y - size / 2)*sin(r), (x + 7 * size / 5 + size / 5)*sin(r) + (y - size / 2)*cos(r));
	glVertex2d((x + 7 * size / 5 + size / 5)*cos(r) - (y + 9 * size / 4)*sin(r), (x + 7 * size / 5 + size / 5)*sin(r) + (y + 9 * size / 4)*cos(r));
	glVertex2d((x + 7 * size / 5 - size / 5)*cos(r) - (y + 9 * size / 4)*sin(r), (x + 7 * size / 5 - size / 5)*sin(r) + (y + 9 * size / 4)*cos(r));
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d((x - 7 * size / 5 - size / 5)*cos(r) - (y - size / 2)*sin(r), (x - 7 * size / 5 - size / 5)*sin(r) + (y - size / 2)*cos(r));
	glVertex2d((x - 7 * size / 5 + size / 5)*cos(r) - (y - size / 2)*sin(r), (x - 7 * size / 5 + size / 5)*sin(r) + (y - size / 2)*cos(r));
	glVertex2d((x - 7 * size / 5 + size / 5)*cos(r) - (y + 9 * size / 4)*sin(r), (x - 7 * size / 5 + size / 5)*sin(r) + (y + 9 * size / 4)*cos(r));
	glVertex2d((x - 7 * size / 5 - size / 5)*cos(r) - (y + 9 * size / 4)*sin(r), (x - 7 * size / 5 - size / 5)*sin(r) + (y + 9 * size / 4)*cos(r));
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d((x - size / 2)*cos(r) - (y - 5 * size / 4)*sin(r), (x - size / 2)*sin(r) + (y - 5 * size / 4)*cos(r));
	glVertex2d((x + size / 2)*cos(r) - (y - 5 * size / 4)*sin(r), (x + size / 2)*sin(r) + (y - 5 * size / 4)*cos(r));
	glVertex2d((x + 7 * size / 5)*cos(r) - (y - size / 2)*sin(r), (x + 7 * size / 5)*sin(r) + (y - size / 2)*cos(r));
	glVertex2d((x + 7 * size / 5)*cos(r) - (y + 3 * size - 3 * size / 4)*sin(r), (x + 7 * size / 5)*sin(r) + (y + 3 * size - 3 * size / 4)*cos(r));
	glVertex2d((x + size / 2)*cos(r) - (y + 3 * size)*sin(r), (x + size / 2)*sin(r) + (y + 3 * size)*cos(r));
	glVertex2d((x - size / 2)*cos(r) - (y + 3 * size)*sin(r), (x - size / 2)*sin(r) + (y + 3 * size)*cos(r));
	glVertex2d((x - 7 * size / 5)*cos(r) - (y + 3 * size - 3 * size / 4)*sin(r), (x - 7 * size / 5)*sin(r) + (y + 3 * size - 3 * size / 4)*cos(r));
	glVertex2d((x - 7 * size / 5)*cos(r) - (y - size / 2)*sin(r), (x - 7 * size / 5)*sin(r) + (y - size / 2)*cos(r));
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d((x - size / 2 + size / 7)*cos(r) - (y - 5 * size / 4 + size / 7)*sin(r), (x - size / 2 + size / 7)*sin(r) + (y - 5 * size / 4 + size / 7)*cos(r));
	glVertex2d((x + size / 2 - size / 7)*cos(r) - (y - 5 * size / 4 + size / 7)*sin(r), (x + size / 2 - size / 7)*sin(r) + (y - 5 * size / 4 + size / 7)*cos(r));
	glVertex2d((x + 7 * size / 5 - size / 7)*cos(r) - (y - size / 2)*sin(r), (x + 7 * size / 5 - size / 7)*sin(r) + (y - size / 2)*cos(r));
	glVertex2d((x + 7 * size / 5 - size / 7)*cos(r) - (y + 3 * size - 3 * size / 4 - size / 7)*sin(r), (x + 7 * size / 5 - size / 7)*sin(r) + (y + 3 * size - 3 * size / 4 - size / 7)*cos(r));
	glVertex2d((x + size / 2 - size / 7)*cos(r) - (y + 3 * size - size / 7)*sin(r), (x + size / 2 - size / 7)*sin(r) + (y + 3 * size - size / 7)*cos(r));
	glVertex2d((x - size / 2 + size / 7)*cos(r) - (y + 3 * size - size / 7)*sin(r), (x - size / 2 + size / 7)*sin(r) + (y + 3 * size - size / 7)*cos(r));
	glVertex2d((x - 7 * size / 5 + size / 7)*cos(r) - (y + 3 * size - 3 * size / 4 - size / 7)*sin(r), (x - 7 * size / 5 + size / 7)*sin(r) + (y + 3 * size - 3 * size / 4 - size / 7)*cos(r));
	glVertex2d((x - 7 * size / 5 + size / 7)*cos(r) - (y - size / 2 + size / 7)*sin(r), (x - 7 * size / 5 + size / 7)*sin(r) + (y - size / 2 + size / 7)*cos(r));
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d((x - size / 2 - size / 10)*cos(r) - (y - size + size / 2 - size / 10)*sin(r), (x - size / 2 - size / 10)*sin(r) + (y - size + size / 2 - size / 10)*cos(r));
	glVertex2d((x + size / 2 + size / 10)*cos(r) - (y - size + size / 2 - size / 10)*sin(r), (x + size / 2 + size / 10)*sin(r) + (y - size + size / 2 - size / 10)*cos(r));
	glVertex2d((x + size + size / 10)*cos(r) - (y - size / 2 + size / 2 - size / 10)*sin(r), (x + size + size / 10)*sin(r) + (y - size / 2 + size / 2 - size / 10)*cos(r));
	glVertex2d((x + size + size / 10)*cos(r) - (y + size / 2 + size / 2 + size / 10)*sin(r), (x + size + size / 10)*sin(r) + (y + size / 2 + size / 2 + size / 10)*cos(r));
	glVertex2d((x + size / 2 + size / 10)*cos(r) - (y + size + size / 2 + size / 10)*sin(r), (x + size / 2 + size / 10)*sin(r) + (y + size + size / 2 + size / 10)*cos(r));
	glVertex2d((x - size / 2 - size / 10)*cos(r) - (y + size + size / 2 + size / 10)*sin(r), (x - size / 2 - size / 10)*sin(r) + (y + size + size / 2 + size / 10)*cos(r));
	glVertex2d((x - size - size / 10)*cos(r) - (y + size / 2 + size / 2 + size / 10)*sin(r), (x - size - size / 10)*sin(r) + (y + size / 2 + size / 2 + size / 10)*cos(r));
	glVertex2d((x - size - size / 10)*cos(r) - (y - size / 2 + size / 2 - size / 10)*sin(r), (x - size - size / 10)*sin(r) + (y - size / 2 + size / 2 - size / 10)*cos(r));
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2d((x - size / 2)*cos(r) - (y - size + size / 2)*sin(r), (x - size / 2)*sin(r) + (y - size + size / 2)*cos(r));
	glVertex2d((x + size / 2)*cos(r) - (y - size + size / 2)*sin(r), (x + size / 2)*sin(r) + (y - size + size / 2)*cos(r));
	glVertex2d((x + size)*cos(r) - (y - size / 2 + size / 2)*sin(r), (x + size)*sin(r) + (y - size / 2 + size / 2)*cos(r));
	glVertex2d((x + size)*cos(r) - (y + size / 2 + size / 2)*sin(r), (x + size)*sin(r) + (y + size / 2 + size / 2)*cos(r));
	glVertex2d((x + size / 2)*cos(r) - (y + size + size / 2)*sin(r), (x + size / 2)*sin(r) + (y + size + size / 2)*cos(r));
	glVertex2d((x - size / 2)*cos(r) - (y + size + size / 2)*sin(r), (x - size / 2)*sin(r) + (y + size + size / 2)*cos(r));
	glVertex2d((x - size)*cos(r) - (y + size / 2 + size / 2)*sin(r), (x - size)*sin(r) + (y + size / 2 + size / 2)*cos(r));
	glVertex2d((x - size)*cos(r) - (y - size / 2 + size / 2)*sin(r), (x - size)*sin(r) + (y - size / 2 + size / 2)*cos(r));
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d((x - size / 2)*cos(r) - (y + size + size / 2)*sin(r), (x - size / 2)*sin(r) - (y + size + size / 2)*cos(r));
	glVertex2d((x - size / 2)*cos(r) - (y + size + size / 5 + size / 2)*sin(r), (x - size / 2)*sin(r) - (y + size + size / 5 + size / 2)*cos(r));
	glVertex2d((x + size / 2)*cos(r) - (y + size + size / 5 + size / 2)*sin(r), (x + size / 2)*sin(r) - (y + size + size / 5 + size / 2)*cos(r));
	glVertex2d((x + size / 2)*cos(r) - (y + size + size / 2)*sin(r), (x + size / 2)*sin(r) - (y + size + size / 2)*cos(r));
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d((x - size / 8)*cos(r) - (y + 6 * size / 5 + size / 2)*sin(r), (x - size / 8)*sin(r) + (y + 6 * size / 5 + size / 2)*cos(r));
	glVertex2d((x - size / 8)*cos(r) - (y + 6 * size / 4 + 2 * size + size / 2)*sin(r), (x - size / 8)*sin(r) + (y + 6 * size / 4 + 2 * size + size / 2)*cos(r));
	glVertex2d((x + size / 8)*cos(r) - (y + 6 * size / 4 + 2 * size + size / 2)*sin(r), (x + size / 8)*sin(r) + (y + 6 * size / 4 + 2 * size + size / 2)*cos(r));
	glVertex2d((x + size / 8)*cos(r) - (y + 6 * size / 5 + size / 2)*sin(r), (x + size / 8)*sin(r) + (y + 6 * size / 5 + size / 2)*cos(r));
	glEnd();


}*/