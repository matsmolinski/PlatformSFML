#include "LevelLoader.h"
#include <iostream>

void LevelLoader::loadLevel(std::fstream &in, Level &level)
{
	while (!in.eof()) {
		std::string type;
		int xo, yo, x, y;
		in >> type >> xo >> yo >> x >> y;
		if (type == "hero") {
			int HP, maxHP;
			in >> HP >> maxHP;
			Character character(HP, maxHP, 1);
			character.setTexture(level.textures[3]);
			character.setOrigin(xo, yo);
			character.setPosition(x, y);
			for (int i = x - xo; i < x + xo; i++)
				for (int j = y - yo; j < y + yo; j++)
					level.physicTable[i][j] = CHARACTER;
			level.characters.insert(level.characters.begin() , character);
		}

		if (type == "npc") {
			int HP, maxHP;
			in >> HP >> maxHP;
			Character character(HP, maxHP, 10);
			character.setTexture(level.textures[12]);
			character.setOrigin(xo, yo);
			character.setPosition(x, y);
			character.isGoingRight = true;
			for (int i = x - xo; i < x + xo; i++)
				for (int j = y - yo; j < y + yo; j++)
					level.physicTable[i][j] = CHARACTER;
			level.characters.push_back(character);
		}

		if (type == "block") {
			Block block;
			block.setTexture(level.textures[1]);
			block.setOrigin(xo, yo);
			block.setPosition(x, y);
			for (int i = x - xo; i < x + xo; i++)
				for (int j = y - yo; j < y + yo; j++)
					level.physicTable[i][j] = BLOCK;
			level.blocks.push_back(block);
		}
		
		if (type == "weapon") {
			int ammo, maxAmmo, velX, velY, minDps, maxDps, shootFactor;
			float coolTime;
			in >> ammo >> maxAmmo >> velX >> velY >> minDps >> maxDps >> coolTime >> shootFactor;
			Weapon weapon(maxAmmo, ammo, sf::Vector2f(velX, velY), minDps, maxDps, coolTime, shootFactor);
			weapon.setTexture(level.textures[9]);
			weapon.setOrigin(xo, yo);
			weapon.setPosition(x, y);
			level.weapons.push_back(weapon);
		}
	}
	
	for (int i = 0; i < level.weapons.size(); i++)
		for (int j = 0; j < level.characters.size(); j++)
			if (level.weapons[i].getPosition() == level.characters[j].getPosition()) {
				level.characters[j].currentWeapon = &level.weapons[i];
				break;
			}
}
