#include "Tests.h"
#include "drawing.h"
#include "sfmlObjects.h"
#include <thread>
#include <chrono>

void windowRefresh(int ms)
{
	window.clear();
	myDraw();
	window.display();
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int testAmountOfPossibleMovesNDeep(ChessGame chess, int depth)
{
	if (depth == 0)
		return 0;
	int cnt = 0;
	int refreshRate = 0; // fastest = 0 (sleep ms)

	Piece** pieces = depth % 2 == 0 ? chess.pieces.blackPieces : chess.pieces.whitePieces;
	for(int i = 0 ; i < 16 ; i++)
	{
		std::vector<MoveLog::move_t*> moves = chess.getAllLegalMoves(pieces[i]);
		for (MoveLog::move_t* move : moves)
		{
			chess.performMove(move);
			cnt++;
			windowRefresh(refreshRate);
			cnt += testAmountOfPossibleMovesNDeep(chess, depth - 1);
			chess.revertMove(move);
			windowRefresh(refreshRate);
		}
	}
	return cnt;
}
