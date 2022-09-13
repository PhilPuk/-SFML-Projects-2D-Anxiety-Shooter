#pragma once

#include<iostream>
#include<math.h>
#include<vector>
#include<time.h>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Bullet
{
private:
	void initVariables(sf::Vector2f& spawnPos, sf::Vector2f& Velocity);
	void initTexture(sf::Texture& texture);
	void initSprite();
public:
	sf::Sprite sprite_bullet;
	sf::Vector2f currVelocity;
	float maxSpeed;

	//Accessors
	const sf::Vector2f& getCurrVelocity() const;

	Bullet(sf::Texture& texture, sf::Vector2f& spawnPos, sf::Vector2f& Velocity);
	virtual ~Bullet();

};

