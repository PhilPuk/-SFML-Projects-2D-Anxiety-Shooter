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
  for(size_t i = 0; i < this->blooms.size(); i++)
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

void Bloom::deleteSpecificBloom(int index)
{
  this->blooms.erase(this->blooms.begin() + index);
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

void Bloom::updateBloomMovement(sf::Vector2f movement[], int i)
{    
  this->blooms[i]->move(movement[i]);
}

void Bloom::updateForLoop(sf::Vector2f movement[])
{
   //Flip scale direction
   this->scalebigger = !this->scalebigger;
   
   //All update functions that need the loop
    for(size_t i = 0; i < this->blooms.size(); i++)
    {
      this->updateBloomMovement(movement, i);
      this->updateBloomScaleAnimation(i);
    }
}

void Bloom::update(sf::Vector2f movement[])
{
  this->updateForLoop(movement);
}

void Bloom::renderBlooms(sf::RenderTarget& target)
{
  for(size_t i = 0; i < this->blooms.size(); i++)
  {
    target.draw(*this->blooms[i]);
  }
}

void Bloom::render(sf::RenderTarget& target)
{
  this->renderBlooms(target);
}
