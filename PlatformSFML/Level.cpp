#include "Level.h"
#define PATH "textures/"



Level::Level(int x, int y)
{
	width = x;
	height = y;
	Image images[18];
	images[0].loadFromFile("textures/apple.jpg");
	images[1].loadFromFile("textures/bbrick.jpg");
	images[2].loadFromFile("textures/hero_stand_l.png");
	images[3].loadFromFile("textures/hero_stand_r.png");
	images[4].loadFromFile("textures/hero_walk_l.png");
	images[5].loadFromFile("textures/hero_walk_r.png");
	images[6].loadFromFile("textures/hero_run_l.png");
	images[7].loadFromFile("textures/hero_run_r.png");
	images[8].loadFromFile("textures/bullet01.png");
	images[9].loadFromFile("textures/weapon01_r.png");
	images[10].loadFromFile("textures/weapon01_l.png");
	images[11].loadFromFile("textures/npc_stand_l.png");
	images[12].loadFromFile("textures/npc_stand_r.png");
	images[13].loadFromFile("textures/npc_walk_l.png");
	images[14].loadFromFile("textures/npc_walk_r.png");
	images[15].loadFromFile("textures/npc_run_l.png");
	images[16].loadFromFile("textures/npc_run_r.png");
	images[17].loadFromFile("textures/bag.png");
	for (int i = 0; i < 18; i++)
		images[i].createMaskFromColor(Color(255, 0, 255), 0);
	for (int i = 0; i < 18; i++) {
		textures[i].loadFromImage(images[i]);
		textures[i].setSmooth(true);
	}
		
	physicTable = new ObjectType* [x];
	for (int i = 0; i < width; i++) {
		physicTable[i] = new ObjectType [height];
		for (int j = 0; j < height; j++) {
			physicTable[i][j] = AIR;
		}
	}
}


Level::~Level()
{
	for (int i = 0; i < width; i++)
		delete[] physicTable[i];
	delete[] physicTable;
}

void Level::freeSpace(Vector2f position, Vector2f origin)
{
	int x = position.x, y = position.y, xo = origin.x, yo = origin.y;
	for (int i = x - xo; i < x + xo; i++)
		for (int j = y - yo; j < y + yo; j++)
			physicTable[i][j] = AIR;
}

void Level::allocSpace(Vector2f position, Vector2f origin)
{
	int x = position.x, y = position.y, xo = origin.x, yo = origin.y;
	for (int i = x - xo; i < x + xo; i++)
		for (int j = y - yo; j < y + yo; j++)
			physicTable[i][j] = CHARACTER;
}

void Level::changeCharacterTexture(int character_index, int tex_index)
{
	characters[character_index].setTexture(textures[tex_index]);
}

void Level::changeWeaponTexture(int weapon_index, int tex_index)
{
}

int Level::containsIB(int x, int y)
{
	for (int i = 0; i < IBs.size(); i++)
		if (IBs[i].sprite.getGlobalBounds().contains(x, y))
			return i;
	return IBs.size();
}
