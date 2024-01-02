#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ChessGame.h"
#include "myMouse.h"
#include "drawing.h"
#include "tests.h"
#include "sfmlObjects.h"
#include "Printer.h"
#include "SoundEffects.h"
#include "AssetsPath.h"

using namespace std;
using namespace sf;

int main()
{
	
	
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{

			case Event::KeyPressed :
				if (Keyboard::isKeyPressed(Keyboard::R))
				{
					chess.revertMove(chess.moveLog.popLastMove());
					chess.switchTurns();
				}
				break;
			case Event::Closed :
				window.close();
				break;

			case Event::MouseButtonReleased :
				if (chess.pieces.pressedPiece != nullptr)
				{
					MoveLog::move_t * attemptedMove = chess.moveLog.createMove( chess.pieces.pressedPiece, chess.pieces.pressedPiece->getStablePositionAsField() , mouse.getPosAsField() );
					if (chess.isMoveLegal(attemptedMove))
					{
						chess.performMove(attemptedMove);
						chess.playMoveSound(attemptedMove);
						if (!chess.isEndOfGame())
							chess.switchTurns();
						
						printer.print(chess.board);
					}
					else
					{
						chess.putPieceBackToStablePosition(chess.pieces.pressedPiece);
					}
					printer.print("\n\n");
					chess.pieces.pressedPiece = nullptr;
				}
				else
				{
					printer.print("mouse released");
				}
				break;

			case Event::MouseButtonPressed:	// for first iteration of mouse pressed down
				chess.pieces.pressedPiece = mouse.isInBoundsOfPiece();
				if (chess.pieces.pressedPiece != nullptr)
				{
					chess.onPiecePickup();
				}
				else
				{
					printer.print("mouse pressed");
				}
				break;
			}
		}

		if (mouse.isButtonPressed(Mouse::Button::Left)) // for holding down
		{
			if (chess.pieces.pressedPiece != nullptr)
			{
				int newX = mouse.getPosition(window).x - mouse.mousePieceDelta.x;
				int newY = mouse.getPosition(window).y - mouse.mousePieceDelta.y;
				chess.movePiece(chess.pieces.pressedPiece, sf::Vector2f(newX, newY));
			}
		}

		window.clear();
		myDraw();
		window.display();
	}
	return 0;
}