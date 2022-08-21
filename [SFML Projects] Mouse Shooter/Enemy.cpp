#include "Enemy.h"

//Initialization
void Enemy::initVariables(float& pos_X, float& pos_Y)
{
	this->moveX = 5.f;
	this->moveY = static_cast<float>(rand() % 10 + 5);

	this->MulitplyMoveX = 1.f;
	this->MultiplyMoveY = 1.f;

	this->posX = pos_X;
	this->posY = pos_Y;

	//Spawning
	this->SpawnTimerMax = 300.f;
	this->SpawnTimer = 0.f;

	this->index_Phase = 0;
	this->max_index_Phase = 4;
	for (int i = 0; i < this->max_index_Phase; i++)
	{
		this->Phase[i] = false;
	}
	this->Phase[0] = true;


	//Phase 0
	this->y = 0.f;
	this->xMax = 1.33f;
	this->x = 0.f;

	//Phase 1
	this->counterPhase1Max = static_cast<float>(rand() % 100 + 60);
	this->counterPhase1 = 0.f;

	//Phase 2
	this->subPhaseIndex = 0;
	this->counterPhase2Max = static_cast<float>(rand() % 60 + 50);
	this->counterPhase2 = 0.f;
	this->movexPhase2 = 0.f, moveyPhase2 = 0.f;


}

void Enemy::initSprite(sf::Texture& texture)
{
	float difficulty = static_cast<float>(rand() % 3);
	difficulty /= 5.f;
	//float pos_X = rand() % 700;
	//float pos_Y = rand() % 500;
	this->sprite_enemy.setTexture(texture);
	this->sprite_enemy.scale(0.3f + (0.25f * difficulty), 0.3f + (0.25f * difficulty));
	this->sprite_enemy.setPosition(this->posX, this->posY);
}

Enemy::Enemy(float& pos_X, float& pos_Y, sf::Texture& texture)
{
	this->initVariables(pos_X, pos_Y);
	this->initSprite(texture);
}

Enemy::~Enemy()
{

}

const sf::FloatRect& Enemy::getBounds() const
{
	return this->sprite_enemy.getGlobalBounds();
}

const bool& Enemy::getPhase0() const
{
	return this->Phase[0];
}

const sf::Vector2f Enemy::getMovement() const
{
	sf::Vector2f tmp;
	tmp.x = this->moveX;
	tmp.y = this->moveY;
	return tmp;
}

void Enemy::ModifyMovement(float move_X, float move_Y)
{
	this->moveX = move_X;
	this->moveY = move_Y;
}

void Enemy::ModifyEnemySpeed(float mulX, float mulY)
{
	this->MulitplyMoveX = mulX;
	this->MultiplyMoveY = mulY;
}

//Enemy behaviour
void Enemy::Phase0()
{
	//Movement for Phase 0
	this->MovementCalculationPhase0();

	if (this->x >= this->xMax)
	{
		//Reset x value
		this->x = 0.f;

		//Shift to next phase
		this->Phase[0] = false;
		this->Phase[1] = true;
	}
}

void Enemy::MovementCalculationPhase0()
{
	//Calculate movement multiplier
	float add = static_cast<float>(rand() % 20 + 1) / 1000.f;
	this->x = x + add;
	y = -3 * pow(this->x, 4) + 1.5f * pow(this->x, 3) + 2 * pow(this->x, 2) + 2 * this->x;

	this->sprite_enemy.move(this->moveX * y * this->MulitplyMoveX, this->moveY * y * this->MultiplyMoveY);
}

void Enemy::Phase1()
{
	if (this->counterPhase1 < this->counterPhase1Max)
	{
		//Increase counterPhase1
		this->counterPhase1 += 1.f;
		//Movement for phase 1
		this->MovementCalculationPhase1();
		this->sprite_enemy.move(this->moveX, this->moveY);
	}
	else
	{
		//Reset counterPhase1 and create new random max counterPhase1
		this->counterPhase1 = 0.f;
		this->counterPhase1Max = static_cast<float>(rand() % 100 + 60);

		//Shift to next phase
		this->Phase[1] = false;
		this->Phase[2] = true;
	}
}

void Enemy::MovementCalculationPhase1()
{
	//Slow movement for a few secs
	int coinflip = rand() % 2;
	this->moveX = static_cast<float>(rand() % 3 + 1);
	this->moveY = static_cast<float>(rand() % 3 + 1);

	if (coinflip == 1)
	{
		this->moveX *= -1.f;
		this->moveY *= -1.f;
	}
}

void Enemy::Phase2()
{
	if (this->subPhaseIndex == 0)
	{
		//Create move floats for new pos
		int coinflip = rand() % 2;

		this->movexPhase2 = static_cast<float>(rand() % 5 + 10);
		this->moveyPhase2 = static_cast<float>(rand() % 5 + 10);

		if (coinflip == 1)
		{
			this->movexPhase2 *= -1.f;
			this->moveyPhase2 *= -1.f;
		}
		
		//Shift to next subPhase
		this->subPhaseIndex++;
	}
	else if (this->subPhaseIndex == 1)
	{
		//Move to new pos
		if (this->counterPhase2 <= 0.f)
		{
			this->sprite_enemy.move(this->movexPhase2, this->moveyPhase2);
		}

		if (this->counterPhase2 < this->counterPhase2Max / 2.f)
		{
			this->counterPhase2 += 1.f;
		}
		else
		{
			//Reset timer
			this->counterPhase2 = 0.f;
			
			//Shift to next subPhase
			this->subPhaseIndex++;
		}
	}
	else if (this->subPhaseIndex == 2)
	{
		//Create slow move floats
		int coinflip = rand() % 2;

		this->movexPhase2 = static_cast<float>(rand() % 2 + 1);
		this->moveyPhase2 = static_cast<float>(rand() % 2 + 1);

		if (coinflip == 1)
		{
			this->movexPhase2 *= -1.f;
			this->moveyPhase2 *= -1.f;
		}

		//Shift to next subPhase
		this->subPhaseIndex++;
	}
	else if (this->subPhaseIndex == 3)
	{
		//move slow
		if (this->counterPhase2 < this->counterPhase2Max)
		{
			this->counterPhase2 += 1.f;
			this->sprite_enemy.move(this->movexPhase2, this->moveyPhase2);
		}
		else
		{
			//Reset timer
			this->counterPhase2 = 0.f;

			//Shift to next subPhase
			this->subPhaseIndex++;
		}
	}
	else if (this->subPhaseIndex == 4)
	{

		//Create new max timer
		this->counterPhase2Max = static_cast<float>(rand() % 10 + 30);
		//Next phase
		this->Phase[2] = false;
		this->Phase[0] = true;

		//Reset variables
		this->subPhaseIndex = 0;
	}
}

void Enemy::updatePhases()
{
	/// <summary>
	/// Movement system for enemy.
	/// Phase 0:
	///		- Slow start to fast speed to strong break.
	/// Phase 1:
	///		- chill for 1 - 3 sec with super slow movement.
	/// Phase 2:
	///		- move to new pos quickly, thats not far away from current one.
	/// Phase 3:
	///		- jump back to phase 0
	/// </summary>
	if (this->Phase[0])
	{
		this->Phase0();
	}
	else if (this->Phase[1])
	{
		this->Phase1();
	}
	else if (this->Phase[2])
	{
		//this->Phase2();
		this->Phase[2] = false;
		this->Phase[0] = true;
	}
	else if (this->Phase[3])
	{
		//Go back to phase 0
		this->Phase[3] = false;
		this->Phase[0] = true;
	}
}

void Enemy::updateMovement()
{
	//this->sprite_enemy.move(this->moveX, this->moveY);
}

void Enemy::update()
{
	this->updatePhases();
	//this->updateMovement();
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite_enemy);
}
