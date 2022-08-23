#include "Shop.h"

void Shop::initVariables(sf::RenderWindow* window)
{
	//Logic
	this->endShop = false;
	this->endApplication = false;

	//Money
	this->Bank = 0.f;
	this->IncomeOfRound = 0.f;

	//Upgrades
	this->Amount_Upgrades = 4;

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
}

void Shop::initTexts(sf::RenderWindow* window, sf::Font& font)
{
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

const bool& Shop::getEndApplication() const
{
	return this->endApplication;
}

void Shop::runShop(float* bank, sf::RenderWindow* window)
{
	while (!endShop && !endApplication)
	{
		this->update(bank, window);

		this->render(window);
	}
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
		}
	}
}

void Shop::updateTexts()
{

}

void Shop::updateButtons()
{

}

void Shop::update(float* bank, sf::RenderWindow* window)
{
	this->pollEvents(window);
	this->updateTexts();
	this->updateButtons();
}

void Shop::renderButtons(sf::RenderTarget& target)
{
	//Section choosing
	for (int i = 0; i < 3; i++)
	{
		target.draw(this->Buttons_Navigation[i]);
	}
}

void Shop::renderTexts(sf::RenderTarget& target)
{
	for (int i = 0; i < this->Texts.size(); i++)
	{
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
