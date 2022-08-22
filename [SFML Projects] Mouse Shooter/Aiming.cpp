#include "Aiming.h"

void Aiming::initVariables()
{
    //Vectors for aiming
    this->ObjectCenter.x = 0.f;
    this->ObjectCenter.y = 0.f;

    this->mousePosWindow = this->ObjectCenter;

    this->aimDir = this->ObjectCenter;

    this->aimDirNorm = this->ObjectCenter;
}

Aiming::Aiming()
{
    this->initVariables();
}

Aiming::~Aiming()
{

}

sf::Vector2f& Aiming::getAimDirNorm()
{
    return this->aimDirNorm;
}

void Aiming::updateAimDirection(sf::Vector2f& Object1Pos, sf::Vector2f& Object2Pos)
{
    //this->ObjectCenter = sf::Vector2f(Object1Pos.x, Object1Pos.y);
    //this->mousePosWindow = Object2Pos;

    this->aimDir = Object2Pos - Object1Pos;
    this->aimDirNorm.x = this->aimDir.x / sqrt(pow(this->aimDir.x, 2) + pow(this->aimDir.y, 2));
    this->aimDirNorm.y = this->aimDir.y / sqrt(pow(this->aimDir.x, 2) + pow(this->aimDir.y, 2));

    //this->PlayerAngle = atan2(this->aimDirNorm.y, this->aimDirNorm.x) * 180.0f / 3.1415f;

    // std::cout << "X: " << this->aimDirNorm.x << "\n";
     //std::cout << "Y: " << this->aimDirNorm.y << "\n";

     //For debugging
     //std::cout << this->aimDirNorm.x << "   " << this->aimDirNorm.y << "\n";

}
