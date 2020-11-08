#include "Console.h"
#include "Matrix.h"

#include <iostream>
#include <vector>

int main()
{
	Matrix m({
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
	});

	double det;

	det = m.determinant();

	printf("%.0f", det);

	std::cin.get();
	return 0;
}
