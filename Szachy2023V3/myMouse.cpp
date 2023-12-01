#include "myMouse.h"

Piece* myMouse::isInBoundsOfPiece()
{
	field_t mousePos = (*this).getPosAsField();

	if (chess.turnColor == black)
	{
		for (int i = 0; i < 16; i++)
		{
			if (chess.pieces.blackPieces[i]->isPlaying == false)
				continue;

			field_t piecePos = chess.pieces.blackPieces[i]->getPosAsField();
			if (utility::areFieldsEqual(piecePos, mousePos))
				return chess.pieces.blackPieces[i];
		}
	}
	else if (chess.turnColor == white)
	{
		for (int i = 0; i < 16; i++)
		{
			if (chess.pieces.whitePieces[i]->isPlaying == false)
				continue;

			field_t piecePos = chess.pieces.whitePieces[i]->getPosAsField();
			if (utility::areFieldsEqual(piecePos, mousePos))
				return chess.pieces.whitePieces[i];
		}
	}
	return nullptr;
}

field_t myMouse::getPosAsField()
{
	int row = (*this).getPosition(window).y / 100;
	int col = (*this).getPosition(window).x / 100;
	return field_t{ row,col };
}