#pragma once
#include "global.h"
namespace utility {
	int myMin(int a, int b);
	int myMax(int a, int b);
	void fillPath(field_t* pathFields, int pathLen, field_t oldField, field_t newField);
	bool areFieldsEqual(field_t f1, field_t f2);
}