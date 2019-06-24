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

#define PRINT_METHOD_C 1
#define PRINT_METHOD_CPP 0

namespace Rambug
{
	namespace Math
	{
		struct vec4
		{
			float x;
			float y;
			float z;
			float w;

			vec4();
			vec4(const float& x, const float& y, const float& z, const float& w);

			// Method to get a copy of the current vector
			vec4 getCopy();

			// Static version
			vec4 Copy(vec4 vector);

			// Useful methods to do miscellaneous operations with vectors (will change a vector)
			float magnitude();
			float length();
			vec4& normalize();
			float dotProduct(const vec4& other);

			// Static versions
			static float Magnitude(vec4& vector);
			static float Length(vec4& vector);
			static float DotProduct(vec4& left, const vec4& right);
			static vec4& Normalize(vec4& vector);

			// Same methods, but they will return a value rather than change a vector
			float getMagnitude();
			float getLength();
			float getDotProduct(const vec4& other);
			vec4 getNormal();

			// Static versions
			static float GetMagnitude(vec4 vector);
			static float GetLength(vec4 vector);
			static float GetDotProduct(vec4 left, const vec4& right);
			static vec4 GetNormal(vec4 vector);

			/*          OPERATION METHODS BELOW          */

			// Methods to do arithmetic operations with matrices (will change a vector)
			vec4& add(const vec4& other);
			vec4& subtract(const vec4& other);
			vec4& multiply(const vec4& other);
			vec4& divide(const vec4& other);

			// Static versions 
			vec4& Add(vec4& left, const vec4& right);
			vec4& Subtract(vec4& left, const vec4& right);
			vec4& Multiply(vec4& left, const vec4& right);
			vec4& Divide(vec4& left, const vec4& right);

			// Same methods, but they will return a value rather than change a vector
			vec4 sum(const vec4& other);
			vec4 difference(const vec4& other);
			vec4 product(const vec4& other);
			vec4 quotient(const vec4& other);

			// Static versions
			static vec4 Sum(vec4 left, const vec4& right);
			static vec4 Difference(vec4 left, const vec4& right);
			static vec4 Product(vec4 left, const vec4& right);
			static vec4 Quotient(vec4 left, const vec4& right);

			// Methods to do arithmetic operations with scalars (will change a vector)
			vec4& addScalar(const float& scalar);
			vec4& subtractScalar(const float& scalar);
			vec4& multiplyScalar(const float& scalar);
			vec4& divideScalar(const float& scalar);

			// Static versions 
			vec4& AddScalar(vec4& vector, const float& scalar);
			vec4& SubtractScalar(vec4& vector, const float& scalar);
			vec4& MultiplyScalar(vec4& vector, const float& scalar);
			vec4& DivideScalar(vec4& vector, const float& scalar);

			// Same methods, but they will return a value rather than change a vector
			vec4 scalarSum(const float& scalar);
			vec4 scalarDifference(const float& scalar);
			vec4 scalarProduct(const float& scalar);
			vec4 scalarQuotient(const float& scalar);

			// Static versions 
			static vec4 ScalarSum(vec4 vector, const float& scalar);
			static vec4 ScalarDifference(vec4 vector, const float& scalar);
			static vec4 ScalarProduct(vec4 vector, const float& scalar);
			static vec4 ScalarQuotient(vec4 vector, const float& scalar);

			// Methods to do relational and comparison operations with vectors
			bool isEqualTo(const vec4& other);
			bool isNotEqualTo(const vec4& other);

			// Static versions 
			static bool IsEqualTo(vec4 left, const vec4& right);
			static bool IsNotEqualTo(vec4 left, const vec4& right);

			// Uses C's or C++'s method of printing
			void print();

			// Static versions
			// Uses C++'s method of printing
			static std::ostream& Print(std::ostream& stream, const vec4& vector);

			// Uses C's or C++'s method of printing
			static void Print(vec4 vector);

			/*          OPERATOR OVERLOAD BELOW          */

			// Overflow arithmetic operators with vectors
			friend vec4	operator+(vec4 left, const vec4& right);
			friend vec4 operator-(vec4 left, const vec4& right);
			friend vec4 operator*(vec4 left, const vec4& right);
			friend vec4 operator/(vec4 left, const vec4& right);

			// Overflow arithmetic operators with scalars
			friend vec4 operator+(vec4 vector, const float& scalar);
			friend vec4 operator-(vec4 vector, const float& scalar);
			friend vec4 operator*(vec4 vector, const float& scalar);
			friend vec4 operator/(vec4 vector, const float& scalar);

			// Overflow the compound assignment operators with vectors
			vec4& operator+=(const vec4& other);
			vec4& operator-=(const vec4& other);
			vec4& operator*=(const vec4& other);
			vec4& operator/=(const vec4& other);

			// Overflow the compound assignment operators with scalars
			vec4& operator+=(const float& scalar);
			vec4& operator-=(const float& scalar);
			vec4& operator*=(const float& scalar);
			vec4& operator/=(const float& scalar);

			// Overflow relational and comparison operators
			friend bool operator==(vec4 left, const vec4& right);
			friend bool operator!=(vec4 left, const vec4& right);

			// Overflow the bitwise operator
			friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
		};
	}
}