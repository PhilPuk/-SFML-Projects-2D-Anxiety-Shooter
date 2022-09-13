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
  
  
  void initVariables();
  void initBaseBloom();
public:
  Bloom();
  virtual ~Bloom();
  
  //Accessors
  
  //Modifiers
  
  //Functions
  void createNewBloom(sf::Vector2f& BloomPos, sf::Color color, float opacity);
  
  void update();
  
  void renderBlooms(sf::RenderTarget& target);
  void render(sf::RenderTarget& target);
};
