#include "Weapon.h"

void Weapon::initVariables()
{
	this->MaxAmmo = 10;
	this->CurrAmmo = this->MaxAmmo;

	this->ReloadTimerMax = 120.f;
	this->ReloadTimer = 0.f;

	this->BulletSpeed = 25.f;
}

void Weapon::initTexture()
{
	if (!this->texture_weapon.loadFromFile("Textures/weapons/standart/weapon0.png"))
		std::cout << " - ERROR::WEAPON::INITTEXTURE::Couldn't load texture: standart/weapon0.png!\n";
	std::cout << "Standart Weapon!\n";
}

void Weapon::initSprite(sf::Vector2f spawningPos)
{
	this->sprite_weapon.setTexture(this->texture_weapon);
	this->sprite_weapon.scale(0.3f, 0.3f);

	sf::FloatRect rect_weapon = this->sprite_weapon.getLocalBounds();

	this->sprite_weapon.setOrigin(rect_weapon.left + rect_weapon.width / 5.f, rect_weapon.top + rect_weapon.height / 2.f);

	this->sprite_weapon.setPosition(spawningPos);
	//std::cout << "YES";
}

Weapon::Weapon()
{
	//Standart constructor
}

Weapon::Weapon(sf::Vector2f spawningPos)
{
	//If bug occured you still see the standart weapon
	//Or just for testing
	this->initVariables();
	this->initTexture();
	this->initSprite(spawningPos);
}

Weapon::~Weapon()
{

}

sf::Vector2f& Weapon::getBulletSpawn()
{
	sf::Vector2f spawn = sf::Vector2f(this->sprite_weapon.getPosition().x , this->sprite_weapon.getPosition().y);
	return spawn;
}

//Modifiers
void Weapon::ModifyMaxAmmo(float MaxAmmo)
{
	this->MaxAmmo = MaxAmmo;
}

void Weapon::ModifyReloadTimerMax(float ReloadTimerMax)
{
	this->ReloadTimerMax = ReloadTimerMax;
}

void Weapon::ModifyBulletSpeed(float BulletSpeed)
{
	this->BulletSpeed = BulletSpeed;
}

void Weapon::updateWeaponRotation(float RotationAngle)
{
	this->sprite_weapon.setRotation(RotationAngle);
}

void Weapon::updateWeaponPosition(sf::Vector2f pos)
{
	this->sprite_weapon.setPosition(pos);
}

void Weapon::update(float RotationAngle, sf::Vector2f pos)
{
	this->updateWeaponRotation(RotationAngle);
	this->updateWeaponPosition(pos);
}

void Weapon::renderWeapon(sf::RenderTarget& target)
{
	target.draw(this->sprite_weapon);
}

void Weapon::render(sf::RenderTarget& target)
{
	this->renderWeapon(target);
}
