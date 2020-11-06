#pragma once
#include <vector>

class Matrix
{
public:
	// Constructors
	Matrix();

	Matrix(int rows, int cols, double val = 0);

	Matrix(std::vector<std::vector<double>> grid);



	// Getters (Accessors)
	unsigned int getRows() const;

	unsigned int getCols() const;



	// Overloaded Operator
	Matrix& operator=(const Matrix& other);

	Matrix& operator=(const std::vector<std::vector<double>>& grid);

	Matrix operator+(const Matrix& other) const;

	Matrix operator-(const Matrix& other) const;

	Matrix operator*(const Matrix& other) const;

	bool operator==(const Matrix& other) const;

	bool operator!=(const Matrix& other) const;



	// Boolean Member Functions
	bool isSquare() const;

	bool canMultiplyBy(const Matrix& other) const;

	bool hasSameDimensionsAs(const Matrix& other) const;

	bool isNull() const;



	// Other Member Functions
	Matrix transpose() const;

	void print() const;

	double& at(const int& row, const int& col);



private:
	unsigned int m_Rows;
	unsigned int m_Cols;

	std::vector<std::vector<double>> m_Grid;



	// Private Member Functions
	Matrix& assign(const Matrix& other);

	Matrix& setGrid(const std::vector<std::vector<double>> grid);

	Matrix plus(const Matrix& other) const;

	Matrix minus(const Matrix& other) const;

	Matrix times(const Matrix& other) const;

	bool isEqualTo(const Matrix& other) const;

	bool isNotEqualTo(const Matrix& other) const;

};
