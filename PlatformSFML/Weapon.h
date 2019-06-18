#pragma once
#include "GameObject.h"
#include "Bullet.h"

class Weapon :
	public GameObject
{
public:
	bool invisible = false;
	bool isShooting = false;
	sf::Clock cooldown;
	int maxAmmo, ammo, minDps, maxDps, shootFactor;
	float cooldownTime;
	sf::Vector2f bulletVel;
	Direction dir;
	Weapon(int maxAmmo, int ammo, sf::Vector2f vel, int minDps, int maxDps, float cooldownTime, int shootFactor);
	void shoot(std::vector <Bullet> &v, sf::Texture &bullet_texture);
	void addAmmo(int newAmmo);
};

