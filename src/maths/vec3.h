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
		struct vec3
		{
			float x;
			float y;
			float z;

			vec3();
			vec3(const float& x, const float& y, const float& z);

			// Method to get a copy of the current vector
			vec3 getCopy();

			// Static version
			vec3 Copy(vec3 vector);

			// Useful methods to do miscellaneous operations with vectors (will change a vector)
			float magnitude();
			float length();
			float dotProduct(const vec3& other);
			vec3& crossProduct(const vec3& other);
			vec3& normalize();

			// Static versions
			static float Magnitude(vec3& vector);
			static float Length(vec3& vector);
			static float DotProduct(vec3& left, const vec3& right);
			static vec3& CrossProduct(vec3& left, const vec3& right);
			static vec3& Normalize(vec3& vector);

			// Same methods, but they will return a value rather than change a vector
			float getMagnitude();
			float getLength();
			float getDotProduct(const vec3& other);
			vec3 getCrossProduct(const vec3& other);
			vec3 getNormal();

			// Static versions
			static float GetMagnitude(vec3 vector);
			static float GetLength(vec3 vector);
			static float GetDotProduct(vec3 left, const vec3& right);
			static vec3 GetCrossProduct(vec3 left, const vec3& right);
			static vec3 GetNormal(vec3 vector);

			/*          OPERATION METHODS BELOW          */

			// Methods to do arithmetic operations with matrices (will change a vector)
			vec3& add(const vec3& other);
			vec3& subtract(const vec3& other);
			vec3& multiply(const vec3& other);
			vec3& divide(const vec3& other);

			// Static versions 
			vec3& Add(vec3& left, const vec3& right);
			vec3& Subtract(vec3& left, const vec3& right);
			vec3& Multiply(vec3& left, const vec3& right);
			vec3& Divide(vec3& left, const vec3& right);

			// Same methods, but they will return a value rather than change a vector
			vec3 sum(const vec3& other);
			vec3 difference(const vec3& other);
			vec3 product(const vec3& other);
			vec3 quotient(const vec3& other);

			// Static versions
			static vec3 Sum(vec3 left, const vec3& right);
			static vec3 Difference(vec3 left, const vec3& right);
			static vec3 Product(vec3 left, const vec3& right);
			static vec3 Quotient(vec3 left, const vec3& right);

			// Methods to do arithmetic operations with scalars (will change a vector)
			vec3& addScalar(const float& scalar);
			vec3& subtractScalar(const float& scalar);
			vec3& multiplyScalar(const float& scalar);
			vec3& divideScalar(const float& scalar);

			// Static versions 
			vec3& AddScalar(vec3& vector, const float& scalar);
			vec3& SubtractScalar(vec3& vector, const float& scalar);
			vec3& MultiplyScalar(vec3& vector, const float& scalar);
			vec3& DivideScalar(vec3& vector, const float& scalar);

			// Same methods, but they will return a value rather than change a vector
			vec3 scalarSum(const float& scalar);
			vec3 scalarDifference(const float& scalar);
			vec3 scalarProduct(const float& scalar);
			vec3 scalarQuotient(const float& scalar);

			// Static versions 
			static vec3 ScalarSum(vec3 vector, const float& scalar);
			static vec3 ScalarDifference(vec3 vector, const float& scalar);
			static vec3 ScalarProduct(vec3 vector, const float& scalar);
			static vec3 ScalarQuotient(vec3 vector, const float& scalar);

			// Methods to do relational and comparison operations with vectors
			bool isEqualTo(const vec3& other);
			bool isNotEqualTo(const vec3& other);

			// Static versions 
			static bool IsEqualTo(vec3 left, const vec3& right);
			static bool IsNotEqualTo(vec3 left, const vec3& right);

			// Uses C's or C++'s method of printing
			void print();

			// Static versions
			// Uses C++'s method of printing
			static std::ostream& Print(std::ostream& stream, const vec3& vector);

			// Uses C's or C++'s method of printing
			static void Print(vec3 vector);

			/*          OPERATOR OVERLOAD BELOW          */

			// Overflow arithmetic operators with vectors
			friend vec3	operator+(vec3 left, const vec3& right);
			friend vec3 operator-(vec3 left, const vec3& right);
			friend vec3 operator*(vec3 left, const vec3& right);
			friend vec3 operator/(vec3 left, const vec3& right);

			// Overflow arithmetic operators with scalars
			friend vec3 operator+(vec3 vector, const float& scalar);
			friend vec3 operator-(vec3 vector, const float& scalar);
			friend vec3 operator*(vec3 vector, const float& scalar);
			friend vec3 operator/(vec3 vector, const float& scalar);

			// Overflow the compound assignment operators with vectors
			vec3& operator+=(const vec3& other);
			vec3& operator-=(const vec3& other);
			vec3& operator*=(const vec3& other);
			vec3& operator/=(const vec3& other);

			// Overflow the compound assignment operators with scalars
			vec3& operator+=(const float& scalar);
			vec3& operator-=(const float& scalar);
			vec3& operator*=(const float& scalar);
			vec3& operator/=(const float& scalar);

			// Overflow relational and comparison operators
			friend bool operator==(vec3 left, const vec3& right);
			friend bool operator!=(vec3 left, const vec3& right);

			// Overflow the bitwise operator
			friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
		};
	}
}