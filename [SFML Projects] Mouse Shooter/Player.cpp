#include "Player.h"

//Initialization
void Player::initVariables()
{
	//Player shape
    this->sprite.scale(0.3f, 0.3f);
    this->sprite.setTexture(this->Texture_Player);

    sf::FloatRect rect = this->sprite.getLocalBounds();

    this->sprite.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);

    //Game logic
    this->PlayerHPMax = 10.f;
    this->PlayerHP = this->PlayerHPMax;

    //player move variables
    this->playerMoveSpeed = 10.f;

    //HP Bar
    this->HPBarx = 200.f;
    this->HPUpdate = -1.f;
    this->HPMaxUpdate = -1.f;

    //Movement stuff
    this->tileMove.x = 0.f;
    this->tileMove.y = 0.f;

    this->playerMove.x = 0.f;
    this->playerMove.y = 0.f;
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

const float& Player::getHPMax() const
{
    return this->PlayerHPMax;
}

const float& Player::getHP() const
{
    return this->PlayerHP;
}

const sf::Vector2f& Player::getTileMove() const
{
    return this->tileMove;
}

const sf::Vector2f& Player::getPlayerMovement() const
{
    return this->playerMove;
}

const float& Player::getRotationAngle() const
{
    return this->PlayerAngle;
}

const float& Player::getPlayerMoveSpeed() const
{
    return this->playerMoveSpeed;
}

void Player::TakeDamage(float dmg)
{
    this->PlayerHP -= dmg;
    //Debug info
    //std::cout << "HP: " << this->PlayerHP << "\n";
}

//Takes the current value of HP Max and increases it by the given value
void Player::addMaxHP(float add)
{
    this->PlayerHPMax += add;
}

////Takes the current value of HP and increases it by the given value
void Player::addHP(float add)
{
    this->PlayerHP += add;
}

void Player::changeHP(float change)
{
    this->PlayerHP = change;
}

void Player::addPlayerMoveSpeed(float add)
{
    this->playerMoveSpeed += add;
}

void Player::changePlayerMoveSpeed(float change)
{
    this->playerMoveSpeed = change;
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
        this->sprite.move(-this->playerMoveSpeed, 0.f);

        //Hitbox
        this->shape_hitbox.move(-this->playerMoveSpeed, 0.f);

        //Tile movement
        this->tileMove.x = 1.f;
        this->playerMove.x = -this->playerMoveSpeed;
    }
    //RIGHT
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->sprite.move(this->playerMoveSpeed, 0.f);

        this->shape_hitbox.move(this->playerMoveSpeed, 0.f);

        //Tile movement
        this->tileMove.x = -1.f;
        this->playerMove.x = this->playerMoveSpeed;
    }
    else
    {
        this->tileMove.x = 0.f;
        this->playerMove.x = 0.f;
    }

    //UP
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->sprite.move(0.f, -this->playerMoveSpeed);

        this->shape_hitbox.move(0.f, -this->playerMoveSpeed);

        //Tile movement
        this->tileMove.y = 1.f;
        this->playerMove.y = -this->playerMoveSpeed;
    }
    //DOWN
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->sprite.move(0.f, this->playerMoveSpeed);

        this->shape_hitbox.move(0.f, this->playerMoveSpeed);

        //Tile movement
        this->tileMove.y = -1.f;
        this->playerMove.y = this->playerMoveSpeed;
    }
    else
    {
        this->tileMove.y = 0.f;
        this->playerMove.y = 0.f;
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

void Player::updateHPBar()
{
    float tmpX;
    tmpX = this->HPBarx * (this->PlayerHP / this->PlayerHPMax);
    
    this->redHPBar.setSize(sf::Vector2f(tmpX, 30.f));
}

void Player::updateText()
{
    if (this->HPUpdate != this->PlayerHP || this->HPMaxUpdate != this->PlayerHPMax)
    {
        std::stringstream ss;
        ss << this->PlayerHP << "/" << this->PlayerHPMax;
        this->Text_HP.setString(ss.str());

        this->HPUpdate = this->PlayerHP;
        this->HPMaxUpdate = this->PlayerHPMax;
    }
    else
        return;
}

void Player::update(sf::Vector2f& MousePos, const sf::Vector2u& winSize, sf::Vector2f BulletSpawn)
{
    this->updateAimSystem(MousePos);

    this->updatePlayerMovement();

    this->updateWindowBoundCollision(winSize);

    this->updateHPBar();

    this->updateText();
}

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
    this->renderPlayer(target);

    this->renderHPBar(target);

    this->renderText(target);
}
