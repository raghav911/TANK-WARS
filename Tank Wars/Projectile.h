#pragma once
//#4.
#include "object.h"
class Projectile:public GameObject
{
	int pWidth;			//width of Projectile
	
	void init()
	{
		speed = 2.5;
		size = 30;
		pWidth = 2;
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
};

//---------------------~>[ UPDATE POSITION ]<~---------------------
void Projectile::UpdatePos()
{
	switch (state)
	{
	case FORWARD:
		if (centre.x < width+size)
			centre.x += speed;
		break;
	case BACKWARD:
		if (centre.x > -size)
			centre.x -= speed;
		break;
	case UPWARD:
		if (centre.y < height+size)
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
		glVertex2d(centre.x+size/2-size/3,centre.y-pWidth/2);
		glVertex2d(centre.x+size/2-size/3,centre.y+ pWidth/2);
		glEnd();

		glBegin(GL_TRIANGLES);//arrowhead
		
		glVertex2d(centre.x + size / 2, centre.y);
		glVertex2d((centre.x + size / 2)-size/3, centre.y+size/3);
		glVertex2d((centre.x + size / 2)-size/3, centre.y-size/3);
		
		glEnd();
		break;
	case BACKWARD:
		glBegin(GL_QUADS);//back of arrow

		glVertex2d(centre.x - size / 2+size/3, centre.y + pWidth / 2);
		glVertex2d(centre.x - size / 2+size/3, centre.y - pWidth / 2);
		glVertex2d(centre.x + size / 2, centre.y - pWidth / 2);
		glVertex2d(centre.x + size / 2, centre.y + pWidth / 2);
		glEnd();

		glBegin(GL_TRIANGLES);//arrowhead

		glVertex2d(centre.x - size / 2, centre.y);
		glVertex2d((centre.x - size / 2) + size/3, centre.y + size/3);
		glVertex2d((centre.x - size / 2) + size/3, centre.y - size/3);

		glEnd();
		break;
	case UPWARD:
		glBegin(GL_QUADS);//back of arrow

		glVertex2d(centre.x - pWidth / 2, centre.y - size / 2);
		glVertex2d(centre.x + pWidth / 2, centre.y - size/ 2);
		glVertex2d(centre.x - pWidth / 2, centre.y + size / 2-size/3);
		glVertex2d(centre.x + pWidth / 2, centre.y + size / 2-size/3);
		glEnd();

		glBegin(GL_TRIANGLES);//arrowhead

		glVertex2d(centre.x, centre.y+size/2);
		glVertex2d(centre.x - size/3, centre.y+size/2 - size/3);
		glVertex2d(centre.x + size/3, centre.y+size/2 - size/3);

		glEnd();
		break;
	case DOWNWARD:
		glBegin(GL_QUADS);//back of arrow

		glVertex2d(centre.x - pWidth / 2, centre.y - size / 2+size/3);
		glVertex2d(centre.x + pWidth / 2, centre.y - size / 2+size/3);
		glVertex2d(centre.x - pWidth / 2, centre.y + size / 2 );
		glVertex2d(centre.x + pWidth / 2, centre.y + size / 2 );
		glEnd();

		glBegin(GL_TRIANGLES);//arrowhead

		glVertex2d(centre.x, centre.y - size / 2);
		glVertex2d(centre.x - size/3, centre.y - size / 2 + size/3);
		glVertex2d(centre.x + size/3, centre.y - size / 2 + size/3);

		glEnd();
		break;

	}
}
