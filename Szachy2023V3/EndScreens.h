#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "AssetsPath.h"

class EndScreens
{
public :
	EndScreens();
public :
	typedef struct endScreen {
		std::string path;
		sf::Texture texture;
		sf::Sprite sprite;
	}screen_t;

	screen_t whiteWins;
	screen_t blackWins;
	screen_t draw;

	int newGameX = 325;
	int newGameY = 400;
	int newGameWidth = 150;
	int newGameHeight = 50;
public :
	void createEndScreens();
};
