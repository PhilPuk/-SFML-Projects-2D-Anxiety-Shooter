#include"bloom.h"

void Bloom::initTextures()
{
    //Base bloom texture
    if(!this->texture_bloom.loadFromFile("Textures/blooms/base.png"))
    std::cout<<" - ERROR::BLOOM::INITTEXTURES::Couldn't load texture: base.png";
}

void Bloom::initVariables()
{
    //Animations
    //Scale animation
    this->scalebigger = false;
    this->ScaleAnimationAmount = 0.3f;
    this->maxScale = 1.f + this->ScaleAnimationAmount;
}

void Bloom::initBaseBloom()
{
    this->baseBloom.setRadius(30.f);
    this->baseBloom.setTexture(&this->texture_bloom);
    //this->baseBloom.setFillColor(sf::Color::White);
    sf::FloatRect rect = this->baseBloom.getLocalBounds();
    this->baseBloom.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
}

Bloom::Bloom()
{
    this->initVariables();
    this->initTextures();
    this->initBaseBloom();
}

Bloom::~Bloom()
{
    for(int i = 0; i < this->blooms.size(); i++)
    {
    delete this->blooms[i];
    this->blooms.erase(this->blooms.begin(), this->blooms.end());
    }
}

void Bloom::createNewBloom(sf::Vector2f& BloomPos, sf::Color color, float radius)
{
    if(radius != 0)
    this->baseBloom.setRadius(radius);
    if(color != sf::Color::White)
    this->baseBloom.setFillColor(color);
    this->baseBloom.setPosition(BloomPos);
    this->blooms.push_back(new sf::CircleShape(this->baseBloom));
}

void Bloom::createNewBloomVelocity(sf::Vector2f* velocity)
{
    this->bloomVelocity.push_back(velocity);
}

void Bloom::deleteSpecificBloom(int index)
{
    this->blooms.erase(this->blooms.begin() + index);
    this->bloomVelocity.erase(this->bloomVelocity.begin() + index);
    //Debugging
    //std::cout << "Bloom vector size: " << this->blooms.size() << "\n";
    //std::cout << "Bloom Velocity vector size: " << this->bloomVelocity.size() << "\n";
}

void Bloom::updateBloomOutOfScreen(int i, sf::Vector2u& winSize)
{
    if (this->blooms[i]->getPosition().x < 0 ||
        this->blooms[i]->getPosition().x > winSize.x ||
        this->blooms[i]->getPosition().y < 0 ||
        this->blooms[i]->getPosition().y > winSize.y)
        this->deleteSpecificBloom(i);
}

void Bloom::updateBloomScaleAnimation(int& i)
{
    if (this->scalebigger)
    {
        if (this->blooms[i]->getScale().x > this->maxScale)
        {
            this->scalebigger = !this->scalebigger;
            return;
        }
            this->blooms[i]->scale(1.f + this->ScaleAnimationAmount, 1.f + this->ScaleAnimationAmount);
    }
    else
    {
        if (this->blooms[i]->getScale().x < 1.f)
        {
            this->scalebigger = !this->scalebigger;
            return;
        }
            this->blooms[i]->scale(1.f - this->ScaleAnimationAmount, 1.f - this->ScaleAnimationAmount);
    }

}

void Bloom::updateBloomMovement(int i)
{    
    // if (this->bloomVelocity[i]->x == 0.f || this->bloomVelocity[i]->y == 0.f)
    //    this->deleteSpecificBloom(i);
    //else
        this->blooms[i]->move(*this->bloomVelocity[i]);
}

void Bloom::updateDeletedBullets(bool& deletedbullet, short index)
{
    if (deletedbullet)
        this->deleteSpecificBloom(index);
    else
        return;
}

void Bloom::updateForLoop(sf::Vector2u& winSize)
{
    //Flip scale direction
    //this->scalebigger = !this->scalebigger;

    //All update functions that need the loop
    for(int i = 0; i < this->blooms.size(); i++)
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
    for(int i = 0; i < this->blooms.size(); i++)
    {
    target.draw(*this->blooms[i]);
    }
}

void Bloom::render(sf::RenderTarget& target)
{
    this->renderBlooms(target);
}
