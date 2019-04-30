#pragma once
//TANK WARS
//This File Will Contains All the Information About the Obstacle in the Game

#include "object.h"

class Obstacle:public GameObject
{
	void Init(int ht,int wd)
	{
		height     = ht;
		width      = wd;
		state      = NEUTRAL;
		drawState  = NEUTRAL;
		//internal = Color::BLACK();
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
	string GetType() { return "obstacle"; }

	//Box Collider
	Vector2 GetTopRight();     //returns topright point of object area
	Vector2 GetBottomLeft();   //returns bottomleft point of object area

	
    //map design helper functions  comment after designing maps
	//void MoveForward() { drawState = state = FORWARD; }
	//void MoveBackward() { drawState = state = BACKWARD; }
	//void MoveUpward() { drawState = state = UPWARD; }
	//void MoveDownward() { drawState = state = DOWNWARD; }
	//void StopMovement() { state = NEUTRAL; }
	//void IncreaseHeight() { height += speed; }
	//void IncreaseWidth() { width += speed; }
	//void DecreaseHeight() { height -= speed; }
	//void DecreaseWidth() { width -= speed; }
	//void IncreaseSpeed() { speed ++; }
	//void DecreaseSpeed() { speed --; }
	//void NeutralSpeed() { speed =1; }

	//void ShowPoints()
	//{
	//	cout << "CENTRE          :" << centre.x << " ," << centre.y << endl;
	//	cout << "DIMENSIONS(h,w) : " << height << " ," << width << endl;
	//}
	//map design helper functions  comment after designing maps//
};











 
//---------------------~>[ DRAW ]<~---------------------
void Obstacle:: Draw()
{
	this->color.SetGLColor();
	DrawRectangle(centre.x,centre.y,width,height);
	
	this->internal.SetGLColor();
	DrawRectangle(centre.x,centre.y,width-5,height-5);

	//mapdesign helper
	state = NEUTRAL;
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

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
//					:~>  MAP DESIGN HELP <~:
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
//void Obstacle::UpdatePos()
//{
//	switch (state)
//	{
//	case FORWARD:
//		if (centre.x < GAME_WIDTH + height)
//			centre.x += speed;
//		break;
//	case BACKWARD:
//		if (centre.x > -height)
//			centre.x -= speed;
//		break;
//	case UPWARD:
//		if (centre.y < GAME_HEIGHT + height)
//			centre.y += speed;
//		break;
//	case DOWNWARD:
//		if (centre.y > -height)
//			centre.y -= speed;
//		break;
//	}
//}
