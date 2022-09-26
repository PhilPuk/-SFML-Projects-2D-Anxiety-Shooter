#include "BloomManager.h"

void BloomManager::initTextures()
{
	if (!this->t_Bloom.loadFromFile("Textures/Blooms/base.png"))
		std::cout << " - ERROR::BLOOM::INITTEXTURES::Couldn't load texture: base.png";
}

void BloomManager::initVariables()
{
	this->scalebigger = false;
	this->ScaleAnimationAmount = 0.1f;
	this->maxScale = 1.f + 0.3f;
}

void BloomManager::initBaseBloom()
{
	this->Circle_Bloom.setRadius(30.f);
	this->Circle_Bloom.setTexture(&this->t_Bloom);
	this->Circle_Bloom.setFillColor(sf::Color(255, 255, 255, 110));
	sf::FloatRect rect = this->Circle_Bloom.getLocalBounds();
	this->Circle_Bloom.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
}

void BloomManager::initCategoryVectors()
{
	//LAST CHECKPOINT
}

BloomManager::BloomManager()
{
	this->initTextures();
	this->initVariables();
	this->initBaseBloom();
}

BloomManager::~BloomManager()
{
	for (int i = 0; i < this->blooms.size(); i++)
	{
		for (int j = 0; j < this->blooms[i].size(); j++)
		{
			//Blooms clear up
			delete this->blooms[i][j];
			this->blooms.erase(this->blooms.begin(), this->blooms.end());

			//Bloom velocity clear up
			delete this->bloomVelocity[i][j];
			this->bloomVelocity.erase(this->bloomVelocity.begin(), this->bloomVelocity.end());
		}
	}
}

void BloomManager::deleteSpecificBloom(int CategoryIndex, int index)
{
	this->blooms[CategoryIndex].erase(this->blooms[CategoryIndex].begin() + index);
	this->bloomVelocity[CategoryIndex].erase(this->bloomVelocity[CategoryIndex].begin() + index);
}

void BloomManager::createNewBloom(int CategoryIndex, sf::Vector2f& bloomPos, sf::Vector2f* bloomVelocity, sf::Color color, float radius)
{
	//Adjust base bloom before push back
	this->Circle_Bloom.setRadius(radius);
	this->Circle_Bloom.setPosition(bloomPos);
	this->Circle_Bloom.setFillColor(color);
		//Center origin
	sf::FloatRect rect = this->Circle_Bloom.getLocalBounds();
	this->Circle_Bloom.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);

	//Add new bloom
	this->blooms[CategoryIndex].push_back(new sf::CircleShape(this->Circle_Bloom));

	//Add velocity to vector
	this->bloomVelocity[CategoryIndex].push_back(bloomVelocity);
}

void BloomManager::updateScalingAnimation(int CategroyIndex, int index)
{
	if (this->scalebigger)
	{
		if (this->blooms[CategroyIndex][index]->getScale().x > this->maxScale)
		{
			this->scalebigger = !this->scalebigger;
			return;
		}
		this->blooms[CategroyIndex][index]->scale(1.f + this->ScaleAnimationAmount, 1.f + this->ScaleAnimationAmount);
	}
	else
	{
		if (this->blooms[CategroyIndex][index]->getScale().x < 1.f)
		{
			this->scalebigger = !this->scalebigger;
			return;
		}
		this->blooms[CategroyIndex][index]->scale(1.f - this->ScaleAnimationAmount, 1.f - this->ScaleAnimationAmount);
	}
}

void BloomManager::updateBloomMovement(int CategroyIndex, int index)
{
	this->blooms[CategroyIndex][index]->move(*this->bloomVelocity[CategroyIndex][index]);
}

void BloomManager::updateBloomOutOfScreen(int CategroyIndex, int index, sf::Vector2u& winSize)
{
	if (this->blooms[CategroyIndex][index]->getPosition().x < 0 ||
		this->blooms[CategroyIndex][index]->getPosition().x > winSize.x ||
		this->blooms[CategroyIndex][index]->getPosition().y < 0 ||
		this->blooms[CategroyIndex][index]->getPosition().y > winSize.y)
		this->deleteSpecificBloom(CategroyIndex, index);
}

void BloomManager::update2dVectorLoop(sf::Vector2u& winSize)
{
	for (int i = 0; i < this->blooms.size(); i++)
	{
		for (int j = 0; j < this->blooms[i].size(); j++)
		{
			this->updateScalingAnimation(i, j);
			this->updateBloomMovement(i, j);
			this->updateBloomOutOfScreen(i, j, winSize);
		}
	}
}

void BloomManager::update(sf::Vector2u& winSize)
{
	this->update2dVectorLoop(winSize);
}

void BloomManager::renderBlooms(sf::RenderTarget& target)
{
	for (int i = 0; i < this->blooms.size(); i++)
	{
		for (int j = 0; j < this->blooms[i].size(); j++)
		{
			target.draw(*this->blooms[i][j]);
		}
	}
}

void BloomManager::render(sf::RenderTarget& target)
{
	this->renderBlooms(target);
}
