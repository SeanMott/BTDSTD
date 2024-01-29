#pragma once

//defines a Unordered Map

#include <map>
#include <unordered_map>
#include <vector>

#include <cstdio>

//namespace BTD
////{
////	//defines a pair object
////	template<typename Key, typename Value>
////	struct Pair
////	{
////		//size_t lastItemCount = 0; //stored
////		std::vector<Key> keys;
////		std::vector<Value> values;
////
////		//reserves space
////		
////		//clears the pair || optionally reserve space ahead of time
////		inline void Clear()
////		{
////			keys.clear(); values.clear();
////		}
////
////		//checks if the key is already used
////		inline bool AlreadyHasKey(Key& key)
////		{
////			for (uint32 i = 0; i < keys.size(); ++i)
////			{
////				if(key == keys[])
////			}
////		}
////
////		//creates a new entry
////		inline Value& NewEntry(Key& key)
////		{
////			keys.emplace_back(key); return values.emplace_back(Value());
////		}
////		//creates a new entry
////		inline Value& NewEntry(Key& key, Value& value)
////		{
////			keys.emplace_back(key); return values.emplace_back(value);
////		}
////	};
//
//	////defines a unordered map
//	//template<typename Key, typename Value>
//	//struct UnorderedMap
//	//{
//	//	std::unordered_map<Key, Value> map;
//
//	//	//reserves space in the map
//	//	//clears the map
//
//	//	//checks if the key is already in the map
//	//	inline bool AlreadyHasKey(Key key) {return (map.find(key) != map.end() ? true : false);}
//
//	//	//finds a value by key
//	//	//finds a key by value
//
//	//	//gets the keys
//	//	//gets the values
//
//	//	//gets a key by index
//	//	inline Key& GetKeyByIndex(const uint32 index)
//	//	{
//
//	//	}
//
//	//	/*Value& operator[](Key key, char* callbackErrorMessage = "Key doesn't exist, can not retrive value!")
//	//	{
//	//		if (!AlreadyHasKey(key))
//	//		{
//	//			printf("BTD Unordered Map Error: %s\n", callbackErrorMessage);
//	//			Value v;
//	//			return v;
//	//		}
//
//	//		return map[key];
//	//	}*/
//	//};
//}