#include "Shop.h"

void Shop::initVariables(sf::RenderWindow* window)
{
	//Logic
	this->endShop = false;
	this->endApplication = false;

	this->PlayerUpgrades = true;
	this->WeaponUpgrades = false;

	//Money
	this->Bank = 0.f;
	this->lastBank = -1.f;
	this->IncomeOfRound = 0.f;

	//Price upgrades
	for (int i = 0; i < 4; i++)
	{
		this->Price_PlayerUpgrades[i] = 10.f;
		this->Price_WeaponUpgrades[i] = 10.f;

		this->CounterUpgrade_Player[i] = 0;
		this->CounterUpgrade_Weapon[i] = 0;
	}

	//Upgrades
	this->Amount_Upgrades = 4;

	this->indexOfChoosenUpgrade = -1.f;
	this->indexOfChoosenUpgradeSave = -1.f;

	//Spacing
	this->spacing_SectionChooser = 20.f;
	this->spacing_Upgrades = window->getSize().x / 2.f / 4.f;
}

void Shop::initShapes(sf::RenderWindow* window)
{
	//Section choosing buttons
		//Go back
	this->Buttons_Navigation[0].setSize(sf::Vector2f(static_cast<float>(window->getSize().x) / 5.f, 30.f));
	this->Buttons_Navigation[0].setFillColor(sf::Color::White);
	this->Buttons_Navigation[0].setOutlineColor(sf::Color(200, 200, 200, 255));
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
	this->Buttons_Upgrades[0].setSize(sf::Vector2f(static_cast<float>(window->getSize().x) / 10.f, window->getSize().y / 10.f));
	this->Buttons_Upgrades[0].setFillColor(sf::Color(255,255,255, 255));
	this->Buttons_Upgrades[0].setOutlineColor(sf::Color(200, 200, 200, 255));
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

void Shop::initTexts(sf::RenderWindow* window, sf::Font& font)
{
	std::stringstream price;

	sf::Text base;
	base.setFont(font);
	base.setFillColor(sf::Color::Black);
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
	base.setFillColor(sf::Color::White);
	base.setPosition(static_cast<float>(window->getSize().x) / 2 - base.getGlobalBounds().width,
		0.f);
	this->Texts.push_back(new sf::Text(base));

	
	//Player upgrades
	base.setCharacterSize(24.f);
	base.setFillColor(sf::Color::Black);
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
			base.setString("Bullet\nspeed" + price.str());
		else if (i == 1)
			base.setString("Max\nAmmo" + price.str());
		else if (i == 2)
			base.setString("Reload\nSpeed!" + price.str());
		else if (i == 3)
			base.setString("Bullet\ndamage!" + price.str());

		base.setPosition(this->Buttons_Upgrades[i].getPosition().x,
			this->Buttons_Upgrades[i].getPosition().y);
		this->Texts.push_back(new sf::Text(base));
		price.str("");
	}
	
	//Money text
	base.setString("Money");
	base.setPosition(
		window->getSize().x - base.getGlobalBounds().width * 2.f,
		this->Buttons_Navigation[0].getPosition().y);
	
	this->Texts.push_back(new sf::Text(base));
}

Shop::Shop(sf::RenderWindow* window, sf::Font& font)
{
	this->initVariables(window);
	this->initShapes(window);
	this->initTexts(window, font);
}

Shop::~Shop()
{

}

void Shop::resetUpgradeCounter()
{
	//Price upgrades
	for (int i = 0; i < 4; i++)
	{
		this->CounterUpgrade_Player[i] = 0;
		this->CounterUpgrade_Weapon[i] = 0;
	}
}

const bool& Shop::getEndApplication() const
{
	return this->endApplication;
}

const int Shop::getWeapon_UpgradeCounters(int index)
{
	return CounterUpgrade_Weapon[index];
}

const int Shop::getPlayer_UpgradeCounters(int index)
{
	return CounterUpgrade_Player[index];
}

void Shop::runShop(float* bank, sf::RenderWindow* window)
{
	std::cout << "Money: " << *bank<<"\n";
	while (!endShop && !endApplication)
	{
		this->update(bank, window);

		this->render(window);
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

void Shop::pollEvents(sf::RenderWindow* window)
{
	sf::Event ev;
	while (window->pollEvent(ev))
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

void Shop::updateTexts()
{
	//Money
	if(this->lastBank != this->Bank)
	{
		//Save last bank
		this->lastBank = this->Bank;
		
		//Update money text
		std::stringstream ssBank;
		ssBank<<"Money: "<<this->Bank;
		this->Texts[texts.end()]->setString(ssBank.str());	
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

void Shop::updateMouseVector(sf::RenderWindow* window)
{
	this->mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(*window));
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

void Shop::updateUpgradingAbilities()
{

	if (this->indexOfChoosenUpgrade != this->indexOfChoosenUpgradeSave)
	{
		if (this->PlayerUpgrades)
		{
			this->CounterUpgrade_Player[this->indexOfChoosenUpgrade]++;
		}
		else if (this->WeaponUpgrades)
		{
			this->CounterUpgrade_Weapon[this->indexOfChoosenUpgrade]++;
			std::cout << "Weapon " << this->indexOfChoosenUpgrade << ": " << this->CounterUpgrade_Player[this->indexOfChoosenUpgrade] << "\n";
		}

		this->indexOfChoosenUpgrade = this->indexOfChoosenUpgradeSave;
	}
}

void Shop::updateupgradeMain(float* bank)
{
	this->updateUpgradingAbilities();
}

void Shop::update(float* bank, sf::RenderWindow* window)
{
	this->pollEvents(window);
	this->updateTexts();
	this->updateMouseVector(window);
	this->updateupgradeMain(bank);
}

void Shop::renderButtons(sf::RenderTarget& target)
{
	//Section choosing buttons
	for (int i = 0; i < 3; i++)
	{
		target.draw(this->Buttons_Navigation[i]);
	}
	
	//Upgrade buttons
	for(int i = 0; i < 4; i++)
	{
		target.draw(this->Buttons_Upgrades[i]);
	}
}

void Shop::renderTexts(sf::RenderTarget& target)
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
				target.draw(*this->Texts[i]);
		}
		else
		target.draw(*this->Texts[i]);
	}
}

void Shop::render(sf::RenderWindow* window)
{
	window->clear();

	this->renderButtons(*window);
	this->renderTexts(*window);

	window->display();
}
