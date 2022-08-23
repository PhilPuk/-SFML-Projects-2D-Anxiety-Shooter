#pragma once

#include<iostream>
#include<sstream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Money
{
private:

  //Used for saving all income
  float Bank;
  //Used for saving income while playing
  //Adds to bank once game is over
  float IncomePerGame;
  
  void initVariables();
public:
  Money();
  virtual ~Money();
  
  //Accessors
  const float& getBank() const;
  const float& getIncomePerGame() const;
  
  //Modifiers
  void IncreaseIncomePerGame(float Income);
};
