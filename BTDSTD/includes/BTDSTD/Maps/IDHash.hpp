#pragma once

//defines a hash map for pairing IDs and strings

#include <BTDSTD/Logger.hpp>
#include <BTDSTD/String.hpp>
#include <BTDSTD/Types.hpp>

#include <BTDSTD/Maps/IDRegistery.hpp>

#include <unordered_map>
#include <vector>

namespace BTD
{
	struct IDStringHash
	{
		IDRegistery iDRegistery;
		std::unordered_map<std::string, uint64> hash;

		//clears all IDs
		inline void Clear()
		{
			iDRegistery.Clear(); hash.clear();
		}

		//generates a new ID
		inline bool GenerateNewID(const std::string& name, uint64& ID)
		{
			//if already exists
			if (hash.find(name) != hash.end())
			{
				//if (!ignoreWarning)
				//{
				BTD::Logger::LogWarning("BTDSTD", "IDStringHash", "GenerateNewID", (std::string(name) + std::string(" is in the hash already!")).c_str());
					return false;
				//}

				////if ignore warning, just retrive the ID
				//_ID = hash.at(name);
				//return true;
			}

			//generates new
			ID = hash[name] = iDRegistery.GenerateNewID();
			return true;
		}

		//frees a ID
		inline void FreeID(const std::string& name)
		{
			uint64 ID = hash[name];
			hash.erase(name);
			iDRegistery.FreeID(ID);
		}

		//checks if the name is associated with a ID
		inline bool IsID(const std::string& name)
		{
			const char* n = name.c_str();
			for (auto& h : hash)
			{
				if (!strcmp(h.first.c_str(), n)) //if the name matches
					return true;
			}

			return false;
		}

		//checks if the ID is associated with a name
		inline bool IsName(const uint64& ID)
		{
			for (auto& h : hash)
			{
				if (h.second == ID) //if the ID matches
					return true;
			}

			return false;
		}

		//gets the string associated with a ID
		inline std::string GetStr(const uint64& ID)
		{
			for (auto& h : hash)
			{
				if (h.second == ID) //if the ID matches
					return h.first;
			}

			BTD::Logger::LogWarning("BTDSTD", "IDStringHash", "GetStr", (BTD::Util::ToString(ID) + std::string(" is not a valid ID in a pair!")).c_str());
			return "";
		}

		//gets the ID associated with a string
		inline uint64 GetID(const std::string& name)
		{
			const char* n = name.c_str();
			for (auto& h : hash)
			{
				if (!strcmp(h.first.c_str(), n)) //if the name matches
					return h.second;
			}

			BTD::Logger::LogWarning("BTDSTD", "IDStringHash", "GetID", (std::string(name) + std::string(" is not a valid name in a pair!")).c_str());
			return 0;
		}

		//changes the string associated with a ID
		inline bool UpdateString(const std::string& newStr, const uint64& ID)
		{
			//checks if the ID event exists
			if (!IsName(ID))
			{
				BTD::Logger::LogError("BTD STD", "ID Hash", "UpdateString",
					std::string("\"" + newStr + "\" was attempted to be used to replace another string. But the ID was not in use in the hash.").c_str());
				return false;
			}

			//removes the old string and update it
			std::string str = "";
			for (auto& s : hash)
			{
				if (s.second == ID)
				{
					str = s.first;
					break;
				}
			}
			hash.erase(str); hash[newStr] = ID;

			return true;
		}
	};
}