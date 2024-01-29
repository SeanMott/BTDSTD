#pragma once

//defines a YAML implitation for BTD and writing types to file

#include <BTDSTD/Math/Vector.hpp>
#include <BTDSTD_C/Math/Vectors.h>

#include <BTDSTD/Reflection/Datatypes.hpp>

#include <yaml-cpp/yaml.h>
//
//namespace BTD::IO::yaml
//{
//	//defines the types of YAML nodes
//	enum class YAMLNodeType
//	{
//		Key_Value = 0, //defines a key and value pair node
//
//		Map, //defines a map
//
//		Sequence, //defines a sequence
//
//		Count
//	};
//
//	//defines a node in the graph
//	struct YAMLNode
//	{
//		YAMLNodeType type = YAMLNodeType::Key_Value; //the type of YAML node
//
//		Reflection::Datatype datatype = Reflection::Datatype::Bool; //the datatype of the value
//		std::string keyStr = "", //the key for the value
//			valueStr = ""; //the value, as a string, bound to the key
//
//		std::vector<YAMLNode> nodes; //the extra data used if this is a map or sequence
//
//		//checks the key associated with this Node
//
//		//is the node a key_value pair
//
//		//is the node a map
//
//		//is the node a sequence
//	};
//
//	//adds a key value pair node
//	inline YAMLNode AddYAMLNode_KeyValuePair(const std::string& keyStr, const std::string& valueStr,
//		const Reflection::Datatype& valueDatatype)
//	{
//		YAMLNode node;
//
//		node.type = YAMLNodeType::Key_Value;
//
//		node.keyStr = keyStr;
//
//		node.datatype = valueDatatype; node.valueStr = valueStr;
//
//		return node;
//	}
//
//	//adds a map node
//	inline YAMLNode AddYAMLNode_Map(const std::vector<YAMLNode>& mapNodes)
//	{
//		YAMLNode node;
//
//		node.type = YAMLNodeType::Map;
//		node.nodes = mapNodes;
//
//		return node;
//	}
//
//	//adds a sequence node
//
//	//converts a YAML graph into text
//	inline void ConvertGraph_Text(const std::vector<YAMLNode>& nodes, YAML::Emitter& emitter)
//	{
//		for (uint32 i = 0; i < nodes.size(); ++i)
//		{
//			//recursive convert for maps
//			if (nodes[i].type == YAMLNodeType::Map)
//			{
//				emitter << YAML::BeginMap;
//				ConvertGraph_Text(nodes[i].nodes, emitter);
//				emitter << YAML::EndMap;
//			}
//
//			//key value pair
//			else if (nodes[i].type == YAMLNodeType::Key_Value)
//			{
//				emitter << YAML::Key << nodes[i].keyStr << (nodes[i].datatype == BTD::Reflection::Datatype::String == true ? YAML::DoubleQuoted : YAML::Value)
//					<< nodes[i].valueStr;
//			}
//		}
//	}
//
//	//converts a YAML graph into text
//	inline std::string ConvertGraph_Text(const std::vector<YAMLNode>& nodes)
//	{
//		YAML::Emitter emitter;
//		ConvertGraph_Text(nodes, emitter);
//		return emitter.c_str();
//	}
//}

//----YAML OPERATOR OVERRIDES IMPORT------------------//

template<>
inline BTD::Math::Color YAML::Node::as() const
{
	return { (*this)[0].as<float>(), (*this)[1].as<float>(), (*this)[2].as<float>(), (*this)[3].as<float>() };
}

template<>
inline BTD::Math::FVec3 YAML::Node::as() const
{
	return { (*this)[0].as<float>(), (*this)[1].as<float>(), (*this)[2].as<float>() };
}

template<>
inline BTD::Math::FVec2 YAML::Node::as() const
{
	return { (*this)[0].as<float>(), (*this)[1].as<float>() };
}

template<>
inline BTD::Math::I32Vec2 YAML::Node::as() const
{
	return { (*this)[0].as<int32>(), (*this)[1].as<int32>() };
}

template<>
inline BTD::Math::U32Vec2 YAML::Node::as() const
{
	return { (*this)[0].as<uint32>(), (*this)[1].as<uint32>() };
}

template<>
inline BTD_Math_U32Vec2 YAML::Node::as() const
{
	return { (*this)[0].as<uint32>(), (*this)[1].as<uint32>() };
}

//macro for importing a Value from a YAML data
//#define BTD_IO_YAML_LoadVarValue(outputStruct, outputStructType, YAML_Data, dataPtr, dataType, var) \
//dataPtr = YAML_Data[(#var)].as<dataType>(); \
//memcpy(((uint8*)&(outputStruct)) + offsetof(outputStructType, var), &dataPtr, sizeof(dataType));

//macro for importing a string from a YAML data
//#define BTD_IO_YAML_LoadStringValue(outputStruct, YAML_Data, var) \
//outputStruct.var = YAML_Data[#var].as<std::string>();

//----YAML OPERATOR OVERRIDES EXPORT------------------//

static inline YAML::Emitter& operator<<(YAML::Emitter& emitter, const BTD::Math::Color& data)
{
	emitter << YAML::Flow << YAML::BeginSeq << data.r << data.g << data.b << data.a << YAML::EndSeq; return emitter;
}

static inline YAML::Emitter& operator<<(YAML::Emitter& emitter, const BTD::Math::FVec2& data)
{
	emitter << YAML::Flow << YAML::BeginSeq << data.x << data.y << YAML::EndSeq; return emitter;
}
static inline YAML::Emitter& operator<<(YAML::Emitter& emitter, const BTD::Math::FVec3& data)
{
	emitter << YAML::Flow << YAML::BeginSeq << data.x << data.y << data.z << YAML::EndSeq; return emitter;
}

static inline YAML::Emitter& operator<<(YAML::Emitter& emitter, const BTD::Math::I32Vec2& data)
{
	emitter << YAML::Flow << YAML::BeginSeq << data.x << data.y << YAML::EndSeq; return emitter;
}

static inline YAML::Emitter& operator<<(YAML::Emitter& emitter, const BTD::Math::U32Vec2& data)
{
	emitter << YAML::Flow << YAML::BeginSeq << data.x << data.y << YAML::EndSeq; return emitter;
}

static inline YAML::Emitter& operator<<(YAML::Emitter& emitter, const BTD_Math_U32Vec2& data)
{
	emitter << YAML::Flow << YAML::BeginSeq << data.x << data.y << YAML::EndSeq; return emitter;
}

//static inline YAML::Emitter& operator<<(YAML::Emitter& emitter, const glm::quat& data)
//{
//	emitter << YAML::Flow << YAML::BeginSeq << data.x << data.y << data.z << data.w << YAML::EndSeq; return emitter;
//}

//macro for writing a Value into a emitter
//#define BTD_IO_YAML_WriteVarValue(emitter, value, valueStr) emitter << YAML::Key << valueStr << YAML::Value << value;

//macro for writing a string into a emitter
//#define BTD_IO_YAML_WriteStringValue(emitter, value, valueStr) emitter << YAML::Key << valueStr << YAML::DoubleQuoted << value;