#include "stdafx.h"
#include "Model.h"
#include "SceneManager.h"



Model::Model(const char * objPath, const char * texPNGPath)
{
	//3D��
	LoadModel(objPath, texPNGPath);
	
}


Model::~Model()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteBuffers(1, &normalBuffer);
	glDeleteBuffers(1, &elementBuffer);
	glDeleteTextures(1, &textureID);
	glDeleteVertexArrays(1,&vertexArrayID);
}

bool Model::LoadModel(const char * objPath, const char * texPNGPath)
{
	textureID = LoadPNG(texPNGPath);
	if (textureID == -1) {
		return false;
	}
	//���ؽ� �� ������ �ӽ� �迭
	vector<Vec3>v;
	vector<Vec2>u;
	vector<Vec3>n;
	if (!LoadOBJ(objPath, v, u, n)) 
	{
		printf("%s�� obj���� �ε忡 �����Ͽ����ϴ�.\n", objPath);
		return false;
	}
	//�ε��� ���۰� ������ �ӽ� �迭
	vector<Vec3>iv;
	vector<Vec2>iu;
	vector<Vec3>in;
	VBOIndexing(
		v, u, n,
		indices,
		iv, iu, in);

	//1. glGen*�� �� ����  2. glBind*�� ���ε�  3. glBufferData�� �� ����
	//4~7�� ���� �ܰ迡�� ����
	//4. glvertexattribpointer�� �Ķ���� ����  5. enablevertexattibarray�� �迭 Ȱ��ȭ (�� ���� ���� ������� �� ����)
	//6. glDrawArray�� �׸�  7. glDisableVertexAttribArray�� �ٽ� ��Ȱ��ȭ
	glGenVertexArrays(1, &vertexArrayID);					//n���� ����(vertex) �迭 ��ü �̸��� �迭�� ��ȯ
	glBindVertexArray(vertexArrayID);						//����(vertex) �迭 ��ü�� name �迭�� ���ε�
	

	//1,2,3�ܰ�
	glGenBuffers(1, &vertexBuffer);									//���� ����
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);					//�� ���۸� ������
	glBufferData(GL_ARRAY_BUFFER, iv.size() * sizeof(Vec3), &iv[0].x, GL_STATIC_DRAW);	//���ۿ� ������ ����
	
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, iu.size() * sizeof(Vec2), &iu[0].x, GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, in.size() * sizeof(Vec3), &in[0].x, GL_STATIC_DRAW);

	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
	
	return true;
}


GLuint Model::LoadPNG(const char * path)
{
	int w, h;
	unsigned char* image = LoadPNGinPath(path, &w, &h, 0, 3);//RGB : 3, RGBA : 4
	GLuint textureID = -1;
	if (!image) {
		printf("%s PNG �̹��� �ε� ����!\n", path);
		return textureID;
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	free((void*)image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	return textureID;
}

bool Model::LoadOBJ(const char * path, vector<Vec3>& outVertices, vector<Vec2>& outUVs, vector<Vec3>& outNormals)
{
	//v�� vertex
	//vt�� �� ���ؽ��� ���� �ؽ��� ��ǥ ����
	//vn�� �� ���ؽ��� ���� �븻 ���� ����
	//f�� ���̽�, a/b/c ���·� �Ǿ����� a��° v���� ���, b��° vt ���, c��° vn ���
	//�ٵ� ����GL�� �ؽ���, ������, �븻���� ���� ���� �ѹ��� ������ �Ұ����ϴ�
	std::vector<unsigned int> vIndices, uvIndices, nmIndices;
	std::vector<Vec3> tmpvert;
	std::vector<Vec2> tmpuv;
	std::vector<Vec3> tmpnormal;

	FILE* f = fopen(path, "r");
	if (!f)
	{
		printf("RUNAGLM->loadOBJ : ��ΰ� �߸���\n");
		return false;
	}

	int count = 0;	//���°��
	while (true)
	{
		++count;
		char lineHeader[256];	//���ٿ� 255�� �Ѿ�� ���� ������ ���� ������ ���� ����
								//printf("RUNAGLM->LoadOBJ : fscanf����, obj���� %d��° ��\n",count);
		int res = fscanf(f, "%s", lineHeader);	//fscanf�� ��¥ �����Լ��̴�
		if (res == EOF)
			break;
		//printf("RUNAGLM->LoadOBJ : strcmp����, obj���� %d��° ��\n", count);
		if (strcmp(lineHeader, "v") == 0)		//���ؽ����
		{
			//printf("RUNAGLM->LoadOBJ : v�Է� ����, obj���� %d��° ��\n", count);
			Vec3 v;
			fscanf(f, "%f %f %f\n", &v.x, &v.y, &v.z);
			tmpvert.push_back(v);
		}
		else if (strcmp(lineHeader, "vt") == 0)	//���ؽ��ؽ��Ķ��
		{
			//printf("RUNAGLM->LoadOBJ : vt�Է� ����, obj���� %d��° ��\n", count);
			Vec2 uv;
			fscanf(f, "%f %f\n", &uv.x, &uv.y);
			tmpuv.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)	//���ؽ��븻���̶��
		{
			//printf("RUNAGLM->LoadOBJ : vn�Է� ����, obj���� %d��° ��\n", count);
			Vec3 nm;
			fscanf(f, "%f %f %f\n", &nm.x, &nm.y, &nm.z);
			tmpnormal.push_back(nm);
		}
		else if (strcmp(lineHeader, "f") == 0)	//���̽����
		{
			//printf("RUNAGLM->LoadOBJ : f�Է� ����, obj���� %d��° ��\n", count);
			string v1, v2, v3;
			unsigned int vi[3], uvi[3], nmi[3];
			int matches = fscanf(f, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vi[0], &uvi[0], &nmi[0], &vi[1], &uvi[1], &nmi[1], &vi[2], &uvi[2], &nmi[2]);
			if (matches != 9)
			{
				printf("f���� ���� ������ �ֽ��ϴ�. �ƴϸ� obj�δ� �����ϼ��� �־��. ��ȹ�� ����������\n");
				fclose(f);
				return false;
			}
			vIndices.push_back(vi[0]);
			vIndices.push_back(vi[1]);
			vIndices.push_back(vi[2]);
			uvIndices.push_back(uvi[0]);
			uvIndices.push_back(uvi[1]);
			uvIndices.push_back(uvi[2]);
			nmIndices.push_back(nmi[0]);
			nmIndices.push_back(nmi[1]);
			nmIndices.push_back(nmi[2]);
		}
	}
	//�ε���
	//���� �ּ��� ��������
	//printf("RUNAGLM->LoadOBJ : �ε��̿���\n", count);
	for (unsigned int i = 0; i < vIndices.size(); ++i)
	{
		unsigned int vi = vIndices[i];
		unsigned int uvi = uvIndices[i];
		unsigned int nmi = nmIndices[i];

		Vec3 v1 = tmpvert[vi - 1];
		Vec2 v2 = tmpuv[uvi - 1];
		Vec3 v3 = tmpnormal[nmi - 1];

		outVertices.push_back(v1);
		outUVs.push_back(v2);
		outNormals.push_back(v3);
	}
	fclose(f);
	return true;
}

void Model::VBOIndexing(
	vector<Vec3>& inVert, vector<Vec2>& inUV, vector<Vec3>& inNM,
	vector<unsigned short>& resIndices,
	vector<Vec3>& resVert, vector<Vec2>& resUV, vector<Vec3>& resNM)
{
	//�ߺ� �ε��� ����������� �޸� ���� �� ���� ���ϸ� ���� ���� �ε��� �۾��Դϴ�.
	//���� �ε����� �ߺ����� �ʴ� ������ ��ȯ�մϴ�.
	map<VertexPUN, unsigned short> vertexMap;	//Map�� �̿��Ͽ� ���� (���� Ž��)
	for (int i = 0; i < inVert.size(); ++i)
	{
		unsigned short index;

		VertexPUN pun;
		pun.pos = inVert[i];
		pun.uv = inUV[i];
		pun.normal = inNM[i];
		map<VertexPUN, unsigned short>::iterator iter = vertexMap.find(pun);
		if (iter == vertexMap.end()) {	//���ٸ� end()���� ��ȯ, end���� ������ �ϳ� �ڰ�
										//���ؽ� �ʿ��� ���� ���� ���ٸ�
										//��ȯ �迭�� ���� �ϳ��� �߰�����
										//resIndices���� ��Ȳ�� ���� ����� ��ȣ�� �������� (like ������)
			resVert.push_back(inVert[i]);
			resUV.push_back(inUV[i]);
			resNM.push_back(inNM[i]);
			unsigned short a = (unsigned short)resVert.size() - 1;
			resIndices.push_back(a);
			vertexMap[pun] = a;
		}
		else
		{
			//���ؽ��ʿ��� ���� ���� �ִٸ�
			//��ȯ �迭�� �� ���� ����־���
			index = iter->second;
			resIndices.push_back(index);
		}
	}
}
