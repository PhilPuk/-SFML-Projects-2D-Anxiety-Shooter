#pragma once

#include<iostream>
#include<sstream>
#include<vector>
#include"TileManager.h"

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Shop
{
private:
	sf::RenderWindow* window;

	//Logic
	bool endShop;
	bool endApplication;

	bool PlayerUpgrades;
	bool WeaponUpgrades;

	int RangeStartPlayerUpgrades;
	int RangeEndPlayerUpgrades;

	//Mouse
	sf::Vector2f mousePosWindow;

	//UI opacity
	int UIOpacity;

	//Money
	float Bank;
	float lastBank;
	float IncomeOfRound;

	//Price upgrades
	float Price_PlayerUpgrades[4];
	float Price_WeaponUpgrades[4];


	//Upgrade counting
	int CounterUpgrade_Player[4];
	float CurrCounterUpgrade_Player[4];
	int CounterUpgrade_Weapon[4];
	float CurrCounterUpgrade_Weapon[4];
	//Upgrades
	int Amount_Upgrades;

	int indexOfChoosenUpgrade;
	int indexOfChoosenUpgradeSave;

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

	void initWindow(sf::RenderWindow* window);
	void initVariables(sf::Vector2u& winSize);
	void initShapes(sf::Vector2u& winSize);
	void initTexts(sf::Vector2u& winSize, sf::Font& font);
public:
	Shop(sf::RenderWindow* window, sf::Vector2u& winSize, sf::Font& font);
	virtual ~Shop();

	void resetUpgradeCounter();

	//Accessors
	const bool& getEndApplication() const;
		//UPGRADES

		/// Get player upgrades.
		/// Index list:
		/// 0 = Move Speed.
		/// 1 = Max HP.
		/// 2 = COOMING SOON.
		/// 3 = COOMING SOON.
	const int getPlayer_UpgradeCounters(int index);

		/// Get weapon upgrades.
		/// Index list:
		/// 0 = Bullet Speed.
		/// 1 = Max Ammo.
		/// 2 = Reload Speed.
		/// 3 = Bullet damage
	const int getWeapon_UpgradeCounters(int index);



	//Main loop
	void runShop(float* bank, TileManager& tileManager, float* ReloadTimerMax, int* MaxAmmo);

	bool checkUpgradeAvailable(float* bank, float upgrade_price);

	void pollEvents();
	void updateTexts(float* bank, float* ReloadTimerMax, int* MaxAmmo);
	void updateToPlayerUpgrades();
	void updateToWeaponUpgrades();
	void updateMouseVector();
	void updateMouseOnButtons();
	void updateUpgradingAbilities(float* bank, float* ReloadTimerMax, int* MaxAmmo);
	void updateupgradeMain(float* bank, float* ReloadTimerMax, int* MaxAmmo);
	void update(float* bank, TileManager& tileManager, float* ReloadTimerMax, int* MaxAmmo);

	void renderButtons();
	void renderTexts();
	void render(TileManager& tileManager);
};