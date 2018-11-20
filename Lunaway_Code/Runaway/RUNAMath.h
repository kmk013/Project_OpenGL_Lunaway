#ifndef _RUNAMATH_H_
#define _RUNAMATH_H_


#define RUNA_PI 3.141592653589793f
#define RUNA_RADPERDEG 0.017453292519943f
#define RUNA_DEGPERRAD 57.295779513082306f

#define RUNA_DEGTORAD(deg) deg*RUNA_RADPERDEG
#define RUNA_RADTODEG(rad) rad*RUNA_DEGPERRAD

//필요한 것만 넣은 벡터
typedef struct _vector2 {
	float x;
	float y;
	_vector2() {
		x = y = 0.0f;
	}
	_vector2(float x, float y) {
		this->x = x; this->y = y;
	}
}Vec2;

typedef struct _vector3 {
	float x;
	float y;
	float z; 
	_vector3() {
		x = y = z = 0.0f;
	}
	_vector3(float x, float y, float z) {
		this->x = x; this->y = y; this->z = z;
	}
}Vec3;

typedef struct _vector4 {
	float x;
	float y;
	float z;
	float w;
	_vector4() {
		x = y = z = 0.0f;
	}
	_vector4(float x, float y, float z, float w) {
		this->x = x; this->y = y; this->z = z; this->w = w;
	}
}Vec4;

//필요한 것만 넣은 매트릭스
typedef struct _matrix4 {
	Vec4 v[4];	//v == 가로축, x,y,z,w == 0,1,2,3 == 세로축

	_matrix4() {
		for (int i = 0; i < 4; ++i) {
			v[i].x = v[i].y = v[i].z = v[i].w = 0.0f;
		}
	}
	_matrix4(float value) //단위행렬
	{
		for (int i = 0; i < 4; ++i) {
			v[i].x = v[i].y = v[i].z = v[i].w = 0.0f;
		}
		v[0].x = v[1].y = v[2].z = v[3].w = value;
	}
	_matrix4(
		float ax, float bx, float cx, float dx,
		float ay, float by, float cy, float dy,
		float az, float bz, float cz, float dz,
		float aw, float bw, float cw, float dw
	) {
		v[0].x = ax; v[0].y = ay; v[0].z = az; v[0].w = aw;
		v[1].x = bx; v[1].y = by; v[1].z = bz; v[1].w = bw;
		v[2].x = cx; v[2].y = cy; v[2].z = cz; v[2].w = cw;
		v[3].x = dx; v[3].y = dy; v[3].z = dz; v[3].w = dw;
	}

	_matrix4 operator +(const _matrix4 &m) {
		return _matrix4(
			v[0].x + m.v[0].x, v[1].x + m.v[1].x, v[2].x + m.v[2].x, v[3].x + m.v[3].x,
			v[0].y + m.v[0].y, v[1].y + m.v[1].y, v[2].y + m.v[2].y, v[3].y + m.v[3].y,
			v[0].z + m.v[0].z, v[1].z + m.v[1].z, v[2].z + m.v[2].z, v[3].z + m.v[3].z,
			v[0].w + m.v[0].w, v[1].w + m.v[1].w, v[2].w + m.v[2].w, v[3].w + m.v[3].w
		);
	}
	Vec4 operator*(const Vec4 &m) {
		return Vec4(
			v[0].x*m.x + v[1].x*m.y + v[2].x*m.z + v[3].x*m.w,
			v[0].y*m.x + v[1].y*m.y + v[2].y*m.z + v[3].y*m.w,
			v[0].z*m.x + v[1].z*m.y + v[2].z*m.z + v[3].z*m.w,
			v[0].w*m.x + v[1].w*m.y + v[2].w*m.z + v[3].w*m.w
		);
	}
	_matrix4 operator*(const _matrix4 &m) {
		//왼쪽 세로 * 오른쪽 가로
		return _matrix4(
			v[0].x*m.v[0].x + v[0].y * m.v[1].x + v[0].z * m.v[2].x + v[0].w * m.v[3].x,
			v[1].x*m.v[0].x + v[1].y * m.v[1].x + v[1].z * m.v[2].x + v[1].w * m.v[3].x,
			v[2].x*m.v[0].x + v[2].y * m.v[1].x + v[2].z * m.v[2].x + v[2].w * m.v[3].x,
			v[3].x*m.v[0].x + v[3].y * m.v[1].x + v[3].z * m.v[2].x + v[3].w * m.v[3].x,

			v[0].x*m.v[0].y + v[0].y * m.v[1].y + v[0].z * m.v[2].y + v[0].w * m.v[3].y,
			v[1].x*m.v[0].y + v[1].y * m.v[1].y + v[1].z * m.v[2].y + v[1].w * m.v[3].y,
			v[2].x*m.v[0].y + v[2].y * m.v[1].y + v[2].z * m.v[2].y + v[2].w * m.v[3].y,
			v[3].x*m.v[0].y + v[3].y * m.v[1].y + v[3].z * m.v[2].y + v[3].w * m.v[3].y,
			
			v[0].x*m.v[0].z + v[0].y * m.v[1].z + v[0].z * m.v[2].z + v[0].w * m.v[3].z,
			v[1].x*m.v[0].z + v[1].y * m.v[1].z + v[1].z * m.v[2].z + v[1].w * m.v[3].z,
			v[2].x*m.v[0].z + v[2].y * m.v[1].z + v[2].z * m.v[2].z + v[2].w * m.v[3].z,
			v[3].x*m.v[0].z + v[3].y * m.v[1].z + v[3].z * m.v[2].z + v[3].w * m.v[3].z,

			v[0].x*m.v[0].w + v[0].y * m.v[1].w + v[0].z * m.v[2].w + v[0].w * m.v[3].w,
			v[1].x*m.v[0].w + v[1].y * m.v[1].w + v[1].z * m.v[2].w + v[1].w * m.v[3].w,
			v[2].x*m.v[0].w + v[2].y * m.v[1].w + v[2].z * m.v[2].w + v[2].w * m.v[3].w,
			v[3].x*m.v[0].w + v[3].y * m.v[1].w + v[3].z * m.v[2].w + v[3].w * m.v[3].w
		);
	}
	_matrix4& operator=(const _matrix4 &m) {
		for (int i = 0; i < 4; ++i) {
			v[i].x = m.v[i].x; v[i].y = m.v[i].y; v[i].z = m.v[i].z; v[i].w = m.v[i].w;
		}
		return *this;
	}
}Mat4;

Mat4 Translate(float x, float y, float z);//평행이동 행렬을 계산합니다.
Mat4 RotateX( float rad);	//X축 기준 회전
Mat4 RotateY(float rad);	//Y축 기준 회전
Mat4 RotateZ(float rad);	//Z축 기준 회전
Mat4 RotateXYZ(float x, float y, float z);//라디안 좌표
Mat4 Scale(float x, float y, float z);	//스케일링 행렬을 계산합니다.
Mat4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
Mat4 Frustum(float left, float right, float bottom, float top, float zNear, float zFar);
Mat4 Perspective(float fovy, float aspect, float zNear, float zFar);
Mat4 LookAt(Vec3 eye, Vec3 center, Vec3 up);

#endif