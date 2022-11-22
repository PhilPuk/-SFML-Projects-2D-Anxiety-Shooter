#include "Vignette.h"

void Vignette::initTexture()
{
	if (!this->t_Vignette.loadFromFile("Textures/Vignette/vignette.png"))
	{
		std::cout << " - ERROR::VIGNETTE::INITTEXTURE::Couldn't load texture: Textures/Vignette/vignette.png\n";
	}
}

void Vignette::initVariables()
{
	this->scale = false;
	this->scale_Max = 1.2f;
	this->scale_fac = 0.01f;
	this->scale_Min = 1.f + this->scale_fac;
}

void Vignette::initSprite(sf::Vector2u& winSize)
{
	this->s_Vignette.setTexture(this->t_Vignette);
	
	this->s_Vignette.setColor(sf::Color(255, 255, 255, 200));
	sf::FloatRect rect = this->s_Vignette.getLocalBounds();
	this->s_Vignette.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	this->s_Vignette.setPosition(static_cast<float>(winSize.x) / 2.f, static_cast<float>(winSize.y) / 2.f);
}

Vignette::Vignette(sf::Vector2u& winSize)
{
	this->initTexture();
	this->initVariables();
	this->initSprite(winSize);
}

Vignette::~Vignette()
{

}

void Vignette::changeOpacity(int opactiy)
{
	this->s_Vignette.setColor(sf::Color(255, 255, 255, opactiy));
}

void Vignette::updateScaling()
{
	if (scale)
	{
		if (this->s_Vignette.getScale().x > this->scale_Max)
		{
			scale = !scale;
		}
		this->s_Vignette.scale(1.f + this->scale_fac, 1.f + this->scale_fac);
	}
	else
	{
		if (this->s_Vignette.getScale().x < this->scale_Min)
		{
			scale = !scale;
		}
		this->s_Vignette.scale(1.f - this->scale_fac, 1.f - this->scale_fac);
	}
}

void Vignette::update()
{
	this->updateScaling();
}

void Vignette::renderVignette(sf::RenderTarget& target)
{
	target.draw(this->s_Vignette);
}

void Vignette::render(sf::RenderTarget& target)
{
	this->renderVignette(target);
}
