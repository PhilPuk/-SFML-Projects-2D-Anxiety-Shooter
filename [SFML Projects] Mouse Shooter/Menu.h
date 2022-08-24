#pragma once

#include<iostream>
#include<string>
#include<sstream>

#include"Game.h"
#include"Shop.h"

/// <summary>
/// Engine for Menu
/// Creates window
/// Starts game in poll events
/// Game uses same window as a copy
/// </summary>

class Menu
{
private:
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	std::string Application_Title;
	int Framerate;

	//Fonts
	sf::Font font;

	//Texts
	sf::Text Text_Title;
	sf::Text Text_Menu_Options[3];
	sf::Color Color_Menu;
	sf::Vector2f Vector_Menu_Pos;
	sf::Text Text_Highscore;
	float Spacing_Menu_Pos_Y;

	//Menu_Navigation
	short Menu_Navigation_Index;
	bool Navigation_Index_Changed;

	//Game
	Game* game;

	//Shop
	Shop* shop;

	//Private functions
		//Menu_Navigation
	void navigateUP();
	void navigateDOWN();
	 
		//Initilalization
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initGame();
	void initShop();
	void initHighScoreText();
public:
	//Constructor / Destructor
	Menu();
	~Menu();

	//Functions
	void run();
	void pollEvents();
	void SetTextToNewHighscore();
	void applyShopUpgrades();
		//update
	void updateText();
	void udpate();
		//render
	void renderText();
	void render();
};

