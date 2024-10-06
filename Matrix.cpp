
#include "Matrix.hpp"

Matrix& Matrix::operator=(const Matrix& A)
{
	for (int i=0; i<row; i++)
	{
		for (int j=0; j<col; j++)
		{
			this->val[i][j] = A[i][j];
		}
	}
	return (*this);
}

Matrix	Matrix::operator+()
{
	return (*this);
}

Matrix	Matrix::operator-()
{
	Matrix A;
	for (int i=0; i<row; i++)
	{
		for (int j=0; j<col; j++)
		{
			A[i][j] = (*this)[i][j] * (-1);
		}
	}
	return (A);
}

Matrix	Matrix::operator+(const Matrix& A, const Matrix& B)
{
	Matrix C;
	for (int i=0; i<row; i++)
	{
		for (int j=0; j<col; j++)
		{
			C.val[i][j] = A.val[i][j] + B.val[i][j];
		}
	}
	return C;
}

Matrix	Matrix::operator*(const Matrix& A, const Matrix& B)
{
	Matrix C;
	for (int i=0; i<row; i++)
	{
		for (int j=0; j<col; j++)
		{
			for (int k=0; k<row; k++)
			{
				C.val[i][j] = A.val[i][k] * B.val[k][j];
			}
		}
	}
	return C;
}

