#pragma once
#include "Board.h"
#include "Pieces.h"
#include "myMouse.h"
#include "MoveLog.h"
#include "EndScreens.h"
#include "SoundEffects.h"


class ChessGame {
public:
	ChessGame();
public:
	Pieces pieces;
	Board board;
	MoveLog moveLog;
	EndScreens endScreens;
	SoundEffects soundEffects;
	int turnColor = white;
	int winner = -1;


public: // ChessGame.cpp
	void fillBoardWithPointersToPieces();
	void switchTurns();

public: //movingPieces.cpp
	void movePiece(Piece* piece, sf::Vector2f newPos);
	void movePiece(Piece* piece, field_t field);
	void movePiece(MoveLog::move_t* move);
	void performMove(MoveLog::move_t * move);
	void completeCastling();
	void completePromotion(MoveLog::move_t * move);
	void transformPiece(Piece* piece, int type, int color);
	void displayPromotionOptions();
	void onPiecePickup();
	void updateBoardOfPointers(Piece* piece, field_t oldField, field_t newField);
	void updateBoardOfPointers(MoveLog::move_t* move);
	void putPieceBackToStablePosition(Piece* piece);

public: //isMoveLegal.cpp
	bool isMoveLegal(MoveLog:: move_t * move);
	bool isMoveKingThreatening( MoveLog::move_t * move);
	bool isInBoundsOfBoard(field_t field);
	bool isIllegallyReleasedOnTheSameColor( Piece* piece, field_t newField);
	bool isTryingToCaptureEnemyKing( Piece* piece, field_t newField);
	bool isMoveWithinPieceRules(MoveLog::move_t * move);
	bool havePiecesOverlapped(MoveLog::move_t * move);
public: // pieceLogic.cpp (includes overlapping)
	bool kingRuleCheck( MoveLog::move_t*move);
	Piece *  hasKingCastled(Piece * , field_t oldField, field_t newField);
	bool queenRuleCheck(MoveLog::move_t* move);
	bool bishopRuleCheck(MoveLog::move_t* move);
	bool knightRuleCheck(MoveLog::move_t* move);
	bool rookRuleCheck(MoveLog::move_t* move);
	bool pawnRuleCheck(MoveLog::move_t* move);
public: // kingStatus.cpp
	Piece *isKingSafeAfterMove(MoveLog::move_t * move);
	Piece* isKingThreatened(int color);
	Piece* isFieldAttacked( field_t field, int color);
	bool isStalemate(int color);
	bool isCheckmate(int color);
public : //misc
	int getEnemyColor(int friendlyColor);
	void playMoveSound(MoveLog::move_t* move);
	bool newGameButtonPressed();
	bool isEndOfGame();
	void displayEndScreen();
	void startNewGame();
	void revertMove(MoveLog::move_t * move);
	std::vector<MoveLog::move_t*> getAllLegalMoves(Piece * piece);
	void capturePiece(field_t field);
	void deCaptureLastPiece(int color);

};
inline ChessGame chess;