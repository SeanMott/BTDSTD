#pragma once

//defines a string object

#include <BTDSTD/Types.hpp>

#include <string>

namespace BTD::Util
{
	//converts to a string
	inline std::string ToString(uint64& data)
	{
		return std::to_string(data);
	}
	//converts to a string
	inline std::string ToString(const uint64& data)
	{
		return std::to_string(data);
	}

	//converts to a string
	inline std::string ToString(uint8& data)
	{
		return std::to_string(data);
	}
	//converts to a string
	inline std::string ToString(const uint8& data)
	{
		return std::to_string(data);
	}

	////converts to a string
	//inline std::string ToString(uint32& data)
	//{
	//	std::string str = "";
	//	uint32 n = data;
	//	while (n > 0) //do till num greater than  0
	//	{
	//		int mod = n % 10;  //split last digit from number
	//		str += std::to_string(mod); //print the digit. 

	//		n = n / 10;    //divide num by 10. num /= 10 also a valid one 
	//	}

	//	return str;
	//}
	
	//converts to a string
	inline std::string ToString(const uint32& data)
	{
		return std::to_string(data);
	}

	//converts to a string
	inline std::string ToString(char& data)
	{
		return std::to_string(data);
	}
	//converts to a string
	inline std::string ToString(const char& data)
	{
		return std::to_string(data);
	}
}