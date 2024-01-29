#pragma once

//defines a Set, Sets will only store unique objects not equal to anything else of the same type

#include <BTDSTD/Types.hpp>

#include <vector>

namespace BTD::Set
{
	//defines a set using a boolean logic to compare
	template<typename T>
	struct Set
	{
		//---vars
		std::vector<T> objs;

		//---methods

		//clears the data
		inline void Clear() { objs.clear(); }

		//adds a unique object to the set, returns true if the object was new
		
		//adds a unique object to the set, returns the position of the object
		inline uint32 Add_ReturnPosition(T& obj)
		{
			//if it's already in the set
			uint32 i = 0;
			if (IsIn(obj, i))
				return i;

			//adds it
			objs.emplace_back(obj);
			return objs.size() - 1;
		}

		//removes a object from the set
	
		//checks if the object exists in the set
		inline bool IsIn(T& obj)
		{
			for (uint32 i = 0; i < objs.size(); ++i)
			{
				if (obj == objs[i])
					return true;
			}

			return false;
		}

		//checks if the object exists in the set, and gives the position of the object
		inline bool IsIn(T& obj, uint32& posInArray)
		{
			for (uint32 i = 0; i < objs.size(); ++i)
			{
				if (obj == objs[i])
				{
					posInArray = i;
					return true;
				}
			}

			return false;
		}
	};

	//defines a set using a compare function
}