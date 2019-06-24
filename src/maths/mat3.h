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

#include "mat2.h"

#define ERROR_MATRIX_ELEMENT -1

#define PRINT_METHOD_C 1
#define PRINT_METHOD_CPP 0


namespace Rambug
{
	namespace Math
	{
		struct mat3
		{
			// This mat3 class is organized in column-major, as it is the format that OpenGL uses.
			// To address any part of the matrix, use the following format:
			// elements[row + col * width] 
			// Width in this class would be 3, as it is a 3 x 3 matrix.

			float elements[3 * 3];

			mat3();
			mat3(float diagonal);

			// Method to get a copy of the current matrix
			mat3 getCopy();

			// Methods to get matrices
			static mat3 Identity();
			static mat3 Sign();

			// Static version
			static mat3 Copy(mat3 matrix);

			// Useful methods to do miscellaneous operations with matrices (will change a matrix)
			float determinant();
			mat3& transpose();
			mat2 subMatrix(const int& row, const int& column);
			float minor(const int& row, const int& column);
			float cofactor(const int& row, const int& column);
			mat3& minorMatrix();
			mat3& cofactorMatrix(); 
			mat3& adjugate();
			mat3& inverse();

			// Static versions
			static float Determinant(mat3& matrix);
			static mat3& Transpose(mat3& matrix);
			static mat2 SubMatrix(mat3& matrix, const int& row, const int& column);
			static float Minor(mat3& matrix, const int& row, const int& column);
			static float Cofactor(mat3& matrix, const int& row, const int& column);
			static mat3& MinorMatrix(mat3& matrix);
			static mat3& CofactorMatrix(mat3& matrix);
			static mat3& Adjugate(mat3& matrix);
			static mat3& Inverse(mat3& matrix);

			// Same methods, but they will return a value rather than change a matrix
			float getDeterminant();
			mat3 getTranspose();
			mat2 getSubMatrix(const int& row, const int& column);
			float getMinor(const int& row, const int& column);
			float getCofactor(const int& row, const int& column);
			mat3 getMinorMatrix();
			mat3 getCofactorMatrix(); 
			mat3 getAdjugate();
			mat3 getInverse();

			// Static versions
			static float GetDeterminant(mat3 matrix);
			static mat3 GetTranspose(mat3 matrix);
			static mat2 GetSubMatrix(mat3 matrix, const int& row, const int& column);
			static float GetMinor(mat3 matrix, const int& row, const int& column);
			static float GetCofactor(mat3 matrix, const int& row, const int& column);
			static mat3 GetMinorMatrix(mat3 matrix);
			static mat3 GetCofactorMatrix(mat3 matrix);
			static mat3 GetAdjugate(mat3 matrix);
			static mat3 GetInverse(mat3 matrix);

			// Methods to do arithmetic operations with matrices (will change a matrix)
			mat3& add(const mat3& other);
			mat3& subtract(const mat3& other);
			mat3& multiply(const mat3& other);
			mat3& divide(const mat3& other);

			// Static versions 
			mat3& Add(mat3& left, const mat3& right);
			mat3& Subtract(mat3& left, const mat3& right);
			mat3& Multiply(mat3& left, const mat3& right);
			mat3& Divide(mat3& left, const mat3& right);

			// Same methods, but they will return a value rather than change a matrix
			mat3 sum(const mat3& other);
			mat3 difference(const mat3& other);
			mat3 product(const mat3& other);
			mat3 quotient(const mat3& other);

			// Static versions
			static mat3 Sum(mat3 left, const mat3& right);
			static mat3 Difference(mat3 left, const mat3& right);
			static mat3 Product(mat3 left, const mat3& right);
			static mat3 Quotient(mat3 left, const mat3& right);

			// Methods to do arithmetic operations with scalars (will change a matrix)
			mat3& addScalar(const float& scalar);
			mat3& subtractScalar(const float& scalar);
			mat3& multiplyScalar(const float& scalar);
			mat3& divideScalar(const float& scalar);

			// Static versions 
			mat3& AddScalar(mat3& matrix, const float& scalar);
			mat3& SubtractScalar(mat3& matrix, const float& scalar);
			mat3& MultiplyScalar(mat3& matrix, const float& scalar);
			mat3& DivideScalar(mat3& matrix, const float& scalar);

			// Same methods, but they will return a value rather than change a matrix
			mat3 scalarSum(const float& scalar);
			mat3 scalarDifference(const float& scalar);
			mat3 scalarProduct(const float& scalar);
			mat3 scalarQuotient(const float& scalar);

			// Static versions 
			static mat3 ScalarSum(mat3 matrix, const float& scalar);
			static mat3 ScalarDifference(mat3 matrix, const float& scalar);
			static mat3 ScalarProduct(mat3 matrix, const float& scalar);
			static mat3 ScalarQuotient(mat3 matrix, const float& scalar);

			// Methods to do relational and comparison operations with matrices
			bool isEqualTo(const mat3& matrix);
			bool isNotEqualTo(const mat3& matrix);

			// Static versions
			static bool IsEqualTo(mat3 left, const mat3& right);
			static bool IsNotEqualTo(mat3 left, const mat3& right);

			// Methods to print the matrix to the screen
			void print(); // Uses C or C++'s method of printing

			// Static version
			static void Print(mat3 matrix); // Uses C or C++'s method of printing
			static std::ostream& Print(std::ostream& stream, const mat3& matrix); // Uses C++'s way of printing

			/*          OPERATOR OVERLOAD BELOW          */

			// Overflow arithmetic operators with matrices
			friend mat3 operator+(mat3 left, const mat3& right);
			friend mat3 operator-(mat3 left, const mat3& right);
			friend mat3 operator*(mat3 left, const mat3& right);
			friend mat3 operator/(mat3 left, const mat3& right);

			// Overflow arithmetic operators with scalars
			friend mat3 operator+(mat3 matrix, const float& scalar);
			friend mat3 operator-(mat3 matrix, const float& scalar);
			friend mat3 operator*(mat3 matrix, const float& scalar);
			friend mat3 operator/(mat3 matrix, const float& scalar);

			// Overflow the compound assignment operators with matrices
			mat3& operator+=(const mat3& other);
			mat3& operator-=(const mat3& other);
			mat3& operator*=(const mat3& other);
			mat3& operator/=(const mat3& other);

			// Overflow the compound assignment operators with scalars
			mat3& operator+=(const float& scalar);
			mat3& operator-=(const float& scalar);
			mat3& operator*=(const float& scalar);
			mat3& operator/=(const float& scalar);

			// Overflow relational and comparison operators
			friend bool operator==(mat3 left, const mat3& right);
			friend bool operator!=(mat3 left, const mat3& right);

			// Overflow the bitwise operator
			friend std::ostream& operator<<(std::ostream& stream, mat3 matrix);
		};	
	}
}