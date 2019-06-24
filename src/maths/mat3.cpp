/*
DO NOT DELETE THIS COMMENT:
The ROM(Rambug Optical Mathematics) Library:
This software is written by Danyil Blyschak, 8/2015 (1st Build).
For any permissions, questions, or bug fixes, email the
support email that came with your distribution of this software.
*/

#include "mat3.h"

namespace Rambug
{
	namespace Math
	{
		mat3::mat3()
		{
			for (int i = 0; i < 3 * 3; i++)
			{
				elements[i] = 0.0f;
			}
		}

		mat3::mat3(float diagonal)
		{
			for (int i = 0; i < 3 * 3; i++)
			{
				elements[i] = 0.0f;
			}

			elements[0 + 0 * 3] = diagonal;
			elements[1 + 1 * 3] = diagonal;
			elements[2 + 2 * 3] = diagonal;
		}

		// Method to get a copy of the current matrix
		mat3 mat3::getCopy()
		{
			// Returns a copy of the current matrix
			mat3 copy;

			for (int i = 0; i < 3 * 3; i++)
			{
				copy.elements[i] = elements[i];
			}

			return copy;
		}

		// Static version
		mat3 mat3::Copy(mat3 matrix)
		{
			return matrix.getCopy();
		}

		// Methods to get matrices
		mat3 mat3::Identity()
		{
			return mat3(1);
		}

		mat3 mat3::Sign()
		{
			// Return a 3 x 3 sign matrix

			// + - +
			// - + -
			// + - +

			mat3 signMatrix(1);

			// Column one
			signMatrix.elements[0 + 0 * 3] = 1;
			signMatrix.elements[1 + 0 * 3] = -1;
			signMatrix.elements[2 + 0 * 3] = 1;
			
			// Column two
			signMatrix.elements[0 + 1 * 3] = -1;
			signMatrix.elements[1 + 1 * 3] = 1;
			signMatrix.elements[2 + 1 * 3] = -1;

			// Column three
			signMatrix.elements[0 + 2 * 3] = 1;
			signMatrix.elements[1 + 2 * 3] = -1;
			signMatrix.elements[2 + 2 * 3] = 1;
			
			return signMatrix;
		}

		// Useful methods to do miscellaneous operations with matrices (will change the current matrix)
		float mat3::determinant()
		{
			mat3 signMatrix = Sign();

			// Get the submatrices of the first row
			mat2 a = subMatrix(0, 0);
			mat2 b = subMatrix(0, 1);
			mat2 c = subMatrix(0, 2);

			// Get the determinants of the submatrices
			float aDeterminant = a.determinant();
			float bDeterminant = b.determinant();
			float cDeterminant = c.determinant();

			// Get the numbers that we are going to multiply the determinants by
			float aTerm = elements[0 + 0 * 3] * signMatrix.elements[0 + 0 * 3];
			float bTerm = elements[0 + 1 * 3] * signMatrix.elements[0 + 1 * 3];
			float cTerm = elements[0 + 2 * 3] * signMatrix.elements[0 + 2 * 3];

			float aResult = aDeterminant * aTerm;
			float bResult = bDeterminant * bTerm;
			float cResult = cDeterminant * cTerm;

			float result = aResult + bResult + cResult;

			return result;
		}
	
		mat3& mat3::transpose()
		{
			// Make the columns of the matrix to rows
			mat3 copy = getCopy();
			
			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					elements[y + x * 3] = copy.elements[x + y * 3];
					elements[x + y * 3] = copy.elements[y + x * 3];
				}
			}
			return *this;
		}
		
		mat2 mat3::subMatrix(const int& row, const int& column)
		{	
			mat3 copy = getCopy();
			
			mat2 result;

			// Check if we are not going out of bounds
			if (row > 2 || column > 2)
			{
				return mat2(ERROR_MATRIX_ELEMENT);
			}
			
			switch (row)
			{
			case 0:
				// 1st row
				switch (column)
				{
				case 0:
					// 1st row, 1st column
					result.elements[0] = copy.elements[1 + 1 * 3];
					result.elements[1] = copy.elements[2 + 1 * 3];
					result.elements[2] = copy.elements[1 + 2 * 3];
					result.elements[3] = copy.elements[2 + 2 * 3];
					break;
				case 1:
					// 1st row, 2nd column
					result.elements[0] = copy.elements[1 + 0 * 3];
					result.elements[1] = copy.elements[2 + 0 * 3];
					result.elements[2] = copy.elements[1 + 2 * 3];
					result.elements[3] = copy.elements[2 + 2 * 3];
					break;
				case 2:
					// 1st row, 3rd column
					result.elements[0] = copy.elements[1 + 0 * 3];
					result.elements[1] = copy.elements[2 + 0 * 3];
					result.elements[2] = copy.elements[1 + 1 * 3];
					result.elements[3] = copy.elements[2 + 1 * 3];
					break;
				}
				break;
			case 1:
				// 2nd row
				switch (column)
				{
				case 0:
					// 2nd row, 1st column
					result.elements[0] = copy.elements[0 + 1 * 3];
					result.elements[1] = copy.elements[2 + 1 * 3];
					result.elements[2] = copy.elements[0 + 2 * 3];
					result.elements[3] = copy.elements[2 + 2 * 3];
					break;
				case 1:
					// 2nd row, 2nd column
					result.elements[0] = copy.elements[0 + 0 * 3];
					result.elements[1] = copy.elements[2 + 0 * 3];
					result.elements[2] = copy.elements[0 + 2 * 3];
					result.elements[3] = copy.elements[2 + 2 * 3];
					break;
				case 2:
					// 2nd row, 3rd column
					result.elements[0] = copy.elements[0 + 0 * 3];
					result.elements[1] = copy.elements[2 + 0 * 3];
					result.elements[2] = copy.elements[0 + 1 * 3];
					result.elements[3] = copy.elements[2 + 1 * 3];
					break;
				}
				break;
			case 2:
				// 3rd row
				switch (column)
				{
				case 0:
					// 3rd row, 1st column
					result.elements[0] = copy.elements[0 + 1 * 3];
					result.elements[1] = copy.elements[1 + 1 * 3];
					result.elements[2] = copy.elements[0 + 2 * 3];
					result.elements[3] = copy.elements[1 + 2 * 3];
					break;
				case 1:
					// 3rd row, 2nd column
					result.elements[0] = copy.elements[0 + 0 * 3];
					result.elements[1] = copy.elements[1 + 0 * 3];
					result.elements[2] = copy.elements[0 + 2 * 3];
					result.elements[3] = copy.elements[1 + 2 * 3];
					break;
				case 2:
					// 3rd row, 3rd column
					result.elements[0] = copy.elements[0 + 0 * 3];
					result.elements[1] = copy.elements[1 + 0 * 3];
					result.elements[2] = copy.elements[0 + 1 * 3];
					result.elements[3] = copy.elements[1 + 1 * 3];
					break;
				}
				break;
			}
			return result;
		}
	
		float mat3::minor(const int& row, const int& column)
		{
			mat2 smallerMatrix = subMatrix(row, column);
			float smallerMatrixDeterminant = smallerMatrix.determinant();
			return smallerMatrixDeterminant;
		}

		float mat3::cofactor(const int& row, const int& column)
		{
			mat3 signMatrix = Sign();

			float Minor = minor(row, column);
			float cofactor = Minor * signMatrix.elements[row + column * 4];

			return cofactor;
		}
		
		mat3& mat3::minorMatrix()
		{
			mat3 copy = getCopy();

			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					elements[x + y * 3] = copy.getMinor(x, y);
				}
			}
			return *this;
		}

		mat3& mat3::cofactorMatrix()
		{	
			mat3 copy = getCopy();
			
			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					elements[x + y * 3] = copy.getCofactor(x, y);
				}
			}
			return *this;
		}

		mat3& mat3::adjugate()
		{
			cofactorMatrix();
			transpose();

			return *this;
		}

		mat3& mat3::inverse()
		{
			float Determinant = determinant();
			try
			{
				if (Determinant == 0)
					throw "Divide by zero error";

				float oneOverDeterminant = 1 / Determinant;
				adjugate();
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
		float mat3::Determinant(mat3& matrix)
		{
			return matrix.determinant();
		}

		mat3& mat3::Transpose(mat3& matrix)
		{
			return matrix.transpose();
		}

		mat2 mat3::SubMatrix(mat3& matrix, const int& row, const int& column)
		{
			return matrix.subMatrix(row, column);
		}

		float mat3::Minor(mat3& matrix, const int& row, const int& column)
		{
			return matrix.minor(row, column);
		}

		float mat3::Cofactor(mat3& matrix, const int& row, const int& column)
		{
			return matrix.cofactor(row, column);
		}
		
		mat3& mat3::MinorMatrix(mat3& matrix)
		{
			return matrix.minorMatrix();
		}

		mat3& mat3::CofactorMatrix(mat3& matrix)
		{
			return matrix.cofactorMatrix();
		}

		mat3& mat3::Adjugate(mat3& matrix)
		{
			return matrix.adjugate();
		}
		
		mat3& mat3::Inverse(mat3& matrix)
		{
			return matrix.inverse();
		}

		// Same methods, but they will return a value rather than change a matrix
		float mat3::getDeterminant()
		{
			mat3 copy = getCopy();
			return copy.determinant();
		}

		mat3 mat3::getTranspose()
		{
			mat3 copy = getCopy();
			copy.transpose();
			return copy;
		}

		mat2 mat3::getSubMatrix(const int& row, const int& column)
		{
			mat3 copy = getCopy();
			return copy.subMatrix(row, column);
		}

		float mat3::getMinor(const int& row, const int& column)
		{
			mat3 copy = getCopy();
			return copy.minor(row, column);
		}

		float mat3::getCofactor(const int& row, const int& column)
		{
			mat3 copy = getCopy();
			return copy.cofactor(row, column);
		}

		mat3 mat3::getMinorMatrix()
		{
			mat3 copy = getCopy();
			return copy.minorMatrix();
		}

		mat3 mat3::getCofactorMatrix()
		{
			mat3 copy = getCopy();
			copy.cofactorMatrix();
			return copy;
		}

		mat3 mat3::getAdjugate()
		{
			mat3 copy = getCopy();
			copy.adjugate();
			return copy;
		}

		mat3 mat3::getInverse()
		{
			mat3 copy = getCopy();
			copy.inverse();
			return copy;
		}

		// Static versions
		float mat3::GetDeterminant(mat3 matrix)
		{
			return matrix.getDeterminant();
		}

		mat3 mat3::GetTranspose(mat3 matrix)
		{
			return matrix.getTranspose();
		}

		mat2 mat3::GetSubMatrix(mat3 matrix, const int& row, const int& column)
		{
			return matrix.getSubMatrix(row, column);
		}

		float mat3::GetMinor(mat3 matrix, const int& row, const int& column)
		{
			return matrix.getMinor(row, column);
		}

		float mat3::GetCofactor(mat3 matrix, const int& row, const int& column)
		{
			return matrix.getCofactor(row, column);
		}

		mat3 mat3::GetMinorMatrix(mat3 matrix)
		{
			return matrix.getMinorMatrix();
		}

		mat3 mat3::GetCofactorMatrix(mat3 matrix)
		{
			return matrix.getCofactorMatrix();
		}

		mat3 mat3::GetAdjugate(mat3 matrix)
		{
			return matrix.getAdjugate();
		}

		mat3 mat3::GetInverse(mat3 matrix)
		{
			return matrix.getInverse();
		}

		/*          OPERATION METHODS BELOW          */

		// Methods to do arithmetic operations with matrices
		mat3& mat3::add(const mat3& other)
		{
			for (int i = 0; i < 3 * 3; i++)
			{
				elements[i] += other.elements[i];
			}

			return *this;
		}

		mat3& mat3::subtract(const mat3& other)
		{
			for (int i = 0; i < 3 * 3; i++)
			{
				elements[i] -= other.elements[i];
			}

			return *this;
		}

		mat3& mat3::multiply(const mat3& other)
		{
			mat3 copy = getCopy();
			
			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					float sum = 0.0f;
					for (int e = 0; e < 3; e++)
					{
						sum += copy.elements[x + e * 3] * other.elements[e + y * 3];
					}
					elements[x + y * 3] = sum;
				}
			}
			return *this;
		}

		mat3& mat3::divide(const mat3& other)
		{
			return multiply(GetInverse(other));
		}

		// Static versions 
		mat3& mat3::Add(mat3& left, const mat3& right)
		{
			return left.add(right);
		}

		mat3& mat3::Subtract(mat3& left, const mat3& right)
		{
			return left.subtract(right);
		}

		mat3& mat3::Multiply(mat3& left, const mat3& right)
		{
			return left.multiply(right);
		}

		mat3& mat3::Divide(mat3& left, const mat3& right)
		{
			return left.divide(right);
		}

		// Same methods, but they will return a value rather than change a matrix
		mat3 mat3::sum(const mat3& other)
		{
			mat3 copy = getCopy();
			copy.add(other);
			return copy;
		}

		mat3 mat3::difference(const mat3& other)
		{
			mat3 copy = getCopy();
			copy.subtract(other);
			return copy;
		}

		mat3 mat3::product(const mat3& other)
		{
			mat3 copy = getCopy();
			copy.multiply(other);
			return copy;
		}

		mat3 mat3::quotient(const mat3& other)
		{
			mat3 copy = getCopy();
			copy.divide(other);
			return copy;
		}

		// Static versions
		mat3 mat3::Sum(mat3 left, const mat3& right)
		{
			return left.sum(right);
		}

		mat3 mat3::Difference(mat3 left, const mat3& right)
		{
			return left.difference(right);
		}

		mat3 mat3::Product(mat3 left, const mat3& right)
		{
			return left.product(right);
		}

		mat3 mat3::Quotient(mat3 left, const mat3& right)
		{
			return left.quotient(right);
		}

		// Methods to do arithmetic operations with scalars
		mat3& mat3::addScalar(const float& scalar)
		{
			for (int i = 0; i < 3 * 3; i++)
			{
				elements[i] += scalar;
			}

			return *this;
		}

		mat3& mat3::subtractScalar(const float& scalar)
		{
			for (int i = 0; i < 3 * 3; i++)
			{
				elements[i] -= scalar;
			}

			return *this;
		}

		mat3& mat3::multiplyScalar(const float& scalar)
		{
			for (int i = 0; i < 3 * 3; i++)
			{
				elements[i] *= scalar;
			}

			return *this;
		}

		mat3& mat3::divideScalar(const float& scalar)
		{
			for (int i = 0; i < 3 * 3; i++)
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
		mat3& mat3::AddScalar(mat3& matrix, const float& scalar)
		{
			return matrix.addScalar(scalar);
		}

		mat3& mat3::SubtractScalar(mat3& matrix, const float& scalar)
		{
			return matrix.subtractScalar(scalar);
		}

		mat3& mat3::MultiplyScalar(mat3& matrix, const float& scalar)
		{
			return matrix.multiplyScalar(scalar);
		}

		mat3& mat3::DivideScalar(mat3& matrix, const float& scalar)
		{
			return matrix.divideScalar(scalar);
		}

		// Same methods, but they will return a value rather than change a matrix
		mat3 mat3::scalarSum(const float& scalar)
		{
			mat3 copy = getCopy();
			copy.addScalar(scalar);
			return copy;
		}

		mat3 mat3::scalarDifference(const float& scalar)
		{
			mat3 copy = getCopy();
			copy.subtractScalar(scalar);
			return copy;
		}

		mat3 mat3::scalarProduct(const float& scalar)
		{
			mat3 copy = getCopy();
			copy.multiplyScalar(scalar);
			return copy;
		}

		mat3 mat3::scalarQuotient(const float& scalar)
		{
			mat3 copy = getCopy();
			copy.divideScalar(scalar);
			return copy;
		}

		// Static versions
		mat3 mat3::ScalarSum(mat3 matrix, const float& scalar)
		{
			return matrix.scalarSum(scalar);
		}

		mat3 mat3::ScalarDifference(mat3 matrix, const float& scalar)
		{
			return matrix.scalarDifference(scalar);
		}

		mat3 mat3::ScalarProduct(mat3 matrix, const float& scalar)
		{
			return matrix.scalarProduct(scalar);
		}

		mat3 mat3::ScalarQuotient(mat3 matrix, const float& scalar)
		{
			return matrix.scalarQuotient(scalar);
		}

		// Methods to do relational and comparison operations with matrices
		bool mat3::isEqualTo(const mat3& other)
		{
			for (int i = 0; i < 3 * 3; i++)
			{
				if (elements[i] == other.elements[i])
				{
					if (i == (3 * 3 - 1))
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

		bool mat3::isNotEqualTo(const mat3& other)
		{
			return !isEqualTo(other);
		}

		// Static versions
		bool mat3::IsEqualTo(mat3 left, const mat3& right)
		{
			return left.isEqualTo(right);
		}

		bool mat3::IsNotEqualTo(mat3 left, const mat3& right)
		{
			return left.isNotEqualTo(right);
		}

		// Methods to print the matrix to the screen

		// Uses C or C++'s method of printing
		void mat3::print()
		{
#if PRINT_METHOD_C
			printf("mat3: \n");

			for (int y = 0; y < 3; y++)
			{
				printf("[");
				for (int x = 0; x < 3; x++)
				{
					printf("%f%s", elements[y + x * 3], 
						((x != 2 ? ", " : "] \n")));
				}
			}
#endif

#if PRINT_METHOD_CPP 
			Print(std::cout, *this);
#endif
		}

		// Uses C or C++'s method of printing
		void mat3::Print(mat3 matrix)
		{
			matrix.print();
		}

		// Uses C++'s way of printing
		std::ostream& mat3::Print(std::ostream& stream, const mat3& matrix)
		{
			stream << "mat3: " << std::endl;

			for (int y = 0; y < 3; y++)
			{
				stream << "[";
				for (int x = 0; x < 3; x++)
				{
					stream << matrix.elements[y + x * 3] <<
						((x != 2 ? ", " : "] \n"));
				}
			}

			return stream;
		}

		/*          OPERATOR OVERLOAD BELOW          */

		// Overflow arithmetic operators with matrices
		mat3 operator+(mat3 left, const mat3& right)
		{
			return mat3::Sum(left, right);
		}

		mat3 operator-(mat3 left, const mat3& right)
		{
			return mat3::Difference(left, right);
		}

		mat3 operator*(mat3 left, const mat3& right)
		{
			return mat3::Product(left, right);
		}

		mat3 operator/(mat3 left, const mat3& right)
		{
			return mat3::Quotient(left, right);
		}

		// Overflow arithmetic operators with scalars
		mat3 operator+(mat3 matrix, const float& scalar)
		{
			return mat3::ScalarSum(matrix, scalar);
		}
		mat3 operator-(mat3 matrix, const float& scalar)
		{
			return mat3::ScalarDifference(matrix, scalar);
		}
		mat3 operator*(mat3 matrix, const float& scalar)
		{
			return mat3::ScalarProduct(matrix, scalar);
		}
		mat3 operator/(mat3 matrix, const float& scalar)
		{
			return mat3::ScalarQuotient(matrix, scalar);
		}

		// Overflow the compound assignment operators with matrices
		mat3& mat3::operator+=(const mat3& other)
		{
			return add(other);
		}

		mat3& mat3::operator-=(const mat3& other)
		{
			return subtract(other);
		}

		mat3& mat3::operator*=(const mat3& other)
		{
			return multiply(other);
		}

		mat3& mat3::operator/=(const mat3& other)
		{
			return divide(other);
		}

		// Overflow the compound assignment operators with scalars
		mat3& mat3::operator+=(const float& scalar)
		{
			return addScalar(scalar);
		}

		mat3& mat3::operator-=(const float& scalar)
		{
			return subtractScalar(scalar);
		}

		mat3& mat3::operator*=(const float& scalar)
		{
			return multiplyScalar(scalar);
		}

		mat3& mat3::operator/=(const float& scalar)
		{
			return divideScalar(scalar);
		}

		// Overflow relational and comparison operators
		bool operator==(mat3 left, const mat3& right)
		{
			return mat3::IsEqualTo(left, right);
		}

		bool operator!=(mat3 left, const mat3& right)
		{
			return mat3::IsNotEqualTo(left, right);
		}

		// Overflow the bitwise operator
		std::ostream& operator<<(std::ostream& stream, mat3 matrix)
		{
			return mat3::Print(stream, matrix);
		}
	}
}

