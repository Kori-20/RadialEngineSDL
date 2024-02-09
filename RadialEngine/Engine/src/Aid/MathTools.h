#pragma once
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Core/Core.h"

class RE_API MathTools
{
public:

    static float SquareRoot(float val);//returns the square root of a float
    //ex: SquareRoot(4.0f) -> 2.0f

    static void ClampIntRef(int& value, const int& min, const int& max);//clamps a value between min and max as an integer, modifies the value
    //ex: ClampIntRef(5, 0, 10) -> 5
    static int ClampInt(int value, const int& min, const int& max);//clamps a value between min and max as an integer, returns the value
    //ex: ClampInt(5, 10, 20) -> 10
    static float ClampFloat(float value, const float& min, const float& max);//clamps a value between min and max as a float
    //ex: ClampFloat(5.0f, 0.0f, 10.0f) -> 5.0f
    static float Clamp01(float value);//clamps a value between 0 and 1
    //ex: Clamp01(1.5f) -> 1.0f

    static void MapClampRangedIntRef(int& value, const int& oldMin, const int& oldMax,
        const int& newMin, const int& newMax);//maps a value from one range to another
    //ex: MapClampRanged(5, 0, 10, 0, 1) -> 0.5f

    static float MapClampRanged(const float& value, const float& oldMin, const float& oldMax,
        const float& newMin, const float& newMax);//maps a value from one range to another
    //ex: MapClampRanged(0.5f, 0.0f, 1.0f, 0.0f, 10.0f) -> 5.0f

    static int Abs(const int value);//returns the absolute value of an integer
    //ex: Abs(-5) -> 5

    static void SwapVectorElement(int* a, int* b);//swaps the values of two integers
    //ex: a = 1, b = 2 -> a = 2, b = 1
    //ex: a = 5, b = 17 -> a = 17, b = 5

    static int GetRandomInRange(int min, int max);//returns a random integer value between min and max
    //ex: GetRandomInRange(0, 10) -> 5

    static int Sign(int value);//returns 1 if value is positive, -1 if value is negative, 0 if value is 0
    //ex: Sign(33) -> 1 
    //ex: Sign(-5) -> -1 

    static float Distance(float x1, float y1, float x2, float y2);//returns the distance between two points
    //ex: Distance(0.0f, 0.0f, 1.0f, 1.0f) -> 1.41421356237f

    static float Lerp(float a, float b, float t);//returns a value between a and b
    //ex: Lerp(0.0f, 1.0f, 0.5f) -> 0.5f

    static float SmoothStep(float edge0, float edge1, float x);//returns a value between 0 and 1
    //ex: SmoothStep(0.0f, 1.0f, 0.5f) -> 0.5f
    
    template <typename T>//returns the minimum value between a and b
    static T Min(T a, T b);
    //ex: Min(1, 2) -> 1

    template <typename T> //returns the minimum value between a and b
    static T Max(T a, T b);
    //ex: Max(1, 2) -> 2

    static int Round(float value);//rounds a float value to the nearest integer 
    //ex: 1.5 -> 2
    //ex: 1.4 -> 1
   
    static float GetRandomFloatInRange(float min, float max);//returns a random float value between min and max 
    //ex: GetRandomFloatInRange(0.0f, 1.0f) -> 0.5f 
    //ex: GetRandomFloatInRange(0.0f, 5.0f) -> 4.3f
    
    static bool GetRandomBool();//returns a random boolean value
    //ex: GetRandomBool() -> true
    
    static void SeedRandom();//generates a new seed for the random number generator
    //ex: SeedRandom() -> 123456789
    //ex: SeedRandom() -> 987654321
};




