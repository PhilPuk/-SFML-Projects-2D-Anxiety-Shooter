#pragma once

#include<iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include"Mouse.h"
#include"Vignette.h"

class Slider
{
private:
	sf::Text Slider_Title;
	sf::RectangleShape r_Background;
	sf::RectangleShape r_Slider;

	float maxX, minX;

	void initVariables(sf::Vector2f size, sf::Vector2f pos);
	void initBackgroundPart(sf::Vector2f size, sf::Vector2f pos);
	void initSliderPart(sf::Vector2f size, sf::Vector2f pos);
	void initText(sf::Font& font,sf::Vector2f size, sf::Vector2f pos, std::string text);
public:
	Slider(sf::Font& font, sf::Vector2f size, sf::Vector2f pos, std::string text);
	virtual ~Slider();

	void SliderMovement(Mouse& mouse, sf::RenderWindow& window, Vignette& vignette);
	void updateCheckOnEdges();
	void update(Mouse& mouse, sf::RenderWindow& window, Vignette& vignette);

	void renderBackground(sf::RenderTarget& target);
	void renderSlider(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

