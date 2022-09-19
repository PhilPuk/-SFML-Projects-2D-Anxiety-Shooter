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
    sf::Texture texture_bloom;
    sf::CircleShape baseBloom;
    std::vector<sf::Vector2f*> bloomVelocity;
    std::vector<sf::CircleShape*> blooms;
  
    //Animations
    //Scale animation
    bool scalebigger;
    float maxScale;
    float ScaleAnimationAmount;
  
    void initTextures();
    void initVariables();
    void initBaseBloom();
public:
    Bloom();
    virtual ~Bloom();
  
    //Accessors
  
    //Modifiers
  
    //Functions
    void createNewBloom(sf::Vector2f& BloomPos, sf::Color color, float radius);
    void createNewBloomVelocity(sf::Vector2f* velocity);
    void deleteSpecificBloom(int index);
  
    void updateBloomOutOfScreen(int i, sf::Vector2u& winSize);
    void updateBloomScaleAnimation(int& i);
    void updateBloomMovement(int i);
    void updateDeletedBullets(bool& deletedbullet, short index);
    void updateForLoop(sf::Vector2u& winSize);
    void update(sf::Vector2u& winSize, bool& deletedbullet, short index);
  
    void renderBlooms(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};
