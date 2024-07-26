
#ifndef COMMONMATH_H
#include "CommonStruct.h"
#pragma once

float ClampF(float input, float max, float min);

float ReMapF(float input, float inputMax, float inputMin, float newMax, float newMin);

FloatVector2 CalculateVertexFromRadian(float radian, float radius, float x, float y);

float ClampedRandomF(float low, float high);

float DotProduct(FloatVector2 one, FloatVector2 two);
float DotProduct(FloatVector3 one, FloatVector3 two);

FloatVector3 CrossProduct(FloatVector3 one, FloatVector3 two);
float VectorMagnitudeSqred(FloatVector3 vector);
float VectorMagnitude(FloatVector2 vector);
float VectorMagnitude(FloatVector3 vector);
FloatVector2 AddVectors(FloatVector2 one, FloatVector2 two);
FloatVector3 AddVectors(FloatVector3 one, FloatVector3 two);
FloatVector3 VectorDiff(FloatVector3 one, FloatVector3 two);
FloatVector3 DivideVector(FloatVector3 vector, float denomonator);
FloatVector3 InvertVector(FloatVector3 vector);
FloatVector3 MultiplyVector(FloatVector3 one, FloatVector3 two);
FloatVector3 MultiplyVector(FloatVector3 vector, float multiplier);
#endif // !COMMONMATH_H



