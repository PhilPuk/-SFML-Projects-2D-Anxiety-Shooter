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

	bool PlayerUpgrades;
	bool WeaponUpgrades;

	int RangeStartPlayerUpgrades;
	int RangeEndPlayerUpgrades;

	//Mouse
	sf::Vector2f mousePosWindow;

	//Money
	float Bank;
	float IncomeOfRound;

	//Price upgrades
	float Price_PlayerUpgrades[4];
	float Price_WeaponUpgrades[4];

	//Upgrade counting
	int CounterUpgrade_Player[4];
	int CounterUpgrade_Weapon[4];

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

	void initVariables(sf::RenderWindow* window);
	void initShapes(sf::RenderWindow* window);
	void initTexts(sf::RenderWindow* window, sf::Font& font);
public:
	Shop(sf::RenderWindow* window, sf::Font& font);
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
	void runShop(float* bank, sf::RenderWindow* window);

	bool checkUpgradeAvailable(float* bank, float upgrade_price);

	void pollEvents(sf::RenderWindow* window);
	void updateTexts();
	void updateToPlayerUpgrades();
	void updateToWeaponUpgrades();
	void updateMouseVector(sf::RenderWindow* window);
	void updateMouseOnButtons();
	void updateUpgradingAbilities();
	void updateupgradeMain(float* bank);
	void update(float* bank, sf::RenderWindow* window);

	void renderButtons(sf::RenderTarget& target);
	void renderTexts(sf::RenderTarget& target);
	void render(sf::RenderWindow* window);
};

