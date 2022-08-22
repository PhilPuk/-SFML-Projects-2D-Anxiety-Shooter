#pragma once

#include<iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Aiming
{
private:
	//Vectors for aiming
	sf::Vector2f ObjectCenter;
	sf::Vector2f mousePosWindow;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;

	//Initialization
	void initVariables();

public:
	Aiming();
	virtual ~Aiming();

	//Accessors
	sf::Vector2f& getAimDirNorm();

	// Calculates the direction  between Object 1 and Object2.
	// Example: Object1 is the player position, Object2 is the mouse position.
	// Now the direction from Object1 towards Object2 gets calculated.
	// To make it work perfectly center the origins of your objects.
	// To get the caluclated value call getAimDirNorm.
	void updateAimDirection(sf::Vector2f& Object1Pos, sf::Vector2f& Object2Pos);


};

