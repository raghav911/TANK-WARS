//TANK WARS
#pragma once
//#4.
#include "object.h"
class Projectile:public GameObject
{
	int pWidth;			//width of Projectile
	double headRatio;   //size of head(smaller values = bigger head)
	void init()
	{
		speed = 2.5;
		size = 30;
		pWidth = 5;
		headRatio = 3.5;
	}
public:
	Projectile(double x=0,double y=0)
	{
		centre.x = x;
		centre.y = y;
		init();
	}
	Projectile(const Vector2 &point)
	{
		centre = point;
		init();
	}

	void MoveForward()  {state = FORWARD; }
	void MoveBackward() {state = BACKWARD; }
	
	//overrided func
	void Draw();
	void UpdatePos();
	Vector2 GetTopRight();    //returns topright point of player area
	Vector2 GetBottomLeft();   //returns bottomleft point of player area
};
//---------------------~>[ Get Player Extremes POSITION ]<~---------------------
Vector2 Projectile::GetBottomLeft()   //returns bottomleft point of player area
{
	double x, y;
	if (state == FORWARD || state == BACKWARD)
	{
		x = centre.x - size / 2.0;
		y = centre.y - pWidth / 2.0;
	}
	else if (state == UPWARD || state == DOWNWARD)
	{
		x = centre.x - pWidth / 2.0;
		y = centre.y - size / 2.0;
	}
	
	Vector2 temp(x,y);
	return temp;
}
Vector2 Projectile::GetTopRight()   //returns bottomleft point of player area
{
	double x, y;
	if (state == FORWARD || state == BACKWARD)
	{
		x = centre.x + size / 2.0;
		y = centre.y + pWidth / 2.0;
	}
	else if (state == UPWARD || state == DOWNWARD)
	{
		x = centre.x + pWidth / 2.0;
		y = centre.y + size / 2.0;
	}

	Vector2 temp(x, y);
	return temp;
}
//---------------------~>[ UPDATE POSITION ]<~---------------------
void Projectile::UpdatePos()
{
	switch (state)
	{
	case FORWARD:
		if (centre.x < GAME_WIDTH+size)
			centre.x += speed;
		break;
	case BACKWARD:
		if (centre.x > -size)
			centre.x -= speed;
		break;
	case UPWARD:
		if (centre.y < GAME_HEIGHT+size)
			centre.y += speed;
		break;
	case DOWNWARD:
		if (centre.y > -size)
			centre.y -= speed;
		break;
	}
}
//---------------------~>[ Draw ]<~---------------------
void Projectile::Draw()
{
	this->color.SetGLColor();

	switch (state)
	{
	case FORWARD:
		glBegin(GL_QUADS);//back of arrow
		
		glVertex2d(centre.x-size/2,centre.y+pWidth/2);
		glVertex2d(centre.x-size/2,centre.y-pWidth/2);
		glVertex2d(centre.x+size/2-size/headRatio,centre.y-pWidth/2);
		glVertex2d(centre.x+size/2-size/headRatio,centre.y+ pWidth/2);
		glEnd();

		glBegin(GL_TRIANGLES);//arrowhead
		
		glVertex2d(centre.x + size / 2, centre.y);
		glVertex2d((centre.x + size / 2)-size/headRatio, centre.y+size/headRatio);
		glVertex2d((centre.x + size / 2)-size/headRatio, centre.y-size/headRatio);
		
		glEnd();
		break;
	case BACKWARD:
		glBegin(GL_QUADS);//back of arrow

		glVertex2d(centre.x - size / 2+size/headRatio, centre.y + pWidth / 2);
		glVertex2d(centre.x - size / 2+size/headRatio, centre.y - pWidth / 2);
		glVertex2d(centre.x + size / 2, centre.y - pWidth / 2);
		glVertex2d(centre.x + size / 2, centre.y + pWidth / 2);
		glEnd();

		glBegin(GL_TRIANGLES);//arrowhead

		glVertex2d(centre.x - size / 2, centre.y);
		glVertex2d((centre.x - size / 2) + size/headRatio, centre.y + size/headRatio);
		glVertex2d((centre.x - size / 2) + size/headRatio, centre.y - size/headRatio);

		glEnd();
		break;
	case UPWARD:
		glBegin(GL_QUADS);//back of arrow

		glVertex2d(centre.x - pWidth / 2, centre.y - size / 2);
		glVertex2d(centre.x + pWidth / 2, centre.y - size/ 2);
		glVertex2d(centre.x - pWidth / 2, centre.y + size / 2-size/headRatio);
		glVertex2d(centre.x + pWidth / 2, centre.y + size / 2-size/headRatio);
		glEnd();

		glBegin(GL_TRIANGLES);//arrowhead

		glVertex2d(centre.x, centre.y+size/2);
		glVertex2d(centre.x - size/headRatio, centre.y+size/2 - size/headRatio);
		glVertex2d(centre.x + size/headRatio, centre.y+size/2 - size/headRatio);

		glEnd();
		break;
	case DOWNWARD:
		glBegin(GL_QUADS);//back of arrow

		glVertex2d(centre.x - pWidth / 2, centre.y - size / 2+size/headRatio);
		glVertex2d(centre.x + pWidth / 2, centre.y - size / 2+size/headRatio);
		glVertex2d(centre.x - pWidth / 2, centre.y + size / 2 );
		glVertex2d(centre.x + pWidth / 2, centre.y + size / 2 );
		glEnd();

		glBegin(GL_TRIANGLES);//arrowhead

		glVertex2d(centre.x, centre.y - size / 2);
		glVertex2d(centre.x - size/headRatio, centre.y - size / 2 + size/headRatio);
		glVertex2d(centre.x + size/headRatio, centre.y - size / 2 + size/headRatio);

		glEnd();
		break;

	}
}
