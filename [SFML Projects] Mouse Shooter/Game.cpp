#include "Game.h"

void Game::initWindow(sf::RenderWindow* window)
{
    this->window = window;
}

//Initialization
void Game::initVariables(sf::RenderWindow* window)
{
    this->endGame = false;
    this->endApplication = false;

    //Window vars
    this->windowSize = window->getSize();

    //Score
    this->currScore = 0.f;

    //Income / earnings
    this->CurrIncome = 0.f;
}

void Game::initFont(sf::Font& font)
{
    this->font = font;
}

void Game::initPlayer()
{
    this->player = new Player(this->font);
}

void Game::initTiles()
{
    this->tileManager = new TileManager(*this->window);
}

void Game::initWeapons()
{
    this->weapon = new BeginnerWeapon(this->player->getPos(), this->windowSize, this->font);
}

void Game::initScoreSystem()
{
    this->ScoreSys = new ScoreSystem(this->window->getSize(), this->font);
}

void Game::initGameOver()
{
    this->gameOver = new GameOver(this->font, this->windowSize, true, false, 0.f);
}

Game::Game(sf::RenderWindow* window, sf::Font& font)
{
    this->initWindow(window);
    this->initVariables(window);
    this->initFont(font);
    this->initPlayer();
    this->initTiles();
    this->initWeapons();
    this->initScoreSystem();
    this->initGameOver();
}

Game::~Game()
{
    delete this->tileManager;

    delete this->player;

    delete this->weapon;

    delete this->ScoreSys;

    delete this->gameOver;
}

void Game::resetVariables()
{
   //this->initVariables(this->window);
    this->endGame = false;
    this->endApplication = false;
}

const bool& Game::getEndGame() const
{
    return this->endGame;
}

const bool& Game::getEndApplication() const
{
    return this->endApplication;
}

const float& Game::getHighScore() const
{
    //Debug info
    //std::cout << "Current Highscore: " << this->ScoreSys->getHighscore();
    return this->ScoreSys->getHighscore();
}

//Main loop of the game
void Game::run()
{

    /*
    * DEBUGGING UPGRADE COUNTERS
    std::cout << "Max hp: " << this->player->getHPMax() << "\n";
    std::cout << "Bullet speed: " << this->weapon->BulletSpeed << "\n";
    std::cout << "Max Ammo: " << this->weapon->MaxAmmo << "\n";
    std::cout << "Reload speed max: " << this->weapon->ReloadTimerMax<< "\n";
    std::cout << "Bullet damage: " << this->weapon->damageBullet << "\n";
    */

    while (!endGame)
    {
        this->update();

        this->render();
    }

    //If gameover was activated reset everything except the shop
    if (this->gameOver->getActivation())
    {
        this->gameOver->resetENDGAMEOVER();
        this->player->changeHP(this->player->getHPMax());
        this->enemyManager.enemies.clear();
        this->currScore = 0.f;
        this->ScoreSys->setTime(0.f);
        this->ScoreSys->updateTime();
        this->ScoreSys->update(this->currScore);
    }

    this->ScoreSys->saveHighScoreinTxt();
}

	//Functions
	
void Game::checkGameOver()
{
    if (this->player->getHP() <= 0)
    {
        this->gameOver->activateGameOver();
    }
}

//Rolls dices for each rng upgrade 
void Game::rolltheUpgrades(int n)
{
    //RNG Upgrades from killing enemies
    //Max ammo amount
    sf::Vector2f  pos = this->enemyManager.enemies[n]->sprite_enemy.getPosition();

    if (this->weapon->MaxAmmo < 60)
    {
        if (this->upgrades.RNGAddedAmmo())
        {
            this->upgrades.createNewAmmoAnimation(pos);
            this->weapon->MaxAmmo += 1;
        }
    }

    //HP
    if (this->upgrades.RNGAddMaxHP())
    {
        this->upgrades.createNewMaxHPAnimation(pos);
        this->player->addMaxHP(1.f);
    }
    else if (this->upgrades.RNGAddHP())
    {
        if (this->player->getHP() < this->player->getHPMax())
        {
            this->upgrades.createNewHPAnimation(pos);
            this->player->addHP(1.f);
        }
    }
    }

void Game::pollEvents()
{
    sf::Event ev;
    while (this->window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            this->endGame = true;
            this->endApplication = true;
            break;
        case sf::Event::KeyPressed:
            //ESCAPE
            if (ev.key.code == sf::Keyboard::Escape)
            {
                this->endGame = true;
            }
            break;
        }
    }
}

void Game::updateMousePosVectors()
{
    this->mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(*this->window));
}

void Game::updateBulletHittingTarget()
{
    //Loop through bullets
    for (size_t i = 0; i < this->weapon->bullets.size(); i++)
    {
        //Loop through enemies
        for (size_t n = 0; n < this->enemyManager.enemies.size(); n++)
        {
            //Bullet hits enemy check
            if (this->weapon->bullets[i]->sprite_bullet.getGlobalBounds().intersects(this->enemyManager.enemies[n]->sprite_enemy.getGlobalBounds()))
            {     
                //Enemy taking dmg
                this->enemyManager.enemies[n]->takeDamage(this->weapon->getBulletDamage());
                
                //Deleting if hp is 0
                if (this->enemyManager.enemies[n]->getHP() <= 0)
                {
                    //Add money to bank
                    this->ScoreSys->addMoneybyAddition(this->enemyManager.enemies[n]->getMoney());
                    if (this->enemyManager.enemies[n]->getMoney() > 0)
                    {
                        sf::Vector2f pos = this->enemyManager.enemies[n]->sprite_enemy.getPosition();
                        this->upgrades.createNewMoneyAnimation(pos);
                    }

                    //For debugging
                    //std::cout << "Money: " << *this->ScoreSys->getMoney()<<"\n";
                    
                    this->rolltheUpgrades(n);
              
                    //Adding score 
                    this->currScore += 1.f;

                    this->enemyManager.enemies.erase(this->enemyManager.enemies.begin() + n);

                }
                //For Debugging
                //std::cout << "Enemies: " << this->enemyManager.enemies.size() << "\n";

                //Bullet deleting
                this->weapon->bullets.erase(this->weapon->bullets.begin() + i);
                break;
            }

        }
    }
    
}

void Game::updatePlayerHittingEnemy()
{
    for (size_t n = 0; n < this->enemyManager.enemies.size(); n++)
    {
        if (this->player->getBounds().intersects(this->enemyManager.enemies[n]->sprite_enemy.getGlobalBounds()))
        {
		//Taking damage
            	this->player->TakeDamage(1.f);
		
		//Animation damage taken
        sf::Vector2f playerpos = this->player->getPos();
        float playerangle = this->player->getRotationAngle();
		this->upgrades.createNewDamageTakenAnimation(playerpos, playerangle);

            //Enemy deleting
            this->enemyManager.enemies.erase(this->enemyManager.enemies.begin() + n);
        }
    }
}

void Game::updateNewBlooms()
{
    if (this->weapon->getBulletShot())
    {
        this->tileManager->addTimetoShakeScreen(8.f);
        this->weapon->resetBulletShoot();
        //Bloom effect
        sf::Vector2f playerpos = this->player->getPos();
        playerpos.x -= 5.f;
        playerpos.y -= 5.f;
        this->bloom.createNewBloom(playerpos, sf::Color(249, 255, 64, 110), 10.f);
        auto size = this->weapon->bullets.size() - 1;
        sf::Vector2f velocity = this->weapon->bullets[size]->getCurrVelocity();
        this->bloom.createNewBloomVelocity(new sf::Vector2f(velocity));
    }
}

void Game::update()
{
    if (!this->gameOver->getActivation())
    {
        this->checkGameOver();

        //Updates everything for the game
        this->pollEvents();

        //Mouse
        this->updateMousePosVectors();

        //Player
        this->player->update(this->mousePosWindow, this->windowSize, this->weapon->getBulletSpawn());

        //Weapon
        this->weapon->update(this->windowSize, this->player->getRotationAngle(), this->player->getPos(), this->player->aimSys.getAimDirNorm());

        //Tiles
        this->tileManager->update(this->player->getTileMove(), this->player->getPos());

        //Enemies
        this->enemyManager.update(this->player->getCenterOfPlayer(), this->windowSize, this->currScore, this->ScoreSys->getTime());

        //Bloom
        this->updateNewBlooms();
        this->bloom.update(this->windowSize);

        //Bullet enemy collision
        this->updateBulletHittingTarget();

        //Player enemy collision
        this->updatePlayerHittingEnemy();

        //ScoreSystem
        this->ScoreSys->update(this->currScore);

        //Upgrades
        this->upgrades.updateAnimations();
    }
    else
    {
        this->gameOver->update(&this->endGame, true, this->currScore);
        this->tileManager->update(sf::Vector2f(0.f, 0.f), this->player->getPos());
    }
}



void Game::render()
{
    this->window->clear();

    if (!this->gameOver->getActivation())
    {
        //Renders everything for the game

        this->tileManager->render(*this->window);

        //Enemies
        this->enemyManager.render(*this->window);

        //Player
        this->player->render(*this->window);

        //Weapon
        this->weapon->render(*this->window);

        //ScoreSystem
        this->ScoreSys->render(*this->window);

        //Upgrades
        this->upgrades.render(*this->window);

        //Blooms
        this->bloom.render(*this->window);
    }
    else
    {
        this->tileManager->render(*this->window);
        this->gameOver->render(*this->window);
    }

    this->window->display();
}
