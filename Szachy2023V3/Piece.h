#pragma once
#include "SFML/Graphics.hpp"
#include "global.h"
class Piece {
public :
	Piece(bool color, int type, int x, int y, sf::Sprite sprite);

public :
	sf::Sprite sprite;
	sf::Vector2f stablePosition;

public :
	int type;
	bool isPickedUp;
	bool color;
	bool isPlaying = true;
	int timesMoved = 0;

public :
	sf::Vector2f getPosition();
	field_t getPosAsField();
	void setStablePosition(sf::Vector2f newPos);
	void setStablePosition(field_t field);
	field_t getStablePositionAsField();
	void setPosition(sf::Vector2f newPos);
	void setPosition(field_t field);
	sf::Sprite getSpriteCopy();
};