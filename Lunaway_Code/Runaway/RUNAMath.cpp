#include "stdafx.h"
#include "RUNAMath.h"

Mat4 Translate(float x, float y, float z)
{
	return Mat4(
		1.0f, 0.0f, 0.0f, x,
		0.0f, 1.0f, 0.0f, y,
		0.0f, 0.0f, 1.0f, z,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}
Mat4 RotateX( float rad)
{
	return Mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(rad), -sin(rad), 0.0f,
		0.0f, sin(rad), cos(rad), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}
Mat4 RotateY(float rad)
{
	return Mat4(
		cos(rad), 0.0f,sin(rad), 0.0f,
		0.0f, 1, 0.0f, 0.0f,
		-sin(rad), 0.0f, cos(rad), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}
Mat4 RotateZ(float rad)
{
	return Mat4(
		cos(rad), -sin(rad), 0.0f, 0.0f,
		sin(rad), cos(rad), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}
Mat4 RotateXYZ(float x, float y, float z)
{
	return RotateZ(z)*(RotateY(y)*RotateX(x));
}
Mat4 Scale(float x, float y, float z)
{
	return Mat4(
		x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Mat4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	if (right == left) {
		printf("orthoó�� �����߻� : ȭ�� �¿���̰� 0�Դϴ�.");
		return Mat4();
	}
	if (top == bottom) {
		printf("orthoó�� �����߻� : ȭ�� ���ϱ��̰� 0�Դϴ�.");
		return Mat4();
	}
	if (zNear == zFar) {
		printf("orthoó�� �����߻� : ȭ�� ���̰� 0�Դϴ�.");
		return Mat4();
	}

	//ortho���� ���� ����� ����ȭ�� ��, OpenGL�� ���� 3D �׷��Ƚ� 336�� ������
	return Mat4(
		2.0f / (right - left), 0.0f, 0.0f, -(right + left) / (right - left),
		0.0f, 2.0f / (top - bottom), 0.0f, -(top + bottom) / (top - bottom),
		0.0f, 0.0f, -2.0f / (zFar - zNear), -(zFar + zNear) / (zFar - zNear),
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Mat4 Frustum(float left, float right, float bottom, float top, float zNear, float zFar)
{
	if (right == left) {
		printf("perspectiveó�� �����߻� : ȭ�� �¿���̰� 0�Դϴ�.");
		return Mat4();
	}
	if (top == bottom) {
		printf("perspectiveó�� �����߻� : ȭ�� ���ϱ��̰� 0�Դϴ�.");
		return Mat4();
	}
	if (zNear == zFar) {
		printf("perspectiveó�� �����߻� : ȭ�� ���̰� 0�Դϴ�.");
		return Mat4();
	}

	//frustum���� ���� ����� ����ȭ�� ��, OpenGL�� ���� 3D �׷��Ƚ� 343�� ������
	return Mat4(
		(2 * zNear) / (right - left), 0.0f, (right + left) / (right - left), 0.0f,
		0.0f, (2 * zNear) / (top - bottom), (top + bottom) / (top - bottom), 0.0f,
		0.0f, 0.0f, -(zFar + zNear) / (zFar - zNear), -(2 * zFar*zNear) / (zFar - zNear),
		0.0f, 0.0f, -1.0f, 0.0f
	);
}

Mat4 Perspective(float fovy, float aspect, float zNear, float zFar)
{
	float h = zNear*tanf(RUNA_DEGTORAD(fovy / 2.0f));	//���������� *2�ϱ�
	float top = h;
	float bottom = -h;
	float left = aspect*bottom;
	float right = aspect * top;
	return Frustum(left,right,bottom,top,zNear,zFar);
}

Mat4 LookAt(Vec3 eye, Vec3 center, Vec3 up)
{
	//Mesa3D project (http://mesa3d.org/)���� MIT ���̼����� ���ǵ� �Լ��� �����Ͽ� �����Ͽ����ϴ�.
	//������ �Լ��� ���۱��ڴ� Paul Brian�Դϴ�.
	//gluLookAt���� ����Ǵ� ����� ��ȯ�ϴ� �Լ��Դϴ�.
	float x[3], y[3], z[3];
	float mag;

	//Z�� ���� ���
	z[0] = eye.x - center.x;
	z[1] = eye.y - center.y;
	z[2] = eye.z - center.z;


	//z�� ���� ����ȭ
	mag = sqrt(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]);
	if (mag) {
		z[0] /= mag;
		z[1] /= mag;
		z[2] /= mag;
	}
	
	//X�� ���� ���
	x[0] = up.y * z[2] - up.z * z[1];
	x[1] = -up.x * z[2] + up.z * z[0];
	x[2] = up.x * z[1] - up.y * z[0];

	//Y�� ���� ���
	y[0] = z[1] * x[2] - z[2] * x[1];
	y[1] = -z[0] * x[2] + z[2] * x[0];
	y[2] = z[0] * x[1] - z[1] * x[0];

	//x�� ���� ����ȭ
	mag = sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
	if (mag) {
		x[0] /= mag;
		x[1] /= mag;
		x[2] /= mag;
	}

	//y�� ���� ����ȭ
	mag = sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
	if (mag) {
		y[0] /= mag;
		y[1] /= mag;
		y[2] /= mag;
	}
	
	return Translate(-eye.x,-eye.y,-eye.z)*Mat4(
		x[0], x[1], x[2], 0.0f,
		y[0], y[1], y[2], 0.0f,
		z[0], z[1], z[2], 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}
