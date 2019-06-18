#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include <time.h>
#include "GameObject.h"
#include "Level.h"
#include "LevelLoader.h"
#include "Character.h"
#include "screen_0.hpp"
//#include <vld.h>
using namespace sf;

int main()
{
	srand(time(NULL));
	std::vector<cScreen*> screens;
	int screen = 0;

	RenderWindow mainWindow(VideoMode(1366, 768, 32), "Testy");
	mainWindow.setMouseCursorVisible(false);

	screen_0 s0;
	screens.push_back(&s0);

//	screen_1 s1;
//	Screens.push_back(&s1);

	while (screen >= 0) {
		screen = screens[screen]->Run(mainWindow);
	}

	return EXIT_SUCCESS;
}