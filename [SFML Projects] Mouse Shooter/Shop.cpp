#include "Shop.h"


void Shop::initWindow(sf::RenderWindow* window)
{
	this->window = window;
}

void Shop::initVariables(sf::Vector2u& winSize)
{
	//Logic
	this->endShop = false;
	this->endApplication = false;

	this->PlayerUpgrades = true;
	this->WeaponUpgrades = false;

	this->UIOpacity = 150;

	//Money
	this->Bank = 0.f;
	this->lastBank = -1.f;
	this->IncomeOfRound = 0.f;

	//Price upgrades
	for (int i = 0; i < 4; i++)
	{
		this->Price_PlayerUpgrades[i] = 0.f;
		//this->Price_WeaponUpgrades[i] = 10.f;

		this->CounterUpgrade_Player[i] = 0;
		this->CounterUpgrade_Weapon[i] = 0;

		this->CurrCounterUpgrade_Player[i] = 0;
		this->CurrCounterUpgrade_Weapon[i] = 0;
	}

	this->Price_PlayerUpgrades[0] = 100.f;
	this->Price_PlayerUpgrades[1] = 50.f;

	this->Price_WeaponUpgrades[0] = 10.f;
	this->Price_WeaponUpgrades[1] = 15.f;
	this->Price_WeaponUpgrades[2] = 10.f;
	this->Price_WeaponUpgrades[3] = 30.f;

	//Upgrades
	this->Amount_Upgrades = 4;

	this->indexOfChoosenUpgrade = -1.f;
	this->indexOfChoosenUpgradeSave = -1.f;

	//Spacing
	this->spacing_SectionChooser = 20.f;
	this->spacing_Upgrades = winSize.x / 2.f / 4.f;
}

void Shop::initShapes(sf::Vector2u& winSize)
{
	//Section choosing buttons
		//Go back
	this->Buttons_Navigation[0].setSize(sf::Vector2f(static_cast<float>(winSize.x) / 5.f, 30.f));
	this->Buttons_Navigation[0].setFillColor(sf::Color(255, 255, 255, this->UIOpacity));
	this->Buttons_Navigation[0].setOutlineColor(sf::Color(200, 200, 200, this->UIOpacity));
	this->Buttons_Navigation[0].setOutlineThickness(5.f);
	this->Buttons_Navigation[0].setPosition(0.f, 0.f);

	this->Buttons_Navigation[1] = this->Buttons_Navigation[0];
	this->Buttons_Navigation[2] = this->Buttons_Navigation[0];

	//Player
	this->Buttons_Navigation[1].setPosition(
		this->Buttons_Navigation[0].getGlobalBounds().width * 0.5f,
		this->Buttons_Navigation[0].getGlobalBounds().height * 3.f);
	//Weapon
	this->Buttons_Navigation[2].setPosition(
		this->Buttons_Navigation[1].getPosition().x + this->Buttons_Navigation[1].getGlobalBounds().width + this->spacing_SectionChooser,
		this->Buttons_Navigation[1].getPosition().y);
	
	//Upgrade buttons spawns
	this->Buttons_Upgrades[0].setSize(sf::Vector2f(static_cast<float>(winSize.x) / 10.f, winSize.y / 10.f));
	this->Buttons_Upgrades[0].setFillColor(sf::Color(255, 255, 255, this->UIOpacity));
	this->Buttons_Upgrades[0].setOutlineColor(sf::Color(200, 200, 200, this->UIOpacity));
	this->Buttons_Upgrades[0].setOutlineThickness(5.f);
	this->Buttons_Upgrades[0].setPosition(
		this->Buttons_Navigation[1].getPosition().x,
		this->Buttons_Navigation[1].getPosition().y + this->spacing_Upgrades);
	
	this->Buttons_Upgrades[1] = this->Buttons_Upgrades[0];
	this->Buttons_Upgrades[2] = this->Buttons_Upgrades[0];
	this->Buttons_Upgrades[3] = this->Buttons_Upgrades[0];
	
	this->Buttons_Upgrades[1].setPosition(
		this->Buttons_Upgrades[0].getPosition().x + this->Buttons_Upgrades[0].getGlobalBounds().width + this->spacing_Upgrades,
		this->Buttons_Upgrades[0].getPosition().y);
	
	this->Buttons_Upgrades[2].setPosition(
		this->Buttons_Upgrades[1].getPosition().x + this->Buttons_Upgrades[1].getGlobalBounds().width + this->spacing_Upgrades,
		this->Buttons_Upgrades[1].getPosition().y);
	
	this->Buttons_Upgrades[3].setPosition(
		this->Buttons_Upgrades[2].getPosition().x + this->Buttons_Upgrades[2].getGlobalBounds().width + this->spacing_Upgrades,
		this->Buttons_Upgrades[2].getPosition().y);
}

void Shop::initTexts(sf::Vector2u& winSize, sf::Font& font)
{
	std::stringstream price;

	sf::Text base;
	base.setFont(font);
	base.setFillColor(sf::Color(0,0,0, this->UIOpacity));
	base.setCharacterSize(24.f);
	//Section choosing texts
	//GO BACK
	base.setString("Go back");
	base.setPosition(this->Buttons_Navigation[0].getPosition().x, this->Buttons_Navigation[0].getPosition().y);
	this->Texts.push_back(new sf::Text(base));

	//PLayer 
	base.setString("Player");
	base.setPosition(this->Buttons_Navigation[1].getPosition().x, this->Buttons_Navigation[1].getPosition().y);
	this->Texts.push_back(new sf::Text(base));


	//Weapon
	base.setString("Weapon");
	base.setPosition(this->Buttons_Navigation[2].getPosition().x, this->Buttons_Navigation[2].getPosition().y);
	this->Texts.push_back(new sf::Text(base));


	//Text without buttons are last in the array index
	base.setString("Shop");
	base.setCharacterSize(44);
	base.setFillColor(sf::Color(255, 255, 255, this->UIOpacity));
	base.setPosition(static_cast<float>(winSize.x) / 2 - base.getGlobalBounds().width,
		0.f);
	this->Texts.push_back(new sf::Text(base));

	//Money text
	base.setString("Money");
	base.setPosition(
		winSize.x - base.getGlobalBounds().width * 2.f,
		this->Buttons_Navigation[0].getPosition().y);

	this->Texts.push_back(new sf::Text(base));

	
	//Player upgrades
	base.setCharacterSize(24.f);
	base.setFillColor(sf::Color(0, 0, 0, this->UIOpacity));
	this->RangeStartPlayerUpgrades = this->Texts.size() - 1;
	for (int i = 0; i < 4; i++)
	{
		price <<"\n"<< this->Price_PlayerUpgrades[i] << "$";
		if(i == 0)
			base.setString("Move\nspeed"+ price.str());
		else if(i == 1)
			base.setString("Max\nHP" + price.str());
		else if(i == 2)
			base.setString("COOMING\nSOON!" + price.str());
		else if(i == 3)
			base.setString("COOMING\nSOON!" + price.str());

		base.setPosition(this->Buttons_Upgrades[i].getPosition().x,
			this->Buttons_Upgrades[i].getPosition().y);
		this->Texts.push_back(new sf::Text(base));
		price.str("");
	}
	//Weapon upgrades
	this->RangeEndPlayerUpgrades = this->RangeStartPlayerUpgrades + 4;
	for (int i = 0; i < 4; i++)
	{
		price << "\n" << this->Price_WeaponUpgrades[i] << "$";
		if (i == 0)
			base.setString("Bullet\nspeed" + price.str() + " x0");
		else if (i == 1)
			base.setString("Max\nAmmo" + price.str() + " x0");
		else if (i == 2)
			base.setString("Reload\nSpeed!" + price.str() + " x0");
		else if (i == 3)
			base.setString("Bullet\ndamage!" + price.str() + " x0");

		base.setPosition(this->Buttons_Upgrades[i].getPosition().x,
			this->Buttons_Upgrades[i].getPosition().y);
		this->Texts.push_back(new sf::Text(base));
		price.str("");
	}
	
}

Shop::Shop(sf::RenderWindow* window, sf::Vector2u& winSize, sf::Font& font)
{
	this->initWindow(window);
	this->initVariables(winSize);
	this->initShapes(winSize);
	this->initTexts(winSize, font);
}

Shop::~Shop()
{
}

void Shop::resetUpgradeCounter()
{
	//Price upgrades
	for (int i = 0; i < 4; i++)
	{
		this->CurrCounterUpgrade_Player[i] = 0;
		this->CurrCounterUpgrade_Weapon[i] = 0;
	}
}

const bool& Shop::getEndApplication() const
{
	return this->endApplication;
}

const int Shop::getWeapon_UpgradeCounters(int index)
{
	return CurrCounterUpgrade_Weapon[index];
}

const int Shop::getPlayer_UpgradeCounters(int index)
{
	return CurrCounterUpgrade_Player[index];
}

void Shop::runShop(float* bank, TileManager& tileManager)
{
	while (!endShop && !endApplication)
	{
		this->update(bank, tileManager);

		this->render(tileManager);
	}
	this->endShop = false;

}

bool Shop::checkUpgradeAvailable(float* bank, float upgrade_price)
{
	if (*bank >= upgrade_price)
		return true;
	else
		return false;
}

void Shop::pollEvents()
{
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->endShop = true;
			this->endApplication = true;
			break;
		case sf::Event::KeyPressed:
			//ESCAPE
			if (ev.key.code == sf::Keyboard::Escape)
			{
				this->endShop = true;
			}
			break;
		case sf::Event::MouseButtonPressed:
			//Left
			if (ev.key.code == sf::Mouse::Left)
			{
				this->updateMouseOnButtons();
			}
		}
	}
}

void Shop::updateTexts(float* bank)
{
	//Money
	if (this->lastBank != *bank)
	{
		//Save last bank
		this->lastBank = *bank;

		//Update money text
		std::stringstream ssBank;
		ssBank << "Money: " << *bank;
		this->Texts[4]->setString(ssBank.str());

		//Upgrades
		std::stringstream upg[4];
		int n = 0;
		std::string text;
		int index = 0;
		if (this->PlayerUpgrades)
		{
			for (int i = this->RangeStartPlayerUpgrades + 1; i < this->RangeEndPlayerUpgrades + 1; i++)
			{
				if (this->RangeStartPlayerUpgrades + 1 == i)
				{
					text = "Move\nspeed";
				}
				else if (this->RangeStartPlayerUpgrades + 2 == i)
				{
					text = "Max\nHP";
					index = 1;
				}
				else if (this->RangeStartPlayerUpgrades + 3 == i)
				{
					text = "COOMING\nSOON!";
					index = 2;
				}
				else if (this->RangeStartPlayerUpgrades + 4 == i)
				{
					text = "COOMING\nSOON!";
					index = 3;
				}
				upg[n] << text <<"\n" << this->Price_PlayerUpgrades[index] << "$" << " x" << this->CounterUpgrade_Player[index];
				this->Texts[i]->setString(upg[n].str());
				upg[n].str("");
				n++;
			}

		}
		else if (this->WeaponUpgrades)
		{
			for (int i = this->RangeStartPlayerUpgrades + 5; i < this->RangeEndPlayerUpgrades + 5; i++)
			{
				if (this->RangeStartPlayerUpgrades + 5 == i)
				{
					text = "Bullet\nspeed";
				}
				else if (this->RangeStartPlayerUpgrades + 6 == i)
				{
					text = "Max\nAmmo";
					index = 1;
				}
				else if (this->RangeStartPlayerUpgrades + 7 == i)
				{
					text = "Reload\nSpeed!";
					index = 2;
				}
				else if (this->RangeStartPlayerUpgrades + 8 == i)
				{
					text = "Bullet\ndamage!";
					index = 3;
				}
				upg[n] << text << "\n" << this->Price_WeaponUpgrades[index] << "$" << " x" << this->CounterUpgrade_Weapon[index];
				this->Texts[i]->setString(upg[n].str());
				upg[n].str("");
				n++;
			}
		}
	}
}

void Shop::updateToPlayerUpgrades()
{
	this->PlayerUpgrades = true;
	this->WeaponUpgrades = false;
}

void Shop::updateToWeaponUpgrades()
{
	this->PlayerUpgrades = false;
	this->WeaponUpgrades = true;
}

void Shop::updateMouseVector()
{
	this->mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(*this->window));
}

//CALLED IN POLL EVENTS
//IF LEFT MOUSE BUTTON PRESSED CHECK IF A BUTTON IS HIT
//IF YES DO THE BUTTON FUNCTIONS
void Shop::updateMouseOnButtons()
{	

	//Section choosing buttons
	for (int i = 0; i < 3; i++)
	{
		if (this->Buttons_Navigation[i].getGlobalBounds().contains(this->mousePosWindow))
		{
			//Go back
			if (i == 0)
				this->endShop = true;
			//Player section
			else if (i == 1)
				this->updateToPlayerUpgrades();
			//Weapon section
			else if (i == 2)
				this->updateToWeaponUpgrades();
		}
	}
	

	//Upgrade buttons	
	for (int i = 0; i < 4; i++)
	{
		if (this->Buttons_Upgrades[i].getGlobalBounds().contains(this->mousePosWindow))
		{
			this->indexOfChoosenUpgrade = i;
			
		}
		//debugging
		//std::cout << this->indexOfChoosenUpgrade;
	}
	
}

void Shop::updateUpgradingAbilities(float* bank)
{

		if (this->indexOfChoosenUpgrade != this->indexOfChoosenUpgradeSave)
		{
			if (this->PlayerUpgrades)
			{
				if (this->checkUpgradeAvailable(bank , this->Price_PlayerUpgrades[this->indexOfChoosenUpgrade]))
				{
					this->CounterUpgrade_Player[this->indexOfChoosenUpgrade]++;
					this->CurrCounterUpgrade_Player[this->indexOfChoosenUpgrade]++;
					*bank -= this->Price_PlayerUpgrades[this->indexOfChoosenUpgrade];
				}
				else
				{
					//TODO
					//Add event for not enough money to buy upgrade
				}
			}
			else if (this->WeaponUpgrades)
			{
				if (this->checkUpgradeAvailable(bank, this->Price_WeaponUpgrades[this->indexOfChoosenUpgrade]))
				{
					this->CounterUpgrade_Weapon[this->indexOfChoosenUpgrade]++;
					this->CurrCounterUpgrade_Weapon[this->indexOfChoosenUpgrade]++;
					*bank -= this->Price_WeaponUpgrades[this->indexOfChoosenUpgrade];
					//For debugging
					//std::cout << "Weapon " << this->indexOfChoosenUpgrade << ": " << this->CounterUpgrade_Player[this->indexOfChoosenUpgrade] << "\n";
				}
				else
				{
					//TODO
					//Add event for not enough money to buy upgrade
				}
			}

			this->indexOfChoosenUpgrade = this->indexOfChoosenUpgradeSave;
		}
}

void Shop::updateupgradeMain(float* bank)
{
	this->updateUpgradingAbilities(bank);
}

void Shop::update(float* bank, TileManager& tileManager)
{
	this->pollEvents();
	this->updateTexts(bank);
	this->updateMouseVector();
	this->updateupgradeMain(bank);
	tileManager.update(sf::Vector2f(0.f , 0.f), sf::Vector2f(0.f , 0.f));
	tileManager.update(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
}

void Shop::renderButtons()
{
	//Section choosing buttons
	for (int i = 0; i < 3; i++)
	{
		this->window->draw(this->Buttons_Navigation[i]);
	}
	
	//Upgrade buttons
	for(int i = 0; i < 4; i++)
	{
		this->window->draw(this->Buttons_Upgrades[i]);
	}
}

void Shop::renderTexts()
{
	int decrease = 0;
	//player or weapon
	if (this->PlayerUpgrades)
		decrease = sizeof(this->Price_PlayerUpgrades) / sqrt(sizeof(this->Price_PlayerUpgrades));

	for (int i = 0; i < this->Texts.size() - decrease; i++)
	{
		if (this->WeaponUpgrades)
		{
			if(i < this->RangeStartPlayerUpgrades + 1 || i > this->RangeEndPlayerUpgrades )
				this->window->draw(*this->Texts[i]);
		}
		else
		this->window->draw(*this->Texts[i]);
	}
}

void Shop::render(TileManager& tileManager)
{
	window->clear();

	tileManager.render(*this->window);
	this->renderButtons();
	this->renderTexts();

	window->display();
}
