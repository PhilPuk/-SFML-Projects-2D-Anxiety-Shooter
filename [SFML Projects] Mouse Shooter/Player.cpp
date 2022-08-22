#include "Player.h"

//Initialization
void Player::initVariables()
{
	//Player shape
    this->sprite.scale(0.3f, 0.3f);
    this->sprite.setTexture(this->Texture_Player);

    sf::FloatRect rect = this->sprite.getLocalBounds();

    this->sprite.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);

    //Shooting  OLD Bullet sys
    //this->ShootCDMAX = 2.f;
    //this->ShootCD = this->ShootCDMAX;

    //Game logic
    this->PlayerHPMax = 30.f;
    this->PlayerHP = this->PlayerHPMax;

    //HP Bar
    this->HPBarx = 200.f;
    this->HPUpdate = -1.f;

    //For tiles movement
    this->tileMove.x = 0.f;
    this->tileMove.y = 0.f;
}

void Player::initTextures()
{
    if (!this->Texture_Player.loadFromFile("Textures/Player/player0.png"))
    {
        std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: player0.png!\n";
    }
    
    /*
    if (!this->Texture_bullets.loadFromFile("Textures/Player/Bullets/bullet0.png"))
    {
        std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: bullet0.png!\n";
    }
    */
}

void Player::initHPBar()
{
    this->redHPBar.setSize(sf::Vector2f(this->HPBarx, 30.f));
    this->redHPBar.setPosition(10.f, 20.f);
    this->redHPBar.setFillColor(sf::Color(255, 0, 0 ,110));

    this->backgroundHPBar = this->redHPBar;
    this->backgroundHPBar.setFillColor(sf::Color(100, 100, 100, 110));
}

void Player::initText(sf::Font& font)
{
    //HP Bar text
    this->Text_HP.setFont(font);
    this->Text_HP.setCharacterSize(24);
    this->Text_HP.setPosition(10.f, 20.f);
    this->Text_HP.setFillColor(sf::Color(255, 255, 255, 110));

}

void Player::initHitBoxShape()
{
    //Set to size of sprite
    this->shape_hitbox.setSize(sf::Vector2f(this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().height));
    
    //Center
    sf::FloatRect recthitbox = this->shape_hitbox.getLocalBounds();
    this->shape_hitbox.setOrigin(recthitbox.left + recthitbox.width / 2.0f, recthitbox.top + recthitbox.height / 2.0f);

    //Set to position of sprite
    this->shape_hitbox.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y);

    this->shape_hitbox.setFillColor(sf::Color::Red);
}

Player::Player(sf::Font& font)
{
    this->initTextures();
	this->initVariables();
    this->initText(font);
    this->initHPBar();
    this->initHitBoxShape();
}

Player::~Player()
{
    /* OLD Bullet sys
    for (size_t i = 0; i < this->bullets.size(); i++)
    {
        this->bullets.erase(this->bullets.begin(), this->bullets.end());
    }
    // std::cout << "Bullets: " << this->bullets.size() << "\n";
    */
}

const sf::Vector2f& Player::getCenterOfPlayer() const
{
    return this->playerCenter;
}

const sf::Vector2f& Player::getPos() const
{
    return this->sprite.getPosition();
}

const sf::FloatRect& Player::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const float& Player::getHP() const
{
    return this->PlayerHP;
}

const sf::Vector2f& Player::getTileMove() const
{
    return this->tileMove;
}

const float& Player::getRotationAngle() const
{
    return this->PlayerAngle;
}

void Player::TakeDamage(float dmg)
{
    this->PlayerHP -= dmg;
    //Debug info
    //std::cout << "HP: " << this->PlayerHP << "\n";
}

void Player::addHP(float add)
{
    this->PlayerHP += add;
}

void Player::changeHP(float change)
{
    this->PlayerHP = change;
}

//Update
void Player::updateAimSystem(sf::Vector2f& MousePos)
{
    //Gets playerCenter and updates the AimDirection via Object instance Aiming aimSys
    this->playerCenter = sf::Vector2f(this->sprite.getPosition().x, this->sprite.getPosition().y);
    this->aimSys.updateAimDirection(this->playerCenter, MousePos);

    //Calculates the rotation the player needs  in relation to the MousePos
    this->PlayerAngle = atan2(this->aimSys.getAimDirNorm().y, this->aimSys.getAimDirNorm().x) * 180.0f / 3.1415f;

    //For debugging
    //std::cout << "PlayerAngle: " << this->PlayerAngle << "\n";
    
}

void Player::updatePlayerMovement()
{
    //LEFT
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->sprite.move(-10.f, 0.f);

        //Hitbox
        this->shape_hitbox.move(-10.f, 0.f);

        //Tile movement
        this->tileMove.x = 1.f;
    }
    //RIGHT
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->sprite.move(10.f, 0.f);

        this->shape_hitbox.move(10.f, 0.f);

        //Tile movement
        this->tileMove.x = -1.f;
    }
    else
    {
        this->tileMove.x = 0.f;
    }

    //UP
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->sprite.move(0.f, -10.f);

        this->shape_hitbox.move(0.f, -10.f);

        //Tile movement
        this->tileMove.y = 1.f;
    }
    //DOWN
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->sprite.move(0.f, 10.f);

        this->shape_hitbox.move(0.f, 10.f);

        //Tile movement
        this->tileMove.y = -1.f;
    }
    else
    {
        this->tileMove.y = 0.f;
    }

    this->sprite.setRotation(this->PlayerAngle);
}

void Player::updateWindowBoundCollision(const sf::Vector2u& winSize)
{
    // Checks if player hit window border
    // Makes it impossible to move out of the screen

    sf::Vector2f boxSize = this->shape_hitbox.getSize();

    sf::Vector2f newPos;

    //TOP
    if (this->shape_hitbox.getPosition().y - boxSize.y / 2 < 0.f)
    {
        //std::cout << "HIT TOP\n";
        newPos.x = this->shape_hitbox.getPosition().x;
        newPos.y = boxSize.y / 2.f;

        this->shape_hitbox.setPosition(newPos);
        this->sprite.setPosition(newPos);
    }
    //BOTTOM
    else if (this->shape_hitbox.getPosition().y + boxSize.y / 2 > winSize.y)
    {
        //std::cout << "HIT TOP\n";
        newPos.x = this->shape_hitbox.getPosition().x;
        newPos.y =  winSize.y - boxSize.y / 2.f;

        this->shape_hitbox.setPosition(newPos);
        this->sprite.setPosition(newPos);
    }

    //LEFT
    if (this->shape_hitbox.getPosition().x - boxSize.x / 2 < 0.f)
    {
        //std::cout << "HIT TOP\n";
        newPos.x = 0.f + boxSize.x / 2.f;
        newPos.y = this->shape_hitbox.getPosition().y;

        this->shape_hitbox.setPosition(newPos);
        this->sprite.setPosition(newPos);
    }
    //RIGHT
    else if (this->shape_hitbox.getPosition().x + boxSize.x / 2 > winSize.x)
    {
        //std::cout << "HIT TOP\n";
        newPos.x = winSize.x - boxSize.x / 2.f;
        newPos.y = this->shape_hitbox.getPosition().y;

        this->shape_hitbox.setPosition(newPos);
        this->sprite.setPosition(newPos);
    }
}

/* OLD Bullet sys
void Player::updateShooting(const sf::Vector2u& winSize, sf::Vector2f BulletSpawn)
{
    if (this->ShootCD < this->ShootCDMAX)
    {
        this->ShootCD += 1.f;
    }
    else
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->ShootCD = 0.f;
            sf::Vector2f currVelocity = this->aimSys.getAimDirNorm() * 25.f;
            
            //Temporary solution for weapon system
            //Hides bullet behind beginner weapn
            sf::Vector2f spawn = sf::Vector2f(BulletSpawn.x, BulletSpawn.y);
            this->bullets.push_back(new Bullet(this->Texture_bullets, spawn, currVelocity));
        }
        //For debugging bullets vector
        //std::cout << "Bullets Vector size: " << this->bullets.size() << "\n";
    }

    for (size_t i = 0; i < this->bullets.size(); i++)
    {
        this->bullets[i]->sprite_bullet.move(this->bullets[i]->currVelocity);
        if (bullets[i]->sprite_bullet.getPosition().x < 0 ||
            bullets[i]->sprite_bullet.getPosition().x > winSize.x ||
            bullets[i]->sprite_bullet.getPosition().y < 0 ||
            bullets[i]->sprite_bullet.getPosition().y > winSize.y)
            this->bullets.erase(this->bullets.begin() + i);
    }
}
*/

void Player::updateHPBar()
{
    float tmpX;
    tmpX = this->HPBarx * (this->PlayerHP / this->PlayerHPMax);
    
    this->redHPBar.setSize(sf::Vector2f(tmpX, 30.f));
}

void Player::updateText()
{
    if (this->HPUpdate != this->PlayerHP)
    {
        std::stringstream ss;
        ss << this->PlayerHP << "/" << this->PlayerHPMax;
        this->Text_HP.setString(ss.str());

        this->HPUpdate = this->PlayerHP;
    }
    else
        return;
}

void Player::update(sf::Vector2f& MousePos, const sf::Vector2u& winSize, sf::Vector2f BulletSpawn)
{
    this->updateAimSystem(MousePos);

    this->updatePlayerMovement();

    this->updateWindowBoundCollision(winSize);

    //this->updateShooting(winSize, BulletSpawn);

    this->updateHPBar();

    this->updateText();
}

/* OLD BULLET SYS
void Player::renderBullets(sf::RenderTarget& target)
{
    for (size_t i = 0; i < this->bullets.size(); i++)
    {
        target.draw(this->bullets[i]->sprite_bullet);
    }
}
*/

void Player::renderHitbox(sf::RenderTarget& target)
{
    target.draw(this->shape_hitbox);
}

void Player::renderPlayer(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}

void Player::renderHPBar(sf::RenderTarget& target)
{
    target.draw(this->backgroundHPBar);
    target.draw(this->redHPBar);
}

void Player::renderText(sf::RenderTarget& target)
{
    target.draw(this->Text_HP);
}

void Player::render(sf::RenderTarget& target)
{
    //OLD BULLET SYS
    //this->renderBullets(target);

    //this->renderHitbox(target);

    this->renderPlayer(target);

    this->renderHPBar(target);

    this->renderText(target);
}
