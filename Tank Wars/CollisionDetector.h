#pragma once
#include "object.h"
#include "essentials.h"

//CI:This Class Provides Methods to detect Collision Between Two GameObjects
//Methods:
//Simpe Box Collision 

class CollisionDetector
{
public:
	static bool Obj1ColWithObj2(GameObject *Obj1, GameObject *Obj2);
};

bool CollisionDetector::Obj1ColWithObj2(GameObject *obj1, GameObject *obj2)
{

	bool hasCollided = false;
	Vector2 P1topRight = obj1->GetTopRight();
	Vector2 P1bottomLeft = obj1->GetBottomLeft();
	Vector2 P2topRight = obj2->GetTopRight();
	Vector2 P2bottomLeft = obj2->GetBottomLeft();


	double d1x = P2bottomLeft.x - P1topRight.x;
	double d1y = P2bottomLeft.y - P1topRight.y;
	double d2x = P1bottomLeft.x - P2topRight.x;
	double d2y = P1bottomLeft.y - P2topRight.y;

	if (d1x > 0.0f || d1y > 0.0f)
		return false;

	if (d2x > 0.0f || d2y > 0.0f)
		return false;

	return true;
}
