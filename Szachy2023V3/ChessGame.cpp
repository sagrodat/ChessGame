#include "ChessGame.h"
#include "Printer.h"
#include "sfmlObjects.h"
#include <thread>
#include <chrono>


ChessGame::ChessGame()
{
	(*this).soundEffects.playStartOfGameSoundEffect();
	fillBoardWithPointersToPieces();
}

void ChessGame::fillBoardWithPointersToPieces()
{
	for (int i = 0; i < 16; i++)
	{
		Piece* wp = pieces.whitePieces[i];
		board.setPiece(wp, wp->getStablePositionAsField());

		Piece* bp = pieces.blackPieces[i];
		board.setPiece(bp, bp->getStablePositionAsField());
	}
}

void ChessGame::switchTurns()
{
	turnColor = !turnColor;
	printer.print("its now ");
	printer.print(turnColor);
	printer.print("'s turn! \n");
}

std::vector<MoveLog::move_t*> ChessGame::getAllLegalMoves(Piece* piece)
{
	
	std::vector<MoveLog::move_t*> legalMoves;

	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			MoveLog::move_t* attemptedMove = chess.moveLog.createMove(piece, piece->getStablePositionAsField(), field_t{ r,c });
			if (chess.isMoveLegal(attemptedMove))
			{
				legalMoves.push_back(attemptedMove);
			}
		}
	}
	return legalMoves;
}

int ChessGame::getEnemyColor(int friendlyColor)
{
	if (friendlyColor == white)
		return black;
	if (friendlyColor == black)
		return white;
}
bool ChessGame::newGameButtonPressed()
{
	sf::Vector2i mPos = mouse.getPosition(window);
	if (   mPos.x > endScreens.newGameX && mPos.x < endScreens.newGameX + endScreens.newGameWidth
		&& mPos.y > endScreens.newGameY && mPos.y < endScreens.newGameY + endScreens.newGameHeight)
		return true;
	return false;
}
bool ChessGame::isEndOfGame()
{
	if(chess.isCheckmate(getEnemyColor(chess.turnColor)))
		chess.winner = chess.turnColor;
	if (chess.isStalemate(getEnemyColor(chess.turnColor)))
		chess.winner = draw;

	if (chess.winner != none)
	{
		displayEndScreen();
		return true;
	}
	return false;

}
void ChessGame::startNewGame()
{
	chess = *(new ChessGame);
}

void ChessGame::transformPiece(Piece* piece, int type, int color)
{
	field_t initialPos = piece->getStablePositionAsField();
	piece->type = type;
	piece->color = color;
	sf::Sprite wantedSprite;
	switch (color)
	{
	case white:
		switch (type)
		{
		case queen:
			wantedSprite = chess.pieces.whiteQueen->getSpriteCopy();
			break;
		case rook:
			wantedSprite = chess.pieces.whiteRook1->getSpriteCopy();
			break;
		case knight:
			wantedSprite = chess.pieces.whiteKnight1->getSpriteCopy();
			break;
		case bishop:
			wantedSprite = chess.pieces.whiteBishop1->getSpriteCopy();
			break;
		case pawn:
			wantedSprite = chess.pieces.whitePawn1->getSpriteCopy();
			break;
		default:
			break;
		}
		break;
	case black:
		switch (type)
		{
		case queen:
			wantedSprite = chess.pieces.blackQueen->getSpriteCopy();
			break;
		case rook:
			wantedSprite = chess.pieces.blackRook1->getSpriteCopy();
			break;
		case knight:
			wantedSprite = chess.pieces.blackKnight1->getSpriteCopy();
			break;
		case bishop:
			wantedSprite = chess.pieces.blackBishop1->getSpriteCopy();
			break;
		case pawn:
			wantedSprite = chess.pieces.whitePawn1->getSpriteCopy();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	piece->sprite = wantedSprite;
	piece->setPosition(initialPos);

}

void ChessGame::onPiecePickup()
{
	Piece* p = (*this).pieces.pressedPiece;
	if (p != nullptr)
	{
		printer.print("mouse pressed on a", p);
		mouse.mousePieceDelta = sf::Vector2f(mouse.getPosition(window).x - p->stablePosition.x, mouse.getPosition(window).y - p->stablePosition.y);
	}
}

void ChessGame::playMoveSound(MoveLog::move_t* move)
{
	if (chess.isKingThreatened(!move->piece->color))
	{
		chess.soundEffects.playCheckSoundEffect();
	}
	else if (move->wasPieceCaptured)
	{
		chess.soundEffects.playCaptureSoundEffect();
	}
	else if (move->isCastlingMove)
	{
		chess.soundEffects.playCastlingSoundEffect();
	}
	else
	{
		chess.soundEffects.playPlacingSoundEffect();
	}
}


