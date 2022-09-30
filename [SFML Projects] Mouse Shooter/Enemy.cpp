#include "Enemy.h"

//Initialization
void Enemy::initVariables(float& pos_X, float& pos_Y, float hp)
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

	//HP
	this->EnemyHPMax = hp;
	this->EnemyHP = this->EnemyHPMax;
	this->SavedHP = -1.f;
	
	//Phases
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
	//earnings
	this->money = difficulty;
	difficulty /= 5.f;
	//float pos_X = rand() % 700;
	//float pos_Y = rand() % 500;
	this->sprite_enemy.setTexture(texture);
	this->sprite_enemy.scale(0.3f + (0.25f * difficulty), 0.3f + (0.25f * difficulty));
	this->sprite_enemy.setPosition(this->posX, this->posY);
}

void Enemy::initHPBar()
{
	float offsetY = this->sprite_enemy.getGlobalBounds().height / 5;

	//Grey background
	this->HPBar[0].setFillColor(sf::Color(200, 200, 200, 110));
	this->HPBar[0].setPosition(posX, posY - offsetY);
	this->HPBar[0].setSize(sf::Vector2f(this->sprite_enemy.getGlobalBounds().width, 10.f));
	
	//Red foreground
	this->HPBar[1].setFillColor(sf::Color(255, 0, 0, 110));
	this->HPBar[1].setPosition(posX, posY - offsetY);
	this->HPBar[1].setSize(sf::Vector2f(this->sprite_enemy.getGlobalBounds().width, 10.f));
}

void Enemy::initBloom(sf::Texture& texture, float& pos_X, float& pos_Y)
{
	this->bloom = new Bloom(texture, sf::Color(255, 255, 255, 110), 30.f, true);
	sf::Vector2f spawnpos = sf::Vector2f(this->posX, this->posY);
	this->bloom->createBloom(spawnpos, 0);
	this->bloom->blooms[0]->setRadius(this->sprite_enemy.getGlobalBounds().width / 2.f + 25.f);
	sf::FloatRect rect = this->bloom->blooms[0]->getLocalBounds();
	this->bloom->blooms[0]->setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	this->bloom->blooms[0]->setPosition(this->posX + this->sprite_enemy.getGlobalBounds().width / 2.f, this->posY + this->sprite_enemy.getGlobalBounds().height / 2.f);
}

Enemy::Enemy(float& pos_X, float& pos_Y, sf::Texture& texture, float hp, sf::Texture& bloom_Texture)
{
	this->initVariables(pos_X, pos_Y, hp);
	this->initSprite(texture);
	this->initHPBar();
	this->initBloom(bloom_Texture, pos_X, pos_Y);
}

Enemy::~Enemy()
{
	delete this->bloom;
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

	const float& Enemy::getHPMax() const{
	return this->EnemyHPMax;
	}
	const float& Enemy::getHP() const{
	return this->EnemyHP;
	}

	const float& Enemy::getMoney() const{
	return this->money;
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

///Substracts enemy hp by the given value
void Enemy::takeDamage(float damage)
{
	this->EnemyHP -= damage;
}



///Enemy behaviour
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

	this->updateBodyAndHPBarMovement(this->moveX * y * this->MulitplyMoveX, this->moveY * y * this->MultiplyMoveY);
	//this->sprite_enemy.move(this->moveX * y * this->MulitplyMoveX, this->moveY * y * this->MultiplyMoveY);
}

void Enemy::Phase1()
{
	if (this->counterPhase1 < this->counterPhase1Max)
	{
		//Increase counterPhase1
		this->counterPhase1 += 1.f;
		//Movement for phase 1
		this->MovementCalculationPhase1();

		this->updateBodyAndHPBarMovement(this->moveX, this->moveY);
		//this->sprite_enemy.move(this->moveX, this->moveY);
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

void Enemy::updateBodyAndHPBarMovement(float moveX, float moveY)
{
	this->sprite_enemy.move(moveX, moveY);
	this->HPBar[0].move(moveX, moveY);
	this->HPBar[1].move(moveX, moveY);
	this->bloom->blooms[0]->move(moveX, moveY);
}

void Enemy::updateHPBar()
{
	if (this->SavedHP != this->EnemyHP)
	{
		this->SavedHP = this->EnemyHP;
		this->HPBar[1].setSize(sf::Vector2f(this->sprite_enemy.getGlobalBounds().width * (this->EnemyHP / this->EnemyHPMax), 10.f));
	}
	else
		return;
}

void Enemy::updatePhases()
{
	/// <summary>
	/// TO DO:
	/// -OLD NEED TO UPDATE
	/// 
	/// Movement system for enemy.
	/// Phase 0:
	///		- Slow start to fast speed to strong break.
	/// Phase 1:
	///		- chill for 1 - 3 sec with super slow movement.
	/// Phase 2:
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
	//Old remove soon
	else if (this->Phase[2])
	{
		//this->Phase2();
		this->Phase[2] = false;
		this->Phase[0] = true;
	}
	//OLD remove soon
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
	this->updateHPBar();
	this->updatePhases();
	int i = 0;
	this->bloom->updateBloomScaleAnimation(i);
	//this->updateMovement();
}

void Enemy::renderHPBar(sf::RenderTarget& target)
{
	target.draw(this->HPBar[0]);
	target.draw(this->HPBar[1]);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite_enemy);

	this->renderHPBar(target);

	target.draw(*this->bloom->blooms[0]);
}
