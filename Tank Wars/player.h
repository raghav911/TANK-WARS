#pragma once
//#3.
#include "object.h"

class Player:public GameObject
{
	void Init(int dState = UPWARD)
	{
		size = 40;
		speed = 1.5;
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
	Vector2 temp(centre.x-size/2.0,centre.y-size/2.0);
	return temp;
}
Vector2 Player:: GetTopRight()   //returns bottomleft point of player area
{
	Vector2 temp(centre.x+size/2.0,centre.y+size/2.0);
	return temp;
}
//---------------------~>[ UPDATE POSITION ]<~---------------------
void Player::UpdatePos()
{
	double x_min, y_min, x_max, y_max;

	x_min = centre.x - size / 2;
	y_min = centre.y - size / 2;
	x_max = centre.x + size / 2;
	y_max = centre.y + size / 2;

	switch(state)
	{
	case FORWARD:
		if(x_max<WIDTH)
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
		if (y_max<HEIGHT)
			centre.y+=speed;
		break;
	}
}

//---------------------~>[ Reduce_size ]<~---------------------
void Player:: ReduceSize()
{
	if (size > 5)
	{
		size -= 2;
	}
}
//---------------------~>[ Sharma Draw ]<~---------------------
void Player::Draw()
{
	this->color.SetGLColor();
	
	switch(drawState)
	{
	case FORWARD:
		DrawRectangle(centre.x, centre.y, size, size);//Draw Basic Rectangle
		glColor3f(0, 0, 0);//drawing Black Nozzle
		DrawRectangle(centre.x + size / 2, centre.y, 0.8*size, 0.1*size);//nozzle
		break;
	case BACKWARD:
		DrawRectangle(centre.x, centre.y, size, size);//Draw Basic Rectangle
		glColor3f(0, 0, 0);//drawing Black Nozzle
		DrawRectangle(centre.x - size / 2, centre.y, 0.8*size, 0.1*size);//nozzle
		break;
	case UPWARD:
		DrawRectangle(centre.x, centre.y, size, size);//Draw Basic Rectangle
		glColor3f(0, 0, 0);//drawing Black Nozzle
		DrawRectangle(centre.x, centre.y + size / 2, 0.1*size, 0.8*size);//nozzle
		break;
	case DOWNWARD:
		DrawRectangle(centre.x, centre.y, size, size);//Draw Basic Rectangle
		glColor3f(0, 0, 0);//drawing Black Nozzle
		DrawRectangle(centre.x, centre.y - size / 2, 0.1*size, 0.8*size);//nozzle
		break;
	}
}

//---------------------~>[ Sangu Draw ]<~---------------------
//code incompletes will be completed soon
//these coordinates are the coordinates of the TANK facing Upwards
/*

void Player::Draw()
{
	glPushMatrix();
	switch (drawState)
	{
	case FORWARD:
		glTranslatef(-centre.x, -centre.y, 0);
		glRotatef(90, centre.x, centre.y, 1);
		glTranslatef(centre.x, centre.y, 0);
		break;
	}

	DrawRectangle(centre.x, centre.y, size, size*0.5);
	glPopMatrix();
	
	//this->color.SetGLColor();
	int x = centre.x;
	int y = centre.y;

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
	//glColor3f(1.0, 0.0, 0.0);
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

	this->color.SetGLColor();
	//glColor3f(0.0, 0.0, 1.0);
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

	glPopMatrix();
}
*/