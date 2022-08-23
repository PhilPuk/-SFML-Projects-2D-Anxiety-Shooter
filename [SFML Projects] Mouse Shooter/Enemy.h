#pragma once

#include<iostream>
#include<math.h>
#include<vector>
#include<time.h>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>


/*
* TO-DO:
*
*/

class Enemy
{
private:
	float moveX;
	float moveY;

	float MulitplyMoveX;
	float MultiplyMoveY;

	float SpawnTimerMax;
	float SpawnTimer;

	float posX;
	float posY;

	bool Phase[4];
	short index_Phase;
	short max_index_Phase;

	//Timer
	float TimerMoveMax;
	float TimerMove;

	//HP
	float EnemyHPMax;
	float EnemyHP;
	
//Phases
	//Phase 0
	float y;
	float xMax;
	float x;

	//Phase 1
	float counterPhase1Max;
	float counterPhase1;

	//Phase 2
	int subPhaseIndex;
	float counterPhase2Max;
	float counterPhase2;
	float movexPhase2, moveyPhase2;


	std::vector<Enemy*> enemies;

	void initVariables(float& pos_X, float& pos_Y);
	void initSprite(sf::Texture& texture);
public:
	sf::Sprite sprite_enemy;
	Enemy(float& pos_X, float& pos_Y, sf::Texture& texture);
	virtual ~Enemy();

	//Accessors
	const sf::FloatRect& getBounds() const;
	const bool& getPhase0() const;
	const sf::Vector2f getMovement() const;
	const float& getHPMax() const;
	const float& getHP() const;
	//Modifiers
		//Modifies enemy movement, used for phase system.
	void ModifyMovement(float move_X, float move_Y);
		//Modify max speed of enemy, by multiplying the given value to the current movespeed.
		//Given values should be > 1.
	void ModifyEnemySpeed(float mulX, float mulY);
	void takeDamage(float damage);

	//Enemy behaviour
	void Phase0();
	void MovementCalculationPhase0();
	void Phase1();
	void MovementCalculationPhase1();
	void Phase2();

	void updatePhases();
	void updateMovement();
	void update();

	void render(sf::RenderTarget& target);
};

