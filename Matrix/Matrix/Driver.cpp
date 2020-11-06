#include "Console.h"
#include "Matrix.h"

#include <iostream>
#include <vector>

int main()
{
	Matrix m1 = Matrix({
		{ 1, 2, 3 },
		{ 1, 2, 3 },
		{ 1, 2, 3 }
	});

	Matrix m2 = Matrix({
		{ 1, 1, 1 },
		{ 2, 2, 2 },
		{ 3, 3, 3 }
	});

	printf("Matrix 1:\n");
	m1.print();

	printf("\nMatrix 2:\n");
	m2.print();

	Matrix sum = m1 + m2;
	printf("\nSum:\n");
	sum.print();

	Matrix difference = m1 - m2;
	printf("\nDifference:\n");
	difference.print();

	Matrix product = m1 * m2;
	printf("\nProduct:\n");
	product.print();


	std::cin.get();
	return 0;
}
