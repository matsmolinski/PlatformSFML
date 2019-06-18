#include "GameObject.h"




void GameObject::setTexture(sf::Texture &t)
{
	sprite.setTexture(t);
}

void GameObject::setOrigin(float x, float y)
{
	sprite.setOrigin(x, y);
}

void GameObject::setOrigin(sf::Vector2f vec)
{
	sprite.setOrigin(vec);
}

void GameObject::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void GameObject::setPosition(sf::Vector2f vec)
{
	sprite.setPosition(vec);
}

void GameObject::move(float x, float y)
{
	sprite.move(x, y);
}

void GameObject::move(sf::Vector2f vec)
{
	sprite.move(vec);
}

sf::Vector2f GameObject::getPosition()
{
	return sprite.getPosition();
}


sf::Vector2f GameObject::getOrigin()
{
	return sprite.getOrigin();
}
