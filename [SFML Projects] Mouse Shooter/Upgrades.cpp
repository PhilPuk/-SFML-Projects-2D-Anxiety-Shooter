#include "Upgrades.h"

void Upgrades::initVariables()
{
	this->CurrentAddedAmmo = 0.f;
	this->CurrentAddedMaxHP = 0.f;
	this->CurrentAddedHP = 0.f;

	this->animationTimerMax = 2.f;
	this->animationTimer = 0.f;

	this->animationCounter = 0;
}

void Upgrades::initTextures()
{
	if (!this->Texture_Upgrades[0].loadFromFile("Textures/Upgrades/Ammo.png"))
	{
		std::cout<<" - ERROR::UPGRADES::INITTEXTURES::Couldn't load texture: Ammo.png!\n";
	}

	if (!this->Texture_Upgrades[1].loadFromFile("Textures/Upgrades/MaxHP.png"))
	{
		std::cout << " - ERROR::UPGRADES::INITTEXTURES::Couldn't load texture: MaxHP.png!\n";
	}

	if (!this->Texture_Upgrades[2].loadFromFile("Textures/Upgrades/HP.png"))
	{
		std::cout << " - ERROR::UPGRADES::INITTEXTURES::Couldn't load texture: HP.png!\n";
	}


	if (!this->Texture_Upgrades[3].loadFromFile("Textures/Upgrades/Money.png"))
	{
		std::cout << " - ERROR::UPGRADES::INITTEXTURES::Couldn't load texture: Money.png!\n";
	}
	
	if (!this->Texture_Upgrades[4].loadFromFile("Textures/Upgrades/PlayerTakesDamage.png"))
	{
		std::cout << " - ERROR::UPGRADES::INITTEXTURES::Couldn't load texture: PlayerTakesDamage.png!\n";
	}
}

void Upgrades::initSprites()
{
	for (int i = 0; i < 4; i++)
	{
		this->Sprite_Upgrades[i].setTexture(this->Texture_Upgrades[i]);
		//this->Sprite_Upgrades->setColor(sf::Color(0, 0, 0, 0));
	}

}

Upgrades::Upgrades()
{
	this->initVariables();
	this->initTextures();
	this->initSprites();
	//this->animations.push_back(new sf::Sprite(this->Sprite_Upgrades[0]));
	//this->animations[0]->setPosition(sf::Vector2f(500.f, 400.f));
}

Upgrades::~Upgrades()
{
	for (size_t i = 0; i < this->animations.size(); i++)
	{
		delete this->animations[i];
		this->animations.erase(this->animations.begin(), this->animations.end());
	}
}

bool Upgrades::RNGBaseConstruct(int possibility, float* addCounter)
{
	int dice = rand() % 100;
	if (dice < possibility)
	{
		addCounter += 1;
		return true;
	}
	else
	{
		return false;
	}
}

bool Upgrades::RNGAddedAmmo()
{
	return this->RNGBaseConstruct(3, &this->CurrentAddedAmmo);
}

bool Upgrades::RNGAddMaxHP()
{
	return this->RNGBaseConstruct(2, &this->CurrentAddedMaxHP);
}

bool Upgrades::RNGAddHP()
{
	return this->RNGBaseConstruct(5, &this->CurrentAddedHP);
}

void Upgrades::createNewAnimation(sf::Vector2f& pos, int i)
{
	this->animations.push_back(new sf::Sprite);
	this->animations[this->animationCounter]->setTexture(this->Texture_Upgrades[i]);
	sf::FloatRect rect = this->animations[this->animationCounter]->getLocalBounds();
	this->animations[this->animationCounter]->setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	this->animations[this->animationCounter]->setPosition(pos);
	this->animationCounter++;
}

void Upgrades::createNewAmmoAnimation(sf::Vector2f& pos)
{
	this->createNewAnimation(pos, 0);
}

void Upgrades::createNewMaxHPAnimation(sf::Vector2f& pos)
{
	this->createNewAnimation(pos, 1);
}

void Upgrades::createNewHPAnimation(sf::Vector2f& pos)
{
	this->createNewAnimation(pos, 2);
}

void Upgrades::createNewMoneyAnimation(sf::Vector2f& pos)
{
	this->createNewAnimation(pos, 3);
}

void Upgrades::createNewDamageTakenAnimation(sf::Vector2f& pos, float& angle)
{
	this->createNewAnimation(pos, 4);
	this->animations[this->animationCounter - 1]->scale(1.f, 1.f);
	this->animations[this->animationCounter - 1]->rotate(angle);
}

void Upgrades::updateAnimations()
{
	if (this->animationTimer < this->animationTimerMax)
	{
		this->animationTimer += 1.f;
	}
	else
	{
		this->animationTimer = 0.f;
		float scaleSub = 0.002f;
		for (int i = 0; i < this->animations.size(); i++)
		{
			this->animations[i]->scale(this->animations[i]->getScale().x - scaleSub, this->animations[i]->getScale().y - scaleSub);
			if (this->animations[i]->getScale().x <= 0.f)
			{
				this->animations.erase(this->animations.begin() + i);
				this->animationCounter--;
				//std::cout << "Total animations: "<<this->animations.size() << "\n";
			}
		}
	}
}

void Upgrades::renderAnimation(sf::RenderTarget& target)
{
	for (int i = 0;i < this->animations.size();i++)
	{
		target.draw(*this->animations[i]);
	}
}

void Upgrades::render(sf::RenderTarget& target)
{
	this->renderAnimation(target);
}
