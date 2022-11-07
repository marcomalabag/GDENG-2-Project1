#include "Vector4D.h"

Vector4D::Vector4D()
{
	this->m_x = 0;
	this->m_y = 0;
	this->m_z = 0;
	this->m_w = 0;
}

Vector4D::Vector4D(float x, float y, float z, float w)
{
	this->m_x = x;
	this->m_y = y;
	this->m_z = z;
	this->m_w = w;
}

Vector4D::Vector4D(const Vector4D& vector)
{
	this->m_x = vector.m_x;
	this->m_y = vector.m_y;
	this->m_z = vector.m_z;
	this->m_w = vector.m_w;
}

void Vector4D::cross(Vector4D& v1, Vector4D& v2, Vector4D& v3)
{
	this->m_x = v1.m_y * (v2.m_z * v3.m_w - v3.m_z * v2.m_w) - v1.m_z * (v2.m_y * v3.m_w - v3.m_y * v2.m_w) + v1.m_w * (v2.m_y * v3.m_z - v2.m_z * v3.m_y);
	this->m_y = -(v1.m_x * (v2.m_z * v3.m_w - v3.m_z * v2.m_w) - v1.m_z * (v2.m_x * v3.m_w - v3.m_x * v2.m_w) + v1.m_w * (v2.m_x * v3.m_z - v3.m_x * v2.m_z));
	this->m_z = v1.m_x * (v2.m_y * v3.m_w - v3.m_y * v2.m_w) - v1.m_y * (v2.m_x * v3.m_w - v3.m_x * v2.m_w) + v1.m_w * (v2.m_x * v3.m_y - v3.m_x * v2.m_y);
	this->m_w = -(v1.m_x * (v2.m_y * v3.m_z - v3.m_y * v2.m_z) - v1.m_y * (v2.m_x * v3.m_z - v3.m_x * v2.m_z) + v1.m_z * (v2.m_x * v3.m_y - v3.m_x * v2.m_y));
}

Vector4D::~Vector4D()
{
}
