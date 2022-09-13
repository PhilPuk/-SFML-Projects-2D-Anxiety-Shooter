#include "Bullet.h"

void Bullet::initVariables(sf::Vector2f& spawnPos, sf::Vector2f& Velocity)
{
	this->sprite_bullet.setPosition(spawnPos);
	this->currVelocity = Velocity;

	this->maxSpeed = 25.f;
}

void Bullet::initTexture(sf::Texture& texture)
{
	this->sprite_bullet.setTexture(texture);


}

void Bullet::initSprite()
{

	this->sprite_bullet.scale(0.8f, 0.8f);
	//Center bulllets
	sf::FloatRect rect = this->sprite_bullet.getLocalBounds();

	this->sprite_bullet.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
}

const sf::Vector2f& Bullet::getCurrVelocity() const
{
	return this->currVelocity;
}

Bullet::Bullet(sf::Texture& texture, sf::Vector2f& spawnPos, sf::Vector2f& Velocity)
{
	this->initVariables(spawnPos, Velocity);
	this->initTexture(texture);
	this->initSprite();
		this->sprite_bullet.setTexture(texture);

		//this->sprite_bullet.setFillColor(sf::Color::Red);
}

Bullet::~Bullet()
{

}

