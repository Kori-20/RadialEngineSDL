#pragma once
#include <cmath>
#include "ECS/Component.h"

#define PI 3.14159265f
#define DEG_TO_RAD PI / 180.0f

struct Vector2D {
public:
	float x = 0;
	float y = 0;

	Vector2D() : x{ 0.f }, y{ 0.f } {};
	Vector2D(float xVal, float yVal) : x(xVal), y(yVal) {}

	static Vector2D One() { return Vector2D(1, 1); }
	static Vector2D Zero() { return Vector2D(0, 0); }
	static Vector2D Up() { return Vector2D(0, -1); }
	static Vector2D Right() { return Vector2D(1, 0); }
	static Vector2D Down() { return Vector2D(0, 1); }
	static Vector2D Left() { return Vector2D(-1, 0); }

	inline Vector2D& Add(const Vector2D& vector) {
		x += vector.x;
		y += vector.y;
		return *this;
	}

	inline Vector2D& Subtract(const Vector2D& vector) {
		x -= vector.x;
		y -= vector.y;
		return *this;
	}

	inline Vector2D& Multiply(const Vector2D& vector) {
		x *= vector.x;
		y *= vector.y;
		return *this;
	}

	inline Vector2D& MultiplyFloat(float val) {
		x *= val;
		y *= val;
		return *this;
	}

	inline Vector2D& Divide(const Vector2D& vector) {
		if (vector.x != 0 && vector.y != 0) {
			x /= vector.x;
			y /= vector.y;
		}
		return *this;
	}

	inline Vector2D& Normalize() {
		if (x != 0 || y != 0) {
			float magnitude = std::sqrt(x * x + y * y);
			x /= magnitude;
			y /= magnitude;
		}
		return *this;
	}

	inline float Distance(const Vector2D& v1, const Vector2D& v2) {
		float x = v2.x - v1.x;
		float y = v2.y - v1.y;
		return std::sqrt(x * x + y * y);
	}

	friend Vector2D operator+(Vector2D v1, const Vector2D& v2) { return v1.Add(v2); }
	friend Vector2D operator-(Vector2D v1, const Vector2D& v2) { return v1.Subtract(v2); }
	friend Vector2D operator*(Vector2D v1, const Vector2D& v2) { return v1.Multiply(v2); }
	friend Vector2D operator/(Vector2D v1, const Vector2D& v2) { return v1.Divide(v2); }

	friend Vector2D operator*(Vector2D v1, const float value) { return v1.MultiplyFloat(value); }
	Vector2D& operator*=(const float value) { return this->MultiplyFloat(value); }

	Vector2D& operator+=(const Vector2D& v2) { return this->Add(v2); }
	Vector2D& operator-=(const Vector2D& v2) { return this->Subtract(v2); }
	Vector2D& operator*=(const Vector2D& v2) { return this->Multiply(v2); }
	Vector2D& operator/=(const Vector2D& v2) { return this->Divide(v2); }

	friend bool operator < (Vector2D v1, Vector2D v2) {
		return v1.x < v2.x && v1.y < v2.y;
	}

	friend bool operator > (Vector2D v1, Vector2D v2) {
		return v1.x > v2.x && v1.y > v2.y;
	}

	friend bool operator!= (Vector2D v1, Vector2D v2) {
		return v1.x != v2.x || v1.y != v2.y;
	}
	friend bool operator== (Vector2D v1, Vector2D v2) {
		return v1.x == v2.x && v1.y == v2.y;
	}

	Vector2D RotateVector(Vector2D& vector, float angle) 
	{
		float radAngle = (float)(angle*DEG_TO_RAD);
		return Vector2D((float)(vector.x * cos(radAngle) - vector.y * sin(radAngle)), 
						(float)(vector.x * sin(radAngle) + vector.y * cos(radAngle)));
	}
};

class Transform : public Component
{
protected:
	Vector2D t_Position = Vector2D::One();
	Vector2D t_Scale = Vector2D::One();

public:
	Transform() = default;
	Transform(float x, float y, float xS, float yS) : t_Position(x, y), t_Scale(xS, yS) {}
	Transform(Vector2D position, Vector2D scale) : t_Position(position), t_Scale(scale) {}

	inline Vector2D& GetPosition() { return t_Position; }
	inline void SetPosition(const Vector2D& newPosition) { t_Position = newPosition; }
	inline void SetPosition(const float xPos, const float yPos) { t_Position.x = xPos; t_Position.y = yPos; }
	inline void Translate(const Vector2D& posAdd) { t_Position += posAdd; }
	inline void Translate(const float xPos, const float yPos) { t_Position += Vector2D(xPos, yPos); }

	inline Vector2D& GetScale() { return t_Scale; }
	inline void SetScale(const Vector2D& newScale) { t_Scale = newScale; }
	inline void SetScale(float xScale, float yScale) { t_Scale = Vector2D(xScale, yScale); }

	// Placeholder for actual WorldToLocal implementation
	static Transform& WorldToLocal(Transform Local, Transform Base) { return Local; }

	int banana;
};











