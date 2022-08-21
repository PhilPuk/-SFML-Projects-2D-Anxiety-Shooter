#pragma once

#include"Weapon.h"

class BeginnerWeapon : virtual public Weapon
{
	//Same as weapon class
	// with different texture
		//Initialization
	//void initVariables();
	//void initTexture();
	//void initSprite(sf::Vector2f spawningPos);
public:
	BeginnerWeapon(sf::Vector2f spawnPos);

	sf::Vector2f& getBulletSpawn();
};

