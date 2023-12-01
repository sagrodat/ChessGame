#include "drawing.h"
#include "ChessGame.h"
#include "sfmlObjects.h"
void myDraw()
{
	window.draw(chess.board.sprite);
	for (int i = 0; i < 16; i++)
	{
		if (chess.pieces.whitePieces[i] == chess.pieces.pressedPiece)
			continue;
		window.draw(chess.pieces.whitePieces[i]->sprite);
	}
	for (int i = 0; i < 16; i++)
	{
		if (chess.pieces.blackPieces[i] == chess.pieces.pressedPiece)
			continue;
		window.draw(chess.pieces.blackPieces[i]->sprite);
	}

	if(chess.pieces.pressedPiece != nullptr)
		window.draw(chess.pieces.pressedPiece->sprite);

}

void ChessGame::displayPromotionOptions()
{
	struct promotionBackground {
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Vector2f pos;
		string texturePath;
	};
	struct promotionBackground pB;
	pB.texturePath = assetsPath.concatenate("images\\promotionBackground.png");
	pB.texture.loadFromFile(pB.texturePath);
	pB.sprite.setTexture(pB.texture);

	Piece* pawn = chess.pieces.pressedPiece;
	field_t pawnPos = pawn->getPosAsField();

	pB.pos.x = pawnPos.col * 100;
	pB.pos.y = pawn->color == white ? pawnPos.row * 100 : pawnPos.row * 100 - 300;
	pB.sprite.setPosition(pB.pos);

	//

	sf::Sprite promotionPieces[4];
	promotionPieces[0] = pawn->color == white ? chess.pieces.whiteQueen->getSpriteCopy() : chess.pieces.blackQueen->getSpriteCopy();
	promotionPieces[1] = pawn->color == white ? chess.pieces.whiteRook1->getSpriteCopy() : chess.pieces.blackRook1->getSpriteCopy();
	promotionPieces[2] = pawn->color == white ? chess.pieces.whiteKnight1->getSpriteCopy() : chess.pieces.blackKnight1->getSpriteCopy();
	promotionPieces[3] = pawn->color == white ? chess.pieces.whiteBishop1->getSpriteCopy() : chess.pieces.blackBishop1->getSpriteCopy();
	for (int i = 0; i < 4; i++)
	{
		sf::Vector2f piecePos;
		piecePos.x = pawnPos.col * 100;
		piecePos.y = pawn->color == white ? 0 + i * 100 : 700 - i * 100;
		promotionPieces[i].setPosition(piecePos);
	}
	window.draw(pB.sprite);
	for (int i = 0; i < 4; i++)
		window.draw(promotionPieces[i]);
	window.display();


}
void ChessGame::displayEndScreen()
{
	chess.soundEffects.playEndOfGameSoundEffect();

	switch (chess.winner)
	{
	case white:
		window.draw(chess.endScreens.whiteWins.sprite);
		break;
	case black:
		window.draw(chess.endScreens.blackWins.sprite);
		break;
	case draw:
		window.draw(chess.endScreens.draw.sprite);
		break;
	default:
		break;
	}
	window.display();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				if (newGameButtonPressed())
				{
					goto newGame;
				}
			}
		}
	}
newGame:
	chess.startNewGame();
	return;
}
