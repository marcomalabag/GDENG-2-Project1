#pragma once
class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D& vector);
	Vector2D operator* (float num);
	Vector2D operator+ (Vector2D vec);
	Vector2D operator- (Vector2D vec);
	Vector2D operator/ (Vector2D vec);
	float getX();
	float getY();
	~Vector2D();

private:
	float x, y;
};

