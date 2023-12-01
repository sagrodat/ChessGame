#pragma once
#include "SFML/Graphics.hpp"
#include "Pieces.h"
#include "Board.h"
#include "global.h"
#include "sfmlObjects.h"
#include "ChessGame.h"
#include "utilityFunctions.h"

class myMouse :public sf::Mouse{

public :
	Piece* isInBoundsOfPiece();
	field_t getPosAsField();

public :
	sf::Vector2f mousePieceDelta;
};
inline myMouse mouse;