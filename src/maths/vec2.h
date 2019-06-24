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
		struct vec2
		{
			float x;
			float y;

			vec2();
			vec2(const float& x, const float& y);
			
			// Method to get a copy of the current vector
			vec2 getCopy();

			// Static version
			vec2 Copy(vec2 vector);

			// Useful methods to do miscellaneous operations with vectors (will change a vector)
			float magnitude();
			float length();
			float dotProduct(const vec2& other);
			vec2& normalize();

			// Static versions
			static float Magnitude(vec2& vector);
			static float Length(vec2& vector);
			static float DotProduct(vec2& left, const vec2& right);
			static vec2& Normalize(vec2& vector);

			// Same methods, but they will return a value rather than change a vector
			float getMagnitude();
			float getLength();
			float getDotProduct(const vec2& other);
			vec2 getNormal();

			// Static versions
			static float GetMagnitude(vec2 vector);
			static float GetLength(vec2 vector);
			static float GetDotProduct(vec2 left, const vec2& right);
			static vec2 GetNormal(vec2 vector);

			/*          OPERATION METHODS BELOW          */

			// Methods to do arithmetic operations with matrices (will change a vector)
			vec2& add(const vec2& other);
			vec2& subtract(const vec2& other);
			vec2& multiply(const vec2& other);
			vec2& divide(const vec2& other);

			// Static versions 
			vec2& Add(vec2& left, const vec2& right);
			vec2& Subtract(vec2& left, const vec2& right);
			vec2& Multiply(vec2& left, const vec2& right);
			vec2& Divide(vec2& left, const vec2& right);

			// Same methods, but they will return a value rather than change a vector
			vec2 sum(const vec2& other);
			vec2 difference(const vec2& other);
			vec2 product(const vec2& other);
			vec2 quotient(const vec2& other);

			// Static versions
			static vec2 Sum(vec2 left, const vec2& right);
			static vec2 Difference(vec2 left, const vec2& right);
			static vec2 Product(vec2 left, const vec2& right);
			static vec2 Quotient(vec2 left, const vec2& right);
			
			// Methods to do arithmetic operations with scalars (will change a vector)
			vec2& addScalar(const float& scalar);
			vec2& subtractScalar(const float& scalar);
			vec2& multiplyScalar(const float& scalar);
			vec2& divideScalar(const float& scalar);

			// Static versions 
			vec2& AddScalar(vec2& vector, const float& scalar);
			vec2& SubtractScalar(vec2& vector, const float& scalar);
			vec2& MultiplyScalar(vec2& vector, const float& scalar);
			vec2& DivideScalar(vec2& vector, const float& scalar);

			// Same methods, but they will return a value rather than change a vector
			vec2 scalarSum(const float& scalar);
			vec2 scalarDifference(const float& scalar);
			vec2 scalarProduct(const float& scalar);
			vec2 scalarQuotient(const float& scalar);

			// Static versions 
			static vec2 ScalarSum(vec2 vector, const float& scalar);
			static vec2 ScalarDifference(vec2 vector, const float& scalar);
			static vec2 ScalarProduct(vec2 vector, const float& scalar);
			static vec2 ScalarQuotient(vec2 vector, const float& scalar);

			// Methods to do relational and comparison operations with vectors
			bool isEqualTo(const vec2& other);
			bool isNotEqualTo(const vec2& other);

			// Static versions 
			static bool IsEqualTo(vec2 left, const vec2& right);
			static bool IsNotEqualTo(vec2 left, const vec2& right);  

			// Uses C's or C++'s method of printing
			void print();

			// Static versions
			// Uses C++'s method of printing
			static std::ostream& Print(std::ostream& stream, const vec2& vector);

			// Uses C's or C++'s method of printing
			static void Print(vec2 vector);

			/*          OPERATOR OVERLOAD BELOW          */

			// Overflow arithmetic operators with vectors
			friend vec2	operator+(vec2 left, const vec2& right);
			friend vec2 operator-(vec2 left, const vec2& right);
			friend vec2 operator*(vec2 left, const vec2& right);
			friend vec2 operator/(vec2 left, const vec2& right);
			
			// Overflow arithmetic operators with scalars
			friend vec2 operator+(vec2 vector, const float& scalar);
			friend vec2 operator-(vec2 vector, const float& scalar);
			friend vec2 operator*(vec2 vector, const float& scalar);
			friend vec2 operator/(vec2 vector, const float& scalar);

			// Overflow the compound assignment operators with vectors
			vec2& operator+=(const vec2& other);
			vec2& operator-=(const vec2& other);
			vec2& operator*=(const vec2& other);
			vec2& operator/=(const vec2& other);

			// Overflow the compound assignment operators with scalars
			vec2& operator+=(const float& scalar);
			vec2& operator-=(const float& scalar);
			vec2& operator*=(const float& scalar);
			vec2& operator/=(const float& scalar);
			
			// Overflow relational and comparison operators
			friend bool operator==(vec2 left, const vec2& right);
			friend bool operator!=(vec2 left, const vec2& right);

			// Overflow the bitwise operator
			friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);
		};
	}
}