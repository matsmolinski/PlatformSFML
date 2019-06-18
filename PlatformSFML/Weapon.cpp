#include "Weapon.h"



Weapon::Weapon(int maxAmmo, int ammo, sf::Vector2f vel, int minDps, int maxDps, float cooldownTime, int shootFactor)
	: maxAmmo(maxAmmo)
	, ammo(ammo)
	, bulletVel(vel)
	, minDps(minDps)
	, maxDps(maxDps)
	, cooldownTime(cooldownTime)
	, shootFactor(shootFactor)
{}

void Weapon::shoot(std::vector <Bullet> &v, sf::Texture &bullet_texture)
{
	if (ammo > 0 && cooldown.getElapsedTime().asMilliseconds() > cooldownTime) {
		Bullet bullet;
		bullet.dps = (std::rand() % (maxDps - minDps + 1)) + minDps;
		bullet.vel.x = dir == LEFT ? - bulletVel.x : bulletVel.x;
		bullet.vel.y = bulletVel.y;
		bullet.setTexture(bullet_texture);
		bullet.setPosition(getPosition().x + (dir == LEFT ? -getOrigin().x : getOrigin().x), getPosition().y + shootFactor);
		v.push_back(bullet);
		ammo--;
		cooldown.restart();
	}
}

void Weapon::addAmmo(int newAmmo)
{
	ammo += newAmmo;
	if (ammo > maxAmmo) ammo = maxAmmo;
}

