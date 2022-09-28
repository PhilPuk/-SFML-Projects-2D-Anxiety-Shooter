#include "BloomManager.h"

void BloomManager::initTextures()
{
	if (!this->t_Bloom.loadFromFile("Textures/Blooms/base.png"))
		std::cout << " - ERROR::BLOOM::INITTEXTURES::Couldn't load texture: base.png";

	if (!this->t_EnemiesBloom.loadFromFile("Textures/blooms/enemey.png"))
		std::cout << " - ERROR::BLOOM::INITTEXTURES::Couldn't load texture: enemey.png";

	if (!this->t_PlayerBloom.loadFromFile("Textures/blooms/player.png"))
		std::cout << " - ERROR::BLOOM::INITTEXTURES::Couldn't load texture: player.png";

	if (!this->t_HPBarBloom.loadFromFile("Textures/blooms/HPBar.png"))
		std::cout << " - ERROR::BLOOM::INITTEXTURES::Couldn't load texture: HPBar.png";
}

void BloomManager::initVariables()
{
	this->scalebigger = false;
	this->ScaleAnimationAmount = 0.1f;
	this->maxScale = 1.f + 0.3f;
}

void BloomManager::initBaseBloom()
{
	this->Circle_Bloom.setPosition(-300.f, -300.f);
	this->Circle_Bloom.setRadius(30.f);
	this->Circle_Bloom.setTexture(&this->t_Bloom);
	this->Circle_Bloom.setFillColor(sf::Color(255, 255, 255, 110));
	sf::FloatRect rect = this->Circle_Bloom.getLocalBounds();
	this->Circle_Bloom.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
}

void BloomManager::initPlayerBloom()
{
	this->Player_Bloom.scale(0.35f, 0.35f);
	this->Player_Bloom.setTexture(this->t_PlayerBloom);
	sf::FloatRect rect = this->Player_Bloom.getLocalBounds();
	this->Player_Bloom.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
}

BloomManager::BloomManager()
{
	this->initTextures();
	this->initVariables();
	this->initBaseBloom();
	this->initPlayerBloom();
}

BloomManager::~BloomManager()
{
		for (int i = 0; i < this->blooms.size(); i++)
		{
			//Blooms clear up
			delete this->blooms[i];
			this->blooms.erase(this->blooms.begin(), this->blooms.end());

			delete this->bloomVelocity[i];
			this->bloomVelocity.erase(this->bloomVelocity.begin(), this->bloomVelocity.end());
		}
		//std::cout << "Blooms vector size after delete: " << this->blooms.size()<<"\n";
		//std::cout << "Bloom Velocitys vector size after delete: " << this->bloomVelocity.size()<<"\n";
}

void BloomManager::deleteSpecificBloom(int index)
{
	delete this->blooms[index];
	this->blooms.erase(this->blooms.begin() + index);
	delete this->bloomVelocity[index];
	this->bloomVelocity.erase(this->bloomVelocity.begin() + index);
}

void BloomManager::createNewBloom(sf::Vector2f& bloomPos, sf::Vector2f* bloomVelocity, sf::Color color, float radius)
{
	//Adjust base bloom before push back
	this->Circle_Bloom.setRadius(radius);
	this->Circle_Bloom.setPosition(bloomPos);
	this->Circle_Bloom.setFillColor(color);
		//Center origin
	if (radius != 30.f)
	{
		sf::FloatRect rect = this->Circle_Bloom.getLocalBounds();
		this->Circle_Bloom.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	}

	//Add new bloom
	this->blooms.push_back(new sf::CircleShape(this->Circle_Bloom));

	//Add velocity to vector
	this->bloomVelocity.push_back(new sf::Vector2f(*bloomVelocity));
}

void BloomManager::updateScalingAnimation(int index)
{
	if (this->scalebigger)
	{
		if (this->blooms[index]->getScale().x > this->maxScale)
		{
			this->scalebigger = !this->scalebigger;
			return;
		}
		this->blooms[index]->scale(1.f + this->ScaleAnimationAmount, 1.f + this->ScaleAnimationAmount);
	}
	else
	{
		if (this->blooms[index]->getScale().x < 1.f)
		{
			this->scalebigger = !this->scalebigger;
			return;
		}
		this->blooms[index]->scale(1.f - this->ScaleAnimationAmount, 1.f - this->ScaleAnimationAmount);
	}
}

void BloomManager::updatePlayerBloomMovement(sf::Vector2f& PlayerMovement)
{
	this->Player_Bloom.move(PlayerMovement);
}

void BloomManager::updatePlayerBloomRotation(float angle)
{
	this->Player_Bloom.setRotation(angle);
}

void BloomManager::updateBloomMovement(int index)
{
	this->blooms[index]->move(*this->bloomVelocity[index]);
}

void BloomManager::updateBloomOutOfScreen( int index, sf::Vector2u& winSize)
{
	if (this->blooms[index]->getPosition().x < 0 ||
		this->blooms[index]->getPosition().x > winSize.x ||
		this->blooms[index]->getPosition().y < 0 ||
		this->blooms[index]->getPosition().y > winSize.y)
	{
		this->deleteSpecificBloom(index);
		//std::cout << index << " out of screen!\n";
	}
}

void BloomManager::updateVectorLoop(sf::Vector2u& winSize)
{
	for (int i = 0; i < this->blooms.size(); i++)
	{
			this->updateScalingAnimation(i);
			this->updateBloomMovement(i);
			this->updateBloomOutOfScreen(i, winSize);
	}
}

void BloomManager::update(sf::Vector2u& winSize, sf::Vector2f& PlayerMovement, float rotationangle)
{
	this->updatePlayerBloomMovement(PlayerMovement);
	this->updatePlayerBloomRotation(rotationangle);
	this->updateVectorLoop(winSize);
}

void BloomManager::renderBulletBlooms(sf::RenderTarget& target)
{
	for (int i = 0; i < this->blooms.size(); i++)
	{
			target.draw(*this->blooms[i]);
	}
}

void BloomManager::renderPlayerBloom(sf::RenderTarget& target)
{
	target.draw(this->Player_Bloom);
}

void BloomManager::render(sf::RenderTarget& target)
{
	this->renderBulletBlooms(target);
	this->renderPlayerBloom(target);
}
