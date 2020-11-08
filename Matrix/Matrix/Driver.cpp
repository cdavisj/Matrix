#include "Console.h"
#include "Matrix.h"

#include <iostream>
#include <vector>

int main()
{
	Matrix m1({
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
	});

	Matrix m2 = m1 * -1;
	m1.print();
	m2.print();

	std::cin.get();
	return 0;
}
