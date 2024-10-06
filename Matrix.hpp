
#pragma once

class Matrix {
	private:
		const int row = 2;
		const int col = 2;
	protected:
	public:
		union{
			struct{
				float	a,b,
						c,d;
			};
			float val[row][col];
		};
		Matrix& operator=(const Matrix& A);
		Matrix	operator+();
		Matrix	operator-();
		Matrix	operator+(const Matrix& A, const Matrix&B);
		Matrix	operator-(const Matrix& A, const Matrix& B);
		Matrix	operator*(const Matrix& A, const Matrix& B);


}



