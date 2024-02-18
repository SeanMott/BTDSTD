#pragma once

//defines a Set of Strings

#include <BTDSTD_C/Types.h>

#include <string>
#include <vector>

namespace BTD::Set
{
	//defines a string set
	struct StringSet
	{
		//--vars
		std::vector<std::string> strings;

		//--methods

		//gets the string count
		inline size_t Size() const { return strings.size(); }

		//clears the strings
		inline void Clear() { strings.clear(); }

		//reserve space in the strings
		inline void Reserve(const size_t amount) { strings.reserve(amount); }

		//adds a string || returns false if the string already exists
		inline bool AddString(const std::string& str)
		{
			if (!AlreadyExsists(str))
			{
				strings.emplace_back(str);
				return true;
			}

			return false;
		}

		//removes a string

		//gets a string

		//checks if a string exists already
		inline bool AlreadyExsists(const char* str)
		{
			for (uint32 i = 0; i < strings.size(); ++i)
			{
				if (!strcmp(str, strings[i].c_str()))
					return true;
			}

			return false;
		}

		//checks if a string exists already
		inline bool AlreadyExsists(const std::string& str) { return AlreadyExsists(str.c_str()); }
	};
}