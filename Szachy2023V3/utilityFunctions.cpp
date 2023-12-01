#include "utilityFunctions.h"
#include <iostream>

namespace utility {
	int myMin(int a, int b)
	{
		return a < b ? a : b;
	}
	int myMax(int a, int b)
	{
		return a > b ? a : b;
	}

	void fillPath(field_t* pathFields, int pathLen, field_t oldField, field_t newField)
	{
		int rowIt = oldField.row;
		int colIt = oldField.col;
		if (oldField.row == newField.row)
			for (int i = 0; i < pathLen; i++)
				pathFields[i].row = oldField.row;;
		if (oldField.col == newField.col)
			for (int i = 0; i < pathLen; i++)
				pathFields[i].col = oldField.col;

		if (oldField.row + 1 < newField.row)
			for (int i = 0; i < pathLen; i++)
				pathFields[i].row = ++rowIt;
		else if (oldField.row - 1 > newField.row)
			for (int i = 0; i < pathLen; i++)
				pathFields[i].row = --rowIt;

		if (oldField.col + 1 < newField.col)
			for (int i = 0; i < pathLen; i++)
				pathFields[i].col = ++colIt;
		else if (oldField.col - 1 > newField.col)
			for (int i = 0; i < pathLen; i++)
				pathFields[i].col = --colIt;
	}

	bool areFieldsEqual(field_t f1, field_t f2)
	{
		if (f1.row == f2.row && f1.col == f2.col)
			return true;
		return false;
	}


}
