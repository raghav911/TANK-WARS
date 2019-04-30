//TANK WARS
#pragma once
//#6.
//This File is Responsible for all the Physics,Collisions,etc Involved in the Game

#include "GameArea.h"
#include "CollisionDetector.h"

class GameManager
{
	//ansilary
	static bool BulletsColWithGameobj(vector<Projectile*> &Bullets,GameObject *P);

public:
	//Physics2D
	static void CheckBulletPlayerCollision();
	static void CheckPlayerPlayerCollision();
	static void CheckBulletBulletCollision();
	static void CheckGameObjectObstacleCollision();
};

  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
 //					:~>  ANSILLARY <~:                           //
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//---------------------~>[ P1 collided with P2 ]<~---------------------

//---------------------~>[ Bullets Col With P ]<~---------------------
bool GameManager:: BulletsColWithGameobj(vector<Projectile*> &Bullets, GameObject *p)
{
	unsigned int bulletCount = Bullets.size();

	for (int i = 0; i < bulletCount; i++)//player 1 bullets
	{
		bool hit = CollisionDetector::Obj1ColWithObj2(Bullets[i],p);
		Vector2 bulletCentre = Bullets[i]->GetCentre();
		
		if (bulletCentre.x > GAME_WIDTH || bulletCentre.y > GAME_HEIGHT || bulletCentre.x < 0 || bulletCentre.y < 0 || hit)
		{
			if (hit)
			{
				p->RecieveDamage(Bullets[i]->GetDamage());
				Bullets.erase(Bullets.begin() + i);
				return true;
			}
			Bullets.erase(Bullets.begin() + i);
			bulletCount--;
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

	if (CollisionDetector:: Obj1ColWithObj2(P1,P2) )
		P1->StopMovement();
	if (CollisionDetector:: Obj1ColWithObj2(P2,P1) )
		P2->StopMovement();
}

//---------------------~>[ Player Bullet Collision ]<~---------------------
void GameManager::CheckBulletPlayerCollision()
{
	if (P1 == NULL || P2 == NULL) return;//defence

	//does P1 bullets Collided with P2
	bool isP2hit = BulletsColWithGameobj(P1Bullet, P2);

	if (isP2hit)
	{
		P2->ReduceSize();
		if (P2->IsDead())//P1 WINS
		{
			++P1WinCount;

			P2Alive = false;
			P2Bullet.clear();
			P2 = NULL;
			isGameRunning = false;
			return;
		}
	}
	//does P2 bullets Collided with P1
	bool isP1hit = BulletsColWithGameobj(P2Bullet, P1);
	if (isP1hit)
	{
		P1->ReduceSize();
		if (P1->IsDead())//P2 WINS
		{
			++P2WinCount;

			P1Alive = false;
			P1Bullet.clear();
			P1 = NULL;
			isGameRunning = false;
		}
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
			if (CollisionDetector:: Obj1ColWithObj2(P1Bullet[i], P2Bullet[j]))
			{
				//cache damage of bullets
				double p1Damage = P1Bullet[i]->GetDamage();
				double p2Damage = P2Bullet[i]->GetDamage();
				P1Bullet[i]->RecieveDamage(p2Damage);
 				P2Bullet[j]->RecieveDamage(p1Damage);

				if (P1Bullet[i]->IsDead())
				{
					P1Bullet.erase(P1Bullet.begin() + i);
					i--;
				}

				if(P2Bullet[j]->IsDead())
    				P2Bullet.erase(P2Bullet.begin()+j);

				break;
			}
		}
	}
}

//---------------------~>[ Obstacle Player Collision ]<~---------------------
//this function checks whether any gameobject have collided with Obstacles
void GameManager::CheckGameObjectObstacleCollision()
{
	//cache
	unsigned int obsCount = gameObstacles.size();
	//check bullets
	for (int i = 0; i < obsCount; ++i)
	{
		bool hit;
		BulletsColWithGameobj(P1Bullet,gameObstacles[i]);
		BulletsColWithGameobj(P2Bullet,gameObstacles[i]);

		if (P1)
		{
			hit =CollisionDetector:: Obj1ColWithObj2(P1, gameObstacles[i]);
			if (hit)
				P1->StopMovement();
		}

		if (P2)
		{
			hit =CollisionDetector:: Obj1ColWithObj2(P2, gameObstacles[i]);
			if (hit)
				P2->StopMovement();
		}
	}
}
