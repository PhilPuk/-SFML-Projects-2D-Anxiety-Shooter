#pragma once

#include<iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Tile
{
private:
	float sizeX;
	float sizeY;

	float ScaleIndex;
	float ScaleMax;
	float ScaleMin;
	float ScaleFac;

	float RotationAngle;
	bool ActivateThreeSixtyAnimation;

	//Initizalation
	void initVariables();
	void initTexture(sf::Texture& texture);
	void initSprite();
	void initPosition(sf::Vector2f& pos);
public:
	Tile(sf::Texture& texture, sf::Vector2f& pos);
	virtual ~Tile();

	//Tile Sprite
	sf::Sprite sprite_tile;

	//Accessors
	const float& getSizeX() const;

	//Animation functions
	void ThreeSixtyAnimation();


	//Main functions
	void updateThreeSixtyAnimation();
	void updateHoverScaleAnimation();
	void updateAnimations();
	void update();

	void render(sf::RenderTarget& target);
};

