//TANK WARS
#pragma once
//#4.
#include "object.h"
class Projectile:public GameObject
{
	double headRatio;   //size of head(smaller values = bigger head)
	double boxColliderOffset;
	
	void init()
	{
		speed              = 3.8;
		height             = 39;
		width              = 7.2;
		headRatio          = 2.9;				    //inversely propotional
		boxColliderOffset  = 0.4;
		damage             = 1;						//damage this bullet will imflict on others
		health             = 1;						//health of projectile
	}
public:
	Projectile(double x=0,double y=0,double dmg=1)
	{
		centre.x = x;
		centre.y = y;
		init();
		health=damage = dmg;
	}
	Projectile(const Vector2 &point,double dmg=1)
	{
		centre = point;
		init();
		health=damage = dmg;
	}
	

	//overrided func
	void Draw();
	void UpdatePos();

	//setters
	void SetState(int st)				  { this->state = st; }
	void SetColor(int r, int g, int b)    { color.SetColor(r, g, b); }
	void SetColor(const Color &c)         { color = c; }
	void SetSize(int sz)                  { this->height = sz; }
	void SetWidth(int wd)                 { this->width = wd; }
	void SetSpeed(double sp)              { this->speed = sp; }
	void SetInternalColor(const Color& c) { internal = c; }
	void IncreaseSpeed(double inc)        { speed += inc; }

	//getters
	string GetType()                      { return "projectile"; }
	int GetDrawState()                    { return drawState; }
	int GetState()                        { return state; }
	int GetSize()                         { return height; }
	Color GetPlayerColor()                { return color; }
	bool IsDead()                         { if (this->health <= 0)return true; return false; }
	double GetDamage()                    { return this->damage; }
	Vector2 GetCentre()                   { return centre; }
	void RecieveDamage(double dmg)        { health -= dmg; damage -= dmg; }

	Vector2 GetTopRight();    //returns topright point of player area
	Vector2 GetBottomLeft();   //returns bottomleft point of player area
};




















//---------------------~>[ VOx Colliders ]<~---------------------
Vector2 Projectile::GetBottomLeft()   //returns bottomleft point of player area
{
	double x, y;
	if (state == FORWARD || state == BACKWARD)
	{
		x = centre.x - height / 2.0;
		y = centre.y - width / 2.0;
	}
	else if (state == UPWARD || state == DOWNWARD)
	{
		x = centre.x - width / 2.0;
		y = centre.y - height / 2.0;
	}
	
	x -= boxColliderOffset;
	y -= boxColliderOffset;
	Vector2 temp(x,y);
	return temp;
}
Vector2 Projectile::GetTopRight()   //returns bottomleft point of player area
{
	double x, y;
	if (state == FORWARD || state == BACKWARD)
	{
		x = centre.x + height / 2.0;
		y = centre.y + width / 2.0;
	}
	else if (state == UPWARD || state == DOWNWARD)
	{
		x = centre.x + width / 2.0;
		y = centre.y + height / 2.0;
	}

	x += boxColliderOffset;
	y += boxColliderOffset;

	Vector2 temp(x, y);
	return temp;
}
//---------------------~>[ UPDATE POSITION ]<~---------------------
void Projectile::UpdatePos()
{
	switch (state)
	{
	case FORWARD:
		if (centre.x < GAME_WIDTH+height)
			centre.x += speed;
		break;
	case BACKWARD:
		if (centre.x > -height)
			centre.x -= speed;
		break;
	case UPWARD:
		if (centre.y < GAME_HEIGHT+height)
			centre.y += speed;
		break;
	case DOWNWARD:
		if (centre.y > -height)
			centre.y -= speed;
		break;
	}
}
//---------------------~>[ Draw ]<~---------------------
void Projectile::Draw()
{
	//DrawColliders();
	this->color.SetGLColor();

	switch (state)
	{
	case FORWARD:
		glBegin(GL_QUADS);//back of arrow
		
		glVertex2d(centre.x-height/2,centre.y+width/2);
		glVertex2d(centre.x-height/2,centre.y-width/2);
		glVertex2d(centre.x+height/2-height/headRatio,centre.y-width/2);
		glVertex2d(centre.x+height/2-height/headRatio,centre.y+ width/2);
		glEnd();

		glBegin(GL_TRIANGLES);//arrowhead
		
		this->color.SetGLColor();
		glVertex2d(centre.x + height / 2, centre.y);

		Color::ARROWHEAD1().SetGLColor();
		glVertex2d((centre.x + height / 2)-height/headRatio, centre.y+height/headRatio);
		
		Color::ARROWHEAD2().SetGLColor();
		glVertex2d((centre.x + height / 2)-height/headRatio, centre.y-height/headRatio);
		
		glEnd();
		break;
	case BACKWARD:
		glBegin(GL_QUADS);//back of arrow

		glVertex2d(centre.x - height / 2+height/headRatio, centre.y + width / 2);
		glVertex2d(centre.x - height / 2+height/headRatio, centre.y - width / 2);
		glVertex2d(centre.x + height / 2, centre.y - width / 2);
		glVertex2d(centre.x + height / 2, centre.y + width / 2);
		glEnd();

		glBegin(GL_TRIANGLES);//arrowhead

		this->color.SetGLColor();
		glVertex2d(centre.x - height / 2, centre.y);
		
		Color::ARROWHEAD1().SetGLColor();
		glVertex2d((centre.x - height / 2) + height/headRatio, centre.y + height/headRatio);
		
		Color::ARROWHEAD2().SetGLColor();
		glVertex2d((centre.x - height / 2) + height/headRatio, centre.y - height/headRatio);

		glEnd();
		break;
	case UPWARD:
		glBegin(GL_QUADS);//back of arrow

		glVertex2d(centre.x - width / 2, centre.y - height / 2);
		glVertex2d(centre.x + width / 2, centre.y - height/ 2);
		glVertex2d(centre.x - width / 2, centre.y + height / 2-height/headRatio);
		glVertex2d(centre.x + width / 2, centre.y + height / 2-height/headRatio);
		glEnd();

		glBegin(GL_TRIANGLES);//arrowhead

		this->color.SetGLColor();
		glVertex2d(centre.x, centre.y+height/2);
		
		Color::ARROWHEAD1().SetGLColor();
		glVertex2d(centre.x - height/headRatio, centre.y+height/2 - height/headRatio);
		
		Color::ARROWHEAD2().SetGLColor();
		glVertex2d(centre.x + height/headRatio, centre.y+height/2 - height/headRatio);

		glEnd();
		break;
	case DOWNWARD:
		glBegin(GL_QUADS);//back of arrow

		glVertex2d(centre.x - width / 2, centre.y - height / 2+height/headRatio);
		glVertex2d(centre.x + width / 2, centre.y - height / 2+height/headRatio);
		glVertex2d(centre.x - width / 2, centre.y + height / 2 );
		glVertex2d(centre.x + width / 2, centre.y + height / 2 );
		glEnd();

		glBegin(GL_TRIANGLES);//arrowhead

		this->color.SetGLColor();
		glVertex2d(centre.x, centre.y - height / 2);
		
		Color::ARROWHEAD1().SetGLColor();
		glVertex2d(centre.x - height/headRatio, centre.y - height / 2 + height/headRatio);
		
		Color::ARROWHEAD2().SetGLColor();
		glVertex2d(centre.x + height/headRatio, centre.y - height / 2 + height/headRatio);

		glEnd();
		break;

	}
}
