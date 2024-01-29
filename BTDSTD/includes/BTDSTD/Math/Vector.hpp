#pragma once

//defines various vectors and other algos

//for how world vectors and axises are defined, check the RenderMathDirections.readme at the root of the BTD STD

#include <BTDSTD/CompilerCommands/FunctionModifiers.hpp>

#include <BTDSTD_C/Math/Math.h>

#include <glm/glm.hpp> //<glm/glm.hpp>

namespace BTD::Math
{
	//forward decl the vectors

	struct I32Vec2;
	struct U32Vec2;
	struct I64Vec2;
	struct U64Vec2;
	struct FVec2;
	struct DVec2;

	struct I32Vec3;
	struct U32Vec3;
	struct I64Vec3;
	struct U64Vec3;
	struct FVec3;
	struct DVec3;

	struct I32Vec4;
	struct U32Vec4;
	struct I64Vec4;
	struct U64Vec4;
	struct FVec4;
	struct DVec4;

	//defines a int32 vec 2
	struct I32Vec2
	{
		int32 x = 0, y = 0;

		I32Vec2() {}
		I32Vec2(const int32& _x, const int32& _y)
			:x(_x), y(_y) {}

		//converts to another type
		template<typename T>
		BTD_Compiler_ForceInline T To()
		{
			return T(x, y);
		}

		//converts to another type
		template<typename T>
		BTD_Compiler_ForceInline T To() const
		{
			return T(x, y);
		}

		bool operator==(const I32Vec2& other)
		{
			return (x == other.x && y == other.y);
		}
	};

	//defines a uint32 vec 2
	struct U32Vec2
	{
		uint32 x = 0, y = 0;

		U32Vec2() {}
		U32Vec2(const uint32& _x, const uint32& _y)
			:x(_x), y(_y) {}

		//converts to another type
		template<typename T>
		BTD_Compiler_ForceInline T To()
		{
			return T(x, y);
		}

		//converts to another type
		template<typename T>
		BTD_Compiler_ForceInline T To() const
		{
			return T(x, y);
		}

		bool operator==(const U32Vec2& other)
		{
			return (x == other.x && y == other.y);
		}
	};

	//defines a float vec 2
	struct FVec2
	{
		float x = 0.0f, y = 0.0f;

		FVec2() {}
		FVec2(const float& _x, const float& _y)
			:x(_x), y(_y) {}
		FVec2(float& _x, float& _y)
			:x(_x), y(_y) {}

		//converts to another type
		template<typename T>
		BTD_Compiler_ForceInline T To()
		{
			return T(x, y);
		}

		//converts to another type
		template<typename T>
		BTD_Compiler_ForceInline T To() const
		{
			return T(x, y);
		}

		bool operator==(const FVec2& other)
		{
			return (x == other.x && y == other.y);
		}
	};

	//defines a float vec 3
	struct FVec3
	{
		float x = 0.0f, y = 0.0f, z = 0.0f;

		//constrctor
		FVec3() {}

		//constructs a vector 3 from three floats
		FVec3(const float& _x, const float& _y, const float& _z)
			:x(_x), y(_y), z(_z) {}

		//calculates the length
		BTD_Compiler_ForceInline float Length() { return BTD_Math_QFastInverseSqrt((x * x) + (y * y) + (z * z));  }

		//converts to another type
		template<typename T>
		BTD_Compiler_ForceInline T To()
		{
			return T(x, y, z);
		}

		//converts to another type
		template<typename T>
		BTD_Compiler_ForceInline T To() const
		{
			return T(x, y, z);
		}

		//type pun casts the vector to GLM format
		BTD_Compiler_ForceInline glm::vec3 GLM()
		{
			return glm::vec3(x, y, z);// Smok_Util_Typepun((*this), glm::vec3);
		}

		//type pun casts the vector to GLM format
		BTD_Compiler_ForceInline glm::vec3 GLM() const
		{
			return glm::vec3(x, y, z);// return Smok_Util_Typepun((*this), glm::vec3);
		}

		//converts the GLM type to a BTD type
		BTD_Compiler_ForceInline FVec3 BTD(const glm::vec3& _glm)
		{
			x = _glm.x; y = _glm.y; z = _glm.z;
			return *this;
		}

		//normalizes the vector
		BTD_Compiler_ForceInline FVec3 Normalize()
		{
			const register float length = Length(); //gets the magnitute/length of this vector

			//if it's zero, return the vector as is
			if (!length)
				return *this;

			//if it is not zero, devide each component by the length
			else
				return { x / length, y / length, z / length };
		}

		//returns a zero vector (0, 0, 0)
		static BTD_Compiler_ForceInline FVec3 Zero() { return { 0.0f, 0.0f, 0.0f }; }
		//returns a one vector (1, 1, 1)
		static BTD_Compiler_ForceInline FVec3 One() { return { 1.0f, 1.0f, 1.0f }; }

		//returns the world forward vector (0, 0, -1)
		static BTD_Compiler_ForceInline FVec3 WorldForward() { return { 0.0f, 0.0f, -1.0f }; }
		//returns the world backward vector (0, 0, 1)
		static BTD_Compiler_ForceInline FVec3 WorldBackward() { return { 0.0f, 0.0f, 1.0f }; }

		//returns the world up vector (0, 1, 0)
		static BTD_Compiler_ForceInline FVec3 WorldUp() { return { 0.0f, 1.0f, 0.0f }; }
		//returns the world down vector (0, -1, 0)
		static BTD_Compiler_ForceInline FVec3 WorldDown() { return { 0.0f, -1.0f, 0.0f }; }

		//returns the world left vector (1, 0, 0)
		static BTD_Compiler_ForceInline FVec3 WorldLeft() { return { 1.0f, 0.0f, 0.0f }; }
		//returns the world right vector (-1, 0, 0)
		static BTD_Compiler_ForceInline FVec3 WorldRight() { return { -1.0f, 0.0f, 0.0f }; }

		FVec3 operator+(const FVec2& other)
		{
			return { x + other.x, y + other.y, z };
		}

		FVec3 operator+(const FVec3& other)
		{
			return { x + other.x, y + other.y, z + other.z };
		}

		FVec3 operator*(const FVec3& other)
		{
			return { x * other.x, y * other.y, z * other.z };
		}

		FVec3 operator+=(const FVec3& other)
		{
			return { x += other.x, y += other.y, z += other.z };
		}
		FVec3 operator*=(const FVec3& other)
		{
			return { x *= other.x, y *= other.y, z *= other.z };
		}

		FVec3 operator+(const float& other)
		{
			return { x + other, y + other, z + other };
		}

		FVec3 operator-(const float& other)
		{
			return { x - other, y - other, z - other };
		}

		FVec3 operator*(const float& other)
		{
			return { x * other, y * other, z * other };
		}

		FVec3 operator*(const float& other) const
		{
			return { x * other, y * other, z * other };
		}

		FVec3 operator*=(const float& other)
		{
			return { x *= other, y *= other, z *= other };
		}

		FVec3 operator-(const FVec3& other)
		{
			return { x - other.x, y - other.y, z - other.z };
		}

		bool operator==(const FVec3& other)
		{
			return (x == other.x && y == other.y && z == other.z);
		}

		bool operator!=(const FVec3& other)
		{
			return (x != other.x || y != other.y || z != other.z);
		}
	};

	//defines a double vec 2
	struct DVec2
	{
		double x = 0.0f, y = 0.0f;

		DVec2() {}
		DVec2(const double& _x, const double& _y)
			:x(_x), y(_y) {}

		//converts to another type
		template<typename T>
		BTD_Compiler_ForceInline T To()
		{
			return T(x, y);
		}

		//converts to another type
		template<typename T>
		BTD_Compiler_ForceInline T To() const
		{
			return T(x, y);
		}

		bool operator==(const DVec2& other)
		{
			return (x == other.x && y == other.y);
		}
	};

	//defines a double vec 3
	struct DVec3
	{
		double x = 0.0f, y = 0.0f, z = 0.0f;

		DVec3() {}
		DVec3(const double& _x, const double& _y, const double& _z)
			:x(_x), y(_y), z(_z) {}

		//converts to another type
		template<typename T>
		BTD_Compiler_ForceInline T To()
		{
			return T(x, y, z);
		}

		//converts to another type
		template<typename T>
		BTD_Compiler_ForceInline T To() const
		{
			return T(x, y, z);
		}

		//returns a zero vector
		static BTD_Compiler_ForceInline DVec3 Zero() { return { 0.0f, 0.0f, 0.0f }; }
		//returns a one vector
		static BTD_Compiler_ForceInline DVec3 One() { return { 1.0f, 1.0f, 1.0f }; }

		bool operator==(const DVec3& other)
		{
			return (x == other.x && y == other.y && z == other.z);
		}
	};

	//defines a color
	struct Color
	{
		float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;

		//returns glm
		BTD_Compiler_ForceInline glm::vec4 GLM() const { return { r, g, b, a }; }

		//converts to a 4 element array
		BTD_Compiler_ForceInline void ToArray(float* buffer) { buffer[0] = r; buffer[1] = g; buffer[2] = b; buffer[3] = a; }

		//returns Red color
		static BTD_Compiler_ForceInline Color Red() { return { 1.0f, 0.0f, 0.0f, 1.0f }; }
		//returns Yellow color
		static BTD_Compiler_ForceInline Color Yellow() { return { 255.0f, 255.0f, 0.0f, 1.0f }; }
		//returns Green color
		static BTD_Compiler_ForceInline Color Green() { return { 0.0f, 1.0f, 0.0f, 1.0f }; }
		//returns Blue color
		static BTD_Compiler_ForceInline Color Blue() { return { 0.0f, 0.0f, 1.0f, 1.0f }; }

		//returns a Black color
		static BTD_Compiler_ForceInline Color Black() { return { 0.0f, 0.0f, 0.0f, 1.0f }; }
		//returns a White color
		static BTD_Compiler_ForceInline Color White() { return { 1.0f, 1.0f, 1.0f, 1.0f }; }

		//returns a Pink color
		//static inline Color Pink() { return { 255.0f, 20.0f, 147.0f, 1.0f }; }

	};

	//-----------------------CONVERTS GLM TYPES TO BTD TYPES-----------------------------//

	//quickly converts a GLM vec3 into a FVec3 via type punning
	inline FVec3 GLM_FVec3(const glm::vec3& vec3)
	{
		return Smok_Util_Typepun((vec3), FVec3);
	}
}