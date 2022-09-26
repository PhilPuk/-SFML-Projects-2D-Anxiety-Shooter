#include"bloom.h"

void Bloom::initTextures()
{
    //Base bloom texture
    if(!this->texture_bulletbloom.loadFromFile("Textures/Blooms/base.png"))
    std::cout<<" - ERROR::BLOOM::INITTEXTURES::Couldn't load texture: base.png";

    if (!this->texture_enemybloom.loadFromFile("Textures/blooms/enemey.png"))
        std::cout << " - ERROR::BLOOM::INITTEXTURES::Couldn't load texture: enemey.png";
}

void Bloom::initVariables()
{
    //Animations
    //Scale animation
    this->scalebigger = false;
    this->ScaleAnimationAmount = 0.1f;
    this->maxScale = 1.f + 0.3f;
}

void Bloom::initBaseBloom()
{
    this->baseBulletBloom.setRadius(30.f);
    this->baseBulletBloom.setTexture(&this->texture_bulletbloom);
    //this->baseBulletBloom.setFillColor(sf::Color::White);
    sf::FloatRect rect = this->baseBulletBloom.getLocalBounds();
    this->baseBulletBloom.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
}

void Bloom::initEnemyBlooms()
{
    this->baseBulletBloom.setRadius(60.f);
    this->baseBulletBloom.setTexture(&this->texture_enemybloom);
    this->baseBulletBloom.setPosition(-200.f, -200.f);
    sf::FloatRect rect = this->baseBulletBloom.getLocalBounds();
    this->baseBulletBloom.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);

    for (int i = 0; i < 8; i++)
    {
        this->enemyblooms.push_back(new sf::CircleShape(this->baseBulletBloom));
    }

    this->initBaseBloom();
}

Bloom::Bloom()
{
    this->initVariables();
    this->initTextures();
    this->initBaseBloom();
    this->initEnemyBlooms();
}

Bloom::~Bloom()
{
    for(int i = 0; i < this->bulletblooms.size(); i++)
    {
    delete this->bulletblooms[i];
    this->bulletblooms.erase(this->bulletblooms.begin(), this->bulletblooms.end());
    }
}

void Bloom::createNewBulletBloom(sf::Vector2f& BloomPos, sf::Color color, float radius)
{
    if(radius != 0)
    this->baseBulletBloom.setRadius(radius);
    if(color != sf::Color::White)
    this->baseBulletBloom.setFillColor(color);
    this->baseBulletBloom.setPosition(BloomPos);
    this->bulletblooms.push_back(new sf::CircleShape(this->baseBulletBloom));
}

void Bloom::createNewBloomVelocity(sf::Vector2f* velocity)
{
    this->bloomVelocity.push_back(velocity);
}

void Bloom::deleteSpecificBulletBloom(int index)
{
    this->bulletblooms.erase(this->bulletblooms.begin() + index);
    this->bloomVelocity.erase(this->bloomVelocity.begin() + index);
    //Debugging
    //std::cout << "Bloom vector size: " << this->bulletblooms.size() << "\n";
    //std::cout << "Bloom Velocity vector size: " << this->bloomVelocity.size() << "\n";
}

void Bloom::setNewEnemyBloomPosition(sf::Vector2f& enemyPos, int index)
{
    this->enemyblooms[index]->setPosition(enemyPos);
}

void Bloom::updateBloomOutOfScreen(int i, sf::Vector2u& winSize)
{
    if (this->bulletblooms[i]->getPosition().x < 0 ||
        this->bulletblooms[i]->getPosition().x > winSize.x ||
        this->bulletblooms[i]->getPosition().y < 0 ||
        this->bulletblooms[i]->getPosition().y > winSize.y)
        this->deleteSpecificBulletBloom(i);
}

void Bloom::updateBloomScaleAnimation(int& i)
{
    if (this->scalebigger)
    {
        if (this->bulletblooms[i]->getScale().x > this->maxScale)
        {
            this->scalebigger = !this->scalebigger;
            return;
        }
            this->bulletblooms[i]->scale(1.f + this->ScaleAnimationAmount, 1.f + this->ScaleAnimationAmount);
    }
    else
    {
        if (this->bulletblooms[i]->getScale().x < 1.f)
        {
            this->scalebigger = !this->scalebigger;
            return;
        }
            this->bulletblooms[i]->scale(1.f - this->ScaleAnimationAmount, 1.f - this->ScaleAnimationAmount);
    }
}

void Bloom::updateBloomMovement(int i)
{    
    // if (this->bloomVelocity[i]->x == 0.f || this->bloomVelocity[i]->y == 0.f)
    //    this->deleteSpecificBulletBloom(i);
    //else
        this->bulletblooms[i]->move(*this->bloomVelocity[i]);
}

void Bloom::updateDeletedBullets(bool& deletedbullet, short index)
{
    if (deletedbullet)
        this->deleteSpecificBulletBloom(index);
    else
        return;
}

void Bloom::updateForLoop(sf::Vector2u& winSize)
{
    //Flip scale direction
    //this->scalebigger = !this->scalebigger;

    //All update functions that need the loop
    for(int i = 0; i < this->bulletblooms.size(); i++)
    {
    this->updateBloomMovement(i);
    this->updateBloomScaleAnimation(i);
    this->updateBloomOutOfScreen(i, winSize);
    std::cout << "I: " << i << "\n";
    }
}

void Bloom::update(sf::Vector2u& winSize, bool& deletedbullet, short index)
{
    this->updateForLoop(winSize);
    this->updateDeletedBullets(deletedbullet, index);
}

void Bloom::renderBlooms(sf::RenderTarget& target)
{
    for(int i = 0; i < this->bulletblooms.size(); i++)
    {
    target.draw(*this->bulletblooms[i]);
    }
}

void Bloom::render(sf::RenderTarget& target)
{
    this->renderBlooms(target);
}
