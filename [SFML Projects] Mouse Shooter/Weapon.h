#pragma once

#include<iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Weapon abstract
{
public:

	sf::Texture texture_weapon;
	sf::Sprite sprite_weapon;

	int MaxAmmo;
	int CurrAmmo;

	float ReloadTimerMax;
	float ReloadTimer;

	float BulletSpeed;

	//Initialization
	virtual void initVariables();
	virtual void initTexture();
	virtual void initSprite(sf::Vector2f spawningPos);
	Weapon();
	Weapon(sf::Vector2f spawningPos);
	virtual ~Weapon();

	//Accessors
	virtual sf::Vector2f& getBulletSpawn();

	//Modifiers
	void ModifyMaxAmmo(float MaxAmmo);
	void ModifyReloadTimerMax(float ReloadTimerMax);
	void ModifyBulletSpeed(float BulletSpeed);

	void updateWeaponRotation(float RotationAngle);
	void updateWeaponPosition(sf::Vector2f pos);
	virtual void update(float RotationAngle, sf::Vector2f pos);

	void renderWeapon(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

