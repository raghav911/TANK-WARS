#pragma once
//#2.
//Abstract Base Class For All GameObjects
#include "essentials.h"

class GameObject
{
protected:
	Vector2 centre;			//centre coordinate of gameobject
	Color color;			//color of GameObject
	int size;				//size of GameObject
	int state;				//state during game
	int drawState;          //state of drawing
	double speed;			//speed of gameobject
public:

	//common logic
	void SetState(int st)              { this->state = st; }
	void SetColor(int r, int g, int b) { color.SetColor(r, g, b); }
	void SetColor(const Color &c)      { color = c; }
	//void Dstroy() { state = DEAD; }

	//getters
	int GetState()          { return state; }
	Vector2 GetCentre()     { return centre; }
	Color GetPlayerColor()  { return color; }
	int GetSize()           { return size; }

	//virtual func
	virtual void Draw() = 0;
	virtual void UpdatePos() = 0;
	virtual Vector2 GetTopRight()=0;    //returns topright point of object area
	virtual Vector2 GetBottomLeft()=0;   //returns bottomleft point of object area
};


    //                                   FUTURE NOTES                                              //
   //state and drawState are different because object can be neutral(stationary) but we still need//
  //                     to draw the previous state of object                                    //
 //GetTopRight & GetBottomLeft are virtual because every gameobject have their own              //
//boudary(colliders) and my game supports only BOX Collider                                    //