#include "Matrix4x4.h"

Matrix4x4::Matrix4x4()
{
}

void Matrix4x4::setIdentity()
{
	::memset(Matrix, 0, sizeof(float) * 16);
	Matrix[0][0] = 1;
	Matrix[1][1] = 1;
	Matrix[2][2] = 1;
	Matrix[3][3] = 1;
}

void Matrix4x4::setTranslation(const Vector3D& translation)
{
	setIdentity();
	Matrix[3][0] = translation.x;
	Matrix[3][1] = translation.y;
	Matrix[3][2] = translation.z;
}

void Matrix4x4::setScale(const Vector3D& scale)
{
	setIdentity();
	Matrix[0][0] = scale.x;
	Matrix[1][1] = scale.y;
	Matrix[2][2] = scale.z;
}

void Matrix4x4::operator*=(const Matrix4x4& matrix)
{
	Matrix4x4 out;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			out.Matrix[i][j] =
				Matrix[i][0] * matrix.Matrix[0][j] + Matrix[i][1] * matrix.Matrix[1][j] +
				Matrix[i][2] * matrix.Matrix[2][j] + Matrix[i][3] * matrix.Matrix[3][j];
		}
	}
	setMatrix(out);
}

void Matrix4x4::setMatrix(const Matrix4x4& matrix)
{
	::memcpy(Matrix, matrix.Matrix, sizeof(float) * 16);
}

void Matrix4x4::setOrthoLH(float width, float height, float near_plane, float far_plane)
{
	setIdentity();
	Matrix[0][0] = 2.0f / width;
	Matrix[1][1] = 2.0f / height;
	Matrix[2][2] = 1.0f / (far_plane - near_plane);
	Matrix[3][2] = -(near_plane / (far_plane - near_plane));
}

Matrix4x4::~Matrix4x4()
{
}
