#pragma once

#include"Bullet.h"
#include<string>
#include<sstream>

class Player
{
private:
	//Player
	sf::Sprite sprite;
	sf::RectangleShape shape_hitbox; // Used for window bounds collision
	//Vectors for aiming
	sf::Vector2f playerCenter;
	sf::Vector2f mousePosWindow;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;
	float PlayerAngle;


	//Textures
	sf::Texture Texture_Player;
	sf::Texture Texture_bullets;

	//Shooting
	float ShootCDMAX;
	float ShootCD;

	//Game Logic
	float PlayerHPMax;
	float PlayerHP;
	float HPUpdate;

	//HP Bar
	sf::RectangleShape redHPBar;
	sf::RectangleShape backgroundHPBar;
	float HPBarx;
	sf::Text Text_HP;

	//For tiles movement
	sf::Vector2f tileMove;

	//Initialization
	void initVariables();
	void initTextures();
	void initHPBar();
	void initText(sf::Font& font);
	void initHitBoxShape();
public:
	Player(sf::Font& font);
	virtual ~Player();

	//Bullet
	std::vector<Bullet*> bullets;

	//Accessors
	const sf::Vector2f& getCenterOfPlayer() const;
	const sf::Vector2f& getPos() const;
	const sf::FloatRect& getBounds() const;
	const float& getHP() const;
	const sf::Vector2f& getTileMove() const;
	const float& getRotationAngle() const;

	//Modifiers
	void TakeDamage(float dmg);
	void addHP(float add);
	void changeHP(float change);

	//Update
	void updateAimDirections(sf::Vector2f& MousePos);
	void updatePlayerMovement();
	void updateWindowBoundCollision(const sf::Vector2u& winSize);
	void updateShooting(const sf::Vector2u& winSize, sf::Vector2f BulletSpawn);
	void updateHPBar();
	void updateText();
	void update(sf::Vector2f& MousePos, const sf::Vector2u& winSize, sf::Vector2f BulletSpawn);

	//Rendering
	void renderBullets(sf::RenderTarget& target);
	void renderHitbox(sf::RenderTarget& target);
	void renderPlayer(sf::RenderTarget& target);
	void renderHPBar(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

