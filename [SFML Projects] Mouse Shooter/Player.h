#pragma once

//#include"Bullet.h"
#include"Aiming.h"
#include"bloom.h"
#include<string>
#include<sstream>

class Player
{
private:
	//Player
	sf::Sprite sprite;
	sf::RectangleShape shape_hitbox; // Used for window bounds collision

	//Textures
	sf::Texture Texture_Player;
	sf::Texture t_Bloom;
	sf::Texture Texture_bullets;

		//Variables for Aiming
		sf::Vector2f playerCenter;
		float PlayerAngle;

		int opacity;

	//Shooting
	//float ShootCDMAX;
	//float ShootCD;

	//Game Logic
	float PlayerHPMax;
	float PlayerHP;
	float HPMaxUpdate;
	float HPUpdate;

	//player move variables
	float playerMoveSpeed;

	//HP Bar
	sf::RectangleShape redHPBar;
	sf::RectangleShape backgroundHPBar;
	float HPBarx;
	sf::Text Text_HP;

	//Movement stuff
	sf::Vector2f tileMove;
	sf::Vector2f playerMove;

	//Initialization
	void initVariables();
	void initTextures();
	void initHPBar();
	void initText(sf::Font& font);
	void initHitBoxShape();
	void initPlayerBloom();
public:
	Player(sf::Font& font);
	virtual ~Player();

	//Aim System
	Aiming aimSys;

	//Player Bloom
	Bloom* bloom;

	//Bullet
	//std::vector<Bullet*> bullets;

	//Accessors
	const sf::Vector2f& getCenterOfPlayer() const;
	const sf::Vector2f& getPos() const;
	const sf::FloatRect& getBounds() const;
	const float& getHPMax() const;
	const float& getHP() const;
	const sf::Vector2f& getTileMove() const;
	const sf::Vector2f& getPlayerMovement() const;
	const float& getRotationAngle() const;
	const float& getPlayerMoveSpeed() const;

	//Modifiers
	void TakeDamage(float dmg);
	void addMaxHP(float add);
	void addHP(float add);
	void changeHP(float change);
	void addPlayerMoveSpeed(float add);
	void changePlayerMoveSpeed(float change);

	//Update
	void updateAimSystem(sf::Vector2f& MousePos);
	void updatePlayerMovement();
	void updateWindowBoundCollision(const sf::Vector2u& winSize);
	//void updateShooting(const sf::Vector2u& winSize, sf::Vector2f BulletSpawn);
	void updateHPBar();
	void updateText();
	void update(sf::Vector2f& MousePos, const sf::Vector2u& winSize, sf::Vector2f BulletSpawn);

	//Rendering
	//void renderBullets(sf::RenderTarget& target);
	void renderHitbox(sf::RenderTarget& target);
	void renderPlayer(sf::RenderTarget& target);
	void renderHPBar(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

