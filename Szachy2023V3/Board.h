#pragma once
#include "SFML/Graphics.hpp"
#include "Piece.h"
#include <iostream>
#include "MoveLog.h"
#include "AssetsPath.h"
using namespace std;


class Board {
public :
	Board();
public :
	Piece* getPiece(int row, int col);
	Piece* getPiece(field_t field);
	void setPiece(Piece* piece, field_t field);
public :
	
	string boardPath = assetsPath.concatenate("images\\chessboard.png");
	sf::Sprite sprite;
	sf::Texture texture;
    Piece* fields[8][8] = { nullptr };

};