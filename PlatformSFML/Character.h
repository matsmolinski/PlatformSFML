#pragma once
#include "GameObject.h"
#include "Weapon.h"

class Character :
	public GameObject
{
protected:
	int HP;
	int maxHP;
	int frameCounter = 0;
public:
	int texture_code;
	bool isChangingDir = false;
	bool isStanding = true;
	bool isGoingLeft = false;
	bool isGoingRight = false;
	bool isMoving = false;
	bool isAiming = false;
	int currentMod = 0;
	Direction prevDir = RIGHT;
	Direction currentDir = RIGHT;
	Weapon * currentWeapon = nullptr;
	Character(int HP, int texture_code);
	Character(int HP, int maxHP, int texture_code);
	void setHP(int newHP);
	int getHP();
	void setMaxHP(int newHP);
	int getMaxHP();
	void moveMe(int x, int y);
	void changeDir(Direction dir);
	int moveCharacter(ObjectType ** physicTable, int height, int width);
	bool isYLevelTaken(int checkingY, ObjectType ** physicTable, int height, int width);
	bool isXLevelTaken(int checkingX, ObjectType ** physicTable, int height, int width);
	bool canGoLeft(ObjectType ** physicTable, int height, int width);
	bool canGoRight(ObjectType ** physicTable, int height, int width);
};

