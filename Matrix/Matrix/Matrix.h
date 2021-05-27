
/*
* File: Matrix.h
*
* Authors: Caleb Davis, Grant Fisher, Aidan Hart, Taxminion
*
* Date: 10-05-20
*
* Description:
*   Class implementation for a mathematical matrix.
*
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

class Matrix
{
public:
	// Constructors
	Matrix();

	Matrix(const unsigned int& rows, const unsigned int& cols, const double& val = 0);

	Matrix(const std::vector<std::vector<double>>& grid);



	// Accessors (Getters)
	unsigned int getRows() const;

	unsigned int getCols() const;



	// Overloaded Operators
	Matrix& operator=(const Matrix& other);

	Matrix& operator=(const std::vector<std::vector<double>>& grid);

	Matrix operator+(const Matrix& other) const;

	Matrix operator-(const Matrix& other) const;

	Matrix operator*(const Matrix& other) const;

	Matrix operator*(const double& scalar) const;

	bool operator==(const Matrix& other) const;

	bool operator!=(const Matrix& other) const;

	friend std::ostream& operator<<(std::ostream& output, const Matrix& matrix);

	double operator()(const unsigned int& row, const unsigned int& col) const;

	double& operator()(const unsigned int& row, const unsigned int& col);



	// Boolean Methods
	bool isSquare() const;

	bool canMultiplyBy(const Matrix& other) const;

	bool hasSameDimensionsAs(const Matrix& other) const;

	bool isNull() const;



	// Other Methods
	Matrix transpose() const;

	Matrix minor(const unsigned int& row, const unsigned int& col) const;

	double cofactor(const unsigned int& row, const unsigned int& col) const;

	double determinant() const;

	void print() const;

	double at(const unsigned int& row, const unsigned int& col) const;
	
	double& at(const unsigned int& row, const unsigned int& col);



private:
	// Private Methods
	void assign(const Matrix& other);

	void setGrid(const std::vector<std::vector<double>>& grid);

	Matrix plus(const Matrix& other) const;

	Matrix minus(const Matrix& other) const;

	Matrix times(const Matrix& other) const;

	void scale(const double& scalar);

	bool isEqualTo(const Matrix& other) const;

	bool isNotEqualTo(const Matrix& other) const;

	bool hasRowIndex(const unsigned int& row) const;

	bool hasColIndex(const unsigned int& col) const;



private:
	// Private Member Variables
	unsigned int m_Rows;
	unsigned int m_Cols;

	std::vector<std::vector<double>> m_Grid;

};

#endif
