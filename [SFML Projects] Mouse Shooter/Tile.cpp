#include "Tile.h"

//Initizalation
void Tile::initVariables()
{
	this->sizeX = 200.f;
	this->sizeY = 200.f;

	this->ScaleIndex = 0;
	this->ScaleMax = 2.f;
	this->ScaleMin = 1.40f;
	this->ScaleFac = static_cast<float>(rand() % 3 + 1);
	this->ScaleFac /= 100.f;

	this->RotationAngle = 0.f;

	this->ActivateThreeSixtyAnimation = false;
}

void Tile::initTexture(sf::Texture& texture)
{
	this->sprite_tile.setTexture(texture);
}

void Tile::initSprite()
{
	//this->sprite_tile.scale(1.f, 1.f);

	//Center the origin
	sf::FloatRect rect = this->sprite_tile.getLocalBounds();
	this->sprite_tile.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	this->sprite_tile.scale(1.5f, 1.5f);
}

void Tile::initPosition(sf::Vector2f& pos)
{
	//Sets position in tile system
	//Managed by the tile manager
	this->sprite_tile.setPosition(pos);
}


Tile::Tile(sf::Texture& texture, sf::Vector2f& pos)
{
	this->initVariables();
	this->initTexture(texture);
	this->initSprite();
	this->initPosition(pos);
}

Tile::~Tile()
{

}

const float& Tile::getSizeX() const
{
	return this->sprite_tile.getGlobalBounds().width;
}

void Tile::ThreeSixtyAnimation()
{
	if (this->ActivateThreeSixtyAnimation)
	{
		this->RotationAngle += 1.f;
		this->sprite_tile.rotate(this->RotationAngle);

		if (this->RotationAngle >= 360.f)
		{
			this->RotationAngle = 0.f;
			this->ActivateThreeSixtyAnimation = false;
		}
	}
}

void Tile::updateThreeSixtyAnimation()
{
	int dice = rand() % 10000 + 1;

	if (dice < 3)
	{
		this->ActivateThreeSixtyAnimation = true;
	}
}

void Tile::updateHoverScaleAnimation()
{
	//Create rand scale factor
	this->ScaleFac = static_cast<float>(rand() % 90 + 1);
	this->ScaleFac /= 20000.f;

	//Increase scale
	if (this->ScaleIndex == 0)
	{
		this->sprite_tile.scale(this->ScaleFac + 1.f, this->ScaleFac + 1.f);
		if (this->sprite_tile.getScale().x > this->ScaleMax)
			this->ScaleIndex = 1;
	}
	//Decrease scale
	else if (this->ScaleIndex == 1)
	{
		this->sprite_tile.scale(1.f - this->ScaleFac, 1.f - this->ScaleFac);
		if (this->sprite_tile.getScale().x < this->ScaleMin)
			this->ScaleIndex = 0;
	}
}

void Tile::updateAnimations()
{
	this->updateHoverScaleAnimation();

	this->updateThreeSixtyAnimation();

	//Only plays if bool is true
	this->ThreeSixtyAnimation();
}

void Tile::update()
{
	this->updateAnimations();
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->sprite_tile);
}
