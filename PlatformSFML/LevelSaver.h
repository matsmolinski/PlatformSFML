#pragma once
#include "Level.h"
#include <fstream>

class LevelSaver
{
public:
	static int saveLevel(std::fstream &out, Level &level);
};

