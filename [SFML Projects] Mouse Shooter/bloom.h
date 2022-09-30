#pragma once

#include<iostream>
#include<vector>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Bloom
{
private:
    sf::Texture t_Bloom;
    sf::CircleShape CustomInitBloom;
    sf::CircleShape CustomizedBlooms;
    std::vector<sf::Vector2f*> bloomVelocity;
  
    //Animations

        //Scaling Animation
    struct
    {
        bool scalebigger;
        float maxScale;
        float ScaleAnimationAmount;
    } s_AnimationCircles;

    struct
    {
        bool scalebigger;
        float maxScale;
        float ScaleAnimationAmount;
    } s_AnimationSprite;

  
    void initTextures(sf::Texture texture);
    void initVariables();
    void initCustomInitBloom(sf::Color color, float radius, bool CenterOrigin);
public:
    Bloom(sf::Texture texture_Bloom, sf::Color color, float radius, bool CenterOrigin);
    virtual ~Bloom();

    std::vector<sf::CircleShape*> blooms;
    sf::Sprite CustomizedSpriteBloom;

    //Functions

    //Used for creating initalized custom blooms
    void createBloom(sf::Vector2f& BloomPos, sf::Vector2f* velocity);

    //Used for creating completly customized blooms
    void createCustomizedBloom(sf::Vector2f& BloomPos, sf::Vector2f* velocity, sf::Color color, float radius);
    void createCustomizedSpriteBloom(sf::Texture& texture, sf::Vector2f& BloomPos, sf::Color color, sf::Vector2f scale);
    void deleteSpecificBloom(int index);
  

    void updateBloomOutOfScreen(int i, sf::Vector2u& winSize);
    void updateBloomScaleAnimation(int& i);
    void updateSpriteBloomScaleAnimation();
    void updateBloomMovement(int i);
    void updateForLoop(sf::Vector2u& winSize);
    void update(sf::Vector2u& winSize);
  
    void renderBulletBlooms(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};
