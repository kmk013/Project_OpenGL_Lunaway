#include "stdafx.h"
#include "GraphicManager.h"
#include "MessageManager.h"
#include "Camera.h"
#include "RUNAMath.h"

//초기화시 반드시 InitGLAPI() 사용 후 GL관련 함수들이 사용되어야함 (1.2 이상 버전이 쓰고싶다면)


GraphicManager::GraphicManager()
{

}


GraphicManager::~GraphicManager()
{
}



BOOL GraphicManager::GLInit33()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.05f, 0.06f, 0.12f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return TRUE;
}

void GraphicManager::ViewInit(GLsizei w, GLsizei h)
{
	//시점 초기화
	width = w;
	height = h;

	float ratio = 1.0f*width / height;

	if (height == 0)
		height = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, width, height);

	gluPerspective(45, ratio, 1, 1000);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	CM->CameraInit();
}

void GraphicManager::GetGLVersion(int * major, int * minor)
{
	char* ver = (char*)glGetString(GL_VERSION); // ver = "4.4.0"

	if (ver)
	{
		printf("OpenGL Version : %s\n", ver);
		*major = ver[0] - '0';   // "4.4.0"의 4를 가져옴, int형으로 변환
		if (*major >= 3)
		{
			// 3보다 더 크면 값 반환
			// for GL 3.x
			glGetIntegerv(GL_MAJOR_VERSION, major); // major = 3
			glGetIntegerv(GL_MINOR_VERSION, minor); // minor = 2
		}
		else
		{
			//   3보다 더 작다면 쉐이더 작동 불가능
			*minor = ver[2] - '0';
		}
	}
	else
	{
		printf("glGetString 오류로 사용 가능 버전을 알 수 없습니다\n");
		*major = 3;
		*minor = 2;
	}
}


GLuint GraphicManager::LoadBMP(const char * path)
{
	//OpenGL-Tutorial의 loadBMP 예제를 참고하였습니다.
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int w, h;
	unsigned char* data;

	FILE* f = fopen(path, "rb");
	if (!f) {
		printf("이미지 로드 실패! in RUNAGLM->LoadBMP\n");
		return 0;
	}
	if (fread(header, 1, 54, f) != 54) {
		printf("이미지 포맷이 bmp가 아닙니다 in RUNAGLM->LoadBMP\n");
		fclose(f);
		return 0;
	}
	if (header[0] != 'B' || header[1] != 'M') {
		printf("이미지 포맷이 bmp가 아닙니다 in RUNAGLM->LoadBMP\n");
		fclose(f);
		return 0;
	}
	if (*(int*)&(header[0x1E]) != 0)
	{
		printf("BMP 포맷이 부정확합니다1E\n");
		fclose(f);
		return 0;
	}
	if (*(int*)&(header[0x1C]) != 24)
	{
		printf("BMP 포맷이 부정확합니다1C\n");
		fclose(f);
		return 0;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0)
		imageSize = width*height * 3;
	if (dataPos == 0)
		dataPos = 54;

	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, f);
	fclose(f);

	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	delete[] data;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	return textureID;
}

void GraphicManager::PrepareRender()
{
	wglMakeCurrent(mDC, mRC);
	GLInit33();

	CM->CameraRefresh();
	mProgram = new GLProgram();
	mVertSh = new GLShader(GL_VERTEX_SHADER);
	mTextureSh = new GLShader(GL_FRAGMENT_SHADER);

	mUIProgram = new GLProgram();
	mUIVertSh = new GLShader(GL_VERTEX_SHADER);
	mUITextureSh = new GLShader(GL_FRAGMENT_SHADER);

	mVertSh->Load(L"Resource/VertDraw.vert");      //코드를 로드함
	mTextureSh->Load(L"Resource/VertDraw.frag");
	mVertSh->Compile();            //로드한 코드를 컴파일함
	mTextureSh->Compile();
	mProgram->AttachShader(mVertSh);   //쉐이더를 등록함
	mProgram->AttachShader(mTextureSh);
	mProgram->Link();                     //쉐이더에 따라 프로그램 객체를 연결함

	mUITextureSh->Load(L"Resource/UIDraw.frag");
	mUIVertSh->Load(L"Resource/UIDraw.vert");
	mUITextureSh->Compile();
	mUIVertSh->Compile();
	mUIProgram->AttachShader(mUIVertSh);
	mUIProgram->AttachShader(mUITextureSh);
	mUIProgram->Link();
	SetData();
}

void GraphicManager::SetData()
{
	//모델의 초기화
	MatrixID = mProgram->GetUniformLocation("MVP");
	textureUniformID = mProgram->GetUniformLocation("myTexture");
	uiUniformID = mUIProgram->GetUniformLocation("myTexture");
	uiScreenID = mUIProgram->GetUniformLocation("screenWH");
}

void GraphicManager::ReshapeView(GLsizei w, GLsizei h)
{
	//화면 조정시
	wglMakeCurrent(mDC, mRC);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void GraphicManager::Render()
{
	CM->CameraRefresh();
	DrawScene();
}

void GraphicManager::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//3D 모델들
	mProgram->Use();   //이 프로그램 객체를 사용한다고 알림
	for (auto &i : RUNASCENEM->currentScene->gameObjectList)
	{
		if (i->useModel)
		{
			int ck = 0;


			//Mat4 Model = Mat4(1.0f);
			Mat4 tr = Translate(i->pos.x, i->pos.y, i->pos.z);
			Mat4 sc = Scale(i->scale.x, i->scale.y, i->scale.z);
			Mat4 rt = RotateXYZ(i->rot.x, i->rot.y, i->rot.z);
			Mat4 modelMat = sc*(rt*(tr*CM->View));

			mvp = (modelMat)*CM->Projection;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp.v[0].x);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, i->myModel->textureID);
			glUniform1i(textureUniformID, 0);
			// 버텍스 버퍼 가져옴
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, i->myModel->vertexBuffer);
			glVertexAttribPointer(
				0,                  // 사용할 쉐이더 내 레이아웃 번호
				3,                  // 버텍스 수
				GL_FLOAT,           // 타입
				GL_FALSE,           // 정규화되었는가? X
				0,                  // 배열 요소간의 간격, xyz로만 이루어진 구조체이기 때문에 0
				(void*)0            // 배열의 실제 주소, 현재 없으니 NULL
			);
			// 색상 버퍼 가져옴
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, i->myModel->uvBuffer);
			glVertexAttribPointer(
				1,
				2,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
			);
			//빛, 재질을 구현하기 위한 노말버퍼
			//2017-11-04 v0.12 현재 사용되지 않음
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, i->myModel->normalBuffer);
			glVertexAttribPointer(
				2,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
			);

			// 인덱싱된 버퍼
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i->myModel->elementBuffer);
			// 그리기
			glDrawElements(
				GL_TRIANGLES,      // 어떻게 그릴지
				i->myModel->indices.size(),    // 크기
				GL_UNSIGNED_SHORT,   // 타입
				(void*)0
			);

		}
	}


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//UI들
	mUIProgram->Use();
	for (auto &i : RUNASCENEM->currentScene->uiList) {
		if (i->isEnable) {
			Vec2 sc = Vec2((float)CM->screenWidth*0.5f, (float)CM->screenHeight*0.5f);
			glUniform2fv(uiScreenID, 1, &sc.x);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, i->textureID);
			glUniform1i(uiUniformID, 0);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, i->vertexBuffer);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, i->uvBuffer);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glDrawArrays(GL_TRIANGLES, 0, i->v.size());
			glDisable(GL_BLEND);

			glDisableVertexAttribArray(0); glDisableVertexAttribArray(1);
		}
	}

}

void GraphicManager::DestroyScene()
{
	wglMakeCurrent(mDC, mRC);
	mProgram->DetachShader(mVertSh);
	mProgram->DetachShader(mTextureSh);

	delete mProgram;
	delete mVertSh;
	delete mTextureSh;

	mUIProgram->DetachShader(mUIVertSh);
	mUIProgram->DetachShader(mUITextureSh);

	delete mUIProgram;
	delete mUIVertSh;
	delete mUITextureSh;

	wglMakeCurrent(NULL, NULL);
	if (mRC) {
		wglDeleteContext(mRC);
		mRC = NULL;
	}
}