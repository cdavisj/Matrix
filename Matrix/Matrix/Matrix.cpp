#include "Matrix.h"

#include <iostream>

// Constructors
Matrix::Matrix()
	: m_Rows(1), m_Cols(1)
{
	m_Grid.resize(m_Rows, std::vector<double>(m_Cols));
}

Matrix::Matrix(int rows, int cols, double val)
	: m_Rows(rows), m_Cols(cols)
{
	m_Grid.resize(m_Rows, std::vector<double>(m_Cols, val));
}

Matrix::Matrix(std::vector<std::vector<double>> grid)
	: m_Rows(grid.size()), m_Cols(grid[0].size())
{
	m_Grid.resize(m_Rows, std::vector<double>(m_Cols));

	for (unsigned int i = 0; i < m_Rows; i++)
		for (unsigned int j = 0; j < m_Cols; j++)
			m_Grid[i][j] = grid[i][j];
}



// Getters (Accessors)
unsigned int Matrix::getRows() const
{
	return m_Rows;
}

unsigned int Matrix::getCols() const
{
	return m_Cols;
}



// Overloaded Operators
Matrix& Matrix::operator=(const Matrix& other)
{
	this->assign(other);

	return *this;
}

Matrix& Matrix::operator=(const std::vector<std::vector<double>>& grid)
{
	this->setGrid(grid);

	return *this;
}

Matrix Matrix::operator+(const Matrix& other) const
{
	return this->plus(other);
}

Matrix Matrix::operator-(const Matrix& other) const
{
	return this->minus(other);
}

Matrix Matrix::operator*(const Matrix& other) const
{
	return this->times(other);
}

Matrix Matrix::operator*(const double& scalar) const
{
	Matrix result(m_Rows, m_Cols);

	result.assign(*this);

	result.scale(scalar);

	return result;
}

bool Matrix::operator==(const Matrix& other) const
{
	return this->isEqualTo(other);
}

bool Matrix::operator!=(const Matrix& other) const
{
	return this->isNotEqualTo(other);
}



// Boolean Member Functions
bool Matrix::isSquare() const
{
	return m_Rows == m_Cols;
}

bool Matrix::canMultiplyBy(const Matrix& other) const
{
	return m_Cols == other.m_Rows;
}

bool Matrix::hasSameDimensionsAs(const Matrix& other) const
{
	return m_Rows == other.m_Rows && 
		   m_Cols == other.m_Cols;
}

bool Matrix::isNull() const
{
	return m_Rows == 1 && 
		   m_Cols == 1 && 
		   m_Grid[0][0] == 0;
}



// Other Member Functions
Matrix Matrix::transpose() const
{
	Matrix result(m_Cols, m_Rows);

	for (unsigned int i = 0; i < m_Cols; i++)
		for (unsigned int j = 0; j < m_Rows; j++)
			result.m_Grid[i][j] = m_Grid[j][i];

	return result;
}

Matrix Matrix::minor(const unsigned int& row, const unsigned int& col) const
{
	Matrix result(m_Rows - 1, m_Cols - 1);

	unsigned int i;
	unsigned int j;
	unsigned int k;
	unsigned int l;

	for (i = 0, k = 0; i < m_Rows; i++)
	{
		
		for (j = 0, l = 0; j < m_Cols; j++)
		{
			if (i != row && j != col)
			{
				result.at(k, l) = this->at(i, j);

				l++;
			}
		}

		if (i != row && j != col)
			k++;
	}

	return result;
}

Matrix Matrix::cofactor(const unsigned int& row, const unsigned int& col) const
{
	Matrix result(m_Rows - 1, m_Cols - 1);

	result = this->minor(row, col);

	result.scale(pow(-1, row + col));

	return result;
}

double Matrix::determinant() const
{
	if (this->isSquare())
	{
		unsigned int n = m_Rows;

		if (n == 1)
			return this->at(0, 0);
		else if (n == 2)
			return this->at(0, 0) * this->at(1, 1) - this->at(0, 1) * this->at(1, 0);
		else
		{
			double result = 0.0;



			return result;
		}
	}
	else
	{
		printf("Error: matrix must be square");

		return 0.0;
	}
}

void Matrix::print() const
{
	if (this->isNull())
	{
		printf("null\n");
	}
	else
	{
		for (unsigned int i = 0; i < m_Rows; i++)
		{
			for (unsigned int j = 0; j < m_Cols; j++)
				printf("%.0f ", this->at(i, j));

			printf("\n");
		}
	}
}

double Matrix::at(const unsigned int& row, const unsigned int& col) const
{
	return m_Grid[row][col];
}

double& Matrix::at(const unsigned int& row, const unsigned int& col)
{
	return m_Grid[row][col];
}



// Private Member Functions
void Matrix::assign(const Matrix& other)
{
	m_Rows = other.m_Rows;
	m_Cols = other.m_Cols;

	m_Grid = std::vector<std::vector<double>>(m_Rows, std::vector<double>(m_Cols));

	for (unsigned int i = 0; i < m_Rows; i++)
		for (unsigned int j = 0; j < m_Cols; j++)
			this->at(i, j) = other.at(i, j);

}

void Matrix::setGrid(const std::vector<std::vector<double>>& grid)
{
	m_Rows = grid.size();
	m_Cols = grid[0].size();

	m_Grid = std::vector<std::vector<double>>(m_Rows, std::vector<double>(m_Cols));

	for (unsigned int i = 0; i < m_Rows; i++)
		for (unsigned int j = 0; j < m_Cols; j++)
			this->at(i, j) = grid[i][j];

}

Matrix Matrix::plus(const Matrix& other) const
{
	if (this->hasSameDimensionsAs(other))
	{
		Matrix result(m_Rows, m_Cols);

		for (unsigned int i = 0; i < m_Rows; i++)
			for (unsigned int j = 0; j < m_Cols; j++)
				result.at(i, j) = this->at(i, j) + other.at(i, j);

		return result;
	}
	else
	{
		printf("Error: Dimensions do not match.");

		return Matrix();
	}
}

Matrix Matrix::minus(const Matrix& other) const
{
	if (this->hasSameDimensionsAs(other))
	{
		Matrix result(m_Rows, m_Cols);

		for (unsigned int i = 0; i < m_Rows; i++)
			for (unsigned int j = 0; j < m_Cols; j++)
				result.at(i, j) = this->at(i, j) - other.at(i, j);

		return result;
	}
	else
	{
		printf("Error: Dimensions do not match.");

		return Matrix();
	}
}

Matrix Matrix::times(const Matrix& other) const
{
	if (this->canMultiplyBy(other))
	{
		Matrix result(m_Rows, other.m_Cols);

		double element = 0;

		for (unsigned int i = 0; i < m_Rows; i++)
		{
			for (unsigned int j = 0; j < other.m_Cols; j++)
			{
				for (unsigned int k = 0; k < other.m_Rows; k++)
					element += this->at(i, j) * other.at(i, j);

				result.at(i, j) = element;
				element = 0;
			}
		}

		return result;
	}
	else
	{
		printf("Error: Matrices can not multiply.");

		return Matrix();
	}
}

void Matrix::scale(const double& scalar)
{
	for (unsigned int i = 0; i < m_Rows; i++)
		for (unsigned int j = 0; j < m_Cols; j++)
			this->at(i, j) *= scalar;
}

bool Matrix::isEqualTo(const Matrix& other) const
{
	if (this->hasSameDimensionsAs(other))
	{
		for (unsigned int i = 0; i < m_Rows; i++)
		{
			for (unsigned int j = 0; j < m_Cols; j++)
				if (this->at(i, j) != other.at(i, j))
					return false;
		}
		return true;
	}
	else
		return false;
}

bool Matrix::isNotEqualTo(const Matrix& other) const
{
	if (this->hasSameDimensionsAs(other))
	{
		for (unsigned int i = 0; i < m_Rows; i++)
		{
			for (unsigned int j = 0; j < m_Cols; j++)
				if (this->at(i, j) != other.at(i, j))
					return true;
		}
		return false;
	}
	else
		return true;
}
