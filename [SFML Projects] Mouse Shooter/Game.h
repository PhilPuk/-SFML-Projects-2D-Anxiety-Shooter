#pragma once

#include"Player.h"
#include"EnemyManager.h"
#include"TileManager.h"
#include"BeginnerWeapon.h"
#include"ScoreSystem.h"
#include"Upgrades.h"

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

	//Player
	Player* player;

	//Enemies
	EnemyManager enemyManager;

	//Tile system
	TileManager* tileManager;

	BeginnerWeapon* weapon;

	//Upgrades
	Upgrades upgrades;

	//Score
	float currScore;

	void initWindow(sf::RenderWindow* window);
	void initVariables(sf::RenderWindow* window);
	void initFont(sf::Font& font);
	void initPlayer();
	void initTiles();
	void initWeapons();
	void initScoreSystem();
public:
	Game(sf::RenderWindow* window, sf::Font& font);
	virtual ~Game();

	//Score Sys
	ScoreSystem* ScoreSys;

	//reseter
	void resetVariables();

	//Accessors
	const bool& getEndGame() const;
	const bool& getEndApplication() const;
	const float& getHighScore() const;

	//Main loop
	void run();

	//Update
	void pollEvents();
	void updateMousePosVectors();
	void updateBulletHittingTarget();
	void updatePlayerHittingEnemy();
	void update();

	//Render
	void render();
};

