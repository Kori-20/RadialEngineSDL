#include "MathTools.h"

float MathTools::SquareRoot(float val)
{
    return std::sqrt(val);
}

void MathTools::ClampIntRef(int& value, const int& min, const int& max)
{
    if (value < min)
    {
        value = min;
    }
    if (value > max)
    {
        value = max;
    }
}

int MathTools::ClampInt(int value, const int& min, const int& max)
{
    if (value < min)
    {
        value = min;
    }
    if (value > max)
    {
        value = max;
    }
    return value;
}

float MathTools::ClampFloat(float value, const float& min, const float& max)
{
    if (value < min)
    {
        value = min;
    }
    if (value > max)
    {
        value = max;
    }
    return value;
}

float MathTools::Clamp01(float value)
{
    if (value < 0)
    {
        return 0;
    }
    if (value > 1)
    {
        return 1;
    }
    return value;
}

void MathTools::MapClampRangedIntRef(int& value, const int& oldMin, const int& oldMax, const int& newMin, const int& newMax)
{
    float oldRange = (oldMax - oldMin);
    float NewRange = (newMax - newMin);
    value = static_cast<int>(((value - oldMin) * NewRange) / oldRange) + newMin;
}

float MathTools::MapClampRanged(const float& value, const float& oldMin, const float& oldMax, const float& newMin, const float& newMax)
{
    float oldRange = (oldMax - oldMin);
    float NewRange = (newMax - newMin);
    return ((value - oldMin) * NewRange) / oldRange + newMin;
}

int MathTools::Abs(const int value)
{
    int inverse = -value;
    return value > inverse ? value : inverse;
}

void MathTools::SwapVectorElement(int* a, int* b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

int MathTools::GetRandomInRange(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int MathTools::Sign(int value)
{
    return (value > 0) - (value < 0);
}

float MathTools::Distance(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return SquareRoot(dx * dx + dy * dy);
}

float MathTools::Lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

float MathTools::SmoothStep(float edge0, float edge1, float x)
{
    // Scale, and clamp x to 0..1 range
    x = Clamp01((x - edge0) / (edge1 - edge0));
    // Evaluate polynomial
    return x * x * (3 - 2 * x);
}

template <typename T>
T MathTools::Min(T a, T b)
{
    return a < b ? a : b;
}

template <typename T>
T MathTools::Max(T a, T b)
{
    return a > b ? a : b;
}

int MathTools::Round(float value)
{
    return static_cast<int>(std::round(value));
}

float MathTools::GetRandomFloatInRange(float min, float max)
{
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
}

bool MathTools::GetRandomBool()
{
    return rand() % 2 == 0;
}

void MathTools::SeedRandom()
{
    srand(static_cast<unsigned int>(time(nullptr)));
}
