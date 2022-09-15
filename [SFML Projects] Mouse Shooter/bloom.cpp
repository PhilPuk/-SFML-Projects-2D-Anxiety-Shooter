#include"bloom.h"

void Bloom::initVariables()
{
    //Animations
    //Scale animation
    this->scalebigger = false;
    this->ScaleAnimationAmount = 0.05f;
}

void Bloom::initBaseBloom()
{
    this->baseBloom.setRadius(5.f);
    this->baseBloom.setFillColor(sf::Color::White);
    sf::FloatRect rect = this->baseBloom.getLocalBounds();

    this->baseBloom.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);

}

Bloom::Bloom()
{
    this->initVariables();
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
    this->blooms.push_back(new sf::CircleShape(baseBloom));
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
    std::cout << "Bloom vector size: " << this->blooms.size() << "\n";
    std::cout << "Bloom Velocity vector size: " << this->bloomVelocity.size() << "\n";
}

void Bloom::updateBloomOutOfScreen(int i, sf::Vector2u& winSize)
{
    if (this->blooms[i]->getPosition().x < 0 ||
        this->blooms[i]->getPosition().x > winSize.x ||
        this->blooms[i]->getPosition().y < 0 ||
        this->blooms[i]->getPosition().y > winSize.y)
        this->deleteSpecificBloom(i);
}

void Bloom::updateBloomScaleAnimation(int i)
{
    if(this->scalebigger)
    {
    this->blooms[i]->setScale(
        this->blooms[i]->getScale().x + this->ScaleAnimationAmount,
        this->blooms[i]->getScale().y + this->ScaleAnimationAmount);
    }
    else
    {
        this->blooms[i]->setScale(
        this->blooms[i]->getScale().x - this->ScaleAnimationAmount,
        this->blooms[i]->getScale().y - this->ScaleAnimationAmount);
    }
}

void Bloom::updateBloomMovement(int i)
{    
    // if (this->bloomVelocity[i]->x == 0.f || this->bloomVelocity[i]->y == 0.f)
    //    this->deleteSpecificBloom(i);
    //else
        this->blooms[i]->move(*this->bloomVelocity[i]);
}

void Bloom::updateForLoop(sf::Vector2u& winSize)
{
    //Flip scale direction
    this->scalebigger = !this->scalebigger;
   
    //All update functions that need the loop
    for(int i = 0; i < this->blooms.size(); i++)
    {
    this->updateBloomMovement(i);
    this->updateBloomScaleAnimation(i);
    this->updateBloomOutOfScreen(i, winSize);
    }
}

void Bloom::update(sf::Vector2u& winSize)
{
    this->updateForLoop(winSize);
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
