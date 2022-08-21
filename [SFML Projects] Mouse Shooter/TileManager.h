#pragma once

#include"Tile.h"
#include<vector>
#include<math.h>
#include<sstream>

class TileManager
{
private:
	//Tiles
	std::vector<Tile*> tiles;
	sf::Texture Texture_tiles[8];
	int MaxTextures;

	int MaxTiles;
	float spacing_tiles;
	float SizeXTileStart;

	//Tile Amount
	int AmountX;
	int AmountY;

	//Tile 0 Position for new line movement calculations
	sf::Vector2f Tile1Pos;
	int LineMovedCounterX;
	int LineMovedCounterY;

	sf::Vector2f movement;
	float moveMax;
	sf::Vector2f TileMovingMath;
	float TileXAdd;
	float lastMovement;
	float Camera[4];

	//Tileline movement
		//TOP BOTTOM LEFT RIGHT
	int BorderTiles[4];

	void initVariables();
	void initTexture();
	void spawnTiles(sf::RenderTarget& target);
public:
	TileManager(sf::RenderTarget& target);
	virtual ~TileManager();

	float TileMovingFormula(float x);
	
	void updateTileMovingMath(sf::Vector2f move);
	void updateTileMoving(sf::Vector2f moveTile, int i);
	void updateTileNewPositiong(int i, sf::Vector2f playerPos);
	void update(sf::Vector2f moveTile, sf::Vector2f playerPos);

	void render(sf::RenderTarget& target);
};

