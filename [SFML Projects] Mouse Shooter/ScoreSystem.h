#pragma once

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class ScoreSystem
{
private:
	float Score;
	float HighScore;
	float Money;
	int Timer; // Counts time in frames 60 = 1sek
	int Time; // Counts in sek add after Timer reached 60
	sf::Font font;
	sf::Text Text_Score;
	sf::Text Text_Time;

	void getHighScoreFromTxt();
	void initVariables();
	void initFont(sf::Font& font);
	void initTexts(sf::Vector2u winSize);
public:
	ScoreSystem(sf::Vector2u winSize, sf::Font& font);
	virtual ~ScoreSystem();

	//Accessors
	const float& getHighscore() const;
	const int& getTimer() const;
	float* getMoney();
	int& getTime();

	//Modifiers
	void ModifyHighscore(float newHighScores);
	void addMoneybyAddition(float add);

	//Saving
	void saveHighScoreinTxt();

	void updateScoreText();
	void updateScore(float score);
	void updateTimeText();
	void updateTime();
	void update(float score);

	void renderText(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

