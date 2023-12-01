#include "ChessGame.h"
#include "Printer.h"
Piece * ChessGame::isKingSafeAfterMove( MoveLog::move_t* move)
{	
	chess.performMove(move);
	Piece * kingThreateningPiece = chess.isKingThreatened(move->piece->color);
	chess.revertMove(chess.moveLog.popLastMove());
	return kingThreateningPiece;
}
Piece * ChessGame::isKingThreatened( int kingColor )
{
	Piece** enemyPieces;
	Piece* ownKing;
	kingColor == white ? enemyPieces = (*this).pieces.blackPieces : enemyPieces = (*this).pieces.whitePieces;
	kingColor == white ? ownKing = (*this).pieces.whiteKing : ownKing = (*this).pieces.blackKing;
	for (int i = 0; i < 16; i++)
	{
		if (enemyPieces[i]->type == king) // king cant directly threaten a king
			continue;
		if (enemyPieces[i]->isPlaying == false)
			continue;

		MoveLog::move_t* attemptedMove = chess.moveLog.createMove(enemyPieces[i], enemyPieces[i]->getStablePositionAsField(), ownKing->getStablePositionAsField());
		if((*this).isMoveKingThreatening(attemptedMove))
			return attemptedMove->piece;
	}
	return nullptr;

}
Piece* ChessGame::isFieldAttacked( field_t field, int friendlyColor)
{
	Piece** enemyPieces = friendlyColor == white ? (*this).pieces.blackPieces : (*this).pieces.whitePieces;
	for (int i = 0; i < 16; i++)
	{
		if (enemyPieces[i]->isPlaying == false)
			continue;

		MoveLog::move_t * attackingMove = chess.moveLog.createMove(enemyPieces[i], enemyPieces[i]->getStablePositionAsField(), field);
		if ((*this).isMoveLegal( attackingMove))
			return enemyPieces[i];
	}
	return nullptr;
}
bool ChessGame::isStalemate(int color)
{
	if (isKingThreatened(color))
		return false;
	Piece** friendlyPieces = color == white ? chess.pieces.whitePieces : chess.pieces.blackPieces;

	for (int i = 0; i < 16; i++)
	{
		std::vector<MoveLog::move_t*> possibleMoves = chess.getAllLegalMoves(friendlyPieces[i]);
		if (possibleMoves.size() != 0)
			return false;
	}
	return true;
}
bool ChessGame::isCheckmate(int color)
{
	if (!isKingThreatened(color))
		return false;

	Piece** friendlyPieces = color == white ? chess.pieces.whitePieces : chess.pieces.blackPieces;
	for (int i = 0; i < 16; i++)
	{
		std::vector<MoveLog::move_t*> possibleMoves = chess.getAllLegalMoves(friendlyPieces[i]);
		if (possibleMoves.size() != 0)
			return false;
	}
	return true;
}