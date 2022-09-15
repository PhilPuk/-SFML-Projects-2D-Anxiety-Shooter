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
  sf::CircleShape baseBloom;
  std::vector<sf::Vector2f*> bloomVelocity;
  std::vector<sf::CircleShape*> blooms;
  
  //Animations
    //Scale animation
    bool scalebigger;
    float ScaleAnimationAmount;
  
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
  void updateBloomScaleAnimation(int i);
  void updateBloomMovement(int i);
  void updateForLoop(sf::Vector2u& winSize);
  
  /*Movement Array Order
  0. Player Bloom
  1. HP Bar bloom
  2. Bullets
  ...
  3. Enemies
  ...
  */
  void update(sf::Vector2u& winSize);
  
  void renderBlooms(sf::RenderTarget& target);
  void render(sf::RenderTarget& target);
};
