#include "EnemyManager.h"

/*
* TO-DO:
* 
*/

void EnemyManager::initVariables()
{
	this->movementSpeed = 3.5f;

	//Spawning
	this->SpawnTimerMax = 90.f;
	this->SpawnTimer = 0.f;
	this->CheckMaxEnemy = false;
}

void EnemyManager::initTextures()
{

		if (!this->Textures_Enemy[0].loadFromFile("Textures/Enemy/enemy0.png"))
		{
			std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: enemy0.png!\n";
		}

		if (!this->Textures_Enemy[1].loadFromFile("Textures/Enemy/enemy1.png"))
		{
			std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: enemy1.png!\n";
		}

		if (!this->Textures_Enemy[2].loadFromFile("Textures/Enemy/enemy2.png"))
		{
			std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: enemy2.png!\n";
		}
}

EnemyManager::EnemyManager()
{
	this->initVariables();
	this->initTextures();
}

EnemyManager::~EnemyManager()
{
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		delete this->enemies[i];

		this->enemies.erase(this->enemies.begin(), this->enemies.end());
	}
	std::cout << this->enemies.size() << "\n";
}

const int& EnemyManager::getEnemiesVectorSize() const
{
	return this->enemies.size();
}

void EnemyManager::updateIncreasingMaxHP(float score, int time)
{
	int dice = rand() % 100;
	if (time > 15)
	{
		if (dice > 30)
		{
			this->enemyHPMax = 1.f + score / 30.f + static_cast<float>(time) / 100;
		}
		else
		{
			this->enemyHPMax = 1.f + score / 100.f;
		}
	}
	else
	{
		if (dice < 50)
			this->enemyHPMax = 2.f;
		else
			this->enemyHPMax = 1.f;
	}
}

void EnemyManager::updateSpawning(sf::Vector2f playerCenter, sf::Vector2u& winSize, float& score, int& time)
{
	/// <summary>
	/// Increases spawn timer, if spawn timer reached his max a new enemy is spawned at a random position.
	/// 
	/// </summary>
	/// <param name="playerCenter"></param>

	//Reduce spawn timing by the score
	float TimerReduce = score / 9.f + static_cast<float>(time) / 50.f;

	if (!this->CheckMaxEnemy)
	{
		if (this->SpawnTimer < this->SpawnTimerMax - TimerReduce )
		{
			this->SpawnTimer += 1.f;
		}
		else
		{
			//Reset timer
			this->SpawnTimer = 0.f;

			//Choose rand texture
			int picktexture = rand() % this->MaxEnemyTextures;

			//Create spawning pos
			int DiceBorder = rand() % 2;
			float x, y;

			//TOP BOTTOM BORDER SPAWNING
			if (DiceBorder == 0)
			{
				x = static_cast<float>(rand() % winSize.x);
				if (playerCenter.y < static_cast<float>(winSize.y) / 2)
					y = static_cast<float>(winSize.y) + 200.f;
				else
					y = -200.f;
			}
			//LEFT RIGHT BORDER SPAWNING
			else
			{
					y = static_cast<float>(rand() % winSize.y);
					if (playerCenter.x < static_cast<float>(winSize.x) / 2)
						x = static_cast<float>(winSize.x) + 200.f;
					else
						x = -200.f;
			}

			//HP generation
			this->updateIncreasingMaxHP(score, time);
			//Spawn enemy
			this->enemies.push_back(new Enemy(x, y, this->Textures_Enemy[picktexture], this->enemyHPMax));

			//Modify speed by score and time once score of 10 is reached
			if (score >= 10)
			{
				float multiplier = 1.f + score / 2000.f + time / 5500.f;
				for (int i = 0; i < this->enemies.size(); i++)
				{
					this->enemies[i]->ModifyEnemySpeed(multiplier, multiplier);
				}
				//Debug info
				//std::cout << "Enemy movement speed multiplier: " << multiplier << "\n";
			}
			//std::cout << this->enemies.size() << "\n";
			if (this->enemies.size() >= this->MaxSpawnedEnemy)
				this->CheckMaxEnemy = true;

			//Debug Info
			//std::cout << "Spawn Timer: " << this->SpawnTimerMax - TimerReduce<<"\n";
		}
	}
	else
	{
		if (this->enemies.size() < this->MaxSpawnedEnemy)
			this->CheckMaxEnemy = false;
	}
}

void EnemyManager::updateMovement(int i, sf::Vector2f playerCenter, sf::Vector2u& winSize)
{
	/// <summary>
	/// Calculates the movement direction towards the player, then modifys the value in the enemy object.
	/// </summary>

	sf::Vector2f enemyCenter;
	//Calc move dir to player
	enemyCenter = sf::Vector2f(this->enemies[i]->sprite_enemy.getPosition().x + this->enemies[i]->sprite_enemy.getGlobalBounds().width / 2,
								this->enemies[i]->sprite_enemy.getPosition().y + this->enemies[i]->sprite_enemy.getGlobalBounds().height / 2);
	this->moveDir = playerCenter - enemyCenter;
	this->moveDirNorm.x = this->moveDir.x / sqrt(pow(this->moveDir.x, 2) + pow(this->moveDir.y, 2));
	this->moveDirNorm.y = this->moveDir.y / sqrt(pow(this->moveDir.x, 2) + pow(this->moveDir.y, 2));

	this->currVelocity = this->moveDirNorm * this->movementSpeed;

	//Update moving values inside enemy object
	this->enemies[i]->ModifyMovement(this->currVelocity.x, this->currVelocity.y);
}

void EnemyManager::updateForLoop(sf::Vector2f playerCenter, sf::Vector2u& winSize)
{
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		//Enemies updating
		this->updateMovement(i, playerCenter, winSize);
		this->enemies[i]->update();
	}
}

void EnemyManager::update(sf::Vector2f playerCenter, sf::Vector2u& winSize, float& score, int& time)
{

	this->updateSpawning(playerCenter, winSize, score, time);

	this->updateForLoop(playerCenter, winSize);
}

void EnemyManager::render(sf::RenderTarget& target)
{
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		//render all enemies
		this->enemies[i]->render(target);
	}
}
