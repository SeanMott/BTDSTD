#pragma once

//defines a ID registor for generating and managing IDs

#include <BTDSTD/Types.hpp>

#include <vector>

namespace BTD
{
	//defines a ID register, uses uint64 for IDs, 0 is NULL
	struct IDRegistery
	{
		uint64 nextID = 0;
		std::vector<uint64> freeIDs;
		std::vector<uint64> usedIDs;

		//reserves space on the register
		inline void Reserve(const size_t inUseCount, const size_t freeToUseCount)
		{
			usedIDs.reserve(inUseCount); freeIDs.reserve(freeToUseCount);
		}

		//destroys the registery
		inline void Clear() { freeIDs.clear(); usedIDs.clear(); nextID = 0; }

		//adds a ID
		inline uint64 AddID(const uint64& ID) { return usedIDs.emplace_back(ID); }

		//generates a new ID
		inline uint64 GenerateNewID()
		{
			//checks for free IDs

			//checks that there are IDs left to use

			//creates new ID
			uint64 ID = nextID; nextID++;

			usedIDs.emplace_back(ID);
			return ID;
		}

		//frees a ID
		inline void FreeID(const uint64& ID)
		{
			for (uint64 i = 0; i < usedIDs.size(); ++i)
			{
				if (ID == usedIDs[i])
				{
					usedIDs.erase((usedIDs.begin() + i));
					break;
				}
			}

			freeIDs.emplace_back(ID);
		}
	};
}