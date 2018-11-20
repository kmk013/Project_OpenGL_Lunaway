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
	GLuint vertexArrayID;	//�� ���� ���� ���� ������ ���� ����(�� ��ȣ)
public:
	//����(��ȣ)��
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint normalBuffer;
	GLuint elementBuffer;
	vector<unsigned short> indices; //�ε��� ��ȣ

public:
	GLuint textureID;
public:
	Model(const char* objPath, const char* texPNGPath);	//3D��
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