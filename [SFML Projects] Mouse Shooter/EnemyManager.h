#pragma once

#include"Enemy.h"
#include"bloom.h"

class EnemyManager
{
private:
	float movementSpeed;
	sf::Vector2f moveDir;
	sf::Vector2f moveDirNorm;
	sf::Vector2f currVelocity;


	// Green easy, yellow medium, red hard
	//Textures
	sf::Texture Textures_Enemy[3];
	const int MaxEnemyTextures = 3;

	float SpawnTimerMax;
	float SpawnTimer;

	const int MaxSpawnedEnemy = 8;
	bool CheckMaxEnemy;
	bool enemySpawned;

	//used for enemy constructor
	float enemyHPMax;

	//Bloom
	Bloom blooms;

	void initVariables();
	void initTextures();
public:
	EnemyManager();
	virtual ~EnemyManager();

	std::vector<Enemy*> enemies;

	//Accessors
	const int& getEnemiesVectorSize() const;
	const bool& getNewEnemySpawned() const;

	void updateIncreasingMaxHP(float score, int time);
	void updateSpawning(sf::Vector2f playerCenter, sf::Vector2u& winSize, float& score, int& time);
	void updateMovement(int i, sf::Vector2f playerCenter, sf::Vector2u& winSize);
	void updateForLoop(sf::Vector2f playerCenter, sf::Vector2u& winSize);
	void update(sf::Vector2f playerCenter, sf::Vector2u& winSize, float& score, int& time);
	void render(sf::RenderTarget& target);
};

