#pragma once
#include "Piece.h"
#include "Board.h"
#include "MoveLog.h"
using namespace std;
#include <iostream>

class Printer {

private :
	enum status {OFF,ON};
	const int STATUS = OFF;

public:
	Printer();
	void print(const char* text1);
	void print(const char* text1, Piece* piece, const char* text2, field_t field);
	void print(const char* text1, Piece* piece, const char* text2);
	void print(Piece* piece);
	void print(const char * text1,Piece* piece );
	void print(int color);
	void print(std::vector<MoveLog::move_t*> moves);
	void print(Board& b);
	void print(const char* text, MoveLog::move_t* move);
	void printPossibleMoves(Piece* piece);
	const char* pieceTypeNames[6] = { "king","queen","bishop","knight","rook","pawn" };
	const char* colorNames[2] = { "black","white" };
};

inline Printer printer;