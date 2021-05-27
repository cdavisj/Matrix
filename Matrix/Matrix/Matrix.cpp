#include "Matrix.h"

#include <iostream>

/*
*   ---------------------------------------------
*   |               CONSTRUCTORS                |
*   ---------------------------------------------
*/
Matrix::Matrix()
	: m_Rows(1), m_Cols(1)
{
	m_Grid.resize(m_Rows, std::vector<double>(m_Cols));
}

Matrix::Matrix(const unsigned int& rows, const unsigned int& cols, const double& val)
	: m_Rows(rows), m_Cols(cols)
{
	m_Grid.resize(m_Rows, std::vector<double>(m_Cols, val));
}

Matrix::Matrix(const std::vector<std::vector<double>>& grid)
	: m_Rows(grid.size()), m_Cols(grid[0].size())
{
	m_Grid.resize(m_Rows, std::vector<double>(m_Cols));

	for (unsigned int i = 0; i < m_Rows; i++)
		for (unsigned int j = 0; j < m_Cols; j++)
			m_Grid[i][j] = grid[i][j];
}



/*
*   ---------------------------------------------
*   |            ACCESSORS (GETTERS)            |
*   ---------------------------------------------
*/
unsigned int Matrix::getRows() const
{
	return m_Rows;
}

unsigned int Matrix::getCols() const
{
	return m_Cols;
}



/*
*   ---------------------------------------------
*   |            OVERLOADED OPERATORS           |
*   ---------------------------------------------
*/
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

std::ostream& operator<<(std::ostream& output, const Matrix& matrix)
{
	if (matrix.isNull())
	{
		output << "null";
	}
	else
	{
		for (unsigned int i = 0; i < matrix.m_Rows; i++)
		{
			for (unsigned int j = 0; j < matrix.m_Cols; j++)
				output << matrix.at(i, j) << " ";

			output << std::endl;
		}
	}

	return output;
}

double Matrix::operator()(const unsigned int& row, const unsigned int& col) const
{
	if (this->hasRowIndex(row) && this->hasColIndex(col))
		return this->m_Grid[row][col];
	else
	{
		// NEED EXCEPTIONS HERE
		printf("Error: invalid row-column combination\n");

		return -1;
	}
}

double& Matrix::operator()(const unsigned int& row, const unsigned int& col)
{
	if (this->hasRowIndex(row) && this->hasColIndex(col))
		return this->m_Grid[row][col];
	else
	{
		// NEED EXCEPTIONS HERE
		printf("Error: invalid row-column combination\n");

		double err = -1;

		return err;
	}
}



/*
*   ---------------------------------------------
*   |              BOOLEAN METHODS              |
*   ---------------------------------------------
*/
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



/*
*   ---------------------------------------------
*   |               OTHER METHODS               |
*   ---------------------------------------------
*/
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
	if (this->hasRowIndex(row) && this->hasColIndex(col))
	{
		Matrix result(m_Rows - 1, m_Cols - 1);

		unsigned int i, j, k, l;

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
	else
	{
		// NEED EXCEPTIONS HERE
		printf("Error: invalid row-column combination\n");

		return Matrix();
	}
}

double Matrix::cofactor(const unsigned int& row, const unsigned int& col) const
{
	if (this->hasRowIndex(row) && this->hasColIndex(col))
	{
		Matrix min(m_Rows - 1, m_Cols - 1);

		min = this->minor(row, col);

		return min.determinant() * pow(-1, row + col);
	}
	else
	{
		// NEED EXCEPTIONS HERE
		printf("Error: invalid row-column combination\n");

		return -1;
	}
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
			
			for (unsigned int i = 0; i < n; i++)
				result += this->cofactor(i, 0) * this->at(i, 0);

			return result;
		}
	}
	else
	{
		// NEED EXCEPTIONS HERE
		printf("Error: matrix must be square");

		return -1;
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
				printf("%g ", this->at(i, j));

			printf("\n");
		}
	}
}

double Matrix::at(const unsigned int& row, const unsigned int& col) const
{
	if (this->hasRowIndex(row) && this->hasColIndex(col))
		return m_Grid[row][col];
	else
	{
		// NEED EXCEPTIONS HERE
		printf("Error: invalid row-column combination\n");

		return -1;
	}
}

double& Matrix::at(const unsigned int& row, const unsigned int& col)
{
	if (this->hasRowIndex(row) && this->hasColIndex(col))
		return m_Grid[row][col];
	else
	{
		// NEED EXCEPTIONS HERE
		printf("Error: invalid row-column combination\n");

		double err = -1;

		return err;
	}
}



/*
*   ---------------------------------------------
*   |              PRIVATE METHODS              |
*   ---------------------------------------------
*/
void Matrix::assign(const Matrix& other)
{
	m_Rows = other.m_Rows;
	m_Cols = other.m_Cols;

	m_Grid.resize(m_Rows, std::vector<double>(m_Cols));

	for (unsigned int i = 0; i < m_Rows; i++)
		for (unsigned int j = 0; j < m_Cols; j++)
			this->at(i, j) = other.at(i, j);

}

void Matrix::setGrid(const std::vector<std::vector<double>>& grid)
{
	m_Rows = grid.size();
	m_Cols = grid[0].size();

	m_Grid.resize(m_Rows, std::vector<double>(m_Cols));

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
		// NEED EXCEPTIONS HERE
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
		// NEED EXCEPTIONS HERE
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
		// NEED EXCEPTIONS HERE
		printf("Error: Matrices cannot multiply.");

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

bool Matrix::hasRowIndex(const unsigned int& row) const
{
	return row >= 0 && row < m_Rows;
}

bool Matrix::hasColIndex(const unsigned int& col) const
{
	return col >= 0 && col < m_Cols;
}
