#pragma once
#include "GameObject.h"


class Bullet :
	public GameObject
{
public:
	int dps;
	bool moveBullet(int height, int width);
	ObjectType hitObject(ObjectType ** physicTable, int height, int width);
	bool isNotTransparent(sf::Sprite &character);
};

