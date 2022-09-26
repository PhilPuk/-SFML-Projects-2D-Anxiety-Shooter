#pragma once

#include<iostream>
#include<vector>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class BloomManager
{
private:
	sf::Texture t_Bloom;
	sf::CircleShape Circle_Bloom;
	/*
	* Adjust for the used project
	Category Indexes:
		0 = Player
		1 = HP BAR
		2 = Enemies
		3 = Bullets
	*/
	std::vector<std::vector<sf::Vector2f*>> bloomVelocity;
	std::vector<std::vector<sf::CircleShape*>> blooms;
	//Scaling Animation stuff
	bool scalebigger;
	float maxScale;
	float ScaleAnimationAmount;

	void initTextures();
	void initVariables();
	void initBaseBloom();
	void initCategoryVectors();
public:
	BloomManager();
	virtual ~BloomManager();

	//Delete blooms
	/*
	Category Indexes:
		0 = Player
		1 = HP BAR
		2 = Enemies
		3 = Bullets
	*/
	void deleteSpecificBloom(int CategoryIndex, int index);

	//Create blooms
	/*
	Category Indexes:
		0 = Player
		1 = HP BAR
		2 = Enemies
		3 = Bullets
	*/
	void createNewBloom(int CategoryIndex, sf::Vector2f& bloomPos, sf::Vector2f* bloomVelocity, sf::Color color, float radius);

	//Updating
	void updateScalingAnimation(int CategroyIndex, int index);
	void updateBloomMovement(int CategroyIndex, int index);
	void updateBloomOutOfScreen(int CategroyIndex, int index, sf::Vector2u& winSize);
		//Calls all for loops update functions
	void update2dVectorLoop(sf::Vector2u& winSize);
	void update(sf::Vector2u& winSize);

	//Rendering
	void renderBlooms(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

