#pragma once
#include "cScreen.h"
#include "LevelSaver.h"
using namespace sf;

class screen_0 : public cScreen
{
public:
	screen_0();
	virtual int Run(sf::RenderWindow &mainWindow);
};

screen_0::screen_0() {}

int screen_0::Run(sf::RenderWindow &mainWindow)
{

	Level level(3000, 768);
	View game(Vector2f(500, 500), Vector2f(1366, 768));
	game.setViewport(FloatRect(0, 0, 1.f, 1.f));
	game.setSize(1366, 768);
	game.setCenter(683, 384);
	//game.zoom(0.4f);
	//game.rotate(180);
	mainWindow.setView(game);
	mainWindow.setVerticalSyncEnabled(true);
	//mainWindow.setFramerateLimit(2);
	int visR = 1366;
	int visL = 0;
	int fpsCounter = 0;
	std::fstream tlevel("levels/testlevel.lvl");
	//std::fstream tlevel("levels/testLevel2.lvl");
	LevelLoader::loadLevel(tlevel, level);
	Character* hero = &level.characters[0];
	Text fps, ammo;
	Font font;
	if (!font.loadFromFile("font.ttf"))
		return -1;
	fps.setFont(font);
	fps.setCharacterSize(24);
	fps.setFillColor(Color::Red);
	fps.setPosition(0, 744);
	ammo.setFont(font);
	ammo.setCharacterSize(24);
	ammo.setFillColor(Color::Red);
	ammo.setPosition(0, 0);
	Clock fpsClock;
	while (mainWindow.isOpen())
	{
		//events
		Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
				mainWindow.close();

			if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				mainWindow.close();

			if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
				hero->isGoingLeft = true;
				if (hero->currentDir == RIGHT) {
					hero->changeDir(LEFT);
					hero->isChangingDir = true;
				}
			}

			if (event.type == Event::KeyReleased  && event.key.code == sf::Keyboard::Left) {
				hero->isGoingLeft = false;
			}

			if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
				hero->isGoingRight = true;
				if (hero->currentDir == LEFT) {
					hero->changeDir(RIGHT);
					hero->isChangingDir = true;
				}
			}

			if (event.type == Event::KeyReleased  && event.key.code == sf::Keyboard::Right) {
				hero->isGoingRight = false;
			}

			if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
				if (hero->isStanding)
					hero->vel.y = -150;
				hero->isStanding = false;
				hero->isMoving = true;
				if (hero->currentDir == LEFT) level.changeCharacterTexture(0, 6);
				else level.changeCharacterTexture(0, 7);
				std::cout << "x: " << hero->getPosition().x << "y: " << hero->getPosition().y << std::endl;
			}

			if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
				hero->currentWeapon->isShooting = true;
			}

			if (event.type == Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
				hero->currentWeapon->isShooting = false;
			}

			if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::E) {
				for (int y = hero->getPosition().y + hero->getOrigin().y; y > hero->getPosition().y - hero->getOrigin().y; y -= 10) {
					int index = level.containsIB(hero->getPosition().x, y);
					if (index != level.IBs.size()) {
						hero->currentWeapon->addAmmo(level.IBs[index].ammo);
						level.IBs.erase(level.IBs.begin() + index);
						break;
					}

				}

			}

			if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::S) {
				std::fstream out("levels/testLevel2.lvl", std::ios::out);
				LevelSaver::saveLevel(out, level);
				out.close();
			}
		}
		//logic
		//setting values of variables

		//hero movement interpretation
		if (hero->isGoingRight) {
			hero->vel.x += 10;
			if (hero->vel.x > 100) hero->vel.x = 100;
			std::cout << "x: " << hero->vel.x << "y: " << hero->getPosition().y << std::endl;

		}
		if (hero->isGoingLeft) {
			hero->vel.x -= 10;
			if (hero->vel.x < -100) hero->vel.x = -100;
			std::cout << "x: " << hero->getPosition().x << "y: " << hero->getPosition().y << std::endl;
		}

		//AI
		for (int i = 1; i < level.characters.size(); i++) {
			Character * character = &level.characters[i];
			int distanceY = hero->getPosition().y - character->getPosition().y;
			int distanceX = hero->getPosition().x - character->getPosition().x;
			if (abs(distanceY) < character->getOrigin().y && ((distanceX < 0 ? character->isGoingLeft : character->isGoingRight) || character->isAiming)) {
				if (character->isGoingRight) character->prevDir = RIGHT;
				if (character->isGoingLeft) character->prevDir = LEFT;
				character->isGoingRight = false;
				character->isGoingLeft = false;
				character->vel.x = 0;
				character->isAiming = true;
			}
			else if (character->isAiming) {
				character->isAiming = false;
				if (character->currentWeapon != nullptr)
					character->currentWeapon->isShooting = false;
				if (character->prevDir == LEFT)
					character->isGoingLeft = true;
				else
					character->isGoingRight = true;
			}

			if (character->isAiming) {
				if (character->currentWeapon != nullptr)
					character->currentWeapon->isShooting = true;
			}

			if (character->isGoingRight)
				if (!character->canGoRight(level.physicTable, level.height, level.width)) {
					character->changeDir(LEFT);
					character->isChangingDir = true;
					character->isGoingLeft = true;
					character->isGoingRight = false;
				}
			if (character->isGoingLeft)
				if (!character->canGoLeft(level.physicTable, level.height, level.width)) {
					character->changeDir(RIGHT);
					character->isChangingDir = true;
					character->isGoingLeft = false;
					character->isGoingRight = true;
				}
			if (character->isGoingRight) character->vel.x = 10;
			if (character->isGoingLeft) character->vel.x = -10;
		}
		//moving characters
		for (int i = 0; i < level.characters.size(); i++)
		{
			level.freeSpace(level.characters[i].getPosition(), level.characters[i].getOrigin());
			int tex_code = level.characters[i].moveCharacter(level.physicTable, level.height, level.width);
			if (tex_code)
				level.changeCharacterTexture(i, tex_code + level.characters[i].texture_code);
			if (level.characters[i].isChangingDir) {
				if (level.characters[i].currentWeapon != nullptr)
					if (level.characters[i].currentWeapon->dir == LEFT) level.characters[i].currentWeapon->setTexture(level.textures[10]);
					else level.characters[i].currentWeapon->setTexture(level.textures[9]);
			}
			level.characters[i].isChangingDir = false;
			level.allocSpace(level.characters[i].getPosition(), level.characters[i].getOrigin());

		}

		//moving camera
		if (hero->getPosition().x >= visR - 20) {
			game.move(10, 0);
			fps.move(10, 0);
			ammo.move(10, 0);
			visR += 10;
			visL += 10;
		}
		if (hero->getPosition().x <= visL + 20) {
			game.move(-10, 0);
			fps.move(-10, 0);
			ammo.move(-10, 0);
			visL -= 10;
			visR -= 10;
		}

		//shooting
		for (int i = 0; i < level.weapons.size(); i++)
			if (level.weapons[i].isShooting)
				level.weapons[i].shoot(level.bullets, level.textures[8]);

		//moving bullets
		for (int i = 0; i < level.bullets.size(); i++) {
			if (level.bullets[i].moveBullet(level.height, level.width)) {
				level.bullets.erase(level.bullets.begin() + i);
				i--;
				continue;
			}
			ObjectType hitObject = level.bullets[i].hitObject(level.physicTable, level.height, level.width);
			if (hitObject != AIR) {
				if (hitObject == BLOCK) {
					level.bullets.erase(level.bullets.begin() + i);
					i--;
					continue;
				}
				if (hitObject == CHARACTER)
					for (int j = 0; j < level.characters.size(); j++)
						if (level.bullets[i].isNotTransparent(level.characters[j].sprite)) {
							level.characters[j].setHP(level.characters[j].getHP() - level.bullets[i].dps);
							level.bullets.erase(level.bullets.begin() + i);
							i--;
							if (level.characters[j].getHP() == 0) {
								InteractiveBackground IB;
								if (level.characters[j].currentWeapon != nullptr) {
									level.characters[j].currentWeapon->invisible = true;
									level.characters[j].currentWeapon->isShooting = false;
									IB.ammo = level.characters[j].currentWeapon->ammo;
								}
								IB.setTexture(level.textures[17]);
								IB.setOrigin(25, 25);
								IB.setPosition(level.characters[j].getPosition().x, level.characters[j].getPosition().y +
									(level.characters[j].getOrigin().y - 25));
								level.IBs.push_back(IB);
								level.freeSpace(level.characters[j].getPosition(), level.characters[j].getOrigin());
								level.characters.erase(level.characters.begin() + j);
							}
							break;
						}
			}
		}

		//fps
		fpsCounter++;
		if (fpsClock.getElapsedTime().asSeconds() >= 1) {
			fps.setString("FPS: " + std::to_string(fpsCounter));
			fpsCounter = 0;
			fpsClock.restart();
		}

		//visual
		ammo.setString("Ammo: " + std::to_string(hero->currentWeapon->ammo) + "/" + std::to_string(hero->currentWeapon->maxAmmo));
		//ammo.setString("HP: " + std::to_string(level.characters[1].getHP()) + "/" + std::to_string(level.characters[1].getMaxHP()));
		mainWindow.setView(game);
		mainWindow.clear(Color::White);
		for (InteractiveBackground IB : level.IBs)
			mainWindow.draw(IB.sprite);
		for (Character ch : level.characters)
			mainWindow.draw(ch.sprite);
		for (Block b : level.blocks)
			mainWindow.draw(b.sprite);
		for (Weapon w : level.weapons)
			if (!w.invisible)
				mainWindow.draw(w.sprite);
		for (Bullet bl : level.bullets)
			mainWindow.draw(bl.sprite);
		mainWindow.draw(fps);
		mainWindow.draw(ammo);
		mainWindow.display();
	}
	return -1;

}
