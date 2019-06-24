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

#include "mat4.h"
#include "mat3.h"

#include "vec3.h"

#include "mathutils.h"

#define ERROR_MATRIX_ELEMENT 0

#define PRINT_METHOD_C 1
#define PRINT_METHOD_CPP 0


namespace Rambug
{
	namespace Math
	{
		struct mat4
		{
			// This mat4 class is organized in column-major, as it is the format that OpenGL uses.
			// To address any part of the matrix, use the following format:
			// elements[row + col * width] 
			// Width in this class would be 4, as it is a 4 x 4 matrix.

			float elements[4 * 4];

			mat4();
			mat4(float diagonal);

			// Methods to get matrices
			static mat4 Identity();
			static mat4 Sign();

			// Projection matrices
			static mat4 Orthographic(float left, float right, float bottom, float top, float near, float far);
			static mat4 Perspective(float fov, float aspectRatio, float near, float far);

			// Translation matrices
			static mat4 Translation(const vec3& translation);
			static mat4 Rotation(float angle, const vec3& axis);
			static mat4 Scale(const vec3& scale);

			// Method to get a copy of the current matrix
			mat4 getCopy();

			// Static version
			static mat4 Copy(mat4 matrix);

			// Useful methods to do miscellaneous operations with matrices (will change a matrix)
			float determinant();
			mat4& transpose();
			mat3 subMatrix(const int& row, const int& column);
			float minor(const int& row, const int& column);
			float cofactor(const int& row, const int& column);
			mat4& minorMatrix();
			mat4& cofactorMatrix(); 
			mat4& adjugate();
			mat4& inverse();

			// Static versions
			static float Determinant(mat4& matrix);
			static mat4& Transpose(mat4& matrix);
			static mat3 SubMatrix(mat4& matrix, const int& row, const int& column);
			static float Minor(mat4& matrix, const int& row, const int& column);
			static float Cofactor(mat4& matrix, const int& row, const int& column);
			static mat4& MinorMatrix(mat4& matrix);
			static mat4& CofactorMatrix(mat4& matrix);
			static mat4& Adjugate(mat4& matrix);
			static mat4& Inverse(mat4& matrix);

			// Same methods, but they will return a value rather than change a matrix
			float getDeterminant();
			mat4 getTranspose();
			mat3 getSubMatrix(const int& row, const int& column);
			float getMinor(const int& row, const int& column);
			float getCofactor(const int& row, const int& column);
			mat4 getMinorMatrix();
			mat4 getCofactorMatrix();
			mat4 getAdjugate();
			mat4 getInverse();

			// Static versions
			static float GetDeterminant(mat4 matrix);
			static mat4 GetTranspose(mat4 matrix);
			static mat3 GetSubMatrix(mat4 matrix, const int& row, const int& column);
			static float GetMinor(mat4 matrix, const int& row, const int& column);
			static float GetCofactor(mat4 matrix, const int& row, const int& column);
			static mat4 GetMinorMatrix(mat4 matrix);
			static mat4 GetCofactorMatrix(mat4 matrix);
			static mat4 GetAdjugate(mat4 matrix);
			static mat4 GetInverse(mat4 matrix);

			// Methods to do arithmetic operations with matrices (will change a matrix)
			mat4& add(const mat4& other);
			mat4& subtract(const mat4& other);
			mat4& multiply(const mat4& other);
			mat4& divide(const mat4& other);

			// Static versions 
			mat4& Add(mat4& left, const mat4& right);
			mat4& Subtract(mat4& left, const mat4& right);
			mat4& Multiply(mat4& left, const mat4& right);
			mat4& Divide(mat4& left, const mat4& right);

			// Same methods, but they will return a value rather than change a matrix
			mat4 sum(const mat4& other);
			mat4 difference(const mat4& other);
			mat4 product(const mat4& other);
			mat4 quotient(const mat4& other);

			// Static versions
			static mat4 Sum(mat4 left, const mat4& right);
			static mat4 Difference(mat4 left, const mat4& right);
			static mat4 Product(mat4 left, const mat4& right);
			static mat4 Quotient(mat4 left, const mat4& right);

			// Methods to do arithmetic operations with scalars (will change a matrix)
			mat4& addScalar(const float& scalar);
			mat4& subtractScalar(const float& scalar);
			mat4& multiplyScalar(const float& scalar);
			mat4& divideScalar(const float& scalar);

			// Static versions 
			mat4& AddScalar(mat4& matrix, const float& scalar);
			mat4& SubtractScalar(mat4& matrix, const float& scalar);
			mat4& MultiplyScalar(mat4& matrix, const float& scalar);
			mat4& DivideScalar(mat4& matrix, const float& scalar);

			// Same methods, but they will return a value rather than change a matrix
			mat4 scalarSum(const float& scalar);
			mat4 scalarDifference(const float& scalar);
			mat4 scalarProduct(const float& scalar);
			mat4 scalarQuotient(const float& scalar);

			// Static versions 
			static mat4 ScalarSum(mat4 matrix, const float& scalar);
			static mat4 ScalarDifference(mat4 matrix, const float& scalar);
			static mat4 ScalarProduct(mat4 matrix, const float& scalar);
			static mat4 ScalarQuotient(mat4 matrix, const float& scalar);

			// Methods to do relational and comparison operations with matrices
			bool isEqualTo(const mat4& matrix);
			bool isNotEqualTo(const mat4& matrix);

			// Static versions
			static bool IsEqualTo(mat4 left, const mat4& right);
			static bool IsNotEqualTo(mat4 left, const mat4& right);

			// Methods to print the matrix to the screen
			void print(); // Uses C or C++'s method of printing

			// Static version
			static void Print(mat4 matrix); // Uses C or C++'s method of printing
			static std::ostream& Print(std::ostream& stream, const mat4& matrix); // Uses C++'s way of printing

			/*          OPERATOR OVERLOAD BELOW          */

			// Overflow arithmetic operators with matrices
			friend mat4 operator+(mat4 left, const mat4& right);
			friend mat4 operator-(mat4 left, const mat4& right);
			friend mat4 operator*(mat4 left, const mat4& right);
			friend mat4 operator/(mat4 left, const mat4& right);

			// Overflow arithmetic operators with scalars
			friend mat4 operator+(mat4 matrix, const float& scalar);
			friend mat4 operator-(mat4 matrix, const float& scalar);
			friend mat4 operator*(mat4 matrix, const float& scalar);
			friend mat4 operator/(mat4 matrix, const float& scalar);

			// Overflow the compound assignment operators with matrices
			mat4& operator+=(const mat4& other);
			mat4& operator-=(const mat4& other);
			mat4& operator*=(const mat4& other);
			mat4& operator/=(const mat4& other);

			// Overflow the compound assignment operators with scalars
			mat4& operator+=(const float& scalar);
			mat4& operator-=(const float& scalar);
			mat4& operator*=(const float& scalar);
			mat4& operator/=(const float& scalar);

			// Overflow relational and comparison operators
			friend bool operator==(mat4 left, const mat4& right);
			friend bool operator!=(mat4 left, const mat4& right);

			// Overflow the bitwise operator
			friend std::ostream& operator<<(std::ostream& stream, mat4 matrix);
		};
	}
}