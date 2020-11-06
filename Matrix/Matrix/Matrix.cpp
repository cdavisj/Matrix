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
	return this->assign(other);
}

Matrix& Matrix::operator=(const std::vector<std::vector<double>>& grid)
{
	return this->setGrid(grid);
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
				printf("%.0f ", m_Grid[i][j]);

			printf("\n");
		}
	}
}

double& Matrix::at(const int& row, const int& col)
{
	return m_Grid[row][col];
}



// Private Member Functions
Matrix& Matrix::assign(const Matrix& other)
{
	m_Rows = other.m_Rows;
	m_Cols = other.m_Cols;

	m_Grid = std::vector<std::vector<double>>(m_Rows, std::vector<double>(m_Cols));

	for (unsigned int i = 0; i < m_Rows; i++)
		for (unsigned int j = 0; j < m_Cols; j++)
			m_Grid[i][j] = other.m_Grid[i][j];

	return *this;
}

Matrix& Matrix::setGrid(const std::vector<std::vector<double>> grid)
{
	m_Rows = grid.size();
	m_Cols = grid[0].size();

	m_Grid = std::vector<std::vector<double>>(m_Rows, std::vector<double>(m_Cols));

	for (unsigned int i = 0; i < m_Rows; i++)
		for (unsigned int j = 0; j < m_Cols; j++)
			m_Grid[i][j] = grid[i][j];

	return *this;
}

Matrix Matrix::plus(const Matrix& other) const
{
	if (this->hasSameDimensionsAs(other))
	{
		Matrix result(m_Rows, m_Cols);

		for (unsigned int i = 0; i < m_Rows; i++)
			for (unsigned int j = 0; j < m_Cols; j++)
				result.m_Grid[i][j] = m_Grid[i][j] + other.m_Grid[i][j];

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
				result.m_Grid[i][j] = m_Grid[i][j] - other.m_Grid[i][j];

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
					element += m_Grid[i][k] * other.m_Grid[k][j];

				result.m_Grid[i][j] = element;
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

bool Matrix::isEqualTo(const Matrix& other) const
{
	if (this->hasSameDimensionsAs(other))
	{
		for (unsigned int i = 0; i < m_Rows; i++)
		{
			for (unsigned int j = 0; j < m_Cols; j++)
				if (m_Grid[i][j] != other.m_Grid[i][j])
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
				if (m_Grid[i][j] != other.m_Grid[i][j])
					return true;
		}
		return false;
	}
	else
		return true;
}
