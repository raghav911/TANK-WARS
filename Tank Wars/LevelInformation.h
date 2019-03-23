#pragma once
#include "GameManager.h"
#include "Player.h"
#include "Obstacle.h"
#include "Projectile.h"
#include "GameArea.h"

//This File Contains Information about the Level Design of the Game

//static Class
class Level
{
public:
	static void Level1Obstacles(vector<Obstacle*> &obstacle);
};

//---------------------~>[ Draw ]<~---------------------
//this function will initialize all the obstacle in the Level1
void Level::Level1Obstacles(vector<Obstacle*> &obstacle)
{
	//doing this map design manually
	obstacle.clear();

	obstacle.push_back(new Obstacle(GAME_WIDTH/2,GAME_HEIGHT-GAME_MENU_AREA,2,GAME_WIDTH));
	obstacle[0]->SetColor(Color::RED());

	obstacle.push_back(new Obstacle(GAME_WIDTH/2.0,GAME_HEIGHT/2.0,GAME_HEIGHT/2.0,40));
	obstacle[1]->SetColor(Color::BLACK());
}