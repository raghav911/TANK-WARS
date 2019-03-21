#pragma once
//#3.
#include "object.h"

class Player:public GameObject
{
	void Init(int dState = UPWARD)
	{
		size = 40;
		speed = 1.2;
		drawState = dState;
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
		cout << "lol";
		Init();
	}

	void MoveForward()  { drawState = state = FORWARD; }
	void MoveBackward() { drawState = state = BACKWARD; }
	void MoveUpward()   { drawState = state = UPWARD; }
	void MoveDownward() { drawState = state = DOWNWARD; }
	void StopMovement() { drawState = state = NEUTRAL; }
	//void Jump()         { state = JUMP; }   //plans to use on some other Projects ;)

	void ReduceSize();

	//overrided func
	void Draw();
	void UpdatePos();
};

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
		if(x_max<width)
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
		if (y_max<height)
			centre.y+=speed;
		break;
	//case JUMP:
	//	break;
	}
}

//---------------------~>[ Reduce_size ]<~---------------------
void Player:: ReduceSize()
{
	if (size > 5)
	{
		size -= 2;
		//if (centre.x < width / 2)//P1
		//	centre.x -= 2;
		//else					//P2
		//	centre.x += 2;
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
/*
void Player::Draw()
{
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
}
*/