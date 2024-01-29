#pragma once

//C API implementation of Time

#include <BTDSTD/CompilerCommands/FunctionModifiers.hpp>

#ifdef Desktop_Build
#include <GLFW\glfw3.h>
#endif

//defines a static struct for storing time
typedef struct BTD_IO_Time
{
	float deltaTime;
	float lastFrame;

	float fixedDeltaTime;
	float accumulator;
	float timeStep;

} BTD_IO_Time;

//cals the delta time
BTD_Compiler_ForceInline void BTD_IO_Time_CalDeltaTime(BTD_IO_Time* time)
{
	time->accumulator += time->deltaTime;

	//if fixed delta has passed
	if (time->accumulator >= time->timeStep)
	{
		time->accumulator -= time->timeStep;
		time->fixedDeltaTime = time->timeStep;
	}

	//if not set it to zero
	else
		time->fixedDeltaTime = 0.0f;
}

//cals the fixed delta time
BTD_Compiler_ForceInline void BTD_IO_Time_CalFixedDeltaTime(BTD_IO_Time* time)
{
#ifdef Desktop_Build
	const register float currentTime = glfwGetTime();
	time->deltaTime = currentTime - time->lastFrame;
	time->lastFrame = currentTime;
#endif
}