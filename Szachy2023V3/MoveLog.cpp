#include "MoveLog.h"
#include "Printer.h"
#include <iostream>
using namespace std;

MoveLog::MoveLog()
{
	lastMove = nullptr;
}
void MoveLog::addMove(MoveLog::move_t* move)
{
	printer.print("Logged", move);

	node_t* node = new node_t;
	node->move = move;
	node->moveBefore = nullptr;

	if ((*this).lastMove == nullptr)
	{
		lastMove = node;
	}
	else
	{
		node->moveBefore = lastMove;
		lastMove = node;
	}
}
void MoveLog::addMove(Piece * piece, field_t oldField, field_t newField)
{
	
	move_t* move = new move_t;
	move->newField = newField;
	move->oldField = oldField;
	move->piece = piece;
	printer.print("Logged", move);

	node_t* node = new node_t;
	node->move = move;
	node->moveBefore = nullptr;

	if ((*this).lastMove == nullptr)
	{
		lastMove = node;
	}
	else
	{
		node->moveBefore = lastMove;
		lastMove = node;
	}
}
MoveLog::move_t* MoveLog::popLastMove()
{
	if (lastMove == nullptr)
		return nullptr;
	
	node_t* toReturn = lastMove;
	lastMove = lastMove->moveBefore;
	return toReturn->move;
}

MoveLog::move_t* MoveLog::peekLastMove()
{
	if (lastMove == nullptr)
		return nullptr;

	return lastMove->move;
}

MoveLog::move_t* MoveLog::createMove(Piece * p, field_t oldField, field_t newField)
{

	MoveLog::move_t* move = new MoveLog::move_t;
	move->piece = p;
	move->oldField = oldField;
	move->newField = newField;

	return move;
}

MoveLog::move_t* MoveLog::copyMove(MoveLog::move_t * move)
{
	MoveLog::move_t* newMove = new MoveLog::move_t;
	newMove->piece = move->piece;
	newMove->oldField = move->oldField;
	newMove->newField = move->newField;
	newMove->isEnPassanteMove = move->isEnPassanteMove;
	newMove->isCastlingMove = move->isCastlingMove;
	newMove->wasPieceCaptured = move->wasPieceCaptured;
	return newMove;
}