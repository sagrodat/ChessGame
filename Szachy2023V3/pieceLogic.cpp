#include "ChessGame.h"
#include "utilityFunctions.h"

Piece * ChessGame::hasKingCastled(Piece* king, field_t oldField, field_t newField)
{
	if(king != (*this).pieces.pressedPiece)
		return nullptr;

	Piece* leftRook = king->color == white ? chess.pieces.whiteRook1 : chess.pieces.blackRook1;
	Piece* rightRook = king->color == white ? chess.pieces.whiteRook2 : chess.pieces.blackRook2;

	Piece* chosenRook = nullptr;
	if (board.getPiece(newField) == leftRook)
		chosenRook = leftRook;
	if (board.getPiece(newField) == rightRook)
		chosenRook = rightRook;

	if (chosenRook == nullptr)
		return nullptr;
	if (chosenRook->timesMoved != 0)
		return nullptr;
	if (king->timesMoved != 0)
		return nullptr;
	if (isKingThreatened(king->color))
		return nullptr;

	int pathLen = chosenRook == leftRook ? 3 : 2;
	field_t* pathToCheck = new field_t[pathLen];
	utility::fillPath(pathToCheck, pathLen, king->getStablePositionAsField(), chosenRook->getPosAsField());
	for (int i = 0; i < pathLen; i++)
	{
		if (chess.board.getPiece(pathToCheck[i]) != nullptr)
			return 0;
		if (isFieldAttacked(pathToCheck[i],king->color) != nullptr)
			return 0;
	}
	return chosenRook;
}
bool ChessGame::kingRuleCheck(MoveLog::move_t * move)
{
	move->isCastlingMove = hasKingCastled(move->piece, move->oldField, move->newField);
	if (move->isCastlingMove != nullptr)
	{
		return true;
	}
	int dr = move->newField.row - move->oldField.row;
	int dc = move->newField.col - move->oldField.col;
	if (abs(dr) > 1 || abs(dc) > 1)
		return false;
	return true;
}
bool ChessGame::queenRuleCheck(MoveLog::move_t * move)
{
	int dr = move->newField.row - move->oldField.row;
	int dc = move->newField.col - move->oldField.col;
	if (dr == 0 && dc == 0)
		return false;
	if (abs(dr) > 0 && abs(dc) > 0 && abs(dr) != abs(dc))
		return false;
	if (havePiecesOverlapped(move))
		return false;
	return true;
}
bool ChessGame::bishopRuleCheck(MoveLog::move_t * move)
{
	
	int dr = move->newField.row - move->oldField.row;
	int dc = move->newField.col - move->oldField.col;
	if (dr == 0 && dc == 0)
		return false;
	if (min(abs(dr), abs(dc)) == 0 && max(abs(dr), abs(dc)) > 0)
		return false;
	if (abs(dr) != abs(dc))
		return false;
	if (havePiecesOverlapped(move))
		return false;
	return true;
}
bool ChessGame::knightRuleCheck(MoveLog::move_t * move)
{
	int dr = move->newField.row - move->oldField.row;
	int dc = move->newField.col - move->oldField.col;
	if (dr == 0 || dc == 0)
		return false;
	if (abs(dr) + abs(dc) != 3)
		return false;
	return true;
}
bool ChessGame::rookRuleCheck(MoveLog::move_t * move)
{
	int dr = move->newField.row - move->oldField.row;
	int dc = move->newField.col - move->oldField.col;
	if (dr == 0 && dc == 0)
		return false;
	if (abs(dr) > 0 && abs(dc) > 0)
		return false;
	if (havePiecesOverlapped(move))
		return false;

	return true;
}
bool ChessGame::pawnRuleCheck(MoveLog::move_t * move)
{
	int dr = move->newField.row - move->oldField.row;
	int dc = move->newField.col - move->oldField.col;
	int r = move->oldField.row;
	int c = move->oldField.col;
	int whiteStartingRow = 6;
	int blackStartingRow = 1;
	if (move->piece->color == white)
	{
		Piece* left = board.getPiece(r, c - 1);
		Piece* right = board.getPiece(r, c + 1);
		Piece* oneUp = board.getPiece(r - 1, c);
		Piece* twoUp = board.getPiece(r - 2, c);
		Piece* leftUp = board.getPiece(r - 1, c - 1);
		Piece* rightUp = board.getPiece(r - 1, c + 1);
		MoveLog::move_t* lastMove = chess.moveLog.peekLastMove();
		if (move->newField.row == 0)
			move->isPromotionMove = true;

		if (dc == 0 && dr == -1 && oneUp == nullptr)
			return true;
		if (dc == 0 && dr == -2 && oneUp == nullptr && twoUp == nullptr && r == whiteStartingRow)
			return true;
		if (dc == -1 && dr == -1 && leftUp != nullptr && leftUp->color == !move->piece->color)
			return true;
		if (dc == 1 && dr == -1 && rightUp != nullptr && rightUp->color == !move->piece->color)
			return true;
		if (dc == 1 && dr == -1 && right != nullptr && rightUp == nullptr && lastMove != nullptr && right == lastMove->piece && right->type == pawn && right->timesMoved == 1 && right->getPosAsField().row == 3)
		{
			move->isEnPassanteMove = right;
			return true;
		}
			
		if (dc == -1 && dr == -1 && left != nullptr && leftUp == nullptr && lastMove != nullptr && left == lastMove->piece && left->type == pawn && left->timesMoved == 1 && left->getPosAsField().row == 3)
		{
			move->isEnPassanteMove = left;
			return true;
		}
		
	}
	else if (move->piece->color == black)
	{
		Piece* left = board.getPiece(r, c - 1);
		Piece* right = board.getPiece(r, c + 1);
		Piece* oneDown = board.getPiece(r + 1, c);
		Piece* twoDown = board.getPiece(r + 2, c);
		Piece* leftDown = board.getPiece(r + 1, c - 1);
		Piece* rightDown = board.getPiece(r + 1, c + 1);
		MoveLog::move_t* lastMove = chess.moveLog.peekLastMove();

		if (move->newField.row == 7)
			move->isPromotionMove = true;

		if (dc == 0 && dr == 1 && oneDown == nullptr)
			return true;
		if (dc == 0 && dr == 2 && oneDown == nullptr && twoDown == nullptr && r == blackStartingRow)
			return true;
		if (dc == -1 && dr == 1 && leftDown != nullptr && leftDown->color == !move->piece->color)
			return true;
		if (dc == 1 && dr == 1 && rightDown != nullptr && rightDown->color == !move->piece->color)
			return true;
		if (dc == 1 && dr == 1 && right != nullptr && rightDown == nullptr && lastMove != nullptr && right == lastMove->piece && right->type == pawn && right->timesMoved == 1 && right->getPosAsField().row == 4)
		{
			move->isEnPassanteMove = right;
			return true;
		}
		
		if (dc == -1 && dr == 1 && left != nullptr && leftDown == nullptr && lastMove != nullptr && left == lastMove->piece && left->type == pawn && left->timesMoved == 1 && left->getPosAsField().row == 4)
		{
			move->isEnPassanteMove = left;
			return true;
		}
	}
	return false;
}