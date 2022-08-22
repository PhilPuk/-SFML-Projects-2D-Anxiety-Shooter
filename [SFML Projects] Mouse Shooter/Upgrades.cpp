#include "Upgrades.h"

void Upgrades::initVariables()
{
	this->CurrentAddedAmmo = 0.f;
	this->CurrentAddedMaxHP = 0.f;
	this->CurrentAddedHP = 0.f;
}

Upgrades::Upgrades()
{
	this->initVariables();
}

Upgrades::~Upgrades()
{

}

bool Upgrades::RNGBaseConstruct(int possibility, float* addCounter)
{
	int dice = rand() % 100;
	if (dice < possibility)
	{
		addCounter += 1;
		return true;
	}
	else
	{
		return false;
	}
}

bool Upgrades::RNGAddedAmmo()
{
	return this->RNGBaseConstruct(5, &this->CurrentAddedAmmo);
}

bool Upgrades::RNGAddMaxHP()
{
	return this->RNGBaseConstruct(2, &this->CurrentAddedMaxHP);
}

bool Upgrades::RNGAddHP()
{
	return this->RNGBaseConstruct(3, &this->CurrentAddedHP);
}
