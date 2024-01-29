#pragma once

//C API implementation of vectors

#include <BTDSTD_C/Math/Math.h>

#include <string.h>

//defines a int32 vec 2
typedef struct BTD_Math_I32Vec2
{
	int32 x, y;

} BTD_Math_I32Vec2;

//defines a uint32 vec 2
typedef struct BTD_Math_U32Vec2
{
	uint32 x, y;

} BTD_Math_U32Vec2;

//defines a color
typedef struct BTD_Math_Color
{
	float r, g, b, a;

} BTD_Math_Color;

////converts to a 4 element array
//BTD_Compiler_ForceInline void BTD_Math_Color_ToArray(BTD_Math_Color* color, float* buffer)
//{
//	buffer = (float*)memcpy(buffer, color, sizeof(BTD_Math_Color));
//}

//sets the color
BTD_Compiler_ForceInline void BTD_Math_Color_SetColor(BTD_Math_Color* color, BTD_Math_Color* colorToSet)
{
	color = (BTD_Math_Color*)memcpy(color, colorToSet, sizeof(BTD_Math_Color));
}

//returns Red color
static BTD_Compiler_ForceInline BTD_Math_Color BTD_Math_Color_Red()
{
	BTD_Math_Color color = { 1.0f, 0.0f, 0.0f, 1.0f };
	return color;
}

//returns Yellow color
static BTD_Compiler_ForceInline BTD_Math_Color BTD_Math_Color_Yellow()
{
	BTD_Math_Color color = { 255.0f, 255.0f, 0.0f, 1.0f };
	return color;
}

//returns Green color
static BTD_Compiler_ForceInline BTD_Math_Color BTD_Math_Color_Green()
{
	BTD_Math_Color color = { 0.0f, 1.0f, 0.0f, 1.0f };
	return color;
}

//returns Blue color
static BTD_Compiler_ForceInline BTD_Math_Color BTD_Math_Color_Blue()
{ 
	BTD_Math_Color color = { 0.0f, 0.0f, 1.0f, 1.0f };
	return color;
}

//returns a Black color
static BTD_Compiler_ForceInline BTD_Math_Color BTD_Math_Color_Black() 
{ 
	BTD_Math_Color color = { 0.0f, 0.0f, 0.0f, 1.0f };
	return color;
}

//returns a White color
static BTD_Compiler_ForceInline BTD_Math_Color BTD_Math_Color_White()
{
	BTD_Math_Color color = { 1.0f, 1.0f, 1.0f, 1.0f };
	return color;
}