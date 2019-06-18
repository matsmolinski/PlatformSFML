#pragma once
#include <SFML/Graphics.hpp>

enum ObjectType {
	AIR, CHARACTER, BLOCK
};

enum Direction {
	LEFT, RIGHT
};

class GameObject
{
public:
	bool touchable = true;
	sf::Vector2f vel = sf::Vector2f(0, 0);
	sf::Sprite sprite;
	void setTexture(sf::Texture &t);
	void setOrigin(float x, float y);
	void setOrigin(sf::Vector2f vec);
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f vec);
	void move(float x, float y);
	void move(sf::Vector2f vec);
	sf::Vector2f getPosition();
	sf::Vector2f getOrigin();
};

