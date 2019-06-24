/* 
	DO NOT DELETE THIS COMMENT:
	The ROM(Rambug Optical Mathematics) Library:
	This software is written by Danyil Blyschak, 8/2015 (1st Build).
	For any permissions, questions, or bug fixes, email the 
	support email that came with your distribution of this software.
*/

#pragma once 

#include <iostream>
#include <stdio.h>


#define ERROR_MATRIX_ELEMENT -1

#define PRINT_METHOD_C 1
#define PRINT_METHOD_CPP 0


namespace Rambug
{
	namespace Math
	{
		struct mat2
		{
			// This mat2 class is organized in column-major, as it is the format that OpenGL uses.
			// To address any part of the matrix, use the following format:
			// elements[row + col * width] 
			// Width in this class would be 2, as it is a 2 x 2 matrix.

			float elements[2 * 2];

			mat2();
			mat2(float diagonal);

			// Method to get a copy of the current matrix
			mat2 getCopy();

			// Static version
			static mat2 Copy(mat2 matrix);

			// Methods to get matrices
			static mat2 Identity();
			static mat2 Sign();

			// Useful methods to do miscellaneous operations with matrices (will change a matrix)
			float determinant();
			mat2& transpose();
			mat2& adjugate();
			mat2& inverse();

			// Static versions
			static float Determinant(mat2& matrix);
			static mat2& Transpose(mat2& matrix);
			static mat2& Adjugate(mat2& matrix);
			static mat2& Inverse(mat2& matrix);

			// Same methods, but they will return a value rather than change a matrix
			float getDeterminant();
			mat2 getTranspose();
			mat2 getAdjugate();
			mat2 getInverse();

			// Static versions
			static float GetDeterminant(mat2 matrix);
			static mat2 GetTranspose(mat2 matrix);
			static mat2 GetAdjugate(mat2 matrix);
			static mat2 GetInverse(mat2 matrix);

			// Methods to do arithmetic operations with matrices (will change a matrix)
			mat2& add(const mat2& other);
			mat2& subtract(const mat2& other);
			mat2& multiply(const mat2& other);
			mat2& divide(const mat2& other);

			// Static versions 
			mat2& Add(mat2& left, const mat2& right);
			mat2& Subtract(mat2& left, const mat2& right);
			mat2& Multiply(mat2& left, const mat2& right);
			mat2& Divide(mat2& left, const mat2& right);

			// Same methods, but they will return a value rather than change a matrix
			mat2 sum(const mat2& other);
			mat2 difference(const mat2& other);
			mat2 product(const mat2& other);
			mat2 quotient(const mat2& other);

			// Static versions
			static mat2 Sum(mat2 left, const mat2& right);
			static mat2 Difference(mat2 left, const mat2& right);
			static mat2 Product(mat2 left, const mat2& right);
			static mat2 Quotient(mat2 left, const mat2& right);

			// Methods to do arithmetic operations with scalars (will change a matrix)
			mat2& addScalar(const float& scalar);
			mat2& subtractScalar(const float& scalar);
			mat2& multiplyScalar(const float& scalar);
			mat2& divideScalar(const float& scalar);

			// Static versions 
			mat2& AddScalar(mat2& matrix, const float& scalar);
			mat2& SubtractScalar(mat2& matrix, const float& scalar);
			mat2& MultiplyScalar(mat2& matrix, const float& scalar);
			mat2& DivideScalar(mat2& matrix, const float& scalar);

			// Same methods, but they will return a value rather than change a matrix
			mat2 scalarSum(const float& scalar);
			mat2 scalarDifference(const float& scalar);
			mat2 scalarProduct(const float& scalar);
			mat2 scalarQuotient(const float& scalar);

			// Static versions 
			static mat2 ScalarSum(mat2 matrix, const float& scalar);
			static mat2 ScalarDifference(mat2 matrix, const float& scalar);
			static mat2 ScalarProduct(mat2 matrix, const float& scalar);
			static mat2 ScalarQuotient(mat2 matrix, const float& scalar);

			// Methods to do relational and comparison operations with matrices
			bool isEqualTo(const mat2& matrix);
			bool isNotEqualTo(const mat2& matrix);

			// Static versions
			static bool IsEqualTo(mat2 left, const mat2& right);
			static bool IsNotEqualTo(mat2 left, const mat2& right);

			// Methods to print the matrix to the screen
			void print(); // Uses C or C++'s method of printing

			// Static version
			static void Print(mat2 matrix); // Uses C or C++'s method of printing
			static std::ostream& Print(std::ostream& stream, const mat2& matrix); // Uses C++'s method of printing

			/*          OPERATOR OVERLOAD BELOW          */

			// Overflow arithmetic operators with matrices
			friend mat2 operator+(mat2 left, const mat2& right);
			friend mat2 operator-(mat2 left, const mat2& right);
			friend mat2 operator*(mat2 left, const mat2& right);
			friend mat2 operator/(mat2 left, const mat2& right);

			// Overflow arithmetic operators with scalars
			friend mat2 operator+(mat2 matrix, const float& scalar);
			friend mat2 operator-(mat2 matrix, const float& scalar);
			friend mat2 operator*(mat2 matrix, const float& scalar);
			friend mat2 operator/(mat2 matrix, const float& scalar);

			// Overflow the compound assignment operators with matrices
			mat2& operator+=(const mat2& other);
			mat2& operator-=(const mat2& other);
			mat2& operator*=(const mat2& other);
			mat2& operator/=(const mat2& other);

			// Overflow the compound assignment operators with scalars
			mat2& operator+=(const float& scalar);
			mat2& operator-=(const float& scalar);
			mat2& operator*=(const float& scalar);
			mat2& operator/=(const float& scalar);

			// Overflow relational and comparison operators
			friend bool operator==(mat2 left, const mat2& right);
			friend bool operator!=(mat2 left, const mat2& right);

			// Overflow the bitwise operator
			friend std::ostream& operator<<(std::ostream& stream, mat2 matrix);
		};
	}
}