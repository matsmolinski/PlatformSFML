#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Block.h"
#include "Weapon.h"
#include "Bullet.h"
#include "InteractiveBackground.h"
using namespace sf;

class Level
{
public:
	int height;
	int width;
public:
	ObjectType ** physicTable;
	Texture textures[18];
	std::vector <Character> characters;
	std::vector <Block> blocks;
	std::vector <Weapon> weapons;
	std::vector <Bullet> bullets;
	std::vector <InteractiveBackground> IBs;
	Level(int x, int y);
	~Level();
	void freeSpace(Vector2f position, Vector2f origin);
	void allocSpace(Vector2f position, Vector2f origin);
	void changeCharacterTexture(int character_index, int tex_index);
	void changeWeaponTexture(int weapon_index, int tex_index);
	int containsIB(int x, int y);
};

