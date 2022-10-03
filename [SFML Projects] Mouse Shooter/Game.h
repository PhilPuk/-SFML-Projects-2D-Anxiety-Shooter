#pragma once

#include<math.h>

#include"Player.h"
#include"EnemyManager.h"
#include"TileManager.h"
#include"BeginnerWeapon.h"
#include"ScoreSystem.h"
#include"Upgrades.h"
#include"Vignette.h"
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
	
	//Bloom manager
	//BloomManager bloom_Manager;

	//Income / Earnings
	float CurrIncome;

	void initWindow(sf::RenderWindow* window);
	void initVariables(sf::RenderWindow* window);
	void initFont(sf::Font& font);
	void initPlayer();
	void initTiles();
	void initWeapons();
	void initScoreSystem();
	void initVignette();
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

	//Vignette
	Vignette* vignette;

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
	void rolltheUpgrades(size_t& n);
	
	//Update
	void pollEvents();
	void updateMousePosVectors();
	void updateBulletHittingTarget();
	void updatePlayerHittingEnemy();
	void updateScreenShake();
	void update();

	//Render
	void render();
};

