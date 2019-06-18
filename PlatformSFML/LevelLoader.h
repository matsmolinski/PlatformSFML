#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include <fstream>
using namespace sf;

class LevelLoader
{
public:
	static void loadLevel(std::fstream &in, Level &level);
};

