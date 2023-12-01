#pragma once
#include "SFML/Graphics.hpp"
using namespace std;

class PieceTextures
{
public :
	PieceTextures()
	{
		blackKing.loadFromFile(piecesPath, sf::IntRect(0, 100, 100, 100));
		blackQueen.loadFromFile(piecesPath, sf::IntRect(100, 100, 100, 100));
		blackBishop.loadFromFile(piecesPath, sf::IntRect(200, 100, 100, 100));
		blackKnight.loadFromFile(piecesPath, sf::IntRect(300, 100, 100, 100));
		blackRook.loadFromFile(piecesPath, sf::IntRect(400, 100, 100, 100));
		blackPawn.loadFromFile(piecesPath, sf::IntRect(500, 100, 100, 100));

		whiteKing.loadFromFile(piecesPath, sf::IntRect(0, 0, 100, 100));
		whiteQueen.loadFromFile(piecesPath, sf::IntRect(100, 0, 100, 100));
		whiteBishop.loadFromFile(piecesPath, sf::IntRect(200, 0, 100, 100));
		whiteKnight.loadFromFile(piecesPath, sf::IntRect(300, 0, 100, 100));
		whiteRook.loadFromFile(piecesPath, sf::IntRect(400, 0, 100, 100));
		whitePawn.loadFromFile(piecesPath, sf::IntRect(500, 0, 100, 100));
	}
public:
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

	string piecesPath = "E:\\INFORMATYKA\\PROGRAMOWANIE\\C++\\VISUAL STUDIO C++\\Szachy2023V3\\assets\\pieces.png";
};

class PieceSprites {
public :
	PieceSprites()
	{
		blackKing.setTexture(textures.blackKing);
		blackQueen.setTexture(textures.blackQueen);
		blackBishop.setTexture(textures.blackBishop);
		blackKnight.setTexture(textures.blackKnight);
		blackRook.setTexture(textures.blackRook);
		blackPawn.setTexture(textures.blackPawn);

		whiteKing.setTexture(textures.whiteKing);
		whiteQueen.setTexture(textures.whiteQueen);
		whiteBishop.setTexture(textures.whiteBishop);
		whiteKnight.setTexture(textures.whiteKnight);
		whiteRook.setTexture(textures.whiteRook);
		whitePawn.setTexture(textures.whitePawn);

	}
public :
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

};