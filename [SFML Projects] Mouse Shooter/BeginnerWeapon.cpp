#include "BeginnerWeapon.h"


void BeginnerWeapon::initTexture()
{
	if (!this->texture_weapon.loadFromFile("Textures/weapons/beginner/weapon1.png"))
		
		std::cout<< " - ERROR::WEAPON::INITTEXTURE::Couldn't load texture: beginner/weapon1.png!\n";

	std::cout << "BeginnerWeapon!\n";
}



void BeginnerWeapon::initSprite(sf::Vector2f spawningPos)
{
	this->sprite_weapon.setTexture(this->texture_weapon);
	this->sprite_weapon.scale(0.45f, 0.45f);

	sf::FloatRect rect_weapon = this->sprite_weapon.getLocalBounds();

	this->sprite_weapon.setOrigin(rect_weapon.left + rect_weapon.width / 2.f, rect_weapon.top + rect_weapon.height / 1.67f);

	this->sprite_weapon.setPosition(spawningPos);
}


BeginnerWeapon::BeginnerWeapon(sf::Vector2f spawnPos, sf::Vector2u& winSize, sf::Font& font)
{
	this->initVariables();
	this->initTexture();
	this->initSprite(spawnPos);
	this->initBulletTexture();
	this->initTexts(winSize, font);
}

sf::Vector2f& BeginnerWeapon::getBulletSpawn()
{
		sf::Vector2f spawn = sf::Vector2f(this->sprite_weapon.getPosition().x, this->sprite_weapon.getPosition().y);
		return spawn;
}
