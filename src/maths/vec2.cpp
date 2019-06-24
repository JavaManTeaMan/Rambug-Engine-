/*
DO NOT DELETE THIS COMMENT:
The ROM(Rambug Optical Mathematics) Library:
This software is written by Danyil Blyschak, 8/2015 (1st Build).
For any permissions, questions, or bug fixes, email the
support email that came with your distribution of this software.
*/

#include "vec2.h"

namespace Rambug
{
	namespace Math
	{
		vec2::vec2()
		{
			x = 0;
			y = 0;
		}

		vec2::vec2(const float& x, const float& y)
		{
			this->x = x;
			this->y = y;
		}

		vec2 vec2::getCopy()
		{
			vec2 copy;
			
			copy.x = x;
			copy.y = y;
		
			return copy;
		}

		// Static version
		vec2 vec2::Copy(vec2 vector)
		{
			return vector.getCopy();
		}

		// Useful methods to do miscellaneous operations with vectors (will change a vector)
		float vec2::magnitude()
		{
			float magnitude = sqrt(x * x + y * y);
			return magnitude;
		}

		float vec2::length()
		{
			float length = sqrt(x * x + y * y);
			return length;
		}
	
		float vec2::dotProduct(const vec2& other)
		{
			float dotProduct = (x * other.x + y * other.y);
			return dotProduct;
		}

		vec2& vec2::normalize()
		{
			divideScalar(getMagnitude());
			return *this;
		}

		// Static versions
		float vec2::Magnitude(vec2& vector)
		{
			return vector.magnitude();
		}

		float vec2::Length(vec2& vector)
		{
			return vector.length();
		}

		float vec2::DotProduct(vec2& left, const vec2& right)
		{
			return left.dotProduct(right);
		}

		vec2& vec2::Normalize(vec2& vector)
		{
			return vector.normalize();
		}

		// Same methods, but they will return a value rather than change a vector
		float vec2::getMagnitude()
		{
			vec2 copy = getCopy();
			return copy.magnitude();
		}

		float vec2::getLength()
		{
			vec2 copy = getCopy();
			return copy.length();
		}

		float vec2::getDotProduct(const vec2& other)
		{
			vec2 copy = getCopy();
			return copy.dotProduct(other);
		}

		vec2 vec2::getNormal()
		{
			vec2 copy = getCopy();
			copy.normalize();
			return copy;
		}

		// Static versions
		float vec2::GetMagnitude(vec2 vector)
		{
			return vector.getMagnitude();
		}

		float vec2::GetLength(vec2 vector)
		{
			return vector.getLength();
		}
		
		float vec2::GetDotProduct(vec2 left, const vec2& right)
		{
			return left.getDotProduct(right);
		}

		vec2 vec2::GetNormal(vec2 vector)
		{
			return vector.getNormal();
		}

		/*          OPERATION METHODS BELOW          */

		// Methods to do arithmetic operations
		vec2& vec2::add(const vec2& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		vec2& vec2::subtract(const vec2& other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		vec2& vec2::multiply(const vec2& other)
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}

		vec2& vec2::divide(const vec2& other)
		{
			try
			{
				if (other.x == 0)
					throw "Divide by zero error";
				x /= other.x;

				if (other.y == 0)
					throw "Divide by zero error";
				y /= other.y;
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
		vec2& vec2::Add(vec2& left, const vec2& right)
		{
			return left.add(right);
		}

		vec2& vec2::Subtract(vec2& left, const vec2& right)
		{
			return left.subtract(right);
		}

		vec2& vec2::Multiply(vec2& left, const vec2& right)
		{
			return left.multiply(right);
		}

		vec2& vec2::Divide(vec2& left, const vec2& right)
		{
			return left.divide(right);
		}

		// Same methods, but they will return a value rather than change a vector
		vec2 vec2::sum(const vec2& other)
		{
			vec2 copy = getCopy();
			copy.add(other);
			return copy;
		}

		vec2 vec2::difference(const vec2& other)
		{
			vec2 copy = getCopy();
			copy.subtract(other);
			return copy;
		}

		vec2 vec2::product(const vec2& other)
		{
			vec2 copy = getCopy();
			copy.multiply(other);
			return copy;
		}

		vec2 vec2::quotient(const vec2& other)
		{
			vec2 copy = getCopy();
			copy.divide(other);
			return copy;
		}

		// Static versions
		vec2 vec2::Sum(vec2 left, const vec2& right)
		{
			return left.sum(right);
		}

		vec2 vec2::Difference(vec2 left, const vec2& right)
		{
			return left.difference(right);
		}

		vec2 vec2::Product(vec2 left, const vec2& right)
		{
			return left.product(right);
		}

		vec2 vec2::Quotient(vec2 left, const vec2& right)
		{
			return left.quotient(right);
		}

		// Methods to do arithmetic operations with scalars
		vec2& vec2::addScalar(const float& scalar)
		{
			x += scalar;
			y += scalar;

			return *this;
		}
		
		vec2& vec2::subtractScalar(const float& scalar)
		{
			x -= scalar;
			y -= scalar;
			
			return *this;
		}
		
		vec2& vec2::multiplyScalar(const float& scalar)
		{
			x *= scalar;
			y *= scalar;

			return *this;
		}
	
		vec2& vec2::divideScalar(const float& scalar)
		{
			try
			{
				if (scalar == 0)
					throw "Divide by zero error";
				
				x /= scalar;
				y /= scalar;
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
		vec2& vec2::AddScalar(vec2& vector, const float& scalar)
		{
			return vector.addScalar(scalar);
		}

		vec2& vec2::SubtractScalar(vec2& vector, const float& scalar)
		{
			return vector.subtractScalar(scalar);
		}

		vec2& vec2::MultiplyScalar(vec2& vector, const float& scalar)
		{
			return vector.multiplyScalar(scalar);
		}

		vec2& vec2::DivideScalar(vec2& vector, const float& scalar)
		{
			return vector.divideScalar(scalar);
		}

		// Same methods, but they will return a value rather than change a vector
		vec2 vec2::scalarSum(const float& scalar)
		{
			vec2 copy = getCopy();
			copy.addScalar(scalar);
			return copy;
		}

		vec2 vec2::scalarDifference(const float& scalar)
		{
			vec2 copy = getCopy();
			copy.subtractScalar(scalar);
			return copy;
		}

		vec2 vec2::scalarProduct(const float& scalar)
		{
			vec2 copy = getCopy();
			copy.multiplyScalar(scalar);
			return copy;
		}

		vec2 vec2::scalarQuotient(const float& scalar)
		{
			vec2 copy = getCopy();
			copy.divideScalar (scalar);
			return copy;
		}

		// Static versions
		vec2 vec2::ScalarSum(vec2 vector, const float& scalar)
		{
			return vector.scalarSum(scalar);
		}

		vec2 vec2::ScalarDifference(vec2 vector, const float& scalar)
		{
			return vector.scalarDifference(scalar);
		}

		vec2 vec2::ScalarProduct(vec2 vector, const float& scalar)
		{
			return vector.scalarProduct(scalar);
		}

		vec2 vec2::ScalarQuotient(vec2 vector, const float& scalar)
		{
			return vector.scalarQuotient(scalar);
		}

		// Methods to do relational and comparison operations
		bool vec2::isEqualTo(const vec2& other)
		{
			return (x == other.x && y == other.y);
		}
		
		bool vec2::isNotEqualTo(const vec2& other)
		{
			return !isEqualTo(other);
		}
		
		// Static versions 
		bool vec2::IsEqualTo(vec2 left, const vec2& right)
		{
			return left.isEqualTo(right);
		}
		
		bool vec2::IsNotEqualTo(vec2 left, const vec2& right)
		{
			return left.isNotEqualTo(right);
		}  

		// Methods to print the vector to the screen
		void vec2::print()
		{
#if PRINT_METHOD_C
			printf("vec2: (%f, %f) \n", x, y);
#endif

#if PRINT_METHOD_CPP
			Print(std::cout, *this);
#endif
		}

		// Static versions
		// Uses C++'s method of printing
		std::ostream& vec2::Print(std::ostream& stream, const vec2& vector)
		{
			stream << "vec2: (" << vector.x << ", " << vector.y << ")";
			return stream;
		}

		// This static method will use C's printf method
		void vec2::Print(vec2 vector)
		{
			vector.print();
		}

		/*          OPERATOR OVERLOAD BELOW          */

		// Overflow arithmetic operators with vectors
		vec2 operator+(vec2 left, const vec2& right)
		{
			return vec2::Sum(left, right);
		}

		vec2 operator-(vec2 left, const vec2& right)
		{
			return vec2::Difference(left, right);
		}

		vec2 operator*(vec2 left, const vec2& right)
		{
			return vec2::Product(left, right);
		}
		
		vec2 operator/(vec2 left, const vec2& right)
		{
			return vec2::Quotient(left, right);
		}

		// Overflow arithmetic operators with scalars
		vec2 operator+(vec2 vector, const float& scalar)
		{
			return vec2::ScalarSum(vector, scalar);
		}
		
		vec2 operator-(vec2 vector, const float& scalar)
		{
			return vec2::ScalarDifference(vector, scalar);
		}
	
		vec2 operator*(vec2 vector, const float& scalar)
		{
			return vec2::ScalarProduct(vector, scalar);
		}
		
		vec2 operator/(vec2 vector, const float& scalar)
		{
			return vec2::ScalarQuotient(vector, scalar);
		}

		// Overflow the compound assignment operators with vectors
		vec2& vec2::operator+=(const vec2& other)
		{
			return add(other);
		}
		
		vec2& vec2::operator-=(const vec2& other)
		{
			return subtract(other);
		}
		
		vec2& vec2::operator*=(const vec2& other)
		{
			return multiply(other);
		}
		
		vec2& vec2::operator/=(const vec2& other)
		{
			return divide(other);
		}

		// Overflow the compound assignment operators with scalars
		vec2& vec2::operator+=(const float& scalar)
		{
			return addScalar(scalar);
		}
	
		vec2& vec2::operator-=(const float& scalar)
		{
			return subtractScalar(scalar);
		}
	
		vec2& vec2::operator*=(const float& scalar)
		{
			return multiplyScalar(scalar);
		}
		
		vec2& vec2::operator/=(const float& scalar)
		{
			return divideScalar(scalar);
		}

		// Overflow relational and comparison operators
		bool operator==(vec2 left, const vec2& right)
		{
			return vec2::IsEqualTo(left, right);
		}

		bool operator!=(vec2 left, const vec2& right)
		{
			return vec2::IsNotEqualTo(left, right);
		}
		
		// Overflow the bitwise operator
		std::ostream& operator<<(std::ostream& stream, const vec2& vector)
		{
			return vec2::Print(stream, vector);
		}
	}
}