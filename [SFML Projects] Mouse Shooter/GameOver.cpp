#include "GameOver.h"

void GameOver::initVariables(bool endWithKeyPress, bool endAfterTime, float SceneTimeMax)
{
	this->activated = false;
	this->scoreset = false;
	this->endWithKeyPress = endWithKeyPress;
	this->endAfterTime = endAfterTime;
	this->SceneTimeMax = SceneTimeMax;
	this->SceneTime = this->SceneTimeMax;

	this->ENDGAMEOVER = false;
}

void GameOver::initText(sf::Font& font, sf::Vector2u winSize)
{
	//Game over
	this->Text_GameOver.setFont(font);
	this->Text_GameOver.setCharacterSize(44);
	this->Text_GameOver.setFillColor(sf::Color::Red);
	this->Text_GameOver.setString("GAME OVER\nPress space to continue");
	//Center origin
	sf::FloatRect textRect = this->Text_GameOver.getLocalBounds();
	this->Text_GameOver.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	//Center position
	this->Text_GameOver.setPosition(static_cast<float>(winSize.x) / 2.f, static_cast<float>(winSize.y) / 2.f);

	//Score
	this->Text_Score = this->Text_GameOver;
	this->Text_Score.setString("Score: 000");
	this->Text_Score.setPosition(this->Text_GameOver.getPosition().x, this->Text_GameOver.getPosition().y - this->Text_Score.getGlobalBounds().height);
}

GameOver::GameOver(sf::Font& font, sf::Vector2u winSize, bool endWithKeyPress, bool endAfterTime, float SceneTimeMax)
{
	this->initVariables(endWithKeyPress, endAfterTime, SceneTimeMax);
	this->initText(font, winSize);
}

GameOver::~GameOver()
{

}

const bool& GameOver::getActivation() const
{
	return this->activated;
}

void GameOver::activateGameOver()
{
	this->activated = true;
}

void GameOver::resetENDGAMEOVER()
{
	this->activated = false;
	this->ENDGAMEOVER = false;
}

void GameOver::setScore(float& score, bool hasScore)
{
	//If has Score set score, but only once.
	if (!scoreset)
	{
		if (hasScore)
		{
			std::stringstream ssScore;
			ssScore << "Score: " << score;
			this->Text_Score.setString(ssScore.str());
		}
	}
}

void GameOver::updateKeyPress()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->ENDGAMEOVER = true;
	}
}

void GameOver::updateTime()
{
	if (this->SceneTime < this->SceneTimeMax)
	{
		this->SceneTime += 1.f;
	}
	else
	{
		this->SceneTime = 0.f;
		this->ENDGAMEOVER = true;
	}
}

void GameOver::update(bool* endGame, bool hasScore, float& score)
{
	this->setScore(score, hasScore);

	//Checks for the choosen scene.
	if (this->endWithKeyPress)
	{
		this->updateKeyPress();
	}
	else if (this->endAfterTime)
	{
		this->updateTime();
	}

	if (ENDGAMEOVER)
	{
		*endGame = true;
	}
}

void GameOver::renderText(sf::RenderTarget& target)
{
	target.draw(this->Text_GameOver);
	target.draw(this->Text_Score);
}

void GameOver::render(sf::RenderTarget& target)
{
	this->renderText(target);
}
