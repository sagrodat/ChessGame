#include "ChessGame.h"
#include "utilityFunctions.h"


bool ChessGame::isMoveKingThreatening( MoveLog::move_t * move)
{
	if (move->piece->isPlaying == false)
		return false;
	if (!isInBoundsOfBoard(move->newField))
		return false;
	if (isIllegallyReleasedOnTheSameColor( move->piece, move->newField))
		return false;
	if (!isMoveWithinPieceRules( move ) )
		return false;
	if (!isTryingToCaptureEnemyKing( move->piece, move->newField))
		return false;

	return true;
}
bool ChessGame::isInBoundsOfBoard(field_t field)
{
	if (field.row > 7 || field.col > 7 || field.row < 0 || field.col < 0)
		return false;
	return true;
}
bool ChessGame::isIllegallyReleasedOnTheSameColor( Piece *piece, field_t newField)
{
	if (piece->type == king)
	{
		Piece* pieceOnNewField = (*this).board.getPiece(newField.row, newField.col);
		if (pieceOnNewField != nullptr)
		{
			if (pieceOnNewField->type == rook && pieceOnNewField->color == piece->color && piece->timesMoved== 0 && pieceOnNewField->timesMoved == 0)
				return false;
		}
	}

	if ((*this).board.getPiece(newField.row, newField.col) == nullptr)
		return false;

	if ((*this).board.getPiece(newField.row, newField.col)->color != piece->color )
		return false;

	return true;
}
bool ChessGame::isTryingToCaptureEnemyKing( Piece* piece, field_t newField)
{
	Piece* p = board.getPiece(newField.row, newField.col);
	if (p == nullptr)
		return false;

	if (p->color == !piece->color && p->type == king)
		return true;

	return false;
}
bool ChessGame::isMoveWithinPieceRules(MoveLog::move_t * move)
{
	switch (move->piece->type)
	{
	case king :
		return kingRuleCheck( move );
	case queen :
		return queenRuleCheck(move );
	case bishop :
		return bishopRuleCheck(move);
	case knight : 
		return knightRuleCheck(move);
	case rook :
		return rookRuleCheck(move);
	case pawn: 
		return pawnRuleCheck(move);
	default :
		return false;
	}
}
bool ChessGame::havePiecesOverlapped(MoveLog::move_t* move)
{
	int dr = move->newField.row - move->oldField.row;
	int dc = move->newField.col - move->oldField.col;
	int pathLen = utility::myMax(abs(dr), abs(dc)) - 1;
	if (pathLen == 0)
		return false;
	field_t* pathFields = new field_t[pathLen];
	utility::fillPath(pathFields, pathLen, move->oldField, move->newField);

	for (int i = 0; i < pathLen; i++)
	{
		Piece* currentFieldPiece = (*this).board.getPiece(pathFields[i]);

		if (currentFieldPiece != nullptr)
			return true;
	}
	return false;
}

bool ChessGame::isMoveLegal(MoveLog::move_t* move)
{
	if (move->piece->isPlaying == false)
		return false;
	if (!isInBoundsOfBoard(move->newField))
		return false;
	if (isIllegallyReleasedOnTheSameColor(move->piece, move->newField))
		return false;
	if (isTryingToCaptureEnemyKing(move->piece, move->newField))
		return false;
	if (!isMoveWithinPieceRules(move))
		return false;
	if (isKingSafeAfterMove(move) != nullptr)
		return false;

	return true;
}

