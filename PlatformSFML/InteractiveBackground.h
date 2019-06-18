#pragma once
#include "GameObject.h"
class InteractiveBackground :
	public GameObject
{
public:
	bool isMerchant = false;
//	std::vector <Item> items;
	int ammo = 0;
};

