#include "stdafx.h"
#include "Model.h"
#include "SceneManager.h"



Model::Model(const char * objPath, const char * texPNGPath)
{
	//3D모델
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
	//버텍스 값 저장할 임시 배열
	vector<Vec3>v;
	vector<Vec2>u;
	vector<Vec3>n;
	if (!LoadOBJ(objPath, v, u, n)) 
	{
		printf("%s의 obj파일 로드에 실패하였습니다.\n", objPath);
		return false;
	}
	//인덱싱 버퍼값 저장할 임시 배열
	vector<Vec3>iv;
	vector<Vec2>iu;
	vector<Vec3>in;
	VBOIndexing(
		v, u, n,
		indices,
		iv, iu, in);

	//1. glGen*로 값 생성  2. glBind*로 바인딩  3. glBufferData로 값 저장
	//4~7은 렌더 단계에서 진행
	//4. glvertexattribpointer로 파라미터 지정  5. enablevertexattibarray로 배열 활성화 (이 둘은 순서 상관없는 것 같음)
	//6. glDrawArray로 그림  7. glDisableVertexAttribArray로 다시 비활성화
	glGenVertexArrays(1, &vertexArrayID);					//n개의 정점(vertex) 배열 객체 이름을 배열로 반환
	glBindVertexArray(vertexArrayID);						//정점(vertex) 배열 객체를 name 배열로 바인딩
	

	//1,2,3단계
	glGenBuffers(1, &vertexBuffer);									//버퍼 생성
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);					//그 버퍼를 가져옴
	glBufferData(GL_ARRAY_BUFFER, iv.size() * sizeof(Vec3), &iv[0].x, GL_STATIC_DRAW);	//버퍼에 데이터 저장
	
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
		printf("%s PNG 이미지 로드 실패!\n", path);
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
	//v는 vertex
	//vt는 한 버텍스에 대한 텍스쳐 좌표 정보
	//vn은 한 버텍스에 대한 노말 매핑 정보
	//f는 페이스, a/b/c 형태로 되어있음 a번째 v값을 사용, b번째 vt 사용, c번째 vn 사용
	//근데 오픈GL은 텍스쳐, 포지션, 노말맵을 위한 값을 한번에 전달이 불가능하다
	std::vector<unsigned int> vIndices, uvIndices, nmIndices;
	std::vector<Vec3> tmpvert;
	std::vector<Vec2> tmpuv;
	std::vector<Vec3> tmpnormal;

	FILE* f = fopen(path, "r");
	if (!f)
	{
		printf("RUNAGLM->loadOBJ : 경로가 잘못됨\n");
		return false;
	}

	int count = 0;	//몇번째줄
	while (true)
	{
		++count;
		char lineHeader[256];	//한줄에 255자 넘어가는 줄이 있으면 오류 날수도 있음 조심
								//printf("RUNAGLM->LoadOBJ : fscanf오류, obj파일 %d번째 줄\n",count);
		int res = fscanf(f, "%s", lineHeader);	//fscanf는 진짜 갓갓함수이다
		if (res == EOF)
			break;
		//printf("RUNAGLM->LoadOBJ : strcmp오류, obj파일 %d번째 줄\n", count);
		if (strcmp(lineHeader, "v") == 0)		//버텍스라면
		{
			//printf("RUNAGLM->LoadOBJ : v입력 오류, obj파일 %d번째 줄\n", count);
			Vec3 v;
			fscanf(f, "%f %f %f\n", &v.x, &v.y, &v.z);
			tmpvert.push_back(v);
		}
		else if (strcmp(lineHeader, "vt") == 0)	//버텍스텍스쳐라면
		{
			//printf("RUNAGLM->LoadOBJ : vt입력 오류, obj파일 %d번째 줄\n", count);
			Vec2 uv;
			fscanf(f, "%f %f\n", &uv.x, &uv.y);
			tmpuv.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)	//버텍스노말맵이라면
		{
			//printf("RUNAGLM->LoadOBJ : vn입력 오류, obj파일 %d번째 줄\n", count);
			Vec3 nm;
			fscanf(f, "%f %f %f\n", &nm.x, &nm.y, &nm.z);
			tmpnormal.push_back(nm);
		}
		else if (strcmp(lineHeader, "f") == 0)	//페이스라면
		{
			//printf("RUNAGLM->LoadOBJ : f입력 오류, obj파일 %d번째 줄\n", count);
			string v1, v2, v3;
			unsigned int vi[3], uvi[3], nmi[3];
			int matches = fscanf(f, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vi[0], &uvi[0], &nmi[0], &vi[1], &uvi[1], &nmi[1], &vi[2], &uvi[2], &nmi[2]);
			if (matches != 9)
			{
				printf("f값에 뭔가 문제가 있습니다. 아니면 obj로더 문제일수도 있어요. 기획자 잡으러가셈\n");
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
	//인덱싱
	//맨위 주석에 설명있음
	//printf("RUNAGLM->LoadOBJ : 인덱싱오류\n", count);
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
	//중복 인덱스 사용으로인한 메모리 낭비 및 성능 저하를 막기 위한 인덱싱 작업입니다.
	//각각 인덱스와 중복되지 않는 값만을 반환합니다.
	map<VertexPUN, unsigned short> vertexMap;	//Map을 이용하여 구현 (빠른 탐색)
	for (int i = 0; i < inVert.size(); ++i)
	{
		unsigned short index;

		VertexPUN pun;
		pun.pos = inVert[i];
		pun.uv = inUV[i];
		pun.normal = inNM[i];
		map<VertexPUN, unsigned short>::iterator iter = vertexMap.find(pun);
		if (iter == vertexMap.end()) {	//없다면 end()값을 반환, end값은 마지막 하나 뒤값
										//버텍스 맵에서 같은 값이 없다면
										//반환 배열에 값을 하나씩 추가해줌
										//resIndices에는 상황에 따라 사용할 번호를 지정해줌 (like 포인터)
			resVert.push_back(inVert[i]);
			resUV.push_back(inUV[i]);
			resNM.push_back(inNM[i]);
			unsigned short a = (unsigned short)resVert.size() - 1;
			resIndices.push_back(a);
			vertexMap[pun] = a;
		}
		else
		{
			//버텍스맵에서 같은 값이 있다면
			//반환 배열에 그 값을 집어넣어줌
			index = iter->second;
			resIndices.push_back(index);
		}
	}
}
