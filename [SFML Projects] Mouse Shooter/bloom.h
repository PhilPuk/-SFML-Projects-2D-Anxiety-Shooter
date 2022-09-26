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
    sf::Texture texture_bulletbloom;
    sf::CircleShape baseBulletBloom;
    std::vector<sf::Vector2f*> bloomVelocity;
    std::vector<sf::CircleShape*> bulletblooms;
  
    //Animations
    //Scale animation
    bool scalebigger;
    float maxScale;
    float ScaleAnimationAmount;
  
    void initTextures();
    void initVariables();
    void initBaseBloom();
    void initEnemyBlooms();
public:
    Bloom();
    virtual ~Bloom();
  
    sf::Texture texture_enemybloom;
    std::vector<sf::CircleShape*> enemyblooms;

    //Accessors
  
    //Modifiers
  
    //Functions
    void createNewBulletBloom(sf::Vector2f& BloomPos, sf::Color color, float radius);
    void createNewBloomVelocity(sf::Vector2f* velocity);
    void deleteSpecificBulletBloom(int index);
  
    void setNewEnemyBloomPosition(sf::Vector2f& enemyPos, int index);

    void updateBloomOutOfScreen(int i, sf::Vector2u& winSize);
    void updateBloomScaleAnimation(int& i);
    void updateBloomMovement(int i);
    void updateDeletedBullets(bool& deletedbullet, short index);
    void updateForLoop(sf::Vector2u& winSize);
    void update(sf::Vector2u& winSize, bool& deletedbullet, short index);
  
    void renderBlooms(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};
