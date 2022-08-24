#include "Weapon.h"

void Weapon::initVariables()
{
	this->MaxAmmo = 10;
	this->CurrAmmo = this->MaxAmmo;
	this->AmmoSave = this->MaxAmmo;

	this->Reloading = false;
	this->ReloadTimerMax = 120.f;
	this->ReloadTimer = 0.f;

	this->ShootingPressed = false;
	this->BulletSpeed = 25.f;

	//Cooldown between each bullet
	this->ShootCDMAX = 2.f;
	this->ShootCD = this->ShootCDMAX;
	
	//damage bullets
	this->damageBullet = 1.f;
}

void Weapon::initTexture()
{
	if (!this->texture_weapon.loadFromFile("Textures/weapons/standart/weapon0.png"))
		std::cout << " - ERROR::WEAPON::INITTEXTURE::Couldn't load texture: standart/weapon0.png!\n";
	std::cout << "Standart Weapon!\n";
}

void Weapon::initBulletTexture()
{
	if (!this->Texture_bullets.loadFromFile("Textures/Player/Bullets/bullet0.png"))
	{
		std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: bullet0.png!\n";
	}
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

void Weapon::initTexts(sf::Vector2u& winSize, sf::Font& font)
{
	this->updateAmmoTextContent();

	this->Text_Ammo.setFont(font);
	this->Text_Ammo.setCharacterSize(44);
	this->Text_Ammo.setFillColor(sf::Color(255, 255, 255, 110));
	this->Text_Ammo.setOutlineThickness(5.f);
	this->Text_Ammo.setOutlineColor(sf::Color(0, 0, 0, 110));
	this->Text_Ammo.setPosition(
		10.f,
		winSize.y - this->Text_Ammo.getGlobalBounds().height - 10.f
	);
}

Weapon::Weapon()
{
	//Standart constructor
	this->initVariables();
}

Weapon::Weapon(sf::Vector2f spawningPos, sf::Vector2u& winSize, sf::Font& font)
{
	//If bug occured you still see the standart weapon
	//Or just for testing
	this->initVariables();
	this->initTexture();
	this->initSprite(spawningPos);
	this->initBulletTexture();
	this->initTexts(winSize, font);
}

Weapon::~Weapon()
{
	//Delete bullets
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets.erase(this->bullets.begin(), this->bullets.end());
	}
	// std::cout << "Bullets: " << this->bullets.size() << "\n";
}

void Weapon::shootBullet(sf::Vector2f& AimDiretionNormal)
{
	if (this->ShootingPressed)
	{
		sf::Vector2f currVelocity = AimDiretionNormal * this->BulletSpeed;

		sf::Vector2f spawn = this->sprite_weapon.getPosition();
		this->bullets.push_back(new Bullet(this->Texture_bullets, spawn, currVelocity));

		this->CurrAmmo--;
	}
	//For debugging
	//std::cout << "Bullets Vector size: " << this->bullets.size() << "\n";
}

//Reloads weapon untiö the weapon is fully loaded
void Weapon::ReloadWeapon()
{
	if (this->ReloadTimer < this->ReloadTimerMax && this->CurrAmmo < this->MaxAmmo)
	{
		this->ReloadTimer += 1.f;
		if (static_cast<int>(this->ReloadTimer) % (static_cast<int>(this->ReloadTimerMax) / this->MaxAmmo) == 0)
		{
			this->CurrAmmo++;
		}
	}
	else
	{
		this->ReloadTimer = 0.f;
		this->Reloading = false;
	}
}

//Accessors
const float& Weapon::getBulletDamage() const{
return this->damageBullet;
}

//Modifiers
void Weapon::ModifyMaxAmmo(int MaxAmmo)
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

void Weapon::ModifyBulletDamage(float BulletDamage){
this->damageBullet = BulletDamage;
}

void Weapon::addMaxAmmo(int add)
{
	this->MaxAmmo += add;
}

void Weapon::substractReloadTimerMax(float substract)
{
	this->ReloadTimerMax -= substract;
}

void Weapon::addBulletSpeed(float add)
{
	this->BulletSpeed += add;
}

void Weapon::addBulletDamage(float add)
{
	this->damageBullet += add;
}

void Weapon::updateAmmoTextContent()
{
	//Ammo
	//Text content
	std::stringstream ssAmmo;
	ssAmmo << this->CurrAmmo << "/" << this->MaxAmmo;
	this->Text_Ammo.setString(ssAmmo.str());
}

void Weapon::updateAmmoText()
{
	if (this->AmmoSave != this->CurrAmmo)
	{
		this->AmmoSave = this->CurrAmmo;

		this->updateAmmoTextContent();
	}
}

void Weapon::updateWeaponRotation(float RotationAngle)
{
	this->sprite_weapon.setRotation(RotationAngle);
}

void Weapon::updateWeaponPosition(sf::Vector2f pos)
{
	this->sprite_weapon.setPosition(pos);
}

//Deletes bullet once they're out of the screen
void Weapon::updateBulletOutOfScreen(sf::Vector2u& winSize, size_t& i)
{

	if (bullets[i]->sprite_bullet.getPosition().x < 0 ||
		bullets[i]->sprite_bullet.getPosition().x > winSize.x ||
		bullets[i]->sprite_bullet.getPosition().y < 0 ||
		bullets[i]->sprite_bullet.getPosition().y > winSize.y)
		this->bullets.erase(this->bullets.begin() + i);
}

void Weapon::updateBulletMoving(sf::Vector2u& winSize)
{
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i]->sprite_bullet.move(this->bullets[i]->currVelocity);
		this->updateBulletOutOfScreen(winSize, i);
	}
}

void Weapon::updateShootingSystem(sf::Vector2f& AimDiretionNormal)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->ShootingPressed = true;
	else
		this->ShootingPressed = false;

	if (this->ShootCD < this->ShootCDMAX)
	{
		//Increase cooldown timer
		this->ShootCD += 1.f;
	}
	else
	{
		if (!this->Reloading)
		{
			//Reset cooldown
			this->ShootCD = 0.f;
			this->shootBullet(AimDiretionNormal);

			//Checks if reloading is needed
			if (this->CurrAmmo <= 0)
				this->Reloading = true;
		}
		else
		{
			this->ReloadWeapon();
		}
	}
}

void Weapon::update(sf::Vector2u& winSize, float RotationAngle, sf::Vector2f pos, sf::Vector2f& AimDiretionNormal)
{
	this->updateWeaponRotation(RotationAngle);
	this->updateWeaponPosition(pos);
	this->updateShootingSystem(AimDiretionNormal);
	this->updateBulletMoving(winSize);
	this->updateAmmoText();
}

void Weapon::renderTexts(sf::RenderTarget& target)
{
	target.draw(this->Text_Ammo);
}

void Weapon::renderBullets(sf::RenderTarget& target)
{
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		target.draw(this->bullets[i]->sprite_bullet);
	}
}

void Weapon::renderWeapon(sf::RenderTarget& target)
{
	target.draw(this->sprite_weapon);
}

void Weapon::render(sf::RenderTarget& target)
{
	this->renderTexts(target);

	this->renderBullets(target);

	this->renderWeapon(target);
}
