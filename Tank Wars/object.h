//TANK WARS
#pragma once
//#2.
//Abstract Base Class For All GameObjects
#include "essentials.h"

class GameObject
{
protected:
	Vector2 centre;			//centre coordinate of gameobject
	Color color;			//color of GameObject
	Color internal;
	int state;				//state during game
	int drawState;          //state of drawing
	int height;				//size of GameObject
	int width;				//width of gameobject
	double speed;			//speed of gameobject
	double health;			//health of gameobject
	double damage;			//damage given by this gameobject

public:
	GameObject()
	{
		//initialize to initial state
		centre(0, 0);
		color = Color::RED();
		internal = Color::BLACK();
		state = NEUTRAL;
		drawState = NEUTRAL;
		height = 0;
		width = 0;
		speed = 0;
		health = 0;
		damage = 0;
	}


	//setters
	virtual void SetState(int st)                 { this->state = st; }
	virtual void SetColor(int r, int g, int b)    { color.SetColor(r, g, b); }
	virtual void SetColor(const Color &c)         { color = c; }
	virtual void SetSize(int sz)                  { this->height = sz; }
	virtual void SetWidth(int wd)                 { this->width = wd; }
	virtual void SetSpeed(double sp)              { this->speed = sp; }
	virtual void SetInternalColor(const Color& c) { internal = c; }
	virtual void IncreaseSpeed(double in) {}

	//getters
	virtual int GetDrawState()                    { return drawState; }
	virtual int GetState()                        { return state; }
	virtual int GetSize()                         { return height; }
	virtual Color GetColor()                      { return color; }
	virtual Vector2 GetCentre()                   { return centre; }
	virtual string GetType()                      { return "gameobject"; }
	virtual bool IsDead()                         { return health <= 0 ? true : false; }
	virtual void RecieveDamage(double dmg)        { this->health -= dmg; }
	virtual double GetDamage()                    { return this->damage; }
	

	//drawing func
	virtual void Draw() = 0;
	virtual void UpdatePos() = 0;

	//Box Collider
	virtual Vector2 GetTopRight()=0;    //returns topright point of object area
	virtual Vector2 GetBottomLeft()=0;   //returns bottomleft point of object area

	//debugging func
	void DrawColliders();
};
















    //                                   FUTURE NOTES                                              //
   //state and drawState are different because object can be neutral(stationary) but we still need//
  //                     to draw the previous state of object                                    //
 //GetTopRight & GetBottomLeft are virtual because every gameobject have their own              //
//boudary(colliders) and my game supports only BOX Collider                                    //

void GameObject::DrawColliders()
{
	//DRAWS COLLIDERS
	DrawRectangleCorner(GetBottomLeft().x,GetBottomLeft().y, GetTopRight().x, GetTopRight().y,false);
	DText("o", GetBottomLeft().x, GetBottomLeft().y,Color::RED(),3);
	DText("o", GetTopRight().x, GetTopRight().y,Color::YELLOW(),3);

}