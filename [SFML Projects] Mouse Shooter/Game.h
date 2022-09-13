#pragma once

#include"Player.h"
#include"EnemyManager.h"
#include"TileManager.h"
#include"BeginnerWeapon.h"
#include"ScoreSystem.h"
#include"Upgrades.h"
#include"bloom.h"
#include"GameOver.h"

class Game
{
private:
	//Window
	sf::RenderWindow* window;
	sf::Vector2u windowSize;

	//Texts
	sf::Font font;

	//End logic
	bool endGame;
	bool endApplication;

	//Mouse
	sf::Vector2f mousePosWindow;

	//Enemies
	EnemyManager enemyManager;

	//Upgrades
	Upgrades upgrades;

	//Score
	float currScore;
	
	//Bloom
	Bloom bloom;

	//Income / Earnings
	float CurrIncome;

	void initWindow(sf::RenderWindow* window);
	void initVariables(sf::RenderWindow* window);
	void initFont(sf::Font& font);
	void initPlayer();
	void initTiles();
	void initWeapons();
	void initScoreSystem();
	void initGameOver();
public:
	Game(sf::RenderWindow* window, sf::Font& font);
	virtual ~Game();

	//Tile system
	TileManager* tileManager;

	//Player
	Player* player;

	//Weapon
	BeginnerWeapon* weapon;

	//Score Sys
	ScoreSystem* ScoreSys;

	//Game over
	GameOver* gameOver;

	//reseter
	void resetVariables();
	
	//Accessors
	const bool& getEndGame() const;
	const bool& getEndApplication() const;
	const float& getHighScore() const;

	//Main loop
	void run();

	//Functions
	
	void checkGameOver();
	//Rolls dices for each rng upgrade 
	void rolltheUpgrades(int n);
	
	//Update
	void pollEvents();
	void updateMousePosVectors();
	void updateBulletHittingTarget();
	void updatePlayerHittingEnemy();
	void update();

	//Render
	void render();
};

