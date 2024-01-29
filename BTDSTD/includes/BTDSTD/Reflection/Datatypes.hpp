#pragma once

//defines a datatypes for a reflection system

#include <BTDSTD/Logger.hpp>

#include <BTDSTD/Math/Vector.hpp>

#include <stdio.h>
#include <cstdint>

namespace BTD::Reflection
{
	//defines the value type of the propert
	enum PropertyRefTypeFlag
	{
		Copy = 0x00, //is a copy
		Ref, //is by ref
		Pointer, //is by pointer
	
		Count
	};

	//defines modifier flags || get bitwised into one var
	enum class PropertyModifierFlags
	{
		None = 0x00, //no modifers are attachted
		Static, //is it static
		Const, //is it const
		Inline, //is it inline

		Count
	};

	//defines the public status
	enum class PublicStatusFlag
	{
		Public = 0x00, //is it public
		Private, //is it private
		Protected, //is it protected

		Public_HideInEditor, //is it public but will not show in the editor
		Private_ShowInEditor, //is it private but will show in the editor
		Protected_ShowInEditor, //is it protected but will show in the editor

		Count
	};

	//defines datatypes
	enum class Datatype
	{
		Uint8 = 0x00,
		Uint32,
		Uint64,

		Int8,
		Int32,
		Int64,

		Float,
		Double,

		Bool,

		String, //C++ string
		CString, //C style string

		Size_t, //size type
		Pointer, //genaric pointer for...idk
		FuncPointer, //genaric function pointer for...idk


		//float vectors
		FVec2,
		FVec3,
		FVec4,

		//double vectors
		DVec2,
		DVec3,
		DVec4,

		Color, //color

		AssetID, //defines a asset ID

		List, //defines a list



		//defines a array

		//defines a pointer

		Struct, //custom struct

		Enum, //custom enum

		Count
	};

	//defines various precompiled memory sizes
	static size_t UINT8_MEM_SIZE = sizeof(uint8_t);
	static size_t UINT32_MEM_SIZE = sizeof(uint32_t);
	static size_t UINT64_MEM_SIZE = sizeof(uint64_t);

	static size_t BOOL_MEM_SIZE = sizeof(bool);

	static size_t DVEC2_MEM_SIZE = sizeof(Math::DVec2);
	static size_t DVEC3_MEM_SIZE = sizeof(Math::DVec3);

	static size_t COLOR_MEM_SIZE = sizeof(Math::Color);

	//gets the memory size based on the type passed
	inline size_t GetMemSizeOfType(const Datatype type)
	{
		switch (type)
		{
		case Datatype::Uint8:
			return UINT8_MEM_SIZE;
		case Datatype::Uint32:
			return UINT32_MEM_SIZE;
		case Datatype::Uint64:
			return UINT64_MEM_SIZE;

		case Datatype::Bool:
			return BOOL_MEM_SIZE;

		case Datatype::DVec2:
			return DVEC2_MEM_SIZE;
		case Datatype::DVec3:
			return DVEC3_MEM_SIZE;

		case Datatype::Color:
			return COLOR_MEM_SIZE;

		case Datatype::CString:
			return 0;
		case Datatype::String:
			return 0;
		case Datatype::Enum:
			return UINT32_MEM_SIZE;

		case Datatype::AssetID:
			return UINT64_MEM_SIZE;

		case Datatype::List:
			return 0;

		case Datatype::Struct:
			return 0;

		default:
			BTD::Logger::LogError("BTDSTD", "Reflection", "GetMemSizeOfType", "Datatype passed in is not a valid one, can not return a memory size!");
			//printf("BTD Reflection Error: \"GetMemSizeOfType\" || Datatype passed in is not a valid one, can not return a memory size!\n");
			break;
		}

		return 0;
	}
}