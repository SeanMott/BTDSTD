#pragma once

//defines a camera for rendering mesh data

#include <BTDSTD/Math/RenderMath.hpp>

namespace BTD::Math
{
	//defines a camera type
	enum class CameraProjectionType
	{
		Perspective = 0, //defines a perspective projection
		//defines a orthographic projection

		Count
	};

	//defines a camera
	struct Camera
	{
		//--vars

		bool isDirty = true; //has the camera's data changed

		//the camera transform
		BTD::Math::Transform transform;

		CameraProjectionType projectionType = CameraProjectionType::Perspective; //the projection type

		float FOV = 75.0f; //the FOV
		bool isFOVInRadiansAlready = false; //is the FOV in radians or does it need to be converted
		
		float nearClipping = 0.01f; //the near clipping
		float farClipping = 200.0f; //the far clipping

		bool isBoundToDisplaySize = true; //is the camera bound to update it's projection when the display changes
		BTD::Math::FVec2 aspectSize; //the width and height for the aspect

		//the view and position final matrixs
		glm::mat4 P = glm::mat4(1.0f), //the projection matrix
			V = glm::mat4(1.0f); //the view matrix for positioning

		//--methods

		//calculates the view matrix

		//calculates the perspective projection matrix

		//updates the camera projection and view
		BTD_Compiler_ForceInline void UpdateMatrixData()
		{
			V = glm::lookAt(transform.position.GLM(), (transform.position + transform.CalFrontVector()).GLM(), transform.CalUpVector().GLM());

			P = glm::perspective((isFOVInRadiansAlready == true ? FOV : glm::radians(FOV)),
				aspectSize.x / aspectSize.y, nearClipping, farClipping);
			P[1][1] *= -1;

			isDirty = true;
		}

		//updates the camera projection and view
		BTD_Compiler_ForceInline void UpdateMatrixData(const BTD::Math::FVec2 forcedAspectSize)
		{
			aspectSize = forcedAspectSize;
			UpdateMatrixData();
		}

		//sets the position
		BTD_Compiler_ForceInline void SetPosition(const FVec3& _position)
		{
			transform.SetPosition(_position);
			isDirty = true;
		}

		//sets the rotation
		BTD_Compiler_ForceInline void SetRotation(const BTD::Math::Quat::Quaterion& _rotation)
		{
			transform.SetRotation(_rotation);
			isDirty = true;
		}

		//translates the transform
		BTD_Compiler_ForceInline void Translate(const FVec3& _amount)
		{
			transform.Translate(_amount);
			isDirty = true;
		}
	};
}