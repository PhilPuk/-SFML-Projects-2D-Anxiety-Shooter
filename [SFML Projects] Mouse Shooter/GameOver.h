#pragma once

#include<iostream>
#include<sstream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class GameOver
{
private:
	bool activated;
	bool scoreset;

	bool endWithKeyPress;
	bool endAfterTime;
	float SceneTimeMax;
	float SceneTime;
	bool ENDGAMEOVER;

	sf::Text Text_GameOver;
	sf::Text Text_Score;

	void initVariables(bool endWithKeyPress, bool endAfterTime, float SceneTimeMax);
	void initText(sf::Font& font, sf::Vector2u winSize);
public:
	/// <summary>
	/// Set over constructor how the game over scene should be used.
	/// endWithKeyPress: ends game over scene once enter or esc key is pressed.
	/// endAfterTime: end game over scene once SceneTimerMax is reached(counts in seconds).
	/// When you dont want to use endAfterTime put SceneTimeMax to 0.f.
	/// </summary>
	GameOver(sf::Font& font, sf::Vector2u winSize, bool endWithKeyPress, bool endAfterTime, float SceneTimeMax);
	virtual ~GameOver();

	//Accessors

	const bool& getActivation() const;

	//Modifiers

	void activateGameOver();
	void resetENDGAMEOVER();

	//Functions


	void setScore(float& score, bool hasScore);

	/// <summary>
	/// Waits for enter or esc key to end the game over scene.
	/// </summary>
	void updateKeyPress();
	void updateTime();
	/// <summary>
	/// endGame: to end the game once the scene is over.
	/// hasScore: if there is a score you want to print with the game over set to true and put in score.
	/// </summary>
	void update(bool* endGame, bool hasScore, float& score);


	void renderText(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

