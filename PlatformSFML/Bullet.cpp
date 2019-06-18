#include "Bullet.h"
#include <iostream>


bool Bullet::moveBullet(int height, int width)
{
	move(vel.x / 60, vel.y / 60);
	if (getPosition().x < 0 || getPosition().x >= width || getPosition().y < 0 || getPosition().y >= height)
		return true;
	return false;
}

ObjectType Bullet::hitObject(ObjectType ** physicTable, int height, int width)
{
	if (physicTable[(int)sprite.getPosition().x][(int)sprite.getPosition().y]) {
		if (physicTable[(int)sprite.getPosition().x][(int)sprite.getPosition().y] == CHARACTER)
			return CHARACTER;
		if (physicTable[(int)sprite.getPosition().x][(int)sprite.getPosition().y] == BLOCK)
			return BLOCK;
	}
	else return AIR;
}

bool Bullet::isNotTransparent(sf::Sprite &character)
{
	if (character.getGlobalBounds().contains(getPosition())) {
		sf::Image character_img = character.getTexture()->copyToImage();
		for (int l = 0, x = getPosition().x - (character.getPosition().x - character.getOrigin().x);
			x >= 0 && x < 2 * character.getOrigin().x && l < abs(vel.x); vel.x < 0 ? x++, l++ : x--, l++)
			if (character_img.getPixel(x, getPosition().y - (character.getPosition().y - character.getOrigin().y)).a != 0)
				return true;
		}
	return false;
}

