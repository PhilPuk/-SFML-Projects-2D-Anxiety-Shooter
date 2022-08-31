#include "ScoreSystem.h"

void ScoreSystem::getHighScoreFromTxt()
{
	//Called in initVariables
	std::ifstream in("local/Highscores.txt");
	std::string line;
	

	while (getline(in, line))
	{
		this->HighScore = std::stof(line);
	}
	std::cout << "Loaded Highscore: " << this->HighScore<<"\n";

	in.close();
}

void ScoreSystem::initVariables()
{
	this->Score = 0.f;
	this->Time = 0;
	this->Timer = 0.f;

	this->Money = 500.f;
	this->Earning = 0.f;
	this->earningsaved = -1.f;
		
	this->getHighScoreFromTxt();
}

void ScoreSystem::initFont(sf::Font& font)
{
	this->font = font;
}

void ScoreSystem::initTexts(sf::Vector2u winSize)
{
	float spacingy = 60.f;
	//Score text
	//Text basic settings 
	this->Text_Score.setFont(this->font);
	this->Text_Score.setPosition(10.f, spacingy);
	this->Text_Score.setFillColor(sf::Color(255,255,255, 110));
	this->Text_Score.setOutlineThickness(5.f);
	this->Text_Score.setOutlineColor(sf::Color(0,0,0, 110));

	//Set text content
	std::stringstream ssScore;
	ssScore << "Score: " << this->Score;

	this->Text_Score.setString(ssScore.str());

	//Time
	this->Text_Time = this->Text_Score;
	this->Text_Time.setString("Time: 0");
	this->Text_Time.setPosition(winSize.x - this->Text_Time.getGlobalBounds().width - 35.f, spacingy / 3.f);
	
	//Earning
	this->Text_Money = this->Text_Time;
	this->Text_Money.setString("Earning: 0");
	this->Text_Money.setPosition(
	this->Text_Time.getPosition().x,
	this->Text_Time.getPosition().y - this->Text_Money.getGlobalBounds().height
	);
				  
}

ScoreSystem::ScoreSystem(sf::Vector2u winSize, sf::Font& font)
{
	this->initVariables();
	this->initFont(font);
	this->initTexts(winSize);
}

ScoreSystem::~ScoreSystem()
{
	this->saveHighScoreinTxt();
}

const float& ScoreSystem::getHighscore() const
{
	return this->HighScore;
}

const int& ScoreSystem::getTimer() const
{
	//Returns time in frames, 60 = 1 sek.
	return this->Timer;
}

float* ScoreSystem::getMoney()
{
	return &this->Money;
}

int& ScoreSystem::getTime()
{
	//Returns time in sek.
	return this->Time;
}

//Modifiers
void ScoreSystem::ModifyHighscore(float newHighScores)
{
	this->HighScore = newHighScores;
}

void ScoreSystem::addMoneybyAddition(float add) {
this->Money += add;	
}

//Saving
void ScoreSystem::saveHighScoreinTxt()
{
	if (this->Score > this->HighScore)
	{
		std::ofstream of;
		of.open("local/Highscores.txt");
		of << this->Score;

		of.close();

		this->HighScore = this->Score;

		//Debug info
		//std::cout << "Saved new Highscore: " << this->Score << "\n";
	}
}

//Changed the score text once score got updated
void ScoreSystem::updateScoreText()
{
	
	std::stringstream ssScore;
	ssScore << "Score: " << this->Score;

	this->Text_Score.setString(ssScore.str());
}

//If score in game is bigger then here then change it here
void ScoreSystem::updateScore(float score)
{
	if (this->Score < score)
	{
		this->Score = score;

		this->updateScoreText();
	}
}

void ScoreSystem::updateTimeText()
{
	std::stringstream ssTime;
	ssTime << "Time: " << this->Time;
	this->Text_Time.setString(ssTime.str());
}

void ScoreSystem::updateTime()
{
	this->Timer += 1;

	if (this->Timer % 60 == 0)
	{
		this->Time += 1;

		//Update timer text
		this->updateTimeText();
	}
	else
	{
		return;
	}
}

void updateEarningsText(){
	if(this->Earning != this->earningsaved)
	{
		this->earningsaved = this->Earning;
		std::stringstream ssEarning;
		ssEarning<<"Earning: "<<this->Earning;
		this->Text_Money.setString(ssEarning.str());
	}
	else
		return;
}

void updateEarnings(float earning){
	
	this->Earning = earning;
	
	this->updateEarningsText();
}


void ScoreSystem::update(float score)
{
	this->updateScore(score);
	this->updateTime();
	this->updateEarnings();
}

void ScoreSystem::renderText(sf::RenderTarget& target)
{
	//Score
	target.draw(this->Text_Score);

	//Time
	target.draw(this->Text_Time);
	
	target.draw(this->Text_Money);
}

void ScoreSystem::render(sf::RenderTarget& target)
{
	this->renderText(target);
}
