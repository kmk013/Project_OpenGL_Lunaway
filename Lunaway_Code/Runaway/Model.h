#pragma once
#include "stdafx.h"
#include "RUNAMath.h"
#include "PNGLoader.h"


class Model
{
	struct VertexPUN {
		Vec3 pos;
		Vec2 uv;
		Vec3 normal;
		bool operator<(const VertexPUN t) const {
			return memcmp((void*)this, (void*)&t, sizeof(VertexPUN)) > 0;
		}
	};
public:
	GLuint vertexArrayID;	//이 모델을 위한 값들 저장할 버퍼 지정(그 번호)
public:
	//버퍼(번호)들
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint normalBuffer;
	GLuint elementBuffer;
	vector<unsigned short> indices; //인덱싱 번호

public:
	GLuint textureID;
public:
	Model(const char* objPath, const char* texPNGPath);	//3D모델
	~Model();
	bool LoadModel(const char* objPath, const char* texPNGPath);
	GLuint LoadPNG(const char* path);
	bool LoadOBJ(
		const char* path, vector<Vec3>& outVertices, vector<Vec2>& outUVs, vector<Vec3>& outNormals);
	void VBOIndexing(
		vector<Vec3>& inVert, vector<Vec2>& inUV, vector<Vec3>& inNM,
		vector<unsigned short>& resIndices,
		vector<Vec3>& resVert, vector<Vec2>& resUV, vector<Vec3>& resNM);
};