/*
DO NOT DELETE THIS COMMENT:
The ROM(Rambug Optical Mathematics) Library:
This software is written by Danyil Blyschak, 8/2015 (1st Build).
For any permissions, questions, or bug fixes, email the
support email that came with your distribution of this software.
*/

#include "mat4.h"

namespace Rambug
{
	namespace Math
	{
		mat4::mat4()
		{
			for (int i = 0; i < 4 * 4; i++)
			{
				elements[i] = 0.0f;
			}
		}

		mat4::mat4(float diagonal)
		{
			for (int i = 0; i < 4 * 4; i++)
			{
				elements[i] = 0.0f;
			}

			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		// Method to get a copy of the current matrix
		mat4 mat4::getCopy()
		{
			// Returns a copy of the current matrix
			mat4 copy;

			for (int i = 0; i < 4 * 4; i++)
			{
				copy.elements[i] = elements[i];
			}

			return copy;
		}

		// Static version
		mat4 mat4::Copy(mat4 matrix)
		{
			return matrix.getCopy();
		}

		// Methods to get matrices
		mat4 mat4::Identity()
		{
			return mat4(1);
		}

		mat4 mat4::Sign()
		{
			// Create the 4 x 4 cofactor matrix 

			// + - + -
			// - + - +
			// + - + -
			// - + - +

			mat4 signMatrix;

			// Column one
			signMatrix.elements[3 + 0 * 4] = -1.0f;
			signMatrix.elements[0 + 0 * 4] = 1.0f;
			signMatrix.elements[1 + 0 * 4] = -1.0f;
			signMatrix.elements[2 + 0 * 4] = 1.0f;

			// Column two
			signMatrix.elements[0 + 1 * 4] = -1.0f;
			signMatrix.elements[1 + 1 * 4] = 1.0f;
			signMatrix.elements[2 + 1 * 4] = -1.0f;
			signMatrix.elements[3 + 1 * 4] = 1.0f;

			// Column three
			signMatrix.elements[0 + 2 * 4] = 1.0f;
			signMatrix.elements[1 + 2 * 4] = -1.0f;
			signMatrix.elements[2 + 2 * 4] = 1.0f;
			signMatrix.elements[3 + 2 * 4] = -1.0f;

			// Column four
			signMatrix.elements[0 + 3 * 4] = -1.0f;
			signMatrix.elements[1 + 3 * 4] = 1.0f;
			signMatrix.elements[2 + 3 * 4] = -1.0f;
			signMatrix.elements[3 + 3 * 4] = 1.0f;

			return signMatrix;
		}

		// Projection matrices
		mat4 mat4::Orthographic(float left, float right, float bottom, float top, float near, float far)
		{
			mat4 result(1.0f);

			try
			{
				// Setting the diagonal of the matrix and setting the last column of the matrix
				// Handle for any divide by zero exceptions
				if ((right - left == 0))
					throw "Divide by zero error";
				result.elements[0 + 0 * 4] = 2.0f / (right - left);
				result.elements[0 + 3 * 4] = -1 * ((right + left) / (right - left));
				
				if ((top - bottom == 0))
					throw "Divide by zero error";
				result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
				result.elements[1 + 3 * 4] = -1 * ((top + bottom) / (top - bottom));
				
				if ((far - near == 0))
					throw "Divide by zero error";
				result.elements[2 + 2 * 4] = -2.0f / (far - near);
				result.elements[2 + 3 * 4] = -1 * ((far + near) / (far - near));
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

			// Setting the last element of the last column and diagonal in the matrix
			result.elements[3 + 3 * 4] = 1;

			return result;
		}

		mat4 mat4::Perspective(float fov, float aspectRatio, float near, float far)
		{
			mat4 result(1.0f);

			try
			{
				if ((tan(ToRadians(0.5 * fov) == 0)))
					throw "Divide by zero error";

				float q = 1.0f / tan(ToRadians(0.5 * fov));
				result.elements[1 + 1 * 4] = q;
			
				if (aspectRatio == 0)
					throw "Divide by zero error";
				
				float a = q / aspectRatio;
				result.elements[0 + 0 * 4] = a;
				
				if ((near - far == 0))
					throw "Divide by zero error";

				float b = (near + far) / (near - far);
				result.elements[2 + 2 * 4] = b;

				float c = (2.0f * near * far) / (near - far);
				result.elements[2 + 3 * 4] = c;
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

			result.elements[3 + 2 * 4] = -1.0f;

			return result;
		}

		// Translation matrices
		mat4 mat4::Translation(const vec3& translation)
		{
			mat4 result(1.0f);

			result.elements[0 + 3 * 4] = translation.x;
			result.elements[1 + 3 * 4] = translation.y;
			result.elements[2 + 3 * 4] = translation.z;

			return result;
		}

		mat4 mat4::Rotation(float angle, const vec3& axis)
		{
			mat4 result(1.0f);

			float radians = ToRadians(angle);
			float cosine = cos(radians);
			float sine = sin(radians);
			float omc = 1.0f - cosine;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0 + 0 * 4] = x * omc + cosine;
			result.elements[1 + 0 * 4] = x * y * omc + z + sine;
			result.elements[2 + 0 * 4] = x * z * omc - y * sine;

			result.elements[0 + 1 * 4] = x * y * omc - z * sine;
			result.elements[1 + 1 * 4] = y * omc + cosine;
			result.elements[2 + 1 * 4] = y * z * omc + x * sine;

			result.elements[0 + 2 * 4] = x * z * omc + y * sine;
			result.elements[1 + 2 * 4] = y * z * omc - x * sine;
			result.elements[2 + 2 * 4] = z * omc + cosine;

			return result;
		}

		mat4 mat4::Scale(const vec3& scale)
		{
			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;

			return result;
		}

		// Useful methods to do miscellaneous operations with matrices (will change the current matrix)
		float mat4::determinant()
		{
			// Getting the determinant similar to the way we got the determinant for a 3 x 3 matrix			
			mat4 signMatrix = Sign();

			// Get the submatrices of the first row
			mat3 a = subMatrix(0, 0);
			mat3 b = subMatrix(0, 1);
			mat3 c = subMatrix(0, 2);
			mat3 d = subMatrix(0, 3);

			// Get the determinants of the submatrices
			float aDeterminant = a.determinant();
			float bDeterminant = b.determinant();
			float cDeterminant = c.determinant();
			float dDeterminant = d.determinant();

			// Get the numbers that we are going to multiply the determinants by
			float aTerm = elements[0 + 0 * 4] * signMatrix.elements[0 + 0 * 4];
			float bTerm = elements[0 + 1 * 4] * signMatrix.elements[0 + 1 * 4];
			float cTerm = elements[0 + 2 * 4] * signMatrix.elements[0 + 2 * 4];
			float dTerm = elements[0 + 3 * 4] * signMatrix.elements[0 + 3 * 4];

			float aResult = aDeterminant * aTerm;
			float bResult = bDeterminant * bTerm;
			float cResult = cDeterminant * cTerm;
			float dResult = dDeterminant * dTerm;

			float result = aResult + bResult + cResult + dResult;

			return result;
		}

		mat4& mat4::transpose()
		{
			// Make the columns of the matrix to rows
			mat4 copy = getCopy();

			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					elements[y + x * 4] = copy.elements[x + y * 4];
					elements[x + y * 4] = copy.elements[y + x * 4];
				}
			}
			return *this;
		}

		mat3 mat4::subMatrix(const int& row, const int& column)
		{
			mat4 copy = getCopy();

			mat3 result;

			// Check if we are not going out of bounds
			if (row > 3 || column > 3)
			{
				return mat3(ERROR_MATRIX_ELEMENT);
			}

			switch (row)
			{
			case 0:
				// 1st row
				switch (column)
				{
				case 0:
					// 1st row, 1st column
					result.elements[0] = copy.elements[1 + 1 * 4];
					result.elements[1] = copy.elements[2 + 1 * 4];
					result.elements[2] = copy.elements[3 + 1 * 4];

					result.elements[3] = copy.elements[1 + 2 * 4];
					result.elements[4] = copy.elements[2 + 2 * 4];
					result.elements[5] = copy.elements[3 + 2 * 4];

					result.elements[6] = copy.elements[1 + 3 * 4];
					result.elements[7] = copy.elements[2 + 3 * 4];
					result.elements[8] = copy.elements[3 + 3 * 4];

					break;
				case 1:
					// 1st row, 2nd column
					result.elements[0] = copy.elements[1 + 0 * 4];
					result.elements[1] = copy.elements[2 + 0 * 4];
					result.elements[2] = copy.elements[3 + 0 * 4];

					result.elements[3] = copy.elements[1 + 2 * 4];
					result.elements[4] = copy.elements[2 + 2 * 4];
					result.elements[5] = copy.elements[3 + 2 * 4];

					result.elements[6] = copy.elements[1 + 3 * 4];
					result.elements[7] = copy.elements[2 + 3 * 4];
					result.elements[8] = copy.elements[3 + 3 * 4];
					break;
				case 2:
					// 1st row, 3rd column
					result.elements[0] = copy.elements[1 + 0 * 4];
					result.elements[1] = copy.elements[2 + 0 * 4];
					result.elements[2] = copy.elements[3 + 0 * 4];

					result.elements[3] = copy.elements[1 + 1 * 4];
					result.elements[4] = copy.elements[2 + 1 * 4];
					result.elements[5] = copy.elements[3 + 1 * 4];

					result.elements[6] = copy.elements[1 + 3 * 4];
					result.elements[7] = copy.elements[2 + 3 * 4];
					result.elements[8] = copy.elements[3 + 3 * 4];
					break;
				case 3:
					// 1st row, 4th column
					result.elements[0] = copy.elements[1 + 0 * 4];
					result.elements[1] = copy.elements[2 + 0 * 4];
					result.elements[2] = copy.elements[3 + 0 * 4];

					result.elements[3] = copy.elements[1 + 1 * 4];
					result.elements[4] = copy.elements[2 + 1 * 4];
					result.elements[5] = copy.elements[3 + 1 * 4];

					result.elements[6] = copy.elements[1 + 2 * 4];
					result.elements[7] = copy.elements[2 + 2 * 4];
					result.elements[8] = copy.elements[3 + 2 * 4];
					break;
				}
				break;
			case 1:
				// 2nd row
				switch (column)
				{
				case 0:
					// 2nd row, 1st column
					result.elements[0] = copy.elements[0 + 1 * 4];
					result.elements[1] = copy.elements[2 + 1 * 4];
					result.elements[2] = copy.elements[3 + 1 * 4];

					result.elements[3] = copy.elements[0 + 2 * 4];
					result.elements[4] = copy.elements[2 + 2 * 4];
					result.elements[5] = copy.elements[3 + 2 * 4];

					result.elements[6] = copy.elements[0 + 3 * 4];
					result.elements[7] = copy.elements[2 + 3 * 4];
					result.elements[8] = copy.elements[3 + 3 * 4];
					break;
				case 1:
					// 2nd row, 2nd column
					result.elements[0] = copy.elements[0 + 0 * 4];
					result.elements[1] = copy.elements[2 + 0 * 4];
					result.elements[2] = copy.elements[3 + 0 * 4];

					result.elements[3] = copy.elements[0 + 2 * 4];
					result.elements[4] = copy.elements[2 + 2 * 4];
					result.elements[5] = copy.elements[3 + 2 * 4];

					result.elements[6] = copy.elements[0 + 3 * 4];
					result.elements[7] = copy.elements[2 + 3 * 4];
					result.elements[8] = copy.elements[3 + 3 * 4];
					break;
				case 2:
					// 2nd row, 3rd column
					result.elements[0] = copy.elements[0 + 0 * 4];
					result.elements[1] = copy.elements[2 + 0 * 4];
					result.elements[2] = copy.elements[3 + 0 * 4];

					result.elements[3] = copy.elements[0 + 1 * 4];
					result.elements[4] = copy.elements[2 + 1 * 4];
					result.elements[5] = copy.elements[3 + 1 * 4];

					result.elements[6] = copy.elements[0 + 3 * 4];
					result.elements[7] = copy.elements[2 + 3 * 4];
					result.elements[8] = copy.elements[3 + 3 * 4];
					break;
				case 3:
					// 2nd row, 4th column
					result.elements[0] = copy.elements[0 + 0 * 4];
					result.elements[1] = copy.elements[2 + 0 * 4];
					result.elements[2] = copy.elements[3 + 0 * 4];

					result.elements[3] = copy.elements[0 + 1 * 4];
					result.elements[4] = copy.elements[2 + 1 * 4];
					result.elements[5] = copy.elements[3 + 1 * 4];

					result.elements[6] = copy.elements[0 + 2 * 4];
					result.elements[7] = copy.elements[2 + 2 * 4];
					result.elements[8] = copy.elements[3 + 2 * 4];
					break;
				}
				break;
			case 2:
				// 3rd row
				switch (column)
				{
				case 0:
					// 3rd row, 1st column
					result.elements[0] = copy.elements[0 + 1 * 4];
					result.elements[1] = copy.elements[1 + 1 * 4];
					result.elements[2] = copy.elements[3 + 1 * 4];

					result.elements[3] = copy.elements[0 + 2 * 4];
					result.elements[4] = copy.elements[1 + 2 * 4];
					result.elements[5] = copy.elements[3 + 2 * 4];

					result.elements[6] = copy.elements[0 + 3 * 4];
					result.elements[7] = copy.elements[1 + 3 * 4];
					result.elements[8] = copy.elements[3 + 3 * 4];
					break;
				case 1:
					// 3rd row, 2nd column
					result.elements[0] = copy.elements[0 + 0 * 4];
					result.elements[1] = copy.elements[1 + 0 * 4];
					result.elements[2] = copy.elements[3 + 0 * 4];

					result.elements[3] = copy.elements[0 + 2 * 4];
					result.elements[4] = copy.elements[1 + 2 * 4];
					result.elements[5] = copy.elements[3 + 2 * 4];

					result.elements[6] = copy.elements[0 + 3 * 4];
					result.elements[7] = copy.elements[1 + 3 * 4];
					result.elements[8] = copy.elements[3 + 3 * 4];
					break;
				case 2:
					// 3rd row, 3rd column
					result.elements[0] = copy.elements[0 + 0 * 4];
					result.elements[1] = copy.elements[1 + 0 * 4];
					result.elements[2] = copy.elements[3 + 0 * 4];

					result.elements[3] = copy.elements[0 + 1 * 4];
					result.elements[4] = copy.elements[1 + 1 * 4];
					result.elements[5] = copy.elements[3 + 1 * 4];

					result.elements[6] = copy.elements[0 + 3 * 4];
					result.elements[7] = copy.elements[1 + 3 * 4];
					result.elements[8] = copy.elements[3 + 3 * 4];
					break;
				case 3:
					// 3rd row, 4th column
					result.elements[0] = copy.elements[0 + 0 * 4];
					result.elements[1] = copy.elements[1 + 0 * 4];
					result.elements[2] = copy.elements[3 + 0 * 4];

					result.elements[3] = copy.elements[0 + 1 * 4];
					result.elements[4] = copy.elements[1 + 1 * 4];
					result.elements[5] = copy.elements[3 + 1 * 4];

					result.elements[6] = copy.elements[0 + 2 * 4];
					result.elements[7] = copy.elements[1 + 2 * 4];
					result.elements[8] = copy.elements[3 + 2 * 4];
					break;
				}
				break;
			case 3:
				// 4th row
				switch (column)
				{
				case 0:
					// 4th row, 1st column
					result.elements[0] = copy.elements[0 + 1 * 4];
					result.elements[1] = copy.elements[1 + 1 * 4];
					result.elements[2] = copy.elements[2 + 1 * 4];

					result.elements[3] = copy.elements[0 + 2 * 4];
					result.elements[4] = copy.elements[1 + 2 * 4];
					result.elements[5] = copy.elements[2 + 2 * 4];

					result.elements[6] = copy.elements[0 + 3 * 4];
					result.elements[7] = copy.elements[1 + 3 * 4];
					result.elements[8] = copy.elements[2 + 3 * 4];
					break;
				case 1:
					// 4th row, 2nd column
					result.elements[0] = copy.elements[0 + 0 * 4];
					result.elements[1] = copy.elements[1 + 0 * 4];
					result.elements[2] = copy.elements[2 + 0 * 4];

					result.elements[3] = copy.elements[0 + 2 * 4];
					result.elements[4] = copy.elements[1 + 2 * 4];
					result.elements[5] = copy.elements[2 + 2 * 4];

					result.elements[6] = copy.elements[0 + 3 * 4];
					result.elements[7] = copy.elements[1 + 3 * 4];
					result.elements[8] = copy.elements[2 + 3 * 4];
					break;
				case 2:
					// 4th row, 3rd column
					result.elements[0] = copy.elements[0 + 0 * 4];
					result.elements[1] = copy.elements[1 + 0 * 4];
					result.elements[2] = copy.elements[2 + 0 * 4];

					result.elements[3] = copy.elements[0 + 1 * 4];
					result.elements[4] = copy.elements[1 + 1 * 4];
					result.elements[5] = copy.elements[2 + 1 * 4];

					result.elements[6] = copy.elements[0 + 3 * 4];
					result.elements[7] = copy.elements[1 + 3 * 4];
					result.elements[8] = copy.elements[2 + 3 * 4];
					break;
				case 3:
					// 4th row, 4th column
					result.elements[0] = copy.elements[0 + 0 * 4];
					result.elements[1] = copy.elements[1 + 0 * 4];
					result.elements[2] = copy.elements[2 + 0 * 4];

					result.elements[3] = copy.elements[0 + 1 * 4];
					result.elements[4] = copy.elements[1 + 1 * 4];
					result.elements[5] = copy.elements[2 + 1 * 4];

					result.elements[6] = copy.elements[0 + 2 * 4];
					result.elements[7] = copy.elements[1 + 2 * 4];
					result.elements[8] = copy.elements[2 + 2 * 4];
					break;
				}
			}
			return result;
		}

		float mat4::minor(const int& row, const int& column)
		{
			mat3 smallerMatrix = subMatrix(row, column);
			float smallerMatrixDeterminant = smallerMatrix.determinant();
			return smallerMatrixDeterminant;
		}

		float mat4::cofactor(const int& row, const int& column)
		{
			mat4 signMatrix = Sign();
			
			float Minor = minor(row, column);
			float result = Minor * signMatrix.elements[row + column * 4];

			return result;
		}

		mat4& mat4::minorMatrix()
		{
			mat4 copy = getCopy();

			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					elements[x + y * 4] = copy.getMinor(x, y);
				}
			}
			return *this;
		}

		mat4& mat4::cofactorMatrix()
		{
			mat4 copy = getCopy();

			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					elements[x + y * 4] = copy.getCofactor(x, y);
				}
			}
			return *this;
		}

		mat4& mat4::adjugate()
		{
			cofactorMatrix();
			transpose();

			return *this;
		}

		mat4& mat4::inverse()
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
		float mat4::Determinant(mat4& matrix)
		{
			return matrix.determinant();
		}

		mat4& mat4::Transpose(mat4& matrix)
		{
			return matrix.transpose();
		}

		mat3 mat4::SubMatrix(mat4& matrix, const int& row, const int& column)
		{
			return matrix.subMatrix(row, column);
		}

		float mat4::Minor(mat4& matrix, const int& row, const int& column)
		{
			return matrix.minor(row, column);
		}

		float mat4::Cofactor(mat4& matrix, const int& row, const int& column)
		{
			return matrix.cofactor(row, column);
		}

		mat4& mat4::MinorMatrix(mat4& matrix)
		{
			return matrix.minorMatrix();
		}

		mat4& mat4::CofactorMatrix(mat4& matrix)
		{
			return matrix.cofactorMatrix();
		}

		mat4& mat4::Adjugate(mat4& matrix)
		{
			return matrix.adjugate();
		}

		mat4& mat4::Inverse(mat4& matrix)
		{
			return matrix.inverse();
		}

		// Same methods, but they will return a value rather than change a matrix
		float mat4::getDeterminant()
		{
			mat4 copy = getCopy();
			return copy.determinant();
		}

		mat4 mat4::getTranspose()
		{
			mat4 copy = getCopy();
			copy.transpose();
			return copy;
		}

		mat3 mat4::getSubMatrix(const int& row, const int& column)
		{
			mat4 copy = getCopy();
			return copy.subMatrix(row, column);
		}

		float mat4::getMinor(const int& row, const int& column)
		{
			mat4 copy = getCopy();
			return copy.minor(row, column);
		}

		float mat4::getCofactor(const int& row, const int& column)
		{
			mat4 copy = getCopy();
			return copy.cofactor(row, column);
		}

		mat4 mat4::getMinorMatrix()
		{
			mat4 copy = getCopy();
			copy.minorMatrix();
			return copy;
		}

		mat4 mat4::getCofactorMatrix()
		{
			mat4 copy = getCopy();
			copy.cofactorMatrix();
			return copy;
		}

		mat4 mat4::getAdjugate()
		{
			mat4 copy = getCopy();
			copy.adjugate();
			return copy;
		}

		mat4 mat4::getInverse()
		{
			mat4 copy = getCopy();
			copy.inverse();
			return copy;
		}

		// Static versions
		float mat4::GetDeterminant(mat4 matrix)
		{
			return matrix.getDeterminant();
		}

		mat4 mat4::GetTranspose(mat4 matrix)
		{
			return matrix.getTranspose();
		}

		mat3 mat4::GetSubMatrix(mat4 matrix, const int& row, const int& column)
		{
			return matrix.getSubMatrix(row, column);
		}

		float mat4::GetMinor(mat4 matrix, const int& row, const int& column)
		{
			return matrix.getMinor(row, column);
		}

		float mat4::GetCofactor(mat4 matrix, const int& row, const int& column)
		{
			return matrix.getCofactor(row, column);
		}

		mat4 mat4::GetMinorMatrix(mat4 matrix)
		{
			return matrix.getMinorMatrix();
		}

		mat4 mat4::GetCofactorMatrix(mat4 matrix)
		{
			return matrix.getCofactorMatrix();
		}

		mat4 mat4::GetAdjugate(mat4 matrix)
		{
			return matrix.getAdjugate();
		}

		mat4 mat4::GetInverse(mat4 matrix)
		{
			return matrix.getInverse();
		}

		/*          OPERATION METHODS BELOW          */

		// Methods to do arithmetic operations with matrices
		mat4& mat4::add(const mat4& other)
		{
			for (int i = 0; i < 4 * 4; i++)
			{
				elements[i] += other.elements[i];
			}

			return *this;
		}

		mat4& mat4::subtract(const mat4& other)
		{
			for (int i = 0; i < 4 * 4; i++)
			{
				elements[i] -= other.elements[i];
			}

			return *this;
		}

		mat4& mat4::multiply(const mat4& other)
		{
			mat4 copy = getCopy();

			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					float sum = 0.0f;
					for (int e = 0; e < 4; e++)
					{
						sum += copy.elements[x + e * 4] * other.elements[e + y * 4];
					}
					elements[x + y * 4] = sum;
				}
			}
			return *this;
		}

		mat4& mat4::divide(const mat4& other)
		{
			return multiply(GetInverse(other));
		}

		// Static versions 
		mat4& mat4::Add(mat4& left, const mat4& right)
		{
			return left.add(right);
		}

		mat4& mat4::Subtract(mat4& left, const mat4& right)
		{
			return left.subtract(right);
		}

		mat4& mat4::Multiply(mat4& left, const mat4& right)
		{
			return left.multiply(right);
		}

		mat4& mat4::Divide(mat4& left, const mat4& right)
		{
			return left.divide(right);
		}

		// Same methods, but they will return a value rather than change a matrix
		mat4 mat4::sum(const mat4& other)
		{
			mat4 copy = getCopy();
			copy.add(other);
			return copy;
		}

		mat4 mat4::difference(const mat4& other)
		{
			mat4 copy = getCopy();
			copy.subtract(other);
			return copy;
		}

		mat4 mat4::product(const mat4& other)
		{
			mat4 copy = getCopy();
			copy.multiply(other);
			return copy;
		}

		mat4 mat4::quotient(const mat4& other)
		{
			mat4 copy = getCopy();
			copy.divide(other);
			return copy;
		}

		// Static versions
		mat4 mat4::Sum(mat4 left, const mat4& right)
		{
			return left.sum(right);
		}

		mat4 mat4::Difference(mat4 left, const mat4& right)
		{
			return left.difference(right);
		}

		mat4 mat4::Product(mat4 left, const mat4& right)
		{
			return left.product(right);
		}

		mat4 mat4::Quotient(mat4 left, const mat4& right)
		{
			return left.quotient(right);
		}

		// Methods to do arithmetic operations with scalars
		mat4& mat4::addScalar(const float& scalar)
		{
			for (int i = 0; i < 4 * 4; i++)
			{
				elements[i] += scalar;
			}

			return *this;
		}

		mat4& mat4::subtractScalar(const float& scalar)
		{
			for (int i = 0; i < 4 * 4; i++)
			{
				elements[i] -= scalar;
			}

			return *this;
		}

		mat4& mat4::multiplyScalar(const float& scalar)
		{
			for (int i = 0; i < 4 * 4; i++)
			{
				elements[i] *= scalar;
			}

			return *this;
		}

		mat4& mat4::divideScalar(const float& scalar)
		{
			for (int i = 0; i < 4 * 4; i++)
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
		mat4& mat4::AddScalar(mat4& matrix, const float& scalar)
		{
			return matrix.addScalar(scalar);
		}

		mat4& mat4::SubtractScalar(mat4& matrix, const float& scalar)
		{
			return matrix.subtractScalar(scalar);
		}

		mat4& mat4::MultiplyScalar(mat4& matrix, const float& scalar)
		{
			return matrix.multiplyScalar(scalar);
		}

		mat4& mat4::DivideScalar(mat4& matrix, const float& scalar)
		{
			return matrix.divideScalar(scalar);
		}

		// Same methods, but they will return a value rather than change a matrix
		mat4 mat4::scalarSum(const float& scalar)
		{
			mat4 copy = getCopy();
			copy.addScalar(scalar);
			return copy;
		}

		mat4 mat4::scalarDifference(const float& scalar)
		{
			mat4 copy = getCopy();
			copy.subtractScalar(scalar);
			return copy;
		}

		mat4 mat4::scalarProduct(const float& scalar)
		{
			mat4 copy = getCopy();
			copy.multiplyScalar(scalar);
			return copy;
		}

		mat4 mat4::scalarQuotient(const float& scalar)
		{
			mat4 copy = getCopy();
			copy.divideScalar(scalar);
			return copy;
		}

		// Static versions
		mat4 mat4::ScalarSum(mat4 matrix, const float& scalar)
		{
			return matrix.scalarSum(scalar);
		}

		mat4 mat4::ScalarDifference(mat4 matrix, const float& scalar)
		{
			return matrix.scalarDifference(scalar);
		}

		mat4 mat4::ScalarProduct(mat4 matrix, const float& scalar)
		{
			return matrix.scalarProduct(scalar);
		}

		mat4 mat4::ScalarQuotient(mat4 matrix, const float& scalar)
		{
			return matrix.scalarQuotient(scalar);
		}

		// Methods to do relational and comparison operations with matrices
		bool mat4::isEqualTo(const mat4& other)
		{
			for (int i = 0; i < 4 * 4; i++)
			{
				if (elements[i] == other.elements[i])
				{
					if (i == (4 * 4 - 1))
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

		bool mat4::isNotEqualTo(const mat4& other)
		{
			return !isEqualTo(other);
		}

		// Static versions
		bool mat4::IsEqualTo(mat4 left, const mat4& right)
		{
			return left.isEqualTo(right);
		}

		bool mat4::IsNotEqualTo(mat4 left, const mat4& right)
		{
			return left.isNotEqualTo(right);
		}

		// Methods to print the matrix to the screen

		// Uses C or C++'s method of printing
		void mat4::print()
		{
#if PRINT_METHOD_C
			printf("mat4: \n");

			for (int y = 0; y < 4; y++)
			{
				printf("[");
				for (int x = 0; x < 4; x++)
				{
					printf("%f%s", elements[y + x * 4], 
						((x != (4 - 1) ? ", " : "] \n")));
				}
			}
#endif

#if PRINT_METHOD_CPP 
			Print(std::cout, *this);
#endif
		}

		// Uses C or C++'s method of printing
		void mat4::Print(mat4 matrix)
		{
			matrix.print();
		}

		// Uses C++'s way of printing
		std::ostream& mat4::Print(std::ostream& stream, const mat4& matrix)
		{
			stream << "mat4: " << std::endl;

			for (int y = 0; y < 4; y++)
			{
				stream << "[";
				for (int x = 0; x < 4; x++)
				{
					stream << matrix.elements[y + x * 4] <<
						((x != (4 - 1) ? ", " : "] \n"));
				}
			}

			return stream;
		}

		/*          OPERATOR OVERLOAD BELOW          */

		// Overflow arithmetic operators with matrices
		mat4 operator+(mat4 left, const mat4& right)
		{
			return mat4::Sum(left, right);
		}

		mat4 operator-(mat4 left, const mat4& right)
		{
			return mat4::Difference(left, right);
		}

		mat4 operator*(mat4 left, const mat4& right)
		{
			return mat4::Product(left, right);
		}

		mat4 operator/(mat4 left, const mat4& right)
		{
			return mat4::Quotient(left, right);
		}

		// Overflow arithmetic operators with scalars
		mat4 operator+(mat4 matrix, const float& scalar)
		{
			return mat4::ScalarSum(matrix, scalar);
		}
		mat4 operator-(mat4 matrix, const float& scalar)
		{
			return mat4::ScalarDifference(matrix, scalar);
		}
		mat4 operator*(mat4 matrix, const float& scalar)
		{
			return mat4::ScalarProduct(matrix, scalar);
		}
		mat4 operator/(mat4 matrix, const float& scalar)
		{
			return mat4::ScalarQuotient(matrix, scalar);
		}

		// Overflow the compound assignment operators with matrices
		mat4& mat4::operator+=(const mat4& other)
		{
			return add(other);
		}

		mat4& mat4::operator-=(const mat4& other)
		{
			return subtract(other);
		}

		mat4& mat4::operator*=(const mat4& other)
		{
			return multiply(other);
		}

		mat4& mat4::operator/=(const mat4& other)
		{
			return divide(other);
		}

		// Overflow the compound assignment operators with scalars
		mat4& mat4::operator+=(const float& scalar)
		{
			return addScalar(scalar);
		}

		mat4& mat4::operator-=(const float& scalar)
		{
			return subtractScalar(scalar);
		}

		mat4& mat4::operator*=(const float& scalar)
		{
			return multiplyScalar(scalar);
		}

		mat4& mat4::operator/=(const float& scalar)
		{
			return divideScalar(scalar);
		}

		// Overflow relational and comparison operators
		bool operator==(mat4 left, const mat4& right)
		{
			return mat4::IsEqualTo(left, right);
		}

		bool operator!=(mat4 left, const mat4& right)
		{
			return mat4::IsNotEqualTo(left, right);
		}

		// Overflow the bitwise operator
		std::ostream& operator<<(std::ostream& stream, mat4 matrix)
		{
			return mat4::Print(stream, matrix);
		}
	}
}

