#pragma once
//TANK WARS
//This File Will Contains All the Information About the Obstacle in the Game

#include "object.h"

class Obstacle:public GameObject
{
	void Init(int ht,int wd)
	{
		this->height = ht;
		this->width = wd;
		this->state = NEUTRAL;
		this->drawState = NEUTRAL;
	}

public:
	Obstacle(double x,double y,int ht=40,int wd=40)
	{
		this->centre.x = x;
		this->centre.y = y;
		Init(ht,wd);
	}
	Obstacle(const Vector2& point, int ht = 40, int wd = 40)
	{
		this->centre = point;
		Init(ht, wd);
	}

	//overrided Func
	void Draw();
	void UpdatePos() {}
	//Box Collider
	Vector2 GetTopRight();    //returns topright point of object area
	Vector2 GetBottomLeft();   //returns bottomleft point of object area
};

//---------------------~>[ DRAW ]<~---------------------
void Obstacle:: Draw()
{
	this->color.SetGLColor();

	DrawRectangle(centre.x,centre.y,width,height);
}

//---------------------~>[ Box Colliders ]<~---------------------
Vector2 Obstacle:: GetTopRight()
{
	Vector2 temp(centre.x+width/2.0,centre.y+height/2.0);
	return temp;
}
Vector2 Obstacle:: GetBottomLeft()
{
	Vector2 temp(centre.x - width / 2.0, centre.y - height / 2.0);
	return temp;
}


