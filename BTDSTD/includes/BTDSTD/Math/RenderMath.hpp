#pragma once

//defines various math functions for rendering

#include <BTDSTD/Math/Vector.hpp>

#include <BTDSTD/IO/YAML.hpp>

#include <glm/gtc\matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx\quaternion.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <math.h>

//for how world vectors and axises are defined, check the RenderMathDirections.readme at the root of the BTD STD

//defines mat 4 functions and structs
namespace BTD::Math::Mat
{
	//defines a matatrix functions and structs
	struct Mat4
	{
		float data[16];

		//gets the x position
		//gets the y position
		//gets the z position

		//sets the position in the matrix
		//gets the position from the matrix

		//gets the w rotation
		//gets the x rotation
		//gets the y rotation
		//gets the z rotation

		//sets the rotation in the matrix
		//gets the rotation from the matrix

		//gets the x scale
		//gets the y scale
		//gets the z scale

		//sets the scale in the matrix
		//gets the scale from the matrix
	};

	//returns a identity matrix
	BTD_Compiler_ForceInline Mat4 Mat4Identity()
	{
		Mat4 matrix;
		memset(&matrix, 0, sizeof(float) * 16);
		matrix.data[0] = 1.0f;
		matrix.data[5] = 1.0f;
		matrix.data[10] = 1.0f;
		matrix.data[15] = 1.0f;
		return matrix;
	}

	//tranlates a matrix

	//rotates a matrix

	//scales a matrix

	//calculates a model matrix
	
}

//defines quaterion functions and structs
namespace BTD::Math::Quat
{
	//defines a quaterion
	struct Quaterion
	{
		//the full quaterion
		glm::quat quaterion = { 1.0f, 0.0f, 0.0f, 0.0f }; //the quaterion version of the rotation data
	
		Quaterion() {}
		Quaterion(const float w, const float x, const float y, const float z)
		{
			quaterion.w = w; quaterion.x = x; quaterion.y = y; quaterion.z = z;
		}
		Quaterion(const glm::quat& _quaterion)
		{
			quaterion = _quaterion;
		}
		//Quaterion(const BTD::Math::FVec3 vec)
		//{
		//	quaterion = glm::quat(vec.GLM());
		//}

		//returns a identity quaterion
		static BTD_Compiler_ForceInline Quaterion Identity() { return { 1.0f, 0.0f, 0.0f, 0.0f }; }
	
		//returns the eular angels of this quaterion
		inline FVec3 Eular() { return GLM_FVec3(glm::eulerAngles(quaterion)); }
		//returns the eular angels of this quaterion
		inline FVec3 Eular() const { return GLM_FVec3(glm::eulerAngles(quaterion)); }

		//sets the rotation
		inline void SetRotation(const float x_pitch, const float y_yaw, const float z_roll)
		{
			glm::quat pitch = glm::angleAxis(glm::radians(x_pitch), BTD::Math::FVec3::WorldLeft().GLM());
			glm::quat yaw = glm::angleAxis(glm::radians(y_yaw), BTD::Math::FVec3::WorldUp().GLM());
			glm::quat roll = glm::angleAxis(glm::radians(z_roll), BTD::Math::FVec3::WorldForward().GLM());

			quaterion = pitch * yaw * roll;
			quaterion = glm::normalize(quaterion);
		}

		//rotates on the X axis
		inline void RotateX(const float xRot)
		{
			quaterion = glm::normalize(glm::angleAxis(glm::radians(xRot), BTD::Math::FVec3::WorldLeft().GLM())) * quaterion;
		}

		//rotates on the Y axis
		inline void RotateY(const float yRot)
		{
			quaterion = glm::normalize(glm::angleAxis(glm::radians(yRot), BTD::Math::FVec3::WorldUp().GLM())) * quaterion;
		}

		//rotates on the Z axis
		inline void RotateZ(const float zRot)
		{
			quaterion = glm::normalize(glm::angleAxis(glm::radians(zRot), BTD::Math::FVec3::WorldForward().GLM())) * quaterion;
		}

		//rotates on all 3 axis
		inline void Rotate(const float x_pitch, const float y_yaw, const float z_roll)
		{
			glm::quat pitch = glm::angleAxis(glm::radians(x_pitch), BTD::Math::FVec3::WorldLeft().GLM());
			glm::quat yaw = glm::angleAxis(glm::radians(y_yaw), BTD::Math::FVec3::WorldUp().GLM());
			glm::quat roll = glm::angleAxis(glm::radians(z_roll), BTD::Math::FVec3::WorldForward().GLM());

			quaterion = glm::normalize(pitch * yaw * roll) * quaterion;
		}

		//FVec3 operator+(const FVec2& other)
		//{
		//	return { x + other.x, y + other.y, z };
		//}
		//
		//FVec3 operator+(const FVec3& other)
		//{
		//	return { x + other.x, y + other.y, z + other.z };
		//}
		
		Quaterion operator*(const Quaterion& other) const
		{
			Quaterion q;
			q.quaterion.w = quaterion.w * other.quaterion.w;
			q.quaterion.x = quaterion.x * other.quaterion.x;
			q.quaterion.y = quaterion.y * other.quaterion.y;
			q.quaterion.z = quaterion.z * other.quaterion.z;

			return q;
		}
		Quaterion operator*(const Quaterion& other)
		{
			Quaterion q;
			q.quaterion.w = quaterion.w * other.quaterion.w;
			q.quaterion.x = quaterion.x * other.quaterion.x;
			q.quaterion.y = quaterion.y * other.quaterion.y;
			q.quaterion.z = quaterion.z * other.quaterion.z;

			return q;
		}
		Quaterion operator*(const float other)
		{
			Quaterion q; q.quaterion* other;

			return q;
		}

		//FVec3 operator+=(const FVec3& other)
		//{
		//	return { x += other.x, y += other.y, z += other.z };
		//}
		//FVec3 operator*=(const FVec3& other)
		//{
		//	return { x *= other.x, y *= other.y, z *= other.z };
		//}
		//
		//FVec3 operator+(const float& other)
		//{
		//	return { x + other, y + other, z + other };
		//}
		//
		//FVec3 operator-(const float& other)
		//{
		//	return { x - other, y - other, z - other };
		//}
		//
		//FVec3 operator*(const float& other)
		//{
		//	return { x * other, y * other, z * other };
		//}
		//
		//FVec3 operator*(const float& other) const
		//{
		//	return { x * other, y * other, z * other };
		//}
		//
		//FVec3 operator*=(const float& other)
		//{
		//	return { x *= other, y *= other, z *= other };
		//}
		//
		//FVec3 operator-(const FVec3& other)
		//{
		//	return { x - other.x, y - other.y, z - other.z };
		//}

		Quaterion operator=(const Quaterion& other)
		{
			quaterion = other.quaterion;
			return *this;
		}
	};

	//calculates a look rotation, expects look direction to be normalized
	BTD_Compiler_ForceInline Quaterion LookRotation(const BTD::Math::FVec3& lookDir, const BTD::Math::FVec3 upDir = BTD::Math::FVec3::WorldUp())
	{
		return glm::quatLookAt(lookDir.GLM(), upDir.GLM());
	}
}

//defines math parts
namespace BTD::Math
{
	////defines a 4 by 4 matrix, defaults to a identity matrix
	//struct Mat4
	//{
	//	glm::mat4 data = glm::mat4(1.0f);
	//	/*
	//	[1, 0, 0, 0]
	//	[0, 1, 0, 0]
	//	[0, 0, 1, 0]
	//	[0, 0, 0, 1]
	//	*/

	//	//generates a identify matrix
	//	/*
	//	[1, 0, 0, 0]
	//	[0, 1, 0, 0]
	//	[0, 0, 1, 0]
	//	[0, 0, 0, 1]
	//	*/
	//	BTD_Compiler_ForceInline static Mat4 Identity()
	//	{
	//		Mat4 m;
	//		m.data = glm::mat4(1.0f);
	//		return m;
	//	}

	//	//sets the first row as a vector
	//	//sets the second row as a vector
	//	//sets the third row as a vector
	//	//sets the fourth row as a vector

	//	//sets the first row as a float
	//	//sets the second row as a float
	//	//sets the third row as a float
	//	//sets the fourth row as a float

	//	//gets the first row as a vector
	//	//gets the second row as a vector
	//	//gets the third row as a vector
	//	//gets the fourth row as a vector

	//	//sets the first colum as a vector
	//	//sets the second colum as a vector
	//	//sets the third colum as a vector
	//	//sets the fourth colum as a vector

	//	//sets the first colum as a float
	//	//sets the second colum as a float
	//	//sets the third colum as a float
	//	//sets the fourth colum as a float

	//	//gets the first colum as a vector
	//	//gets the second colum as a vector
	//	//gets the third colum as a vector
	//	//gets the fourth colum as a vector
	//};

	////defines a eular rotation vector

	////defines a quaterion rotation matrix
	////stores the values x, y, z, w
	//struct Quaterion
	//{
	//	float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;

	//	Quaterion() {}

	//	//takes a vector 3

	//	//takes a vector 4

	//	//takes a quaterion
	//
	//	//converts the quaterion into a mat4

	//	//converts the quaterion into a mat3

	//	//converts the quaterion into a vector 4 representing the eular values

	//	//converts the quaterion to a GLM
	//	BTD_Compiler_ForceInline glm::quat GLM()
	//	{
	//		return glm::quat(w, x, y, z);
	//	}

	//	//converts a GLM quaterion to a BTD quaterion
	//	BTD_Compiler_ForceInline Quaterion BTD(const glm::quat& quat)
	//	{
	//		x = quat.x; y = quat.y; z = quat.z; w = quat.w;
	//		return *this;
	//	}

	//	//normalizes the quaterion

	//	//multiplies a quaterion by a vec4, converts the vec4 into a quaterion before multiplaying
	//};

	//defines a transform
	//abides by the BTD defined world axis directions, see the RenderMath.readme for details
	//not directly change the internal values, use setters for it, as they update the other vectors and matrix automatically
	//you can opt out of updating them, based on the set function used
	struct Transform
	{
		//the pos, rot, scale
		BTD::Math::FVec3 position = BTD::Math::FVec3::Zero(),
			//rotation = BTD::Math::FVec3::Zero(),
			scale = BTD::Math::FVec3::One();

		//the full model matrix
		Quat::Quaterion rotation = Quat::Quaterion::Identity(); //rotation matrix
		glm::mat4 modelMatrix = glm::mat4(1.0f);

		bool isDirty = true; //has the transform been changed

		~Transform() {}

		//------WORLD BASED DIRECTIONS, IGNORES ROTATION----------//

		//calculates the World front direction vector
		BTD_Compiler_ForceInline FVec3 CalWorldFrontVector()
		{
			return position + FVec3::WorldForward();
		}

		//calculates the back World direction vector
		BTD_Compiler_ForceInline FVec3 CalWorldBackVector()
		{
			return position + FVec3::WorldBackward();
		}

		//calculates the left World direction vector
		BTD_Compiler_ForceInline FVec3 CalWorldLeftVector()
		{
			return position + FVec3::WorldLeft();
		}

		//calculates the right World direction vector
		BTD_Compiler_ForceInline FVec3 CalWorldRightVector()
		{
			return position + FVec3::WorldRight();
		}

		//calculates the up World direction vector
		BTD_Compiler_ForceInline FVec3 CalWorldUpVector()
		{
			return position + FVec3::WorldUp();
		}

		//calculates the down World direction vector
		BTD_Compiler_ForceInline FVec3 CalWorldDownVector()
		{
			return position + FVec3::WorldDown();
		}

		//------LOCAL BASED DIRECTIONS, USES ROTATION----------//

		//calculates the front direction vector
		BTD_Compiler_ForceInline FVec3 CalFrontVector()
		{
			return GLM_FVec3(glm::rotate(rotation.quaterion, FVec3::WorldForward().GLM()));// .Normalize();
			//glm::angleAxis(glm::radians(-Pitch), glm::vec3(1, 0, 0));
		}

		//calculates the back direction vector
		BTD_Compiler_ForceInline FVec3 CalBackVector()
		{
			return GLM_FVec3(glm::rotate(rotation.quaterion, FVec3::WorldBackward().GLM()));// .Normalize();
		}

		//calculates the left direction vector
		BTD_Compiler_ForceInline FVec3 CalLeftVector()
		{
			return GLM_FVec3(glm::rotate(rotation.quaterion, FVec3::WorldLeft().GLM()));
		}

		//calculates the right direction vector
		BTD_Compiler_ForceInline FVec3 CalRightVector()
		{
			return GLM_FVec3(glm::rotate(rotation.quaterion, FVec3::WorldRight().GLM()));
		}

		//calculates the up direction vector
		BTD_Compiler_ForceInline FVec3 CalUpVector()
		{
			return GLM_FVec3(glm::rotate(rotation.quaterion, FVec3::WorldUp().GLM()));
		}

		//calculates the down direction vector
		BTD_Compiler_ForceInline FVec3 CalDownVector()
		{
			return GLM_FVec3(glm::rotate(rotation.quaterion, FVec3::WorldDown().GLM()));
		}

		//-----SETS/MODIFIES THE POSITION, ROTATION, AND SCALE-------------//

		//sets the position
		BTD_Compiler_ForceInline void SetPosition(const FVec3& _position)
		{
			position = _position;
			isDirty = true;
		}

		//translates the transform
		BTD_Compiler_ForceInline void Translate(const FVec3& _amount)
		{
			position += _amount;
			isDirty = true;
		}

		//sets the rotation
		BTD_Compiler_ForceInline void SetRotation(const Quat::Quaterion& rot)
		{
			rotation = rot;
			isDirty = true;
		}

		//sets the scale
		BTD_Compiler_ForceInline void SetScale(const FVec3& _scale)
		{
			scale = _scale;
			isDirty = true;
		}

		//scales the transform
		BTD_Compiler_ForceInline void ScaleAllAxis(const FVec3& _amount)
		{
			scale += _amount;
			isDirty = true;
		}

		//-------MODEL MATRIX CAL------//

		//calculate the full model matrix || ignores the dirty flag, will not clear it either
		BTD_Compiler_ForceInline glm::mat4 CalculateModelMatrix_Force()
		{
			glm::vec3 rot = rotation.Eular().GLM();
			const register float c3 = glm::cos(rot.z);
			const register float s3 = glm::sin(rot.z);
			const register float c2 = glm::cos(rot.x);
			const register float s2 = glm::sin(rot.x);
			const register float c1 = glm::cos(rot.y);
			const register float s1 = glm::sin(rot.y);

			modelMatrix = {
				{
					scale.x * (c1 * c3 + s1 * s2 * s3),
					scale.x * (c2 * s3),
					scale.x * (c1 * s2 * s3 - c3 * s1),
					0.0f,
				},
				{
					scale.y * (c3 * s1 * s2 - c1 * s3),
					scale.y * (c2 * c3),
					scale.y * (c1 * c3 * s2 + s1 * s3),
					0.0f,
				},
				{
					scale.z * (c2 * s1),
					scale.z * (-s2),
					scale.z * (c1 * c2),
					0.0f,
				},
				{position.x, position.y, position.z, 1.0f}
			};

			return modelMatrix;
		}

		//calculate the full model matrix, will return the matrix if the dirty flag is false
		BTD_Compiler_ForceInline glm::mat4 CalculateModelMatrix()
		{
			//if data hasen't been changed, return the pre-exsisting model matrix
			if (!isDirty)
				return modelMatrix;

			isDirty = false; //resets the flag

			//recalculate the model matrix
			return CalculateModelMatrix_Force();
		}
	};

	//converts the Transform into YAML data made of three vectors
	inline void Transform_ConvertToYAML(YAML::Emitter& emitter, Transform* component)
	{
		emitter << YAML::Key << "TransformComp" << YAML::Value << YAML::BeginMap;

		emitter << YAML::Key << "position" << YAML::Value << component->position;
		//emitter << YAML::Key << "rotation" << YAML::Value << component->rotation;
		emitter << YAML::Key << "scale" << YAML::Value << component->scale;

		emitter << YAML::EndMap;
	}

	//converts the YAML into the Transform
	inline void Transform_ConvertFromYAML(Transform* component, YAML::Node& data)
	{
		auto comp = data["TransformComp"];
		if (comp)
		{
			component->position = comp["position"].as<BTD::Math::FVec3>();
			//component->rotation = comp["rotation"].as<BTD::Math::FVec3>();
			component->scale = comp["scale"].as<BTD::Math::FVec3>();
		}
	}
}