#pragma once
//#3.
#include "object.h"

class Player:public GameObject
{
	void Init()
	{
		size = 20;
		speed = 0.8;
	}
public:
	
	Player(double x=0,double y=0)
	{
		centre.x = x;
		centre.y = y;
		Init();
	}
	Player(const Vector2 point)
	{
		centre = point;
		Init();
	}

	void MoveForward()  { state = FORWARD; }
	void MoveBackward() { state = BACKWARD; }
	void MoveUpward()   { state = UPWARD; }
	void MoveDownward() { state = DOWNWARD; }
	//void Jump()         { state = JUMP; }   //plans to use on some other Projects ;)

	void ReduceSize();

	//overrided func
	void Draw();
	void UpdatePos();
};

//---------------------~>[ UPDATE POSITION ]<~---------------------
void Player::UpdatePos()
{
	switch(state)
	{
	case FORWARD:
		if(centre.x<width-size)
		centre.x+=speed;
		break;
	case BACKWARD:
		if(centre.x>size)
		centre.x-=speed;
		break;
	case DOWNWARD:
		if (centre.y > size)
			centre.y-=speed;
		break;
	case UPWARD:
		if (centre.y < height - size)
			centre.y+=speed;
		break;
	//case JUMP:
	//	break;
	}
}

//---------------------~>[ Reduce_size ]<~---------------------
void Player:: ReduceSize()
{
	if (size > 10)
	{
		size -= 2;
		if (centre.x < width / 2)//P1
			centre.x -= 2;
		else					//P2
			centre.x += 2;
	}
}

//---------------------~>[ Draw ]<~---------------------
void Player::Draw()
{
	this->color.SetGLColor();

	glBegin(GL_QUADS);
	glVertex2i(centre.x - size, centre.y - size);
	glVertex2i(centre.x + size, centre.y - size);
	glVertex2i(centre.x + size, centre.y + size);
	glVertex2i(centre.x - size, centre.y + size);
	glEnd();
}