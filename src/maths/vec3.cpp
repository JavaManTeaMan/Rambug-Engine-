/*
DO NOT DELETE THIS COMMENT:
The ROM(Rambug Optical Mathematics) Library:
This software is written by Danyil Blyschak, 8/2015 (1st Build).
For any permissions, questions, or bug fixes, email the
support email that came with your distribution of this software.
*/

#include "vec3.h"

namespace Rambug
{
	namespace Math
	{
		vec3::vec3()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		vec3::vec3(const float& x, const float& y, const float& z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		vec3 vec3::getCopy()
		{
			vec3 copy;

			copy.x = x;
			copy.y = y;
			copy.z = z;

			return copy;
		}

		// Static version
		vec3 vec3::Copy(vec3 vector)
		{
			return vector.getCopy();
		}

		// Useful methods to do miscellaneous operations with vectors (will change a vector)
		float vec3::magnitude()
		{
			float magnitude = sqrt(x * x + y * y + z * z);
			return magnitude;
		}

		float vec3::length()
		{
			float length = sqrt(x * x + y * y + z * z);
			return length;
		}

		float vec3::dotProduct(const vec3& other)
		{
			float dotProduct = (x * other.x + y * other.y + z * other.z);
			return dotProduct;
		}

		vec3& vec3::crossProduct(const vec3& other)
		{
			vec3 copy = getCopy();

			x = (copy.y * other.z) - (copy.z * other.y);
			y = (copy.z * other.x) - (copy.x * other.z);
			z = (copy.x * other.y) - (copy.y * other.x);

			return *this;
		}

		vec3& vec3::normalize()
		{
			divideScalar(getMagnitude());
			return *this;
		}

		// Static versions
		float vec3::Magnitude(vec3& vector)
		{
			return vector.magnitude();
		}

		float vec3::Length(vec3& vector)
		{
			return vector.length();
		}

		float vec3::DotProduct(vec3& left, const vec3& right)
		{
			return left.dotProduct(right);
		}

		vec3& vec3::CrossProduct(vec3& left, const vec3& right)
		{
			return left.crossProduct(right);
		}

		vec3& vec3::Normalize(vec3& vector)
		{
			return vector.normalize();
		}

		// Same methods, but they will return a value rather than change a vector
		float vec3::getMagnitude()
		{
			vec3 copy = getCopy();
			return copy.magnitude();
		}

		float vec3::getLength()
		{
			vec3 copy = getCopy();
			return copy.length();
		}

		float vec3::getDotProduct(const vec3& other)
		{
			vec3 copy = getCopy();
			return copy.dotProduct(other);
		}

		vec3 vec3::getCrossProduct(const vec3& other)
		{
			vec3 copy = getCopy();
			copy.crossProduct(other);
			return copy;
		}

		vec3 vec3::getNormal()
		{
			vec3 copy = getCopy();
			copy.normalize();
			return copy;
		}

		// Static versions
		float vec3::GetMagnitude(vec3 vector)
		{
			return vector.getMagnitude();
		}

		float vec3::GetLength(vec3 vector)
		{
			return vector.getLength();
		}

		float vec3::GetDotProduct(vec3 left, const vec3& right)
		{
			return left.getDotProduct(right);
		}

		vec3 vec3::GetCrossProduct(vec3 left, const vec3& right)
		{
			return left.getCrossProduct(right);
		}

		vec3 vec3::GetNormal(vec3 vector)
		{
			return vector.getNormal();
		}

		/*          OPERATION METHODS BELOW          */

		// Methods to do arithmetic operations
		vec3& vec3::add(const vec3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}

		vec3& vec3::subtract(const vec3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}

		vec3& vec3::multiply(const vec3& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;

			return *this;
		}

		vec3& vec3::divide(const vec3& other)
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
		vec3& vec3::Add(vec3& left, const vec3& right)
		{
			return left.add(right);
		}

		vec3& vec3::Subtract(vec3& left, const vec3& right)
		{
			return left.subtract(right);
		}

		vec3& vec3::Multiply(vec3& left, const vec3& right)
		{
			return left.multiply(right);
		}

		vec3& vec3::Divide(vec3& left, const vec3& right)
		{
			return left.divide(right);
		}

		// Same methods, but they will return a value rather than change a vector
		vec3 vec3::sum(const vec3& other)
		{
			vec3 copy = getCopy();
			copy.add(other);
			return copy;
		}

		vec3 vec3::difference(const vec3& other)
		{
			vec3 copy = getCopy();
			copy.subtract(other);
			return copy;
		}

		vec3 vec3::product(const vec3& other)
		{
			vec3 copy = getCopy();
			copy.multiply(other);
			return copy;
		}

		vec3 vec3::quotient(const vec3& other)
		{
			vec3 copy = getCopy();
			copy.divide(other);
			return copy;
		}

		// Static versions
		vec3 vec3::Sum(vec3 left, const vec3& right)
		{
			return left.sum(right);
		}

		vec3 vec3::Difference(vec3 left, const vec3& right)
		{
			return left.difference(right);
		}

		vec3 vec3::Product(vec3 left, const vec3& right)
		{
			return left.product(right);
		}

		vec3 vec3::Quotient(vec3 left, const vec3& right)
		{
			return left.quotient(right);
		}

		// Methods to do arithmetic operations with scalars
		vec3& vec3::addScalar(const float& scalar)
		{
			x += scalar;
			y += scalar;
			z += scalar;

			return *this;
		}

		vec3& vec3::subtractScalar(const float& scalar)
		{
			x -= scalar;
			y -= scalar;
			z -= scalar;

			return *this;
		}

		vec3& vec3::multiplyScalar(const float& scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;

			return *this;
		}

		vec3& vec3::divideScalar(const float& scalar)
		{
			try
			{
				if (scalar == 0)
					throw "Divide by zero error";

				x /= scalar;
				y /= scalar;
				z /= scalar;
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
		vec3& vec3::AddScalar(vec3& vector, const float& scalar)
		{
			return vector.addScalar(scalar);
		}

		vec3& vec3::SubtractScalar(vec3& vector, const float& scalar)
		{
			return vector.subtractScalar(scalar);
		}

		vec3& vec3::MultiplyScalar(vec3& vector, const float& scalar)
		{
			return vector.multiplyScalar(scalar);
		}

		vec3& vec3::DivideScalar(vec3& vector, const float& scalar)
		{
			return vector.divideScalar(scalar);
		}

		// Same methods, but they will return a value rather than change a vector
		vec3 vec3::scalarSum(const float& scalar)
		{
			vec3 copy = getCopy();
			copy.addScalar(scalar);
			return copy;
		}

		vec3 vec3::scalarDifference(const float& scalar)
		{
			vec3 copy = getCopy();
			copy.subtractScalar(scalar);
			return copy;
		}

		vec3 vec3::scalarProduct(const float& scalar)
		{
			vec3 copy = getCopy();
			copy.multiplyScalar(scalar);
			return copy;
		}

		vec3 vec3::scalarQuotient(const float& scalar)
		{
			vec3 copy = getCopy();
			copy.divideScalar(scalar);
			return copy;
		}

		// Static versions
		vec3 vec3::ScalarSum(vec3 vector, const float& scalar)
		{
			return vector.scalarSum(scalar);
		}

		vec3 vec3::ScalarDifference(vec3 vector, const float& scalar)
		{
			return vector.scalarDifference(scalar);
		}

		vec3 vec3::ScalarProduct(vec3 vector, const float& scalar)
		{
			return vector.scalarProduct(scalar);
		}

		vec3 vec3::ScalarQuotient(vec3 vector, const float& scalar)
		{
			return vector.scalarQuotient(scalar);
		}

		// Methods to do relational and comparison operations
		bool vec3::isEqualTo(const vec3& other)
		{
			return (x == other.x && y == other.y && z == other.z);
		}

		bool vec3::isNotEqualTo(const vec3& other)
		{
			return !isEqualTo(other);
		}

		// Static versions 
		bool vec3::IsEqualTo(vec3 left, const vec3& right)
		{
			return left.isEqualTo(right);
		}

		bool vec3::IsNotEqualTo(vec3 left, const vec3& right)
		{
			return left.isNotEqualTo(right);
		}

		// Methods to print the vector to the screen
		void vec3::print()
		{
#if PRINT_METHOD_C
			printf("vec3: (%f, %f, %f) \n", x, y, z);
#endif

#if PRINT_METHOD_CPP
			Print(std::cout, *this);
#endif
		}

		// Static versions
		// Uses C++'s method of printing
		std::ostream& vec3::Print(std::ostream& stream, const vec3& vector)
		{
			stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z <<  ")";
			return stream;
		}

		// This static method will use C's printf method
		void vec3::Print(vec3 vector)
		{
			vector.print();
		}

		/*          OPERATOR OVERLOAD BELOW          */

		// Overflow arithmetic operators with vectors
		vec3 operator+(vec3 left, const vec3& right)
		{
			return vec3::Sum(left, right);
		}

		vec3 operator-(vec3 left, const vec3& right)
		{
			return vec3::Difference(left, right);
		}

		vec3 operator*(vec3 left, const vec3& right)
		{
			return vec3::Product(left, right);
		}

		vec3 operator/(vec3 left, const vec3& right)
		{
			return vec3::Quotient(left, right);
		}

		// Overflow arithmetic operators with scalars
		vec3 operator+(vec3 vector, const float& scalar)
		{
			return vec3::ScalarSum(vector, scalar);
		}

		vec3 operator-(vec3 vector, const float& scalar)
		{
			return vec3::ScalarDifference(vector, scalar);
		}

		vec3 operator*(vec3 vector, const float& scalar)
		{
			return vec3::ScalarProduct(vector, scalar);
		}

		vec3 operator/(vec3 vector, const float& scalar)
		{
			return vec3::ScalarQuotient(vector, scalar);
		}

		// Overflow the compound assignment operators with vectors
		vec3& vec3::operator+=(const vec3& other)
		{
			return add(other);
		}

		vec3& vec3::operator-=(const vec3& other)
		{
			return subtract(other);
		}

		vec3& vec3::operator*=(const vec3& other)
		{
			return multiply(other);
		}

		vec3& vec3::operator/=(const vec3& other)
		{
			return divide(other);
		}

		// Overflow the compound assignment operators with scalars
		vec3& vec3::operator+=(const float& scalar)
		{
			return addScalar(scalar);
		}

		vec3& vec3::operator-=(const float& scalar)
		{
			return subtractScalar(scalar);
		}

		vec3& vec3::operator*=(const float& scalar)
		{
			return multiplyScalar(scalar);
		}

		vec3& vec3::operator/=(const float& scalar)
		{
			return divideScalar(scalar);
		}

		// Overflow relational and comparison operators
		bool operator==(vec3 left, const vec3& right)
		{
			return vec3::IsEqualTo(left, right);
		}

		bool operator!=(vec3 left, const vec3& right)
		{
			return vec3::IsNotEqualTo(left, right);
		}

		// Overflow the bitwise operator
		std::ostream& operator<<(std::ostream& stream, const vec3& vector)
		{
			return vec3::Print(stream, vector);
		}
	}
}