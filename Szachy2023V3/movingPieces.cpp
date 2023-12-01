#include "ChessGame.h"
#include "myMouse.h"
#include "MoveLog.h"
#include "sfmlObjects.h"
#include "Printer.h"
#include "utilityFunctions.h"
#include <chrono>
#include <thread>
#include "drawing.h"

void ChessGame::completeCastling()
{
	field_t mousePos = mouse.getPosAsField();
	field_t newRookField;
	field_t newKingField;
	Piece* rookToMove = nullptr;

	Piece* king = chess.pieces.pressedPiece;
	Piece* rightRook = king->color == white ? chess.pieces.whiteRook2 : chess.pieces.blackRook2;
	Piece* leftRook = king->color == white ? chess.pieces.whiteRook1 : chess.pieces.blackRook1;

	if (utility::areFieldsEqual(mousePos,rightRook->getStablePositionAsField()))
	{
		newRookField = king->color == white ? field_t{ 7,5 } : field_t{ 0,5 };
		newKingField = king->color == white ? field_t{ 7,6 } : field_t{ 0,6 };
		rookToMove = rightRook;
	}
	else if (utility::areFieldsEqual(mousePos, leftRook->getStablePositionAsField()))
	{
		newRookField = king->color == white ? field_t{ 7,3 } : field_t{ 0,3 };
		newKingField = king->color == white ? field_t{ 7,2 } : field_t{ 0,2 };
		rookToMove = leftRook;
	}
	//log moves
	MoveLog::move_t* kingMove = chess.moveLog.createMove(king, king->getStablePositionAsField(), newKingField);
	MoveLog::move_t* rookMove = chess.moveLog.createMove(rookToMove, rookToMove->getStablePositionAsField(), newRookField);
	kingMove->isCastlingMove = rookToMove;
	chess.moveLog.addMove(rookMove);
	chess.moveLog.addMove(kingMove);

	chess.movePiece(king, newKingField);
	chess.movePiece(rookToMove, newRookField);
	printer.print("placed", king, "in", newKingField);
	printer.print("placed", rookToMove, "in", newRookField);

	chess.updateBoardOfPointers(king, king->getStablePositionAsField(), newKingField);
	chess.updateBoardOfPointers(rookToMove, rookToMove->getStablePositionAsField(),newRookField);

	king->setStablePosition(sf::Vector2f(newKingField.col * 100, newKingField.row * 100));
	rookToMove->setStablePosition(sf::Vector2f(newRookField.col * 100, newRookField.row * 100));

	king->timesMoved++;
	rookToMove->timesMoved++;

	
}
void ChessGame::completePromotion(MoveLog::move_t * move)
{
	//check for capturing
	if (chess.board.getPiece(move->newField.row, move->newField.col) != nullptr)
	{
		chess.capturePiece(move->newField);
		move->wasPieceCaptured = true;
	}
	//confirm pawn move
	chess.moveLog.addMove(move);
	chess.movePiece(move);
	printer.print("\n");

	//display pieces to choose
	chess.displayPromotionOptions();

	//check which piece was chosen
	field_t mousePos;
	Piece* pawn = chess.pieces.pressedPiece;
	field_t pawnPos = pawn->getPosAsField();
	field_t promotionFields[4];
	for (int i = 0; i < 4; i++)
	{
		if (pawn->color == white)
			promotionFields[i] = field_t{ pawnPos.row + i, pawnPos.col };
		else if (pawn->color == black)
			promotionFields[i] = field_t{ pawnPos.row - i , pawnPos.col };
	}

	int promotionPieces[4] = { queen,rook,knight,bishop };

	int chosenPiece = -1;
	while(chosenPiece == -1)
	{
		window.pollEvent(event);
		if (event.type == sf::Event::MouseButtonPressed)
		{
			mousePos = mouse.getPosAsField();
			for (int i = 0; i < 4; i++)
			{
				if (utility::areFieldsEqual(promotionFields[i], mousePos))
					chosenPiece = i;
			}
		}
	}

	transformPiece(pawn, promotionPieces[chosenPiece], pawn->color);
	myDraw();
	window.display();

}

void ChessGame::updateBoardOfPointers(Piece * piece, field_t oldField, field_t newField)
{
	(*this).board.fields[oldField.row][oldField.col] = nullptr;
	(*this).board.fields[newField.row][newField.col] = piece;
}
void ChessGame::updateBoardOfPointers(MoveLog::move_t * move)
{
	(*this).board.fields[move->oldField.row][move->oldField.col] = nullptr;
	(*this).board.fields[move->newField.row][move->newField.col] = move->piece;
}

void ChessGame::putPieceBackToStablePosition(Piece * piece)
{
	chess.movePiece(piece, piece->getStablePositionAsField());
	printer.print("returned", piece, "to stable position");
}

void ChessGame::movePiece(Piece* piece, sf::Vector2f newPos)
{
	piece->setPosition(newPos);
}
void ChessGame::movePiece(Piece* piece, field_t field)
{
	piece->setPosition(sf::Vector2f(field.col * 100, field.row * 100));
}
void ChessGame::movePiece(MoveLog::move_t* move)
{
	if (move->newField.row < 0 || move->newField.row > 8 || move->newField.col < 0 || move->newField.col > 8)
		return;

	move->piece->setPosition(move->newField);

	printer.print("placed", move->piece, "in", move->newField);

	chess.updateBoardOfPointers(move);

	move->piece->setStablePosition(move->newField);

	move->piece->timesMoved++;
}

void ChessGame::revertMove(MoveLog::move_t* move)
{
	if (move == nullptr)
		return;

	MoveLog::move_t* reversedMove = chess.moveLog.copyMove(move);
	field_t tmp = reversedMove->newField;
	reversedMove->newField = reversedMove->oldField;
	reversedMove->oldField = tmp;

	chess.movePiece(reversedMove);
	reversedMove->piece->timesMoved -= 2;

	if (move->wasPieceCaptured)
		deCaptureLastPiece(!move->piece->color);

	if (move->isCastlingMove != nullptr)
	{
		MoveLog::move_t* rookCastlingMove = moveLog.popLastMove();
		revertMove(rookCastlingMove);
	}
	
	if (move->isPromotionMove)
	{
		transformPiece(move->piece, pawn, move->piece->color);
	}
}

void ChessGame::capturePiece(field_t field)
{
	printer.print("Captured!");
	Piece* p = chess.board.getPiece(field);
	printer.print(p);

	p->isPlaying = false;
	p->sprite.setScale(sf::Vector2f(0.5, 0.5));

	std::vector<Piece*>* capturedPieces = p->color == white ? &chess.pieces.whiteCapturedPieces : &chess.pieces.blackCapturedPieces;
	capturedPieces->push_back(p);

	int yPos;
	if (capturedPieces->size() <= 8)
		yPos = p->color == white ? 0 : 700;
	else
		yPos = p->color == white ? 50 : 750;

	int offset = capturedPieces->size() - 1;

	p->setPosition(sf::Vector2f(800 + (offset * 50) % 400, yPos));
}
void ChessGame::deCaptureLastPiece(int color)
{
	printer.print("Decaptured piece!");
	std::vector<Piece*>* capturedPieces = color == white ? &chess.pieces.whiteCapturedPieces : &chess.pieces.blackCapturedPieces;
	if (capturedPieces->size() == 0)
		return;
	Piece* lastCaptured = capturedPieces->back();
	capturedPieces->pop_back();

	lastCaptured->isPlaying = true;
	lastCaptured->sprite.setScale(sf::Vector2f(1, 1));
	field_t lastPos = lastCaptured->getStablePositionAsField();
	lastCaptured->setPosition(lastPos);
	updateBoardOfPointers(lastCaptured, lastPos, lastPos);
}

void ChessGame::performMove(MoveLog::move_t* move)
{
	printer.print("Performing", move);
	if (!isInBoundsOfBoard(move->newField))
	{
		chess.putPieceBackToStablePosition(move->piece);
		return;
	}

	//handling special moves
	if (move->isCastlingMove != nullptr)
	{
		printer.print("Completing castling!");
		chess.completeCastling();
		return;
	}

	if (move->isEnPassanteMove != nullptr)
	{
		chess.capturePiece(move->isEnPassanteMove->getStablePositionAsField());
		move->wasPieceCaptured = true;
	}

	if (move->isPromotionMove == true)
	{
		chess.completePromotion(move);
		return;
	}
	//end of 

	if (chess.board.getPiece(move->newField.row, move->newField.col) != nullptr)
	{
		chess.capturePiece(move->newField);
		move->wasPieceCaptured = true;
	}

	chess.moveLog.addMove(move);
	chess.movePiece(move);
	printer.print("\n");
	
}