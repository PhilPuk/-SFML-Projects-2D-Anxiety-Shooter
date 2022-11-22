#pragma once

#include<iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Vignette
{
private:
	sf::Texture t_Vignette;
	sf::Sprite s_Vignette;

	bool scale;
	float scale_Max;
	float scale_Min;
	float scale_fac;

	void initTexture();
	void initVariables();
	void initSprite(sf::Vector2u& winSize);
public:
	Vignette(sf::Vector2u& winSize);
	virtual ~Vignette();

	//Modifiers
	void changeOpacity(int opactiy);

	void updateScaling();
	void update();

	void renderVignette(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

