#include "Printer.h"
#include "ChessGame.h"

Printer::Printer()
{
}

void Printer::print(const char * text, MoveLog::move_t* move)
{
	if (!STATUS)
		return;
	int i = 0;
	while (text[i] != '\0')
		cout << text[i++];
	cout << " move from " << "(" << move->oldField.row << "," << move->oldField.col << ") to (" << move->newField.row << "," << move->newField.col << ")" << endl;
}
void Printer::print(const char* text1,  Piece* piece, const char* text2, field_t field)
{
	if (!STATUS)
		return;

	int i = 0;
	while (text1[i] != '\0')
		cout << text1[i++];
	cout << " ";
	cout << colorNames[piece->color] << " " << pieceTypeNames[piece->type] << " ";
	i = 0;
	while (text2[i] != '\0')
		cout << text2[i++];
	cout << " (" << field.row << "," << field.col << ")" << endl;
}

void Printer::print(const char* text1)
{
	if (!STATUS)
		return;
	
	cout << text1 << endl;
}
void Printer::print(const char* text1, Piece* piece, const char* text2)
{
	if (!STATUS)
		return;

	int i = 0;
	while (text1[i] != '\0')
		cout << text1[i++];
	cout << " ";
	cout << colorNames[piece->color] << " " << pieceTypeNames[piece->type] << " ";
	i = 0;
	while (text2[i] != '\0')
		cout << text2[i++];
	cout << endl;

}

void Printer::print(const char * text1, Piece * piece)
{
	if (!STATUS)
		return;

	int i = 0;
	while (text1[i] != '\0')
		cout << text1[i++];
	cout << " " << colorNames[piece->color] << " " << pieceTypeNames[piece->type] << " ";
	cout << endl;
}

void Printer::print(Piece* piece)
{
	if (!STATUS)
		return;

	cout << colorNames[piece->color] << " " << pieceTypeNames[piece->type] << endl;
}

void Printer::print(int color)
{
	if (!STATUS)
		return;

	cout << colorNames[color];
}

void Printer::print(std::vector<MoveLog::move_t*> moves)
{
	if (!STATUS)
		return;
	

	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			bool legal = false;
			for (int i = 0; i < moves.size(); i++)
			{
				
				if (moves.at(i)->newField.row == r && moves.at(i)->newField.col == c)
					legal = true;
			}
			if (legal)
				cout << "0";
			else
				cout << "X";
		}
		cout << endl;
	}
	cout << endl;
}

void Printer::print(Board & b)
{
	if (!STATUS)
		return;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (b.fields[i][j] == nullptr)
			{
				cout << "X";
			}
			else
			{
				cout << b.fields[i][j]->type;
			}
		}
		cout << endl;
	}
}


void Printer::printPossibleMoves(Piece* piece)
{
	if (!STATUS)
		return;

	(*this).print(chess.getAllLegalMoves(piece));
}