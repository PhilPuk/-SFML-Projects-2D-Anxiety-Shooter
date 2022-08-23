#pragma once

#include<iostream>
#include<sstream>
#include<vector>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Shop
{
private:
	//Logic
	bool endShop;
	bool endApplication;

	//Money
	float Bank;
	float IncomeOfRound;

	//Upgrades
	int Amount_Upgrades;

	//Spacings
	float spacing_SectionChooser;
	float spacing_Upgrades;

	//NAVIGATION BUTTONS:
	//0.BACK BUTTON
	//1.PLAYER UPGRADE SECTION
	//2.WEAPON UPGRADE SECTION
	sf::RectangleShape Buttons_Navigation[3];

	//UPGRADE BUTTONS WEAPON:
	//
	sf::RectangleShape Buttons_Upgrades[4];

	//Text order:
	//TOP LEFT TO TOP RIGHT
	//NEXT ROW and the same...
	std::vector<sf::Text*> Texts;

	void initVariables(sf::RenderWindow* window);
	void initShapes(sf::RenderWindow* window);
	void initTexts(sf::RenderWindow* window, sf::Font& font);
public:
	Shop(sf::RenderWindow* window, sf::Font& font);
	virtual ~Shop();

	//Accessors
	const bool& getEndApplication() const;

	//Main loop
	void runShop(float* bank, sf::RenderWindow* window);

	void pollEvents(sf::RenderWindow* window);
	void updateTexts();
	void updateButtons();
	void update(float* bank, sf::RenderWindow* window);

	void renderButtons(sf::RenderTarget& target);
	void renderTexts(sf::RenderTarget& target);
	void render(sf::RenderWindow* window);
};

