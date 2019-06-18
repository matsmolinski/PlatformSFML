#include "Character.h"
#include <iostream>

Character::Character(int HP, int texture_code)
	: HP(HP)
	, maxHP(HP)
	, texture_code(texture_code)
{}

Character::Character(int HP, int maxHP, int texture_code)
	: HP(HP)
	, maxHP(maxHP)
	, texture_code(texture_code)
{}

void Character::setHP(int newHP)
{
	if (newHP < 0) HP = 0;
	else if (newHP <= maxHP) HP = newHP;
}

int Character::getHP()
{
	return HP;
}

void Character::setMaxHP(int newHP)
{
	maxHP = newHP;
}

int Character::getMaxHP()
{
	return maxHP;
}

void Character::moveMe(int x, int y)
{
	move(x, y);
	if (currentWeapon != nullptr)
		currentWeapon->move(x, y);
}

void Character::changeDir(Direction dir)
{
	currentDir = dir;
	if (currentWeapon != nullptr)
		currentWeapon->dir = dir;
}

int Character::moveCharacter(ObjectType ** physicTable, int height, int width)
{
	int textureValue = 0;
	bool isApproaching = false;
	if (!isYLevelTaken(sprite.getPosition().y + sprite.getOrigin().y + 1, physicTable, height, width)) {
		isStanding = false;

	}
	

	if (vel.x < 0) {
		isMoving = true;
		if (vel.x < -50) {
			if (!isXLevelTaken(sprite.getPosition().x - sprite.getOrigin().x - 6, physicTable, height, width)) {
				moveMe(-6, 0);
				vel.x += 6;
			}
			else isApproaching = true;
		}
		if (vel.x < -10 || isApproaching) {
			if (!isXLevelTaken(sprite.getPosition().x - sprite.getOrigin().x - 4, physicTable, height, width)) {
				moveMe(-4, 0);
				vel.x += 4;
			}
			else isApproaching = true;
		}
		if (vel.x >= -10 || isApproaching) {
			if (!isXLevelTaken(sprite.getPosition().x - sprite.getOrigin().x - 1, physicTable, height, width)) {
				moveMe(-1, 0);
				vel.x += 1;
			}
			else vel.x = 0;
		}
		if (isStanding) {
			if (currentMod % 14 == 0) {
				if (currentDir == LEFT) textureValue = 3;
				else textureValue = 4;
			}
			if (currentMod % 14 == 7) {
				if (currentDir == LEFT) textureValue = 5;
				else textureValue = 6;
			}
			currentMod++;
		}
	}

	else if (vel.x > 0) {
		isMoving = true;
		if (vel.x > 50) {
			if (!isXLevelTaken(sprite.getPosition().x + sprite.getOrigin().x + 6, physicTable, height, width)) {
				moveMe(6, 0);
				vel.x -= 6;
			}
			else isApproaching = true;
		}
		if (vel.x > 10 || isApproaching) {
			if (!isXLevelTaken(sprite.getPosition().x + sprite.getOrigin().x + 4, physicTable, height, width)) {
				moveMe(4, 0);
				vel.x -= 4;
			}
			else isApproaching = true;
		}
		if (vel.x <= 10 || isApproaching) {
			if (!isXLevelTaken(sprite.getPosition().x + sprite.getOrigin().x + 1, physicTable, height, width)) {
				moveMe(1, 0);
				vel.x -= 1;
			}
			else vel.x = 0;
		}
		if (isStanding) {
			if (currentMod % 14 == 0) {
				if (currentDir == LEFT) textureValue = 3;
				else textureValue = 4;
			}
			if (currentMod % 14 == 7) {
				if (currentDir == LEFT) textureValue = 5;
				else textureValue = 6;
			}
			currentMod++;
		}
	}
	else if (isMoving && isStanding) {
		if (currentDir == LEFT) textureValue = 1;
		else textureValue = 2;
		isMoving = false;
		currentMod = 0;
	}
	isApproaching = false;

	if (!isStanding && vel.y >= 0) {
		if (vel.y > 130) {
			if (!isYLevelTaken(sprite.getPosition().y + sprite.getOrigin().y + 10, physicTable, height, width)) {
				moveMe(0, 10);
				vel.y += 10;
			}
			else isApproaching = true;
			
		}
		if ((vel.y > 80 && vel.y <= 130) || isApproaching) {
			if (!isYLevelTaken(sprite.getPosition().y + sprite.getOrigin().y + 8, physicTable, height, width)) {
				moveMe(0, 8);
				vel.y += 8;
				isApproaching = false;
			}
			else isApproaching = true;
		}
		if ((vel.y > 30 && vel.y <= 80) || isApproaching) {
			if (!isYLevelTaken(sprite.getPosition().y + sprite.getOrigin().y + 6, physicTable, height, width)) {
				moveMe(0, 6);
				vel.y += 6;
				isApproaching = false;
			}
			else isApproaching = true;
		}
		if ((vel.y > 10 && vel.y <= 30) || isApproaching) {
			if (!isYLevelTaken(sprite.getPosition().y + sprite.getOrigin().y + 4, physicTable, height, width)) {
				moveMe(0, 4);
				vel.y += 4;
				isApproaching = false;
			}
			else isApproaching = true;
			
		}
		if (vel.y <= 10 || isApproaching) {
			if (!isYLevelTaken(sprite.getPosition().y + sprite.getOrigin().y + 1, physicTable, height, width)) {
				moveMe(0, 1);
				vel.y += 1;
			}
			else {
				isStanding = true;
				vel.y = 0;
			}
			
		}
		isApproaching = false;
	}
	else if (vel.y < 0) {

		if (vel.y < -130) {
			if (!isYLevelTaken(sprite.getPosition().y - sprite.getOrigin().y - 10, physicTable, height, width)) {
				moveMe(0, -10);
				vel.y += 10;
			}
			else isApproaching = true;

		}
		if ((vel.y < -80 && vel.y >= -130) || isApproaching) {
			if (!isYLevelTaken(sprite.getPosition().y - sprite.getOrigin().y - 8, physicTable, height, width)) {
				moveMe(0, -8);
				vel.y += 8;
				isApproaching = false;
			}
			else isApproaching = true;
		}
		if ((vel.y < -30 && vel.y >= -80) || isApproaching) {
			if (!isYLevelTaken(sprite.getPosition().y - sprite.getOrigin().y - 6, physicTable, height, width)) {
				moveMe(0, -6);
				vel.y += 6;
				isApproaching = false;
			}
			else isApproaching = true;
		}
		if ((vel.y < -10 && vel.y >= -30) || isApproaching) {
			if (!isYLevelTaken(sprite.getPosition().y - sprite.getOrigin().y - 4, physicTable, height, width)) {
				moveMe(0, -4);
				vel.y += 4;
				isApproaching = false;
			}
			else isApproaching = true;

		}
		if (vel.y >= -10 || isApproaching) {
			if (!isYLevelTaken(sprite.getPosition().y - sprite.getOrigin().y - 1, physicTable, height, width)) {
				moveMe(0, -1);
				vel.y += 1;
			}
			else vel.y = 0;

		}
		isApproaching = false;

	}

	if (!isStanding && isChangingDir) {
		if (currentDir == LEFT) textureValue = 5;
		else textureValue = 6;
	}
	return textureValue;
}

bool Character::isYLevelTaken(int checkingY, ObjectType ** physicTable, int height, int width)
{
	if (checkingY < 0 || checkingY >= height) return true;
	for (int x = sprite.getPosition().x - sprite.getOrigin().x; x < sprite.getPosition().x + sprite.getOrigin().x; x++)
		if (physicTable[x][checkingY]) return true;
	return false;
}

bool Character::isXLevelTaken(int checkingX, ObjectType ** physicTable, int height, int width)
{
	if (checkingX < 0 || checkingX >= width) return true;
	for (int y = sprite.getPosition().y - sprite.getOrigin().y; y < sprite.getPosition().y + sprite.getOrigin().y; y++)
		if (physicTable[checkingX][y] > 0) return true;
	return false;
}

bool Character::canGoLeft(ObjectType ** physicTable, int height, int width)
{
	if (isXLevelTaken(getPosition().x - getOrigin().x - 1, physicTable, height, width))
		return false;
	moveMe(-30, 0);
	if (!isYLevelTaken(getPosition().y + getOrigin().y + 1, physicTable, height, width)) {
		moveMe(30, 0);
		return false;
	}
	moveMe(30, 0);
	return true;
}

bool Character::canGoRight(ObjectType ** physicTable, int height, int width)
{
	if (isXLevelTaken(getPosition().x + getOrigin().x + 1, physicTable, height, width))
		return false;
	moveMe(30, 0);
	if (!isYLevelTaken(getPosition().y + getOrigin().y + 1, physicTable, height, width)) {
		moveMe(-30, 0);
		return false;
	}
	moveMe(-30, 0);
	return true;
}
