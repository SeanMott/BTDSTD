#pragma once

//C API implementation of math

#include <BTDSTD_C/Types.h>

#include <BTDSTD_C/CompilerCommands/FunctionModifiers.h>

//Quake Inverse Square Root Algo
inline float BTD_Math_QFastInverseSqrt(const float number)
{
	float x2, y;
	long i;

	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (1.5F - (x2 * y * y));

	return y;
}

//Quake Inverse Square Root Algo || also performs the second iteractions
inline float BTD_Math_QFastInverseSqrt_DoubleInteraction(const float number)
{
	float x2, y;
	long i;

	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (1.5F - (x2 * y * y));
	y = y * (1.5F - (x2 * y * y));

	return y;
}

//normalizes the vector || uses only one iteration of the Fast Quake Invertion SQRT
inline float BTD_Math_Normalize_Fvec3(const float x, const float y, const float z)
{
	return BTD_Math_QFastInverseSqrt((x * x) + (y * y) + (z * z));
}

//clamps a float between a max and min

//clamps a uint32 between a max and min
inline uint32 BTD_Math_ClampUint32(const uint32 value, const uint32 min, const uint32 max)
{
	if (value < min)
		return min;

	else if (value > max)
		return max;

	return value;
}