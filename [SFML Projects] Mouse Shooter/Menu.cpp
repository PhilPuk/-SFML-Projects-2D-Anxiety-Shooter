#include "Menu.h"

//Private functions
	//Initialization
void Menu::initVariables()
{
	//Window
		//Screen size
	this->videoMode.width = 1920;
	this->videoMode.height = 1080;

	this->Framerate = 60;

	//Texts
		//Text Title
	this->Application_Title = "Anxiety Shooter";
		//Text Colors
	this->Color_Menu = sf::Color(255,255,255, 70);
		//Text Pos
	this->Vector_Menu_Pos.x = static_cast<float>(this->videoMode.width) / 2.f - 500.f;
	this->Vector_Menu_Pos.y = static_cast<float>(this->videoMode.height) / 1.7f;
		//Text spacing
	this->Spacing_Menu_Pos_Y = 75.f;

	//Menu navigation
	this->Menu_Navigation_Index = 0;
	this->Navigation_Index_Changed = false;
}

void Menu::initWindow()
{
	this->window = new sf::RenderWindow(this->videoMode, this->Application_Title, sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(this->Framerate);
}

void Menu::initFonts()
{
	//Initialize all fonts
	if (!this->font.loadFromFile("Fonts/Starborn.ttf"))
		std::cout << " - ERROR::MENU::INITFONTS:: Couldn't load font!\n";
}

void Menu::initText()
{
	//sets all texts content
		//Title
	this->Text_Title.setString(this->Application_Title);
		//Start
	this->Text_Menu_Options[0].setString("Start");
		//Options
	this->Text_Menu_Options[1].setString("Shop");
		//Stop
	this->Text_Menu_Options[2].setString("Stop");

	//sets all texts settings
		//Title
	this->Text_Title.setFont(this->font);
	this->Text_Title.setCharacterSize(44);
	this->Text_Title.setFillColor(this->Color_Menu);
	this->Text_Title.setPosition(this->Vector_Menu_Pos.x, this->Vector_Menu_Pos.y - this->Spacing_Menu_Pos_Y * 2.f);
		//Menu_Options
	sf::Vector2f tmp_saveVector = this->Vector_Menu_Pos;
	for (int i = 0; i < 3; i++)
	{
		this->Text_Menu_Options[i].setFont(this->font);
		this->Text_Menu_Options[i].setCharacterSize(24);
		this->Text_Menu_Options[i].setFillColor(this->Color_Menu);
		this->Text_Menu_Options[i].setPosition(this->Vector_Menu_Pos);
		//Increase spacing for each text
		this->Vector_Menu_Pos.y = this->Vector_Menu_Pos.y + this->Spacing_Menu_Pos_Y;
	}
	//Reset vector
	this->Vector_Menu_Pos = tmp_saveVector;

	//Sets first option to Navigation Index Color
	this->Text_Menu_Options[this->Menu_Navigation_Index].setFillColor(sf::Color::Magenta);
}

void Menu::initGame()
{
	this->game = new Game(this->window, this->font);
}

void Menu::initShop()
{
	sf::Vector2u winSize = this->window->getSize();
	this->shop = new Shop(this->window, winSize, this->font);
}

void Menu::initHighScoreText()
{
	this->Text_Highscore = this->Text_Menu_Options[1];
	this->Text_Highscore.move(300.f, -this->Spacing_Menu_Pos_Y);

	this->SetTextToNewHighscore();
}

	//Menu_Navigation
void Menu::navigateUP()
{
	if (this->Menu_Navigation_Index > 0)
	{
		this->Menu_Navigation_Index--;
		this->Navigation_Index_Changed = true;
	}
}

void Menu::navigateDOWN()
{
	if (this->Menu_Navigation_Index < 2)
	{
		this->Menu_Navigation_Index++;
		this->Navigation_Index_Changed = true;
	}
}


//Constructor / Destructor
Menu::Menu()
{
	//Call all functions that need to be initialized
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initGame();
	this->initShop();
	this->initHighScoreText();
}

Menu::~Menu()
{
	delete this->window;

	delete this->game;

	delete this->shop;
}

//Functions
void Menu::run()
{
	//Main loop for whole application
	while (this->window->isOpen() && !this->game->getEndApplication() && !this->shop->getEndApplication())
	{
		this->udpate();

		this->render();
	}
}

void Menu::pollEvents()
{
	sf::Event ev;
	//Main loop for event polling
	while (this->window->pollEvent(ev))
	{
		switch (ev.type)
		{
		//Closing Event
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
				//Esc to close
			//if (ev.key.code == sf::Keyboard::Escape)
				//this->window->close();
			
			if (ev.key.code == sf::Keyboard::Enter)
			{
				//Menu_Options function called here
				if (this->Menu_Navigation_Index == 0)
				{
					//Start button action
					this->game->run();
					this->game->resetVariables();
					//Gets newest highscore
					this->SetTextToNewHighscore();
				}
				else if (this->Menu_Navigation_Index == 1)
				{
					//Shop button action
					this->shop->runShop(this->game->ScoreSys->getMoney(), *this->game->tileManager, &this->game->weapon->ReloadTimerMax, &this->game->weapon->MaxAmmo, *this->game->vignette);

					this->applyShopUpgrades();

					this->shop->resetUpgradeCounter();
				}
				else if (this->Menu_Navigation_Index == 2)
				{
					//Stop button action
					this->window->close();
				}
			}

			//Menu Navigation Event
			if (ev.key.code == sf::Keyboard::W || ev.key.code == sf::Keyboard::Up)
				this->navigateUP();
			else if (ev.key.code == sf::Keyboard::S || ev.key.code == sf::Keyboard::Down)
				this->navigateDOWN();
			break;
		}
	}
}

void Menu::SetTextToNewHighscore()
{
	std::stringstream ssHighScore;
	ssHighScore << "Highscore: " << this->game->getHighScore();
	this->Text_Highscore.setString(ssHighScore.str());
}

void Menu::applyShopUpgrades()
{
	bool newUpgrade = false;

		///TO-DO:
		/// add last player upgrades
		 
		//Player
		this->game->player->addPlayerMoveSpeed(static_cast<float>(this->shop->getPlayer_UpgradeCounters(0)));
		//std::cout << "Player move speed upgrade : " << this->shop->getPlayer_UpgradeCounters(0);
		this->game->player->addMaxHP(this->shop->getPlayer_UpgradeCounters(1));

		this->game->player->addIncomeIncrease(this->shop->getPlayer_UpgradeCounters(2) * 0.1f);

		if (this->shop->getPlayer_UpgradeCounters(3) >= 1)
			this->game->weapon->unlockLifesteal();

		//Weapon
		this->game->weapon->addBulletSpeed(this->shop->getWeapon_UpgradeCounters(0));
		//this->game->weapon->addMaxAmmo(this->shop->getWeapon_UpgradeCounters(1));
		//this->game->weapon->substractReloadTimerMax(this->shop->getWeapon_UpgradeCounters(2));
		this->game->weapon->addBulletDamage(this->shop->getWeapon_UpgradeCounters(3));



		//Debugging upgrade counters
		/*
		std::cout << "Weapon 0: " << this->shop->getWeapon_UpgradeCounters(0) << "\n";
		std::cout << "Weapon 1: " << this->shop->getWeapon_UpgradeCounters(1) << "\n";
		std::cout << "Weapon 2: " << this->shop->getWeapon_UpgradeCounters(2) << "\n";
		std::cout << "Weapon 3: " << this->shop->getWeapon_UpgradeCounters(3) << "\n";
		*/
}

//update
void Menu::updateText()
{
	//Changes color of currently selected option 
	//Resets other to standart color
	if (this->Navigation_Index_Changed)
	{
		for (int i = 0; i < 3; i++)
		{
			if (i == this->Menu_Navigation_Index)
				this->Text_Menu_Options[i].setFillColor(sf::Color::Magenta);
			else
				this->Text_Menu_Options[i].setFillColor(this->Color_Menu);
		}
		this->Navigation_Index_Changed = false;
	}
}

void Menu::udpate()
{
	//Calls every function that updates stuff

	//Event polling
	this->pollEvents();

	//Text updating
	this->updateText();
	
	this->game->tileManager->update(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f,0.f));

	this->game->vignette->update();
}

//render
void Menu::renderText()
{
	//Title text
	this->window->draw(this->Text_Title);

	//Menu_Options
	for (int i = 0; i < 3; i++)
	{
		this->window->draw(this->Text_Menu_Options[i]);
	}

	//Highscore
	this->window->draw(this->Text_Highscore);
}

void Menu::render()
{
	//Clears window
	this->window->clear();

	this->game->tileManager->render(*this->window);
	
	this->renderText();

	this->game->vignette->render(*this->window);
	//Displays on window
	this->window->display();
}
