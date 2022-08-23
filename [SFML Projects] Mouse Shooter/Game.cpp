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

Game::Game(sf::RenderWindow* window, sf::Font& font)
{
    this->initWindow(window);
    this->initVariables(window);
    this->initFont(font);
    this->initPlayer();
    this->initTiles();
    this->initWeapons();
    this->initScoreSystem();
}

Game::~Game()
{
    delete this->player;

    delete this->tileManager;

    delete this->weapon;

    delete this->ScoreSys;
}

void Game::resetVariables()
{
    this->initVariables(this->window);
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


void Game::run()
{
    //Main loop of the game

    while (!endGame)
    {
        this->update();

        this->render();
    }
    this->ScoreSys->saveHighScoreinTxt();

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
    //Checking for contact of bullet and enemy
    // If intersects then delete enemy and bullet
    for (size_t i = 0; i < this->weapon->bullets.size(); i++)
    {
        for (size_t n = 0; n < this->enemyManager.enemies.size(); n++)
        {
            //Bullet hits enemy
            if (this->weapon->bullets[i]->sprite_bullet.getGlobalBounds().intersects(this->enemyManager.enemies[n]->sprite_enemy.getGlobalBounds()))
            {     
                //Enemy taking dmg
                this->enemyManager.enemies[n]->takeDamage(this->weapon->getBulletDamage());
                
                //Deleting if hp is 0
                //RNG Upgrades aswell
                //Adding score
                if (this->enemyManager.enemies[n]->getHP() <= 0)
                {

                    //RNG Upgrades from killing enemies
                      //Max ammo amount
                    if (this->upgrades.RNGAddedAmmo())
                        this->weapon->MaxAmmo += 1;

                    //HP
                    if (this->upgrades.RNGAddMaxHP())
                        this->player->addMaxHP(1.f);
                    else if (this->upgrades.RNGAddHP())
                    {
                        if (this->player->getHP() < this->player->getHPMax())
                            this->player->addHP(1.f);
                    }

                    //Adding score 
                    this->currScore += 1.f;

                    this->weapon->bullets.erase(this->weapon->bullets.begin() + i);
                    this->enemyManager.enemies.erase(this->enemyManager.enemies.begin() + n);
                    break;
                }
                //std::cout << "Enemies: " << this->enemyManager.enemies.size() << "\n";

                //Bullet deleting
                this->weapon->bullets.erase(this->weapon->bullets.begin() + i);

                /*
                TO-DO
                add function for rng upgrades inside upgrades class
                values that should be changed are given as * parameters!
                */
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
            this->player->TakeDamage(1.f);

            //Enemy deleting
            this->enemyManager.enemies.erase(this->enemyManager.enemies.begin() + n);
        }
    }
}

void Game::update()
{
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

    //Bullet enemy collision
    this->updateBulletHittingTarget();

    //Player enemy collision
    this->updatePlayerHittingEnemy();

    //ScoreSystem
    this->ScoreSys->update(this->currScore);
}



void Game::render()
{
    this->window->clear();

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

    this->window->display();
}
