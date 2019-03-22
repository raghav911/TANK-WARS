#pragma once
//#6.
//This File is Responsible for all the Physics,Collisions,etc Involved in the Game

#include "GameArea.h"

class GameManager
{
	//ansilary
	static bool P1CollidedWithP2(int state,Vector2 P1bottomLeft, Vector2 P1topRight, Vector2 P2bottomLeft, Vector2 P2topRight);
	static bool BulletsColWithPlayer(vector<Projectile*> &Bullets,Player *p);
public:
	//Physics2D
	static void CheckBulletPlayerCollision();
	static void CheckPlayerPlayerCollision();

};

  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
 //					:~>  ANSILLARY <~:                           //
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//---------------------~>[ P1 collided with P2 ]<~---------------------
bool GameManager:: P1CollidedWithP2(int state, Vector2 P1bottomLeft, Vector2 P1topRight, Vector2 P2bottomLeft, Vector2 P2topRight)
{
	bool hasCollided = false;
	switch (state)
	{
	case FORWARD:
		if (P1topRight.y >= P2bottomLeft.y && P1bottomLeft.y <= P2topRight.y && P1topRight.x >= P2bottomLeft.x && P1topRight.x < P2topRight.x)
			hasCollided = true;
		break;
	case BACKWARD:
		if (P1topRight.y >= P2bottomLeft.y && P1bottomLeft.y <= P2topRight.y && P1bottomLeft.x <= P2topRight.x && P1bottomLeft.x > P2bottomLeft.x)
			hasCollided = true;
		break;
	case UPWARD:
		if (P1topRight.x >= P2bottomLeft.x && P1bottomLeft.x <= P2topRight.x && P1topRight.y >= P2bottomLeft.y && P1topRight.y < P2topRight.y)
			hasCollided = true;
		break;
	case DOWNWARD:
		if (P1topRight.x >= P2bottomLeft.x && P1bottomLeft.x <= P2topRight.x && P1bottomLeft.y <= P2topRight.y && P1bottomLeft.y > P2bottomLeft.y)
			hasCollided = true;
		break;
	}

	return hasCollided;
}
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
 //					:~>  ANSILLARY ENDS <~:                      //
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//---------------------~>[ Player Player Collision ]<~---------------------
void GameManager::CheckPlayerPlayerCollision()
{
	if (P1 == NULL || P2 == NULL) return;//defence

	//cached variables
	Vector2 P1bottomLeft = P1->GetBottomLeft();
	Vector2 P1topRight   = P1->GetTopRight();
	Vector2 P2bottomLeft = P2->GetBottomLeft();
	Vector2 P2topRight   = P2->GetTopRight();

	if (P1CollidedWithP2(P1->GetState(), P1bottomLeft, P1topRight, P2bottomLeft, P2topRight))
		P1->StopMovement();
	if (P1CollidedWithP2(P2->GetState(), P2bottomLeft, P2topRight, P1bottomLeft, P1topRight))
		P2->StopMovement();
}

//---------------------~>[ Player Bullet Collision ]<~---------------------
void GameManager::CheckBulletPlayerCollision()
{
	if (P1 == NULL || P2 == NULL) return;//defence

	Vector2 bPoint;//bullet Point
	int bSize;

	//cached variables
	int p1Size = P1->GetSize();
	int p2Size = P2->GetSize();

	Vector2 p1Point = P1->GetCentre();
	Vector2 p2Point = P2->GetCentre();

	int P1BulletCount = P1Bullet.size();
	int P2BulletCount = P2Bullet.size();

	for (int i = 0; i < P1BulletCount; i++)//player 1 bullets
	{
		bPoint = P1Bullet[i]->GetCentre();
		bSize = P1Bullet[i]->GetSize();

		//check whether i bullet hit the P2 player
		bool hit = false;
		int bState = P1Bullet[i]->GetState();
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

		int x = bPoint.x + x_inc;
		int y = bPoint.y + y_inc;

		if (y > (p2Point.y - p2Size) && y < (p2Point.y + p2Size))//bullet y is in range of P2
		{
			if (x > (p2Point.x - p2Size) && x < (p2Point.x + p2Size))
			{
				hit = true;
				P2->ReduceSize();
			}
		}

		if (x > width || y > height || x < 0 || y < 0 || hit)
		{
			P1Bullet.erase(P1Bullet.begin() + i);
			P1BulletCount--;
		}
		//upward code in one function
		if (hit && ++P2HitTaken >= maxHit)//P2 Loses
		{
			cout << "P1 WINS" << endl;

			P2Alive = false;
			P2Bullet.clear();
			P2 = NULL;
			isGameRunning = false;
			return;
		}
	}//P1 Wins Or not

	for (int i = 0; i < P2BulletCount; i++)//player 2 bullets
	{
		bPoint = P2Bullet[i]->GetCentre();
		bSize = P2Bullet[i]->GetSize();

		//check whether i bullet hit the P2 player
		bool hit = false;
		int bState = P2Bullet[i]->GetState();
		int x_inc = 0, y_inc = 0;

		switch (bState)//bulletState
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

		int x = bPoint.x + x_inc;
		int y = bPoint.y + y_inc;

		if (y > (p1Point.y - p1Size) && y < (p1Point.y + p1Size))//bullet y is in range of P2
		{
			if (x < (p1Point.x + p1Size) && x>(p1Point.x - p1Size))
			{
				hit = true;
				P1->ReduceSize();
			}
		}
		if (x > width || y > height || x < 0 || y < 0 || hit)//to vanish unused bullets of P2
		{
			P2Bullet.erase(P2Bullet.begin() + i);
			P2BulletCount--;
		}

		//p1 loses and p2 wins
		if (hit && ++P1HitTaken >= maxHit)//P1 loses
		{
			cout << "P2 WINS" << endl;

			P1Alive = false;
			P1 = NULL;
			P1Bullet.clear();
			isGameRunning = false;
			return;
		}

	}//P2 Wins Or Not
}
