#include"Money.h"

void Money::initVariables()
{
this->Bank = 0.f;
this->IncomePerGame = 0.f;
}

Money::Money()
{
  this->initVariables();
}

Money::~Money()
{

}

//Accessors
const float& Money::getBank() const
{
return this->Bank;
}

const float& Money::getIncomePerGame() const
{
return this->IncomePerGame;
}

//Modifiers
void Money::IncreaseIncomePerGame(float Income)
{
this->IncomePerGame += Income;
}
