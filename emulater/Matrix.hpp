
#pragma once

#include <complex>

class Matrix {
	private:
		const int row = 2;
		const int col = 2;
	protected:
	public:
		union{
			struct{
				complex<double>	a,b,
								c,d;
			};
			complex<double> val[row][col];
		};
		Matrix	Matrix();
		Matrix	Matrix(complex<double> a_, complex<double> b_, complex<double> c_, complex<double> d_);
		Matrix& operator=(const Matrix& A);
		Matrix	operator+();
		Matrix	operator-();
		Matrix	operator+(const Matrix& A, const Matrix&B);
		Matrix	operator-(const Matrix& A, const Matrix& B);
		Matrix	operator*(const Matrix& A, const Matrix& B);


}



