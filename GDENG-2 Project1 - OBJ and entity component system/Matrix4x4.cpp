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
	
	Matrix[3][0] = translation.x;
	Matrix[3][1] = translation.y;
	Matrix[3][2] = translation.z;
}

void Matrix4x4::setScale(const Vector3D& scale)
{
	
	Matrix[0][0] = scale.x;
	Matrix[1][1] = scale.y;
	Matrix[2][2] = scale.z;
}

void Matrix4x4::setRotationX(float x)
{
	Matrix[1][1] = cos(x);
	Matrix[1][2] = sin(x);
	Matrix[2][1] = -sin(x);
	Matrix[2][2] = cos(x);
}

void Matrix4x4::setRotationY(float y)
{
	Matrix[0][0] = cos(y);
	Matrix[0][2] = -sin(y);
	Matrix[2][0] = sin(y);
	Matrix[2][2] = cos(y);
}

void Matrix4x4::setRotationZ(float z)
{
	Matrix[0][0] = cos(z);
	Matrix[0][1] = sin(z);
	Matrix[1][0] = -sin(z);
	Matrix[1][1] = cos(z);
}

float Matrix4x4::getDeterminant()
{
	Vector4D minor, v1, v2, v3;
	float det;

	v1 = Vector4D(this->Matrix[0][0], this->Matrix[1][0], this->Matrix[2][0], this->Matrix[3][0]);
	v2 = Vector4D(this->Matrix[0][1], this->Matrix[1][1], this->Matrix[2][1], this->Matrix[3][1]);
	v3 = Vector4D(this->Matrix[0][2], this->Matrix[1][2], this->Matrix[2][2], this->Matrix[3][2]);


	minor.cross(v1, v2, v3);
	det = -(this->Matrix[0][3] * minor.m_x + this->Matrix[1][3] * minor.m_y + this->Matrix[2][3] * minor.m_z +
		this->Matrix[3][3] * minor.m_w);
	return det;
}

void Matrix4x4::getInverse()
{
	int a, i, j;
	Matrix4x4 out;
	Vector4D v, vec[3];
	float det = 0.0f;

	det = this->getDeterminant();
	if (!det) return;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (j != i)
			{
				a = j;
				if (j > i) a = a - 1;
				vec[a].m_x = (this->Matrix[j][0]);
				vec[a].m_y = (this->Matrix[j][1]);
				vec[a].m_z = (this->Matrix[j][2]);
				vec[a].m_w = (this->Matrix[j][3]);
			}
		}
		v.cross(vec[0], vec[1], vec[2]);

		out.Matrix[0][i] = pow(-1.0f, i) * v.m_x / det;
		out.Matrix[1][i] = pow(-1.0f, i) * v.m_y / det;
		out.Matrix[2][i] = pow(-1.0f, i) * v.m_z / det;
		out.Matrix[3][i] = pow(-1.0f, i) * v.m_w / det;
	}

	this->setMatrix(out);
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

void Matrix4x4::setMatrix(float matrix[4][4])
{
	::memcpy(Matrix, matrix, sizeof(float) * 16);
}


Vector3D Matrix4x4::getXDirection()
{
	return Vector3D(Matrix[0][0], Matrix[0][1], Matrix[0][2]);
}

Vector3D Matrix4x4::getZDirection()
{
	return Vector3D(Matrix[2][0], Matrix[2][1], Matrix[2][2]);
}

Vector3D Matrix4x4::getTranslation()
{
	return Vector3D(Matrix[3][0], Matrix[3][1], Matrix[3][2]);
}

void Matrix4x4::setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
{
	setIdentity();
	float yscale = 1.0f / tan(fov / 2.0f);
	float xscale = yscale / aspect;
	Matrix[0][0] = xscale;
	Matrix[1][1] = yscale;
	Matrix[2][2] = zfar / (zfar - znear);
	Matrix[2][3] = 1.0f;
	Matrix[3][2] = (-znear * zfar) / (zfar - znear);
}


Matrix4x4 Matrix4x4::getScalar(int constant)
{
	Matrix4x4 Scalar;
	Scalar.setIdentity();
	Scalar.Matrix[0][0] *= constant;
	Scalar.Matrix[1][1] *= constant;
	Scalar.Matrix[2][2] *= constant;
	Scalar.Matrix[3][3] *= constant;
	
	return Scalar;
}

Matrix4x4 Matrix4x4::mulMatrix(Matrix4x4 in)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.Matrix[i][j] =
				Matrix[i][0] * in.Matrix[0][j] + Matrix[i][1] * in.Matrix[1][j] +
				Matrix[i][2] * in.Matrix[2][j] + Matrix[i][3] * in.Matrix[3][j];
		}
	}

	return result;
}


void Matrix4x4::setOrthoLH(float width, float height, float near_plane, float far_plane)
{
	setIdentity();
	Matrix[0][0] = 2.0f / width;
	Matrix[1][1] = 2.0f / height;
	Matrix[2][2] = 1.0f / (far_plane - near_plane);
	Matrix[3][2] = -(near_plane / (far_plane - near_plane));
}

Matrix4x4 Matrix4x4::lookAt(Vector3D eye, Vector3D center, Vector3D up)
{
	Matrix4x4 view;
	view.setIdentity();
	Vector3D X, Y, Z;

	Vector3D forward = eye - center;
	forward = Vector3D::nomalize(forward);

	Vector3D left = Vector3D::cross(up, forward);
	left = Vector3D::nomalize(left);

	Vector3D upDirection = Vector3D::cross(forward, left);


	view.Matrix[0][0] = left.x;
	view.Matrix[1][0] = upDirection.x;
	view.Matrix[2][0] = forward.x;
	view.Matrix[3][0] = 0.0f;
	view.Matrix[0][1] = left.y;
	view.Matrix[1][1] = upDirection.y;
	view.Matrix[2][1] = forward.y;
	view.Matrix[3][1] = 0.0f;
	view.Matrix[0][2] = left.z;
	view.Matrix[1][2] = upDirection.z;
	view.Matrix[2][2] = forward.z;
	view.Matrix[3][2] = 0.0f;
	view.Matrix[0][3] = -left.x * eye.x - left.y * eye.y - left.z * eye.z;
	view.Matrix[1][3] = -up.x * eye.x - up.y * eye.y - up.z * eye.z;
	view.Matrix[2][3] = -forward.x * eye.x - forward.y * eye.y - forward.z * eye.z;
	view.Matrix[3][3] = 1.0f;

	return view;
}

Matrix4x4::~Matrix4x4()
{
}
