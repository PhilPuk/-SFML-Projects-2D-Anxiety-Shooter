#pragma once

#include<iostream>
#include<time.h>
#include<math.h>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>


class Upgrades
{
private:
	//Ammo
	float CurrentAddedAmmo;
	float CurrentAddedMaxHP;
	float CurrentAddedHP;

	/// <summary>
	/// 0 = Max Ammo
	/// 1 = Max Hp
	/// 2 = HP
	/// 3 = Money
	/// 4 = Player takes Damage
	/// </summary>
	sf::Texture Texture_Upgrades[5];
	sf::Sprite Sprite_Upgrades[5];

	std::vector<sf::Sprite*> animations;

	float animationTimerMax;
	float animationTimer;

	int animationCounter;

	void initVariables();
	void initTextures();
	void initSprites();
public:
	Upgrades();
	virtual ~Upgrades();

	//Functions

	///	Base construct for rng upgrades
	///	Checks if the rolled dice is smaller then the given possibilty.
	/// If yes return true else false.
	/// Add variables that will be changed as upgrade counting.
	bool RNGBaseConstruct(int possibility, float* addCounter);

	//RNG Upgrades from killing enemies
	// 
	//Adds more Ammo with a chance of 5%
	bool RNGAddedAmmo();
	//Adds more Ammo with a chance of 2%
	bool RNGAddMaxHP();
	//Adds more Ammo with a chance of 3%
	bool RNGAddHP();

	void createNewAnimation(sf::Vector2f&pos, int i);
	void createNewAmmoAnimation(sf::Vector2f& pos);
	void createNewMaxHPAnimation(sf::Vector2f& pos);
	void createNewHPAnimation(sf::Vector2f& pos);
	void createNewMoneyAnimation(sf::Vector2f& pos);
	void createNewDamageTakenAnimation(sf::Vector2f& pos, float& angle);

	void updateAnimations();

	void renderAnimation(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

