#pragma once
#include "Piece.h"
#include "Board.h"
#include "PieceSpritesTextures.h"
#include "AssetsPath.h"

enum pieceTypes { king, queen, bishop, knight, rook, pawn };
enum colors {none = -1, black, white, draw};

class Pieces {

public :
	Pieces();
	void loadTextures();
	void setSpriteTextures();
	void initiatePieces();

public:
	//PieceSprites sprites;
	Piece* whiteRook1; Piece* whiteKnight1; Piece* whiteBishop1;Piece * whiteQueen;	Piece* whiteKing; Piece* whiteBishop2;	Piece* whiteKnight2;Piece* whiteRook2;
	Piece * whitePawn1;	Piece* whitePawn2; Piece* whitePawn3;	Piece* whitePawn4;	Piece* whitePawn5;	Piece* whitePawn6;	Piece* whitePawn7; Piece* whitePawn8;

	Piece* blackRook1; Piece* blackKnight1; Piece* blackBishop1; Piece* blackQueen; Piece* blackKing;	Piece* blackBishop2; Piece* blackKnight2; Piece* blackRook2;
	Piece* blackPawn1;Piece* blackPawn2;Piece* blackPawn3; Piece* blackPawn4; Piece* blackPawn5; Piece* blackPawn6; Piece* blackPawn7; Piece* blackPawn8;

	Piece* whitePieces[16];
	Piece* blackPieces[16];

	std::vector<Piece*> whiteCapturedPieces;
	std::vector<Piece*> blackCapturedPieces;
	
public :
	
	struct Textures
	{
		sf::Texture whiteKing;
		sf::Texture whiteQueen;
		sf::Texture whiteBishop;
		sf::Texture whiteKnight;
		sf::Texture whiteRook;
		sf::Texture whitePawn;

		sf::Texture blackKing;
		sf::Texture blackQueen;
		sf::Texture blackBishop;
		sf::Texture blackKnight;
		sf::Texture blackRook;
		sf::Texture blackPawn;
	}textures;

	struct Sprites
	{
		PieceTextures textures;

		sf::Sprite whiteKing;
		sf::Sprite whiteQueen;
		sf::Sprite whiteBishop;
		sf::Sprite whiteKnight;
		sf::Sprite whiteRook;
		sf::Sprite whitePawn;

		sf::Sprite blackKing;
		sf::Sprite blackQueen;
		sf::Sprite blackBishop;
		sf::Sprite blackKnight;
		sf::Sprite blackRook;
		sf::Sprite blackPawn;
	}sprites;
	string piecesPath = assetsPath.concatenate("images\\pieces.png");

		


public :
	Piece* pressedPiece = nullptr;
};
