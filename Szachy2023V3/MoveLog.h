#pragma once
#include "Piece.h" 

class MoveLog {

public :
	MoveLog();

public :
	typedef struct Move {
		Piece* piece;
		field_t oldField;
		field_t newField;
		bool wasPieceCaptured = false;
		bool isPromotionMove = false;
		Piece * isCastlingMove = nullptr;
		Piece * isEnPassanteMove = nullptr;

	}move_t;

	typedef struct Node {
		move_t* move;
		struct Node * moveBefore;
	}node_t;

	node_t* lastMove;

	public :
		void addMove(Piece * piece, field_t oldField, field_t newField);
		void addMove(MoveLog::move_t* move);
		move_t* createMove(Piece* piece, field_t oldField, field_t newField);
		move_t* copyMove(MoveLog::move_t* move);
		move_t * popLastMove();
		move_t * peekLastMove();
};