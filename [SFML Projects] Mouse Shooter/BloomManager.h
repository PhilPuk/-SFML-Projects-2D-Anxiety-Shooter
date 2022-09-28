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
	sf::Texture t_EnemiesBloom;
	sf::Texture t_PlayerBloom;
	sf::Texture t_HPBarBloom;

	sf::CircleShape Circle_Bloom;
	sf::Sprite Player_Bloom;

	std::vector<sf::Vector2f*> bloomVelocity;
	std::vector<sf::CircleShape*> blooms;
	//Scaling Animation stuff
	bool scalebigger;
	float maxScale;
	float ScaleAnimationAmount;

	void initTextures();
	void initVariables();
	void initBaseBloom();
	void initPlayerBloom();
public:
	BloomManager();
	virtual ~BloomManager();

	//Delete blooms
	void deleteSpecificBloom(int index);

	//Create blooms
	void createNewBloom(sf::Vector2f& bloomPos, sf::Vector2f* bloomVelocity, sf::Color color, float radius);

	//Updating
	void updateScalingAnimation(int index);
	void updatePlayerBloomMovement(sf::Vector2f& PlayerMovement);
	void updatePlayerBloomRotation(float angle);
	void updateBloomMovement(int index);
	void updateBloomOutOfScreen(int index, sf::Vector2u& winSize);
		//Calls all for loops update functions
	void updateVectorLoop(sf::Vector2u& winSize);
	void update(sf::Vector2u& winSize, sf::Vector2f& PlayerMovement, float rotationangle);

	//Rendering
	void renderBulletBlooms(sf::RenderTarget& target);
	void renderPlayerBloom(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

