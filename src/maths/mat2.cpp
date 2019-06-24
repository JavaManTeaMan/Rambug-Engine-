/*
	DO NOT DELETE THIS COMMENT:
	The ROM(Rambug Optical Mathematics) Library:
	This software is written by Danyil Blyschak, 8/2015 (1st Build).
	For any permissions, questions, or bug fixes, email the
	support email that came with your distribution of this software.
*/

#include "mat2.h"

namespace Rambug
{
	namespace Math
	{
		mat2::mat2()
		{
			for (int i = 0; i < 2 * 2; i++)
			{
				elements[i] = 0.0f;
			}
		}

		mat2::mat2(float diagonal)
		{
			for (int i = 0; i < 2 * 2; i++)
			{
				elements[i] = 0.0f;
			}

			elements[0 + 0 * 2] = diagonal;
			elements[1 + 1 * 2] = diagonal;
			elements[2 + 2 * 2] = diagonal;
		}

		// Method to get a copy of the current matrix
		mat2 mat2::getCopy()
		{
			// Returns a copy of the current matrix
			mat2 copy;

			for (int i = 0; i < 2 * 2; i++)
			{
				copy.elements[i] = elements[i];
			}

			return copy;
		}

		// Static version
		mat2 mat2::Copy(mat2 matrix)
		{
			return matrix.getCopy();
		}

		// Methods to get matrices
		mat2 mat2::Identity()
		{
			return mat2(1);
		}

		mat2 mat2::Sign()
		{
			// Return a 2 x 2 sign matrix

			// + - 
			// - +

			mat2 signMatrix(1);

			// Column one
			signMatrix.elements[0 + 0 * 2] = 1;
			signMatrix.elements[1 + 0 * 2] = -1;
			signMatrix.elements[2 + 0 * 2] = 1;

			// Column two
			signMatrix.elements[0 + 1 * 2] = -1;
			signMatrix.elements[1 + 1 * 2] = 1;
			signMatrix.elements[2 + 1 * 2] = -1;

			return signMatrix;
		}

		// Useful methods to do miscellaneous operations with matrices (will change the current matrix)
		float mat2::determinant()
		{
			float left = elements[0 + 0 * 2] * elements[1 + 1 * 2];
			float right = elements[0 + 1 * 2] * elements[1 + 0 * 2];

			return left - right;
		}

		mat2& mat2::transpose()
		{
			// Make the columns of the matrix to rows
			mat2 copy = getCopy();

			for (int y = 0; y < 2; y++)
			{
				for (int x = 0; x < 2; x++)
				{
					elements[y + x * 2] = copy.elements[x + y * 2];
					elements[x + y * 2] = copy.elements[y + x * 2];
				}
			}
			return *this;
		}

		mat2& mat2::adjugate()
		{
			// Transpose the matrix and then multiply each element by the cooresponding element from the matrix of signs
			mat2 signMatrix = Sign();

			transpose();

			// Multiply each element by the cooresponding element from the matrix of signs
			for (int y = 0; y < 2; y++)
			{
				for (int x = 0; x < 2; x++)
				{
					elements[x + y * 2] *= signMatrix.elements[x + y * 2];
				}
			}

			return *this;
		}

		mat2& mat2::inverse()
		{
			// To find the inverse, swap the 1st and 4th elements, multiply by matrix of signs, and then multiply 1 / determinant with the matrix
			// If the determinant is 0, then the inverse cannot be found. Return a matrix filled with 0s
			mat2 signMatrix = Sign();

			mat2 copy = getCopy();

			float Determinant = determinant();

			try
			{
				if (Determinant == 0)
					throw "Divide by zero error";

				float oneOverDeterminant = ((Determinant == 0) ? ERROR_MATRIX_ELEMENT : (1 / Determinant));

				// Swap the 1st and 4th elements
				elements[0 + 0 * 2] = copy.elements[1 + 1 * 2];
				elements[1 + 1 * 2] = copy.elements[0 + 0 * 2];

				// Multiply 2nd and 3rd elements by -1 (might as well multiply the whole matrix by the Sign Matrix)
				for (int y = 0; y < 2; y++)
				{
					for (int x = 0; x < 2; x++)
					{
						elements[x + y * 2] *= signMatrix.elements[x + y * 2];
					}
				}

				// Mutiply each element of the matrix by 1 / determinant
				multiplyScalar(oneOverDeterminant);
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
		float mat2::Determinant(mat2& matrix)
		{
			return matrix.determinant();
		}

		mat2& mat2::Transpose(mat2& matrix)
		{
			return matrix.transpose();
		}

		mat2& mat2::Adjugate(mat2& matrix)
		{
			return matrix.adjugate();
		}

		mat2& mat2::Inverse(mat2& matrix)
		{
			return matrix.inverse();
		}

		// Same methods, but they will return a value rather than change a matrix
		float mat2::getDeterminant()
		{
			mat2 copy = getCopy();
			return copy.determinant();
		}

		mat2 mat2::getTranspose()
		{
			mat2 copy = getCopy();
			copy.transpose();
			return copy;
		}

		mat2 mat2::getAdjugate()
		{
			mat2 copy = getCopy();
			copy.adjugate();
			return copy;
		}

		mat2 mat2::getInverse()
		{
			mat2 copy = getCopy();
			copy.inverse();
			return copy;
		}

		// Static versions
		float mat2::GetDeterminant(mat2 matrix)
		{
			return matrix.getDeterminant();
		}

		mat2 mat2::GetTranspose(mat2 matrix)
		{
			return matrix.getTranspose();
		}

		mat2 mat2::GetAdjugate(mat2 matrix)
		{
			return matrix.getAdjugate();
		}

		mat2 mat2::GetInverse(mat2 matrix)
		{
			return matrix.getInverse();
		}

		/*          OPERATION METHODS BELOW          */

		// Methods to do arithmetic operations with matrices
		mat2& mat2::add(const mat2& other)
		{
			for (int i = 0; i < 2 * 2; i++)
			{
				elements[i] += other.elements[i];
			}

			return *this;
		}

		mat2& mat2::subtract(const mat2& other)
		{
			for (int i = 0; i < 2 * 2; i++)
			{
				elements[i] -= other.elements[i];
			}

			return *this;
		}

		mat2& mat2::multiply(const mat2& other)
		{
			mat2 copy = getCopy();

			for (int y = 0; y < 2; y++)
			{
				for (int x = 0; x < 2; x++)
				{
					float sum = 0.0f;
					for (int e = 0; e < 2; e++)
					{
						sum += copy.elements[x + e * 2] * other.elements[e + y * 2];
					}
					elements[x + y * 2] = sum;
				}
			}
			return *this;
		}

		mat2& mat2::divide(const mat2& other)
		{
			return multiply(GetInverse(other));
		}

		// Static versions 
		mat2& mat2::Add(mat2& left, const mat2& right)
		{
			return left.add(right);
		}

		mat2& mat2::Subtract(mat2& left, const mat2& right)
		{
			return left.subtract(right);
		}

		mat2& mat2::Multiply(mat2& left, const mat2& right)
		{
			return left.multiply(right);
		}

		mat2& mat2::Divide(mat2& left, const mat2& right)
		{
			return left.divide(right);
		}

		// Same methods, but they will return a value rather than change a matrix
		mat2 mat2::sum(const mat2& other)
		{
			mat2 copy = getCopy();
			copy.add(other);
			return copy;
		}

		mat2 mat2::difference(const mat2& other)
		{
			mat2 copy = getCopy();
			copy.subtract(other);
			return copy;
		}

		mat2 mat2::product(const mat2& other)
		{
			mat2 copy = getCopy();
			copy.multiply(other);
			return copy;
		}

		mat2 mat2::quotient(const mat2& other)
		{
			mat2 copy = getCopy();
			copy.divide(other);
			return copy;
		}

		// Static versions
		mat2 mat2::Sum(mat2 left, const mat2& right)
		{
			return left.sum(right);
		}

		mat2 mat2::Difference(mat2 left, const mat2& right)
		{
			return left.difference(right);
		}

		mat2 mat2::Product(mat2 left, const mat2& right)
		{
			return left.product(right);
		}

		mat2 mat2::Quotient(mat2 left, const mat2& right)
		{
			return left.quotient(right);
		}

		// Methods to do arithmetic operations with scalars
		mat2& mat2::addScalar(const float& scalar)
		{
			for (int i = 0; i < 2 * 2; i++)
			{
				elements[i] += scalar;
			}

			return *this;
		}

		mat2& mat2::subtractScalar(const float& scalar)
		{
			for (int i = 0; i < 2 * 2; i++)
			{
				elements[i] -= scalar;
			}

			return *this;
		}

		mat2& mat2::multiplyScalar(const float& scalar)
		{
			for (int i = 0; i < 2 * 2; i++)
			{
				elements[i] *= scalar;
			}

			return *this;
		}

		mat2& mat2::divideScalar(const float& scalar)
		{
			for (int i = 0; i < 2 * 2; i++)
			{
				try
				{
					if (scalar == 0)
						throw "Divide by zero error";

					elements[i] /= scalar;
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
			}

			return *this;
		}

		// Static versions
		mat2& mat2::AddScalar(mat2& matrix, const float& scalar)
		{
			return matrix.addScalar(scalar);
		}

		mat2& mat2::SubtractScalar(mat2& matrix, const float& scalar)
		{
			return matrix.subtractScalar(scalar);
		}

		mat2& mat2::MultiplyScalar(mat2& matrix, const float& scalar)
		{
			return matrix.multiplyScalar(scalar);
		}

		mat2& mat2::DivideScalar(mat2& matrix, const float& scalar)
		{
			return matrix.divideScalar(scalar);
		}

		// Same methods, but they will return a value rather than change a matrix
		mat2 mat2::scalarSum(const float& scalar)
		{
			mat2 copy = getCopy();
			copy.addScalar(scalar);
			return copy;
		}

		mat2 mat2::scalarDifference(const float& scalar)
		{
			mat2 copy = getCopy();
			copy.subtractScalar(scalar);
			return copy;
		}

		mat2 mat2::scalarProduct(const float& scalar)
		{
			mat2 copy = getCopy();
			copy.multiplyScalar(scalar);
			return copy;
		}

		mat2 mat2::scalarQuotient(const float& scalar)
		{
			mat2 copy = getCopy();
			copy.divideScalar(scalar);
			return copy;
		}

		// Static versions
		mat2 mat2::ScalarSum(mat2 matrix, const float& scalar)
		{
			return matrix.scalarSum(scalar);
		}

		mat2 mat2::ScalarDifference(mat2 matrix, const float& scalar)
		{
			return matrix.scalarDifference(scalar);
		}

		mat2 mat2::ScalarProduct(mat2 matrix, const float& scalar)
		{
			return matrix.scalarProduct(scalar);
		}

		mat2 mat2::ScalarQuotient(mat2 matrix, const float& scalar)
		{
			return matrix.scalarQuotient(scalar);
		}

		// Methods to do relational and comparison operations with matrices
		bool mat2::isEqualTo(const mat2& other)
		{
			for (int i = 0; i < 2 * 2; i++)
			{
				if (elements[i] == other.elements[i])
				{
					if (i == (2 * 2 - 1))
					{
						break;
						return true;
					}
					else
					{
						continue;
					}
				}
				else
				{
					break;
					return false;
				}
			}
		}

		bool mat2::isNotEqualTo(const mat2& other)
		{
			return !isEqualTo(other);
		}

		// Static versions
		bool mat2::IsEqualTo(mat2 left, const mat2& right)
		{
			return left.isEqualTo(right);
		}

		bool mat2::IsNotEqualTo(mat2 left, const mat2& right)
		{
			return left.isNotEqualTo(right);
		}

		// Methods to print the matrix to the screen

		// Uses C or C++'s method of printing
		void mat2::print()
		{
#if PRINT_METHOD_C
			printf("mat2: \n");

			for (int y = 0; y < 2; y++)
			{
				printf("[");
				for (int x = 0; x < 2; x++)
				{
					printf("%f%s", elements[y + x * 2], 
						((x != 2 - 1 ? ", " : "] \n")));
				}
			}
#endif

#if PRINT_METHOD_CPP 
			Print(std::cout, *this);
#endif
		}

		// Uses C or C++'s method of printing
		void mat2::Print(mat2 matrix)
		{
			matrix.print();
		}

		// Uses C++'s way of printing
		std::ostream& mat2::Print(std::ostream& stream, const mat2& matrix)
		{
			stream << "mat2: " << std::endl;

			for (int y = 0; y < 2; y++)
			{
				stream << "[";
				for (int x = 0; x < 2; x++)
				{
					stream << matrix.elements[y + x * 2] <<
						((x != 2 - 1 ? ", " : "] \n"));
				}
			}

			return stream;
		}

		/*          OPERATOR OVERLOAD BELOW          */

		// Overflow arithmetic operators with matrices
		mat2 operator+(mat2 left, const mat2& right)
		{
			return mat2::Sum(left, right);
		}

		mat2 operator-(mat2 left, const mat2& right)
		{
			return mat2::Difference(left, right);
		}

		mat2 operator*(mat2 left, const mat2& right)
		{
			return mat2::Product(left, right);
		}

		mat2 operator/(mat2 left, const mat2& right)
		{
			return mat2::Quotient(left, right);
		}

		// Overflow arithmetic operators with scalars
		mat2 operator+(mat2 matrix, const float& scalar)
		{
			return mat2::ScalarSum(matrix, scalar);
		}
		mat2 operator-(mat2 matrix, const float& scalar)
		{
			return mat2::ScalarDifference(matrix, scalar);
		}
		mat2 operator*(mat2 matrix, const float& scalar)
		{
			return mat2::ScalarProduct(matrix, scalar);
		}
		mat2 operator/(mat2 matrix, const float& scalar)
		{
			return mat2::ScalarQuotient(matrix, scalar);
		}

		// Overflow the compound assignment operators with matrices
		mat2& mat2::operator+=(const mat2& other)
		{
			return add(other);
		}

		mat2& mat2::operator-=(const mat2& other)
		{
			return subtract(other);
		}

		mat2& mat2::operator*=(const mat2& other)
		{
			return multiply(other);
		}

		mat2& mat2::operator/=(const mat2& other)
		{
			return divide(other);
		}

		// Overflow the compound assignment operators with scalars
		mat2& mat2::operator+=(const float& scalar)
		{
			return addScalar(scalar);
		}

		mat2& mat2::operator-=(const float& scalar)
		{
			return subtractScalar(scalar);
		}

		mat2& mat2::operator*=(const float& scalar)
		{
			return multiplyScalar(scalar);
		}

		mat2& mat2::operator/=(const float& scalar)
		{
			return divideScalar(scalar);
		}

		// Overflow relational and comparison operators
		bool operator==(mat2 left, const mat2& right)
		{
			return mat2::IsEqualTo(left, right);
		}

		bool operator!=(mat2 left, const mat2& right)
		{
			return mat2::IsNotEqualTo(left, right);
		}

		// Overflow the bitwise operator
		std::ostream& operator<<(std::ostream& stream, mat2 matrix)
		{
			return mat2::Print(stream, matrix);
		}
	}
}

