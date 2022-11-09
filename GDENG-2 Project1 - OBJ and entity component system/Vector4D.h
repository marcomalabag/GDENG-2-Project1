#pragma once
class Vector4D
{
public:
	Vector4D();
	Vector4D(float x, float y, float z, float w);
	Vector4D(const Vector4D& vector);
	void cross(Vector4D& v1, Vector4D& v2, Vector4D& v3);
	~Vector4D();

public:
	float m_x, m_y, m_z, m_w;
};

