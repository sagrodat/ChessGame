#include "Pieces.h"
#include <iostream>
Pieces::Pieces()
{
	this->loadTextures();
	this->setSpriteTextures();
	this->initiatePieces();	
}

void Pieces::loadTextures()
{
	textures.blackKing.loadFromFile(piecesPath, sf::IntRect(0, 100, 100, 100));
	textures.blackQueen.loadFromFile(piecesPath, sf::IntRect(100, 100, 100, 100));
	textures.blackBishop.loadFromFile(piecesPath, sf::IntRect(200, 100, 100, 100));
	textures.blackKnight.loadFromFile(piecesPath, sf::IntRect(300, 100, 100, 100));
	textures.blackRook.loadFromFile(piecesPath, sf::IntRect(400, 100, 100, 100));
	textures.blackPawn.loadFromFile(piecesPath, sf::IntRect(500, 100, 100, 100));

	textures.whiteKing.loadFromFile(piecesPath, sf::IntRect(0, 0, 100, 100));
	textures.whiteQueen.loadFromFile(piecesPath, sf::IntRect(100, 0, 100, 100));
	textures.whiteBishop.loadFromFile(piecesPath, sf::IntRect(200, 0, 100, 100));
	textures.whiteKnight.loadFromFile(piecesPath, sf::IntRect(300, 0, 100, 100));
	textures.whiteRook.loadFromFile(piecesPath, sf::IntRect(400, 0, 100, 100));
	textures.whitePawn.loadFromFile(piecesPath, sf::IntRect(500, 0, 100, 100));
}

void Pieces::setSpriteTextures()
{
	sprites.blackKing.setTexture(textures.blackKing);
	sprites.blackQueen.setTexture(textures.blackQueen);
	sprites.blackBishop.setTexture(textures.blackBishop);
	sprites.blackKnight.setTexture(textures.blackKnight);
	sprites.blackRook.setTexture(textures.blackRook);
	sprites.blackPawn.setTexture(textures.blackPawn);

	sprites.whiteKing.setTexture(textures.whiteKing);
	sprites.whiteQueen.setTexture(textures.whiteQueen);
	sprites.whiteBishop.setTexture(textures.whiteBishop);
	sprites.whiteKnight.setTexture(textures.whiteKnight);
	sprites.whiteRook.setTexture(textures.whiteRook);
	sprites.whitePawn.setTexture(textures.whitePawn);
}

void Pieces::initiatePieces()
{
	whiteRook1 = new Piece{ white,rook,0,700,sprites.whiteRook };
	whiteKnight1 = new Piece{ white,knight,100,700,sprites.whiteKnight };
	whiteBishop1 = new Piece{ white,bishop,200,700,sprites.whiteBishop };
	whiteQueen = new Piece{ white,queen,300,700,sprites.whiteQueen };
	whiteKing = new Piece{ white,king,400,700,sprites.whiteKing };
	whiteBishop2 = new Piece{ white,bishop,500,700,sprites.whiteBishop };
	whiteKnight2 = new Piece{ white,knight,600,700,sprites.whiteKnight };
	whiteRook2 = new Piece{ white,rook,700,700,sprites.whiteRook };
	whitePawn1 = new Piece{ white,pawn,0,600,sprites.whitePawn };
	whitePawn2 = new Piece{ white,pawn,100,600,sprites.whitePawn };
	whitePawn3 = new Piece{ white,pawn,200,600,sprites.whitePawn };
	whitePawn4 = new Piece{ white,pawn,300,600,sprites.whitePawn };
	whitePawn5 = new Piece{ white,pawn,400,600,sprites.whitePawn };
	whitePawn6 = new Piece{ white,pawn,500,600,sprites.whitePawn };
	whitePawn7 = new Piece{ white,pawn,600,600,sprites.whitePawn };
	whitePawn8 = new Piece{ white,pawn,700,600,sprites.whitePawn };

	blackRook1 = new Piece{ black,rook,0,0,sprites.blackRook };
	blackKnight1 = new Piece{ black,knight,100,0,sprites.blackKnight };
	blackBishop1 = new Piece{ black,bishop,200,0,sprites.blackBishop };
	blackQueen = new Piece{ black,queen,300,0,sprites.blackQueen };
	blackKing = new Piece{ black,king,400,0,sprites.blackKing };
	blackBishop2 = new Piece{ black,bishop,500,0,sprites.blackBishop };
	blackKnight2 = new Piece{ black,knight,600,0,sprites.blackKnight };
	blackRook2 = new Piece{ black,rook,700,0,sprites.blackRook };
	blackPawn1 = new Piece{ black,pawn,0  ,100,sprites.blackPawn };
	blackPawn2 = new Piece{ black,pawn,100,100,sprites.blackPawn };
	blackPawn3 = new Piece{ black,pawn,200,100,sprites.blackPawn };
	blackPawn4 = new Piece{ black,pawn,300,100,sprites.blackPawn };
	blackPawn5 = new Piece{ black,pawn,400,100,sprites.blackPawn };
	blackPawn6 = new Piece{ black,pawn,500,100,sprites.blackPawn };
	blackPawn7 = new Piece{ black,pawn,600,100,sprites.blackPawn };
	blackPawn8 = new Piece{ black,pawn,700,100,sprites.blackPawn };


	whitePieces[0] = whiteRook1;
	whitePieces[1] = whiteKnight1;
	whitePieces[2] = whiteBishop1;
	whitePieces[3] = whiteQueen;
	whitePieces[4] = whiteKing;
	whitePieces[5] = whiteBishop2;
	whitePieces[6] = whiteKnight2;
	whitePieces[7] = whiteRook2;
	whitePieces[8] = whitePawn1;
	whitePieces[9] = whitePawn2;
	whitePieces[10] = whitePawn3;
	whitePieces[11] = whitePawn4;
	whitePieces[12] = whitePawn5;
	whitePieces[13] = whitePawn6;
	whitePieces[14] = whitePawn7;
	whitePieces[15] = whitePawn8;

	blackPieces[0] = blackRook1;
	blackPieces[1] = blackKnight1;
	blackPieces[2] = blackBishop1;
	blackPieces[3] = blackQueen;
	blackPieces[4] = blackKing;
	blackPieces[5] = blackBishop2;
	blackPieces[6] = blackKnight2;
	blackPieces[7] = blackRook2;
	blackPieces[8] = blackPawn1;
	blackPieces[9] = blackPawn2;
	blackPieces[10] = blackPawn3;
	blackPieces[11] = blackPawn4;
	blackPieces[12] = blackPawn5;
	blackPieces[13] = blackPawn6;
	blackPieces[14] = blackPawn7;
	blackPieces[15] = blackPawn8;
}