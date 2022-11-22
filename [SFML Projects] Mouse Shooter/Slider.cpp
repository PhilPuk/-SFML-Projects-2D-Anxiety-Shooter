#include "Slider.h"

void Slider::initVariables(sf::Vector2f size, sf::Vector2f pos)
{
	this->maxX = pos.x + size.x;
	this->minX = pos.x;
}

void Slider::initBackgroundPart(sf::Vector2f size, sf::Vector2f pos)
{
	this->r_Background.setFillColor(sf::Color(255,255,255,70));
	this->r_Background.setSize(size);
	this->r_Background.setPosition(pos);
}

void Slider::initSliderPart(sf::Vector2f size, sf::Vector2f pos)
{
	this->r_Slider.setFillColor(sf::Color::Magenta);
	this->r_Slider.setSize(sf::Vector2f(size.x / 10.f, size.y));
	this->r_Slider.setPosition(pos.x + size.x / 2.f - this->r_Slider.getGlobalBounds().width / 2.f, pos.y);
}

void Slider::initText(sf::Font& font, sf::Vector2f size, sf::Vector2f pos, std::string text)
{
	this->Slider_Title.setFont(font);
	this->Slider_Title.setString(text);
	this->Slider_Title.setFillColor(sf::Color::Magenta);
	this->Slider_Title.setCharacterSize(static_cast<unsigned int>(size.x) / 8);
	this->Slider_Title.setPosition(pos.x, pos.y - this->Slider_Title.getGlobalBounds().height * 1.15f);
}

Slider::Slider(sf::Font& font, sf::Vector2f size, sf::Vector2f pos, std::string text)
{
	this->initVariables(size, pos);
	this->initBackgroundPart(size, pos);
	this->initSliderPart(size, pos);
	this->initText(font, size, pos, text);
}

Slider::~Slider()
{

}

void Slider::SliderMovement(Mouse& mouse, sf::RenderWindow& window, Vignette& vignette)
{
	//Check if mouse is on slider
	if (this->r_Slider.getGlobalBounds().contains(mouse.getMousePosView()))
	{
		if (mouse.getMouseLeftClicked())
		{
		//Move slider on mouse pos
		this->r_Slider.setPosition(mouse.getMousePosView().x - this->r_Slider.getGlobalBounds().width / 2.f, this->r_Slider.getPosition().y);
		mouse.updateMousePositions(window, false);
		std::cout << "Mouse x: " << mouse.getMousePosView().x << "\n";
		std::cout << "r_Slider x: " << this->r_Slider.getPosition().x << "\n";

		//Percentage value of the sliders position
		float posPercentage = ((this->r_Slider.getPosition().x + this->r_Slider.getGlobalBounds().width / 2.f) - this->r_Background.getPosition().x) / (this->r_Background.getGlobalBounds().width);
		std::cout << "Percentage: " << posPercentage << "\n";
		int newOpacity = posPercentage * 200 + 65;
		if (newOpacity > 255)
			newOpacity = 255;

		std::cout << "Opacity: " << newOpacity << "\n";
		vignette.changeOpacity(newOpacity);
		}

	}
}

void Slider::updateCheckOnEdges()
{
	//Left
	if (this->r_Slider.getPosition().x < this->r_Background.getPosition().x)
	{
		this->r_Slider.setPosition(this->r_Background.getPosition().x, this->r_Background.getPosition().y);
	}
	//Right
	else if (this->r_Slider.getPosition().x + this->r_Slider.getGlobalBounds().width > this->r_Background.getPosition().x + this->r_Background.getGlobalBounds().width)
	{
		this->r_Slider.setPosition(this->r_Background.getPosition().x + this->r_Background.getGlobalBounds().width - this->r_Slider.getGlobalBounds().width, this->r_Background.getPosition().y);
	}
}

void Slider::update(Mouse& mouse, sf::RenderWindow& window, Vignette& vignette)
{
	this->SliderMovement(mouse, window, vignette);

	this->updateCheckOnEdges();
}

void Slider::renderBackground(sf::RenderTarget& target)
{
	target.draw(this->r_Background);
}

void Slider::renderSlider(sf::RenderTarget& target)
{
	target.draw(this->r_Slider);
}

void Slider::renderText(sf::RenderTarget& target)
{
	target.draw(this->Slider_Title);
}

void Slider::render(sf::RenderTarget& target)
{
	this->renderBackground(target);
	this->renderSlider(target);
	this->renderText(target);
}
