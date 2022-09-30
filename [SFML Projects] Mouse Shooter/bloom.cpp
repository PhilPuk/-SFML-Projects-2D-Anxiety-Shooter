#include"bloom.h"

void Bloom::initTextures(sf::Texture texture)
{
    this->t_Bloom = texture;
}

void Bloom::initVariables()
{
    //Animations
    //Scale animation
    this->s_AnimationCircles.scalebigger = false;
    this->s_AnimationCircles.ScaleAnimationAmount = 0.1f;
    this->s_AnimationCircles.maxScale = 1.f + 0.3f;

    this->s_AnimationSprite.scalebigger = false;
    this->s_AnimationSprite.ScaleAnimationAmount = 0.025f;
    this->s_AnimationSprite.maxScale = 0.35f + 0.05f;
}

void Bloom::initCustomInitBloom(sf::Color color, float radius, bool CenterOrigin)
{
    this->CustomInitBloom.setTexture(&this->t_Bloom);
    this->CustomInitBloom.setRadius(radius);
    this->CustomInitBloom.setFillColor(color);
    if (CenterOrigin)
    {
        sf::FloatRect rect = this->CustomInitBloom.getLocalBounds();
        this->CustomInitBloom.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    }
}


Bloom::Bloom(sf::Texture texture_Bloom, sf::Color color, float radius, bool CenterOrigin)
{
    this->initVariables();
    this->initTextures(texture_Bloom);
    this->initCustomInitBloom(color, radius, CenterOrigin);
}

Bloom::~Bloom()
{
    for(int i = 0; i < this->blooms.size(); i++)
    {
    delete this->blooms[i];
    this->blooms.erase(this->blooms.begin(), this->blooms.end());
    }
}

void Bloom::createBloom(sf::Vector2f& BloomPos, sf::Vector2f* velocity)
{
    this->CustomInitBloom.setPosition(BloomPos);
    this->blooms.push_back(new sf::CircleShape(this->CustomInitBloom));

    //Velocity for bloom
    if(velocity != nullptr)
    this->bloomVelocity.push_back(new sf::Vector2f(*velocity));
}

void Bloom::createCustomizedBloom(sf::Vector2f& BloomPos, sf::Vector2f* velocity, sf::Color color, float radius)
{
    //New Bloom
    this->CustomizedBlooms.setRadius(radius);
    //Center origin
    sf::FloatRect rect = this->CustomizedBlooms.getLocalBounds();
    this->CustomizedBlooms.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    this->CustomizedBlooms.setFillColor(color);
    this->CustomizedBlooms.setPosition(BloomPos);
    this->blooms.push_back(new sf::CircleShape(this->CustomizedBlooms));

    //Velocity for bloom
    if (velocity != nullptr)
    this->bloomVelocity.push_back(new sf::Vector2f(*velocity));
}

void Bloom::createCustomizedSpriteBloom(sf::Texture& texture, sf::Vector2f& BloomPos, sf::Color color, sf::Vector2f scale)
{
    this->CustomizedSpriteBloom.setTexture(texture);
    this->CustomizedSpriteBloom.scale(scale);
    this->CustomizedSpriteBloom.setColor(color);
    this->CustomizedSpriteBloom.setPosition(BloomPos);
    sf::FloatRect rect = this->CustomizedSpriteBloom.getLocalBounds();
    this->CustomizedSpriteBloom.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
}

void Bloom::deleteSpecificBloom(int index)
{
    this->blooms.erase(this->blooms.begin() + index);
    this->bloomVelocity.erase(this->bloomVelocity.begin() + index);

    std::cout << "Bloom vector size: " << this->blooms.size() << " Bloom velocity vector size: " << this->bloomVelocity.size() << "\n";
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
    if (this->s_AnimationCircles.scalebigger)
    {
        if (this->blooms[i]->getScale().x > this->s_AnimationCircles.maxScale)
        {
            this->s_AnimationCircles.scalebigger = !this->s_AnimationCircles.scalebigger;
            return;
        }
            this->blooms[i]->scale(1.f + this->s_AnimationCircles.ScaleAnimationAmount, 1.f + this->s_AnimationCircles.ScaleAnimationAmount);
    }
    else
    {
        if (this->blooms[i]->getScale().x < 1.f)
        {
            this->s_AnimationCircles.scalebigger = !this->s_AnimationCircles.scalebigger;
            return;
        }
            this->blooms[i]->scale(1.f - this->s_AnimationCircles.ScaleAnimationAmount, 1.f - this->s_AnimationCircles.ScaleAnimationAmount);
    }
}

void Bloom::updateSpriteBloomScaleAnimation()
{
    if(this->s_AnimationSprite.scalebigger)
    {
        if (this->CustomizedSpriteBloom.getScale().x > this->s_AnimationSprite.maxScale)
        {
            this->s_AnimationSprite.scalebigger = !this->s_AnimationSprite.scalebigger;
            return;
        }
        this->CustomizedSpriteBloom.scale(1.f + this->s_AnimationSprite.ScaleAnimationAmount, 1.f + this->s_AnimationSprite.ScaleAnimationAmount);
    }
    else
    {
        if (this->CustomizedSpriteBloom.getScale().x < 0.3f)
        {
            this->s_AnimationSprite.scalebigger = !this->s_AnimationSprite.scalebigger;
            return;
        }
        this->CustomizedSpriteBloom.scale(1.f - this->s_AnimationSprite.ScaleAnimationAmount, 1.f - this->s_AnimationSprite.ScaleAnimationAmount);
    }
}

void Bloom::updateBloomMovement(int i)
{    
    // if (this->bloomVelocity[i]->x == 0.f || this->bloomVelocity[i]->y == 0.f)
    //    this->deleteSpecificBloom(i);
    //else
        this->blooms[i]->move(*this->bloomVelocity[i]);
        //std::cout << "Bloom move x: " << this->bloomVelocity[i] << "\n";
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
    //std::cout << "I: " << i << "\n";
    }
}

void Bloom::update(sf::Vector2u& winSize)
{
    this->updateForLoop(winSize);
}

void Bloom::renderBulletBlooms(sf::RenderTarget& target)
{
    for(int i = 0; i < this->blooms.size(); i++)
    {
    target.draw(*this->blooms[i]);
    }
}

void Bloom::render(sf::RenderTarget& target)
{
    this->renderBulletBlooms(target);
}
