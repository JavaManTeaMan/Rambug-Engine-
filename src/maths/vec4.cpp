/*
DO NOT DELETE THIS COMMENT:
The ROM(Rambug Optical Mathematics) Library:
This software is written by Danyil Blyschak, 8/2015 (1st Build).
For any permissions, questions, or bug fixes, email the
support email that came with your distribution of this software.
*/

#include "vec4.h"

namespace Rambug
{
	namespace Math
	{
		vec4::vec4()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}

		vec4::vec4(const float& x, const float& y, const float& z, const float& w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		vec4 vec4::getCopy()
		{
			vec4 copy;

			copy.x = x;
			copy.y = y;
			copy.z = z;
			copy.w = w;

			return copy;
		}

		// Static version
		vec4 vec4::Copy(vec4 vector)
		{
			return vector.getCopy();
		}

		// Useful methods to do miscellaneous operations with vectors (will change a vector)
		float vec4::magnitude()
		{
			float magnitude = sqrt(x * x + y * y + z * z + w * w);
			return magnitude;
		}

		float vec4::length()
		{
			float length = sqrt(x * x + y * y + z * z + w * w);
			return length;
		}

		float vec4::dotProduct(const vec4& other)
		{
			float dotProduct = (x * other.x + y * other.y + z * other.z + w * other.w);
			return dotProduct;
		}

		vec4& vec4::normalize()
		{
			divideScalar(getMagnitude());
			return *this;
		}

		// Static versions
		float vec4::Magnitude(vec4& vector)
		{
			return vector.magnitude();
		}

		float vec4::Length(vec4& vector)
		{
			return vector.length();
		}

		float vec4::DotProduct(vec4& left, const vec4& right)
		{
			return left.dotProduct(right);
		}

		vec4& vec4::Normalize(vec4& vector)
		{
			return vector.normalize();
		}

		// Same methods, but they will return a value rather than change a vector
		float vec4::getMagnitude()
		{
			vec4 copy = getCopy();
			return copy.magnitude();
		}

		float vec4::getLength()
		{
			vec4 copy = getCopy();
			return copy.length();
		}

		float vec4::getDotProduct(const vec4& other)
		{
			vec4 copy = getCopy();
			return copy.dotProduct(other);
		}

		vec4 vec4::getNormal()
		{
			vec4 copy = getCopy();
			copy.normalize();
			return copy;
		}

		// Static versions
		float vec4::GetMagnitude(vec4 vector)
		{
			return vector.getMagnitude();
		}

		float vec4::GetLength(vec4 vector)
		{
			return vector.getLength();
		}

		float vec4::GetDotProduct(vec4 left, const vec4& right)
		{
			return left.getDotProduct(right);
		}

		vec4 vec4::GetNormal(vec4 vector)
		{
			return vector.getNormal();
		}

		/*          OPERATION METHODS BELOW          */

		// Methods to do arithmetic operations
		vec4& vec4::add(const vec4& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;

			return *this;
		}

		vec4& vec4::subtract(const vec4& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;

			return *this;
		}

		vec4& vec4::multiply(const vec4& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;

			return *this;
		}

		vec4& vec4::divide(const vec4& other)
		{
			try
			{
				if (other.x == 0)
					throw "Divide by zero error";
				x /= other.x;

				if (other.y == 0)
					throw "Divide by zero error";
				y /= other.y;

				if (other.z == 0)
					throw "Divide by zero error";
				z /= other.z;

				if (other.w == 0)
					throw "Divide by zero error";
				w /= other.w;
			}
			catch (const char* e)
			{
#if PRINT_METHOD_C
				printf("MATH EXCEPTION OCCURRED: %s \n", e);
#endif
#if PRINT_METHOD_CPP
				std::cout << "MATH EXCEPTION OCCURRED: " << e << std::endl;
#endif
			}

			return *this;
		}

		// Static versions 
		vec4& vec4::Add(vec4& left, const vec4& right)
		{
			return left.add(right);
		}

		vec4& vec4::Subtract(vec4& left, const vec4& right)
		{
			return left.subtract(right);
		}

		vec4& vec4::Multiply(vec4& left, const vec4& right)
		{
			return left.multiply(right);
		}

		vec4& vec4::Divide(vec4& left, const vec4& right)
		{
			return left.divide(right);
		}

		// Same methods, but they will return a value rather than change a vector
		vec4 vec4::sum(const vec4& other)
		{
			vec4 copy = getCopy();
			copy.add(other);
			return copy;
		}

		vec4 vec4::difference(const vec4& other)
		{
			vec4 copy = getCopy();
			copy.subtract(other);
			return copy;
		}

		vec4 vec4::product(const vec4& other)
		{
			vec4 copy = getCopy();
			copy.multiply(other);
			return copy;
		}

		vec4 vec4::quotient(const vec4& other)
		{
			vec4 copy = getCopy();
			copy.divide(other);
			return copy;
		}

		// Static versions
		vec4 vec4::Sum(vec4 left, const vec4& right)
		{
			return left.sum(right);
		}

		vec4 vec4::Difference(vec4 left, const vec4& right)
		{
			return left.difference(right);
		}

		vec4 vec4::Product(vec4 left, const vec4& right)
		{
			return left.product(right);
		}

		vec4 vec4::Quotient(vec4 left, const vec4& right)
		{
			return left.quotient(right);
		}

		// Methods to do arithmetic operations with scalars
		vec4& vec4::addScalar(const float& scalar)
		{
			x += scalar;
			y += scalar;
			z += scalar;
			w += scalar;

			return *this;
		}

		vec4& vec4::subtractScalar(const float& scalar)
		{
			x -= scalar;
			y -= scalar;
			z -= scalar;
			w -= scalar;

			return *this;
		}

		vec4& vec4::multiplyScalar(const float& scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;

			return *this;
		}

		vec4& vec4::divideScalar(const float& scalar)
		{
			try
			{
				if (scalar == 0)
					throw "Divide by zero error";

				x /= scalar;
				y /= scalar;
				z /= scalar;
				w /= scalar;
			}
			catch (const char* e)
			{
#if PRINT_METHOD_C
				printf("MATH EXCEPTION OCCURRED: %s \n", e);
#endif
#if PRINT_METHOD_CPP
				std::cout << "MATH EXCEPTION OCCURRED: " << e << std::endl;
#endif
			}
			return *this;
		}

		// Static versions 
		vec4& vec4::AddScalar(vec4& vector, const float& scalar)
		{
			return vector.addScalar(scalar);
		}

		vec4& vec4::SubtractScalar(vec4& vector, const float& scalar)
		{
			return vector.subtractScalar(scalar);
		}

		vec4& vec4::MultiplyScalar(vec4& vector, const float& scalar)
		{
			return vector.multiplyScalar(scalar);
		}

		vec4& vec4::DivideScalar(vec4& vector, const float& scalar)
		{
			return vector.divideScalar(scalar);
		}

		// Same methods, but they will return a value rather than change a vector
		vec4 vec4::scalarSum(const float& scalar)
		{
			vec4 copy = getCopy();
			copy.addScalar(scalar);
			return copy;
		}

		vec4 vec4::scalarDifference(const float& scalar)
		{
			vec4 copy = getCopy();
			copy.subtractScalar(scalar);
			return copy;
		}

		vec4 vec4::scalarProduct(const float& scalar)
		{
			vec4 copy = getCopy();
			copy.multiplyScalar(scalar);
			return copy;
		}

		vec4 vec4::scalarQuotient(const float& scalar)
		{
			vec4 copy = getCopy();
			copy.divideScalar(scalar);
			return copy;
		}

		// Static versions
		vec4 vec4::ScalarSum(vec4 vector, const float& scalar)
		{
			return vector.scalarSum(scalar);
		}

		vec4 vec4::ScalarDifference(vec4 vector, const float& scalar)
		{
			return vector.scalarDifference(scalar);
		}

		vec4 vec4::ScalarProduct(vec4 vector, const float& scalar)
		{
			return vector.scalarProduct(scalar);
		}

		vec4 vec4::ScalarQuotient(vec4 vector, const float& scalar)
		{
			return vector.scalarQuotient(scalar);
		}

		// Methods to do relational and comparison operations
		bool vec4::isEqualTo(const vec4& other)
		{
			return (x == other.x && y == other.y && z == other.z);
		}

		bool vec4::isNotEqualTo(const vec4& other)
		{
			return !isEqualTo(other);
		}

		// Static versions 
		bool vec4::IsEqualTo(vec4 left, const vec4& right)
		{
			return left.isEqualTo(right);
		}

		bool vec4::IsNotEqualTo(vec4 left, const vec4& right)
		{
			return left.isNotEqualTo(right);
		}

		// Methods to print the vector to the screen
		void vec4::print()
		{
#if PRINT_METHOD_C
			printf("vec4: (%f, %f, %f, %f) \n", x, y, z, w);
#endif

#if PRINT_METHOD_CPP
			Print(std::cout, *this);
#endif
		}

		// Static versions
		// Uses C++'s method of printing
		std::ostream& vec4::Print(std::ostream& stream, const vec4& vector)
		{
			stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}

		// This static method will use C's printf method
		void vec4::Print(vec4 vector)
		{
			vector.print();
		}

		/*          OPERATOR OVERLOAD BELOW          */

		// Overflow arithmetic operators with vectors
		vec4 operator+(vec4 left, const vec4& right)
		{
			return vec4::Sum(left, right);
		}

		vec4 operator-(vec4 left, const vec4& right)
		{
			return vec4::Difference(left, right);
		}

		vec4 operator*(vec4 left, const vec4& right)
		{
			return vec4::Product(left, right);
		}

		vec4 operator/(vec4 left, const vec4& right)
		{
			return vec4::Quotient(left, right);
		}

		// Overflow arithmetic operators with scalars
		vec4 operator+(vec4 vector, const float& scalar)
		{
			return vec4::ScalarSum(vector, scalar);
		}

		vec4 operator-(vec4 vector, const float& scalar)
		{
			return vec4::ScalarDifference(vector, scalar);
		}

		vec4 operator*(vec4 vector, const float& scalar)
		{
			return vec4::ScalarProduct(vector, scalar);
		}

		vec4 operator/(vec4 vector, const float& scalar)
		{
			return vec4::ScalarQuotient(vector, scalar);
		}

		// Overflow the compound assignment operators with vectors
		vec4& vec4::operator+=(const vec4& other)
		{
			return add(other);
		}

		vec4& vec4::operator-=(const vec4& other)
		{
			return subtract(other);
		}

		vec4& vec4::operator*=(const vec4& other)
		{
			return multiply(other);
		}

		vec4& vec4::operator/=(const vec4& other)
		{
			return divide(other);
		}

		// Overflow the compound assignment operators with scalars
		vec4& vec4::operator+=(const float& scalar)
		{
			return addScalar(scalar);
		}

		vec4& vec4::operator-=(const float& scalar)
		{
			return subtractScalar(scalar);
		}

		vec4& vec4::operator*=(const float& scalar)
		{
			return multiplyScalar(scalar);
		}

		vec4& vec4::operator/=(const float& scalar)
		{
			return divideScalar(scalar);
		}

		// Overflow relational and comparison operators
		bool operator==(vec4 left, const vec4& right)
		{
			return vec4::IsEqualTo(left, right);
		}

		bool operator!=(vec4 left, const vec4& right)
		{
			return vec4::IsNotEqualTo(left, right);
		}

		// Overflow the bitwise operator
		std::ostream& operator<<(std::ostream& stream, const vec4& vector)
		{
			return vec4::Print(stream, vector);
		}
	}
}