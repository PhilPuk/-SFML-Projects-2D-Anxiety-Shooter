#include "TileManager.h"

void TileManager::initVariables()
{
	this->MaxTextures = 8;

	this->MaxTiles = 1;
	this->spacing_tiles = 20.f;

	this->moveMax = 0.37f;

	this->movement.x = 0.f;
	this->movement.y = 0.f;

	this->TileMovingMath.x = 0.f;
	this->TileMovingMath.y = 0.f;
	this->TileXAdd = 0.001f;

	this->lastMovement = 1.f;

	this->AmountX = 0;
	this->AmountY = 0;

	//All below
		//Unnecessary at the moment
	this->LineMovedCounterX = 1;
	this->LineMovedCounterY = 1;

	for (int i = 0; i < 4; i++)
	{
		this->Camera[i] = 0.f;
	}

	//animations
	this->ScreenShake = false;
	this->leftScreenShake = true;
	this->rightScreenShake = false;
	this->Time_ScreenShake = 0.f;
	this->MaxTime_ScreenShake = 40.f;
	this->ScreenShakeStrength = 7.f;


	this->BorderTiles[0] = 1;
	this->BorderTiles[1] = 77;
	this->BorderTiles[2] = 15;
	this->BorderTiles[3] = 64;
}

void TileManager::initTexture()
{
	if (!this->Texture_tiles[0].loadFromFile("Textures/tiles/tile0.png"))
	{
		std::cout << " - ERROR::TILEMANAGER::INITTEXTURE::Couldn't load texture: tile0.png!\n";
	}

	if (!this->Texture_tiles[1].loadFromFile("Textures/tiles/tile1.png"))
	{
		std::cout << " - ERROR::TILEMANAGER::INITTEXTURE::Couldn't load texture: tile1.png!\n";
	}

	if (!this->Texture_tiles[2].loadFromFile("Textures/tiles/tile2.png"))
	{
		std::cout << " - ERROR::TILEMANAGER::INITTEXTURE::Couldn't load texture: tile2.png!\n";
	}

	if (!this->Texture_tiles[3].loadFromFile("Textures/tiles/tile3.png"))
	{
		std::cout << " - ERROR::TILEMANAGER::INITTEXTURE::Couldn't load texture: tile3.png!\n";
	}

	if (!this->Texture_tiles[4].loadFromFile("Textures/tiles/tile4.png"))
	{
		std::cout << " - ERROR::TILEMANAGER::INITTEXTURE::Couldn't load texture: tile4.png!\n";
	}

	if (!this->Texture_tiles[5].loadFromFile("Textures/tiles/tile5.png"))
	{
		std::cout << " - ERROR::TILEMANAGER::INITTEXTURE::Couldn't load texture: tile5.png!\n";
	}

	if (!this->Texture_tiles[6].loadFromFile("Textures/tiles/tile6.png"))
	{
		std::cout << " - ERROR::TILEMANAGER::INITTEXTURE::Couldn't load texture: tile6.png!\n";
	}

	if (!this->Texture_tiles[7].loadFromFile("Textures/tiles/tile7.png"))
	{
		std::cout << " - ERROR::TILEMANAGER::INITTEXTURE::Couldn't load texture: tile7.png!\n";
	}
}

void TileManager::spawnTiles(sf::RenderTarget& target)
{
	//Randomize given texture
	int textureDice = rand() % this->MaxTextures;

	//Create starting tile
	sf::Vector2f pos;
	pos.x = -100.f + this->spacing_tiles;
	pos.y = -100.f + this->spacing_tiles;
	//this->tiles.push_back(new Tile(this->Texture_tiles[textureDice], pos));
	this->tiles.emplace_back(new Tile(this->Texture_tiles[textureDice], pos));

	//Tiles row and coloumn amount
	this->AmountX = 11;
	this->AmountY = 7;

	//X Loop
	for (int i = 0; i < this->AmountX; i++)
	{
		//Y Loop
		for (int n = 0; n < this->AmountY; n++)
		{
			textureDice = rand() % this->MaxTextures;
			pos.y += this->tiles[0]->getSizeX() + this->spacing_tiles;
			//this->tiles.push_back(new Tile(this->Texture_tiles[textureDice], pos));
			this->tiles.emplace_back(new Tile(this->Texture_tiles[textureDice], pos));
		}
		pos.y = -100.f + this->spacing_tiles;
		pos.x += this->tiles[0]->getSizeX() + this->spacing_tiles;
	}

	//Save information for later calculations
	this->Tile1Pos = this->tiles[1]->sprite_tile.getPosition();
	this->SizeXTileStart = this->tiles[1]->sprite_tile.getGlobalBounds().width;

	//Delete tile 0 (isnt used properly)
	//	this->tiles.erase(this->tiles.begin());

	//Debug info
	//std::cout << "Tile Amount X: " << this->AmountX << "\n";
	//std::cout << "Tile Amount Y: " << this->AmountY << "\n";
	//std::cout << "All tiles: " << this->tiles.size() << "\n";
}

TileManager::TileManager(sf::RenderTarget& target)
{
	this->initVariables();
	this->initTexture();
	this->spawnTiles(target);
}

TileManager::~TileManager()
{
	//Deletes all tiles
	for (size_t i = 0; i < this->tiles.size(); i++)
	{
		this->tiles.erase(this->tiles.begin(), this->tiles.end());
	}
}

void TileManager::addTimetoShakeScreen(float add)
{
	this->Time_ScreenShake += add;
}

void TileManager::ActivateShakeScreen()
{
	this->ScreenShake = true;
}

float TileManager::TileMovingFormula(float x)
{
	float y;
	y = pow(x, -x * 4.f) - 1.f;
	return y;
}

void TileManager::updateTileMovingMath(sf::Vector2f move)
{
	if (move.x != 0 || move.y != 0)
	{
		this->TileMovingMath.x += this->TileXAdd;
		if (this->TileMovingMath.x > this->moveMax)
			this->TileMovingMath.x = this->moveMax;
	}
	else
	{
		this->TileMovingMath.x -= this->TileXAdd;
		if (this->TileMovingMath.x < 0.f)
			this->TileMovingMath.x = 0.f;
	}

	this->movement = move * this->TileMovingFormula(this->TileMovingMath.x);

}

void TileManager::updateTileMoving(sf::Vector2f moveTile, int i)
{
	//Moves tile
	//Called in for loop for all tiles
	this->tiles[i]->sprite_tile.move(this->movement);

	//Debug info
	//std::cout << "Move X: " << this->movement.x << "\n";
	//std::cout << "Move Y: " << this->movement.y << "\n";
	//std::cout << "Math x: " << this->TileMovingMath.x << "\n";
}

void TileManager::updateTileNewPositiong(int i, sf::Vector2f playerPos)
{
	/*
	* Just moves tile back and forth so theres never not a tile as background
	*/

		//TOP
	if (playerPos.y <= this->tiles[this->BorderTiles[0] + 2]->sprite_tile.getPosition().y)
	{
		//std::cout << "TOP BORDER -1 Reached!\n";
		for (size_t i = 0; i < this->tiles.size(); i++)
		{
			this->tiles[i]->sprite_tile.move(0.f, -10.f);
		}
	}
	//BOTTOM
	if (playerPos.y >= this->tiles[this->BorderTiles[1] - 2]->sprite_tile.getPosition().y)
	{
		//std::cout << "BOTTOM BORDER - 1 Reached!\n";
		for (size_t i = 0; i < this->tiles.size(); i++)
		{
			this->tiles[i]->sprite_tile.move(0.f, 10.f);
		}
	}

	//LEFT
	if (playerPos.x <= this->tiles[this->BorderTiles[2] + 2]->sprite_tile.getPosition().x)
	{
		//std::cout << "LEFT BORDER -1 Reached!\n";
		for (size_t i = 0; i < this->tiles.size(); i++)
		{
			this->tiles[i]->sprite_tile.move(-10.f, 0.f);
		}
	}
	//RIGHT
	if (playerPos.x >= this->tiles[this->BorderTiles[3] - 2]->sprite_tile.getPosition().x)
	{
		//std::cout << "RIGHT BORDER -1 Reached!\n";
		for (size_t i = 0; i < this->tiles.size(); i++)
		{
			this->tiles[i]->sprite_tile.move(10.f, 0.f);
		}
	}
}

void TileManager::updateScreenShakeChecker()
{
	if (this->Time_ScreenShake > 0.f)
	{
		this->ScreenShake = true;
		this->Time_ScreenShake = this->Time_ScreenShake - 1.f;
		//std::cout << "Time: " << this->Time_ScreenShake << "\nScreenShake bool: " << this->ScreenShake << "\n";
	}
	else
	{
		this->ScreenShake = false;
		this->Time_ScreenShake = 0.f;
	}
}

void TileManager::updateScreenShake(int i)
{
	if (this->ScreenShake)
	{
		if (this->leftScreenShake)
		{
			this->tiles[i]->sprite_tile.move(-this->ScreenShakeStrength, this->ScreenShakeStrength);
		}
		else
		{
			this->tiles[i]->sprite_tile.move(this->ScreenShakeStrength, -this->ScreenShakeStrength);
		}
	}
	else
		return;
}

void TileManager::update(sf::Vector2f moveTile, sf::Vector2f playerPos)
{
	this->updateScreenShakeChecker();
	if (!this->ScreenShake)
	{
		for (size_t i = 0; i < this->tiles.size(); i++)
		{
			this->updateTileMovingMath(moveTile);
			this->updateTileMoving(moveTile, i);
			this->updateTileNewPositiong(i, playerPos);
			this->tiles[i]->update();
		}
	}
	else
	{
		this->leftScreenShake = !this->leftScreenShake;
		for (size_t i = 0; i < this->tiles.size(); i++)
		{
			this->updateTileMovingMath(moveTile);
			this->updateTileMoving(moveTile, i);
			this->updateTileNewPositiong(i, playerPos);
			this->updateScreenShake(i);
			this->tiles[i]->update();
		}
	}
}

void TileManager::render(sf::RenderTarget& target)
{
	for (size_t i = 0; i < this->tiles.size(); i++)
	{
		target.draw(this->tiles[i]->sprite_tile);
	}
}
