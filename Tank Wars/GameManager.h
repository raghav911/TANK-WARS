#pragma once
//#6.
//This File is Responsible for all the Physics,Collisions,etc Involved in the Game

#include "GameArea.h"

class GameManager
{
	//ansilary
	static bool Obj1ColWithObj2(GameObject *Obj1,GameObject *Obj2);
	static bool BulletsColWithPlayer(vector<Projectile*> &Bullets,Player*);

public:
	//Physics2D
	static void CheckBulletPlayerCollision();
	static void CheckPlayerPlayerCollision();
	static void CheckBulletBulletCollision();

};

  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
 //					:~>  ANSILLARY <~:                           //
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//---------------------~>[ P1 collided with P2 ]<~---------------------
bool GameManager:: Obj1ColWithObj2(GameObject *obj1,GameObject *obj2)
{

	bool hasCollided = false;
	Vector2 P1topRight   = obj1->GetTopRight();
	Vector2 P1bottomLeft = obj1->GetBottomLeft();
	Vector2 P2topRight   = obj2->GetTopRight();
	Vector2 P2bottomLeft = obj2->GetBottomLeft();

	double offset=2;
	switch (obj1->GetState())
	{
	case FORWARD:
		if (P1topRight.y > P2bottomLeft.y+offset && P1bottomLeft.y < P2topRight.y-offset && P1topRight.x >= P2bottomLeft.x && P1topRight.x < P2topRight.x)
			hasCollided = true;
		break;
	case BACKWARD:
		if (P1topRight.y > P2bottomLeft.y+offset && P1bottomLeft.y < P2topRight.y-offset && P1bottomLeft.x <= P2topRight.x && P1bottomLeft.x > P2bottomLeft.x)
			hasCollided = true;
		break;
	case UPWARD:
		if (P1topRight.x > P2bottomLeft.x+offset && P1bottomLeft.x < P2topRight.x-offset && P1topRight.y >= P2bottomLeft.y && P1topRight.y < P2topRight.y)
			hasCollided = true;
		break;
	case DOWNWARD:
		if (P1topRight.x > P2bottomLeft.x+offset && P1bottomLeft.x < P2topRight.x-offset && P1bottomLeft.y <= P2topRight.y && P1bottomLeft.y > P2bottomLeft.y)
			hasCollided = true;
		break;
	}

	return hasCollided;
}

//---------------------~>[ Bullets Col With P ]<~---------------------
bool GameManager:: BulletsColWithPlayer(vector<Projectile*> &Bullets, Player *p)
{
	unsigned int bulletCount = Bullets.size();
	bool hit = false;

	for (int i = 0; i < bulletCount; i++)//player 1 bullets
	{
		//cache Bullets[i] info
		Vector2 bCentrePoint = Bullets[i]->GetCentre();
		int bSize = Bullets[i]->GetSize();
		int bState = Bullets[i]->GetState();

		//check whether i bullet hit the player
		int x_inc = 0, y_inc = 0;

		//here we are finding the tip of the projectile
		switch (bState)
		{
		case FORWARD:
			x_inc = bSize / 2;
			break;
		case BACKWARD:
			x_inc = -bSize / 2;
			break;
		case UPWARD:
			y_inc = bSize / 2;
			break;
		case DOWNWARD:
			y_inc = -bSize / 2;
			break;
		}

		int x = bCentrePoint.x + x_inc;
		int y = bCentrePoint.y + y_inc;

		if (y > p->GetBottomLeft().y && y < p->GetTopRight().y && x>p->GetBottomLeft().x && x < p->GetTopRight().x)//bullet y is in range of P2
		{
			hit = true;
			p->ReduceSize();
		}

		if (x > WIDTH || y > HEIGHT || x < 0 || y < 0 || hit)
		{
			Bullets.erase(Bullets.begin() + i);
			bulletCount--;
			if (hit) return true;
		}
	}//for
	return false;
}
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
 //					:~>  ANSILLARY ENDS <~:                      //
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//---------------------~>[ Player Player Collision ]<~---------------------
void GameManager::CheckPlayerPlayerCollision()
{
	if (P1 == NULL || P2 == NULL) return;//defence

	if ( Obj1ColWithObj2(P1,P2) )
		P1->StopMovement();
	if ( Obj1ColWithObj2(P2,P1) )
		P2->StopMovement();
}

//---------------------~>[ Player Bullet Collision ]<~---------------------
void GameManager::CheckBulletPlayerCollision()
{
	if (P1 == NULL || P2 == NULL) return;//defence

	//does P1 bullets Collided with P2
	bool isP2hit = BulletsColWithPlayer(P1Bullet,P2);
	if (isP2hit && ++P2HitTaken >= maxHit)//P1 WINS
	{
		++P1WinCount;

		P2Alive = false;
		P2Bullet.clear();
		P2 = NULL;
		isGameRunning = false;
		return;
	}
	
	//does P2 bullets Collided with P1
	bool isP1hit = BulletsColWithPlayer(P2Bullet,P1);
	if (isP1hit && ++P1HitTaken >= maxHit)//P2 WINS
	{
		++P2WinCount;

		P1Alive = false;
		P1Bullet.clear();
		P1 = NULL;
		isGameRunning = false;
	}
}

//---------------------~>[ Bullet Bullet Collision ]<~---------------------
void GameManager:: CheckBulletBulletCollision()
{
	for (int i = 0; i < P1Bullet.size() ; ++i)
	{
		for (int j = 0; j < P2Bullet.size(); ++j)
		{
			//if i bullet of P1 collides with j bullet of P2 then desroy both Bullets
			if (Obj1ColWithObj2(P1Bullet[i], P2Bullet[j]))
			{
				P1Bullet.erase(P1Bullet.begin()+i);
				P2Bullet.erase(P2Bullet.begin()+j);
				
				i--;
				break;
			}
		}
	}
}
