#pragma once

//defines a reflection objects for reflections

#include <BTDSTD/Reflection/Datatypes.hpp>

//#include <BTDSTD/Maps/IDRegistery.hpp>
#include <BTDSTD/Maps/IDHash.hpp>

#include <BTDSTD/IO/YAML.hpp>

#include <vector>
#include <string>

namespace BTD::Reflection
{
	#define BTD_Reflection_ToString(d) (#d)

	//defines macro for reflecting a variable that inhereted
#define BTD_Reflection_ReflectVar_Inhereted(_struct, publicFlag, modiferFlag, count, datatype, name, parentID) \
	{publicFlag, modiferFlag, datatype, BTD::Reflection::Datatype::Count, BTD::Reflection::GetMemSizeOfType(datatype), offsetof(_struct, name), count, true, parentID, (#name)}

	//defines macro for reflecting a variable
#define BTD_Reflection_ReflectVar(_struct, publicFlag, modiferFlag, count, datatype, name) \
	BTD::Reflection::ReflectedVar::ReflectVar((#name), publicFlag, modiferFlag, datatype, BTD::Reflection::GetMemSizeOfType(datatype), offsetof(_struct, name))
	//{publicFlag, modiferFlag, datatype, BTD::Reflection::Datatype::Count, BTD::Reflection::GetMemSizeOfType(datatype), offsetof(_struct, name), count, false, 0, (#name)}

	//defines macro for reflecting a variable list
#define BTD_Reflection_ReflectListVar(_struct, publicFlag, modiferFlag, count, datatype, name) \
	BTD::Reflection::ReflectedVar::ReflectListVar((#name), publicFlag, modiferFlag, datatype, BTD::Reflection::GetMemSizeOfType(datatype), offsetof(_struct, name))	
//{publicFlag, modiferFlag, BTD::Reflection::Datatype::List, datatype, BTD::Reflection::GetMemSizeOfType(datatype), offsetof(_struct, name), count, false, 0, (#name)}

	//defines a reflected variable
	struct ReflectedVar
	{
		PublicStatusFlag publicityStatus = PublicStatusFlag::Public; //is the variable public, private, or protetcted
		PropertyModifierFlags modiferFlag = PropertyModifierFlags::None; //is the variable static, const, inline, ect
		Datatype datatype = Datatype::Count; //the type it is
		Datatype secondaryDatatype = Datatype::Count; //the secondary type it is
		size_t memSize = 0; //the memory size of the type
		size_t offset = 0; //the offset into the struct of this var
		size_t count = 0; //used for array data and other lengths

		bool isInhereted = false; //is the var inhereted from another class/struct
		uint64 parentID = 0; //if it is, point to the ID of the reflected parent

		std::string name = "\0"; //the name of the var

		//returns a reflected var
		static inline ReflectedVar ReflectVar(const std::string& name, const PublicStatusFlag& publicityStatus, const PropertyModifierFlags& modiferFlag,
			const Datatype& datatype, const size_t& memSize, const size_t& offset)
		{
			ReflectedVar v;
			v.name = name; v.publicityStatus = publicityStatus; v.modiferFlag = modiferFlag; v.datatype = datatype; v.memSize = memSize; v.offset = offset;
			return v;
		}

		//returns a reflected dynamic list var
		static inline ReflectedVar ReflectListVar(const std::string& name, const PublicStatusFlag& publicityStatus, const PropertyModifierFlags& modiferFlag,
			const Datatype& listDatatype, const size_t& memSize, const size_t& offset)
		{
			ReflectedVar v;
			v.name = name; v.publicityStatus = publicityStatus; v.modiferFlag = modiferFlag; v.datatype = Datatype::List; v.memSize = memSize; v.offset = offset;
			v.secondaryDatatype = listDatatype;
			return v;
		}
	};

	//writes a reflected var to a YAML file
	//inline void WriteReflectedVariableToDescriptionFile(YAML::Emitter& emitter, const ReflectedVar& v, const std::string& parantName = "")
	//{
	//	emitter << YAML::BeginMap; //starts a new block of YAML data

	//	emitter << YAML::Key << "name" << YAML::DoubleQuoted << v.name;
	//	emitter << YAML::Key << "offset" << YAML::Value << v.offset;

	//	emitter << YAML::Key << "datatype" << YAML::Value << (uint32)v.datatype;
	//	emitter << YAML::Key << "secondaryDatatype" << YAML::Value << (uint32)v.secondaryDatatype;

	//	emitter << YAML::Key << "publicityStatus" << YAML::Value << (uint32)v.publicityStatus;
	//	emitter << YAML::Key << "modiferFlag" << YAML::Value << (uint32)v.modiferFlag;
	//	emitter << YAML::Key << "count" << YAML::Value << v.count;

	//	emitter << YAML::Key << "isInhereted" << YAML::Value << v.isInhereted;
	//	emitter << YAML::Key << "parantName" << YAML::DoubleQuoted << parantName;

	//	emitter << YAML::EndMap; //ends block of YAML
	//}

	//reads a reflected var from a YAML file

	//defines a reflected function

	//writes a reflected function to a YAML file
	//reads a reflected function from a YAML file

	//defines a reflected struct
	struct ReflectedStruct
	{
		uint64 ID = 0; //the internal ID used as it's refrence to a name
		size_t memSize = 0;
		std::vector<ReflectedVar> vars;
		std::string name = "";
	};

	//writes a reflected struct to a YAML file

	//reads a reflected struct from a YAML file

	//defines a reflection registery
	struct ReflectionRegistery
	{
		IDStringHash IDs;
		std::vector<ReflectedStruct> structs;

		//inits a reflection registery
		inline void Init() {}
		//destroys a reflection registery
		inline void Clear()
		{
			IDs.Clear(); structs.clear();
		}

		//registers a new type
		inline uint64 RegisterType(const char* structName, const size_t& structMemSize,
			const std::vector<ReflectedVar>& vars)
		{
			uint64 ID = 0; if (!IDs.GenerateNewID(structName, ID)) {return 0;}

			ReflectedStruct* s = &structs.emplace_back(ReflectedStruct());
			s->ID = ID; s->name = structName; s->memSize = structMemSize; s->vars = vars;
			return s->ID;
		}

		//unregisters a type
		
		//gets a registered struct
		inline ReflectedStruct* GetReflectedStruct(const char* name)
		{
			uint64 ID = IDs.hash[name];
			for (uint64 i = 0; i < structs.size(); ++i)
			{
				if (ID == structs[i].ID)
					return &structs[i];
			}

			BTD::Logger::LogError("BTDSTD", "Reflection", " GetReflectedStruct", (std::string(name) + std::string(" is not a registered name for a struct!")).c_str());
			//printf("BTD Reflection Error: ReflectionRegistery \"GetReflectedStruct\" || %s is not a registered name for a struct!\n", name);
			return nullptr;
		}

		//gets a registered struct
		inline ReflectedStruct* GetReflectedStruct(const uint64& ID)
		{
			for (uint64 i = 0; i < structs.size(); ++i)
			{
				if (ID == structs[i].ID)
					return &structs[i];
			}

			BTD::Logger::LogError("BTDSTD", "Reflection", " GetReflectedStruct", (BTD::Util::ToString(ID) + std::string(" is not a registered ID for a struct!")).c_str());
			//printf("BTD Reflection Error: ReflectionRegistery \"GetReflectedStruct\" || %i is not a registered ID for a struct!\n", ID);
			return nullptr;
		}

		//gets a ID by name
		inline uint64 GetID(const char* name)
		{
			return IDs.hash[name];
		}
	};

	//gets a reflected C++ standard string
	inline char* GetSTDStringPropteryPointer(void* obj, const ReflectedVar& var)
	{
		return ((std::string*)((uint8_t*)(obj)+var.offset))->data();
	}
	//gets a reflected C++ standard string
	inline std::string* GetSTDStringPropteryPointerStr(void* obj, const ReflectedVar& var)
	{
		return (std::string*)((uint8_t*)(obj)+var.offset);
	}

	//gets a reflected C char* string
	inline const char* GetCStringPropteryPointer(void* obj, const ReflectedVar& var)
	{
		return *((const char**)((uint8_t*)(obj) + var.offset));
	}

	//gets the reflected property from a struct
	template<typename T>
	inline T* GetPropertyPointer(void* obj, const ReflectedVar& var)
	{
		return ((T*)((uint8_t*)(obj) + var.offset));
	}

	//gets the reflected property from a struct
	template<typename T>
	inline T GetPropertyCopy(void* obj, const ReflectedVar & var)
	{
		return (*((T*)((uint8_t*)(obj)+var.offset)));
	}

	//sets a reflected property
	template<typename T>
	inline void SetProperty(void* obj, const ReflectedVar& var, const T* data)
	{
		memcpy((((T*)((uint8_t*)(obj)+var.offset))), data, sizeof(T));
	}
}