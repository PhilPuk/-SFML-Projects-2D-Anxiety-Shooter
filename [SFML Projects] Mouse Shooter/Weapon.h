#pragma once

#include<iostream>
#include<sstream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include"Bullet.h"
#include"bloom.h"

class Weapon abstract
{
private:
	int opacity;

public:
	sf::Texture texture_weapon;
	sf::Sprite sprite_weapon;
	sf::Texture Texture_bullets;
	sf::Texture t_Bloom;
	sf::Texture t_WeaponBloom;

	//Texts
	sf::Text Text_Ammo;

	int MaxAmmo;
	int CurrAmmo;
	int AmmoSave; //Used for updating bullet text

	bool Reloading;
	float ReloadTimerMax;
	float ReloadTimer;

	//Used to get in game 
	bool bulletShot;
	bool ShootingPressed;
	float BulletSpeed;
	bool bulletdeleted;
	short lastdeletedBulletIndex;

	//Cooldowns
	float ShootCDMAX;
	float ShootCD;
	
	//Damage
	float damageBullet;

	std::vector<int> deletedIndexes;

	//Initialization
	virtual void initVariables();
	virtual void initTexture();
	virtual void initBloomTexture();
	virtual void initBulletTexture();
	virtual void initSprite(sf::Vector2f spawningPos);
	virtual void initTexts(sf::Vector2u& winSize, sf::Font& font);
	virtual void initBloom();
	Weapon();
	Weapon(sf::Vector2f spawningPos, sf::Vector2u& winSize, sf::Font& font);
	virtual ~Weapon();

	//Bullet
	std::vector<Bullet*> bullets;

	//Blooms
	Bloom* bloom;

	//Functions
	void shootBullet(sf::Vector2f& AimDiretionNormal);
	void ReloadWeapon();

	//Accessors
	const float& getBulletDamage() const;
	const bool& getBulletShot() const;
	const bool& getBulledDeleted() const;
	const short& getLastDeletedBulledIndex() const;
	const short& getSizeOfBulletArray() const;
	
	//Modifiers
	void ModifyMaxAmmo(int MaxAmmo);
	void ModifyReloadTimerMax(float ReloadTimerMax);
	void ModifyBulletSpeed(float BulletSpeed);
	void ModifyBulletDamage(float BulletDamage);
	void addMaxAmmo(int add);
	void substractReloadTimerMax(float substract);
	void addBulletSpeed(float add);
	void addBulletDamage(float add);
	void resetBulletShoot();
	void resetBulletDeleted();
	void setLastDeletedBulletIndex(short i);

	void updateAmmoTextContent();
	void updateAmmoText();
	void updateWeaponRotation(float RotationAngle);
	void updateWeaponPosition(sf::Vector2f pos);
	void updateBulletOutOfScreen(sf::Vector2u& winSize, size_t& i);
	void updateBulletMoving(sf::Vector2u& winSize);
	void updateShootingSystem(sf::Vector2f& AimDiretionNormal);
	virtual void update(sf::Vector2u& winSize, float RotationAngle, sf::Vector2f pos, sf::Vector2f& AimDiretionNormal);

	void renderTexts(sf::RenderTarget& target);
	void renderBullets(sf::RenderTarget& target);
	void renderWeapon(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

