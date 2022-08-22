#pragma once

#include<iostream>
#include<time.h>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>


class Upgrades
{
private:

	//Ammo
	float CurrentAddedAmmo;
	float CurrentAddedMaxHP;
	float CurrentAddedHP;

	void initVariables();
public:
	Upgrades();
	virtual ~Upgrades();

	//Functions

	///	Base construct for rng upgrades
	///	Checks if the rolled dice is smaller then the given possibilty.
	/// If yes return true else false.
	/// Add variables that will be changed as upgrade counting.
	bool RNGBaseConstruct(int possibility, float* addCounter);

	//RNG Upgrades from killing enemies
	// 
	//Adds more Ammo with a chance of 5%
	bool RNGAddedAmmo();
	//Adds more Ammo with a chance of 2%
	bool RNGAddMaxHP();
	//Adds more Ammo with a chance of 3%
	bool RNGAddHP();
};

