#pragma once

#include <string>
#include <fstream>

#ifndef READ_METHOD_C
#ifndef READ_METHOD_CPP
#define READ_METHOD_C
#endif
#endif

#ifdef READ_METHOD_C
#ifdef READ_METHOD_CPP
#undef READ_METHOD_CPP
#endif
#endif

namespace Rambug
{
	namespace Utils 
	{

		static std::string read_file(const char* filePath)
		{
#ifdef READ_METHOD_C
			FILE* file = new FILE;

			if (file == fopen(filePath, "rt"))
			{
				fseek(file, 0, SEEK_END);
				unsigned long length = ftell(file);

				char* data = new char[length + 1];
				memset(data, 0, length + 1);
				fseek(file, 0, SEEK_SET);
				fread(data, 1, length, file);

				fclose(file);

				std::string result(data);
				delete[] data;
			}
			else
			{
				// Exception Occurred
				// todo: log
				return 0;
			}
#endif
#ifdef READ_METHOD_CPP
			std::ifstream file(filePath);

			if (file)
			{
				std::string result;
				result.assign((std::istreambuf_iterator<char>(file)),
					(std::istreambuf_iterator<char>()));
				return result;
			}
			else
			{
				log_error("READ ERROR: COULD NOT READ FILE AT: " + (std::string) filePath + " \n");
				return 0;
			}
#endif
		}
	}
}
