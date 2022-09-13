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
  void deleteSpecificBloom(int index);
  
  void updateBloomScaleAnimation(int i);
  void updateBloomMovement(sf::Vector2f movement[], int i);
  void updateForLoop(sf::Vector2f movement[]);
  
  /*Movement Array Order
  0. Player Bloom
  1. HP Bar bloom
  2. Bullets
  ...
  3. Enemies
  ...
  */
  void update(sf::Vector2f movement[]);
  
  void renderBlooms(sf::RenderTarget& target);
  void render(sf::RenderTarget& target);
};
