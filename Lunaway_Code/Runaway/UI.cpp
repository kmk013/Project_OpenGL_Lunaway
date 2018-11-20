#include "stdafx.h"
#include "UI.h"
#include "PNGLoader.h"
#include "Camera.h"


UI::UI(const char * pngPath, int x, int y, float scaleX, float scaleY) : pos((float)x*CM->myrateW, (float)y*CM->myrateH), scale(scaleX*CM->myrateW, scaleY*CM->myrateH, 1.0f), isDestroyed(false), isEnable(true), textureShared(false), isPopp(false)
{
	textureID = LoadPNG(pngPath);
	if (textureID == -1) {
		printf("�̹��� ��ο� ������ �ֽ��ϴ�\n");
	}
	else
		LoadUI(pngPath);
}

UI::UI(UI * texture, int x, int y, float scaleX, float scaleY) : pos((float)x*CM->myrateW, (float)y*CM->myrateH), scale(scaleX*CM->myrateW, scaleY*CM->myrateH, 1.0f), isDestroyed(false), isEnable(true), textureShared(true),isPopp(false)
{
}

UI::~UI()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
		glDeleteTextures(1, &textureID);
}


bool UI::LoadUI(const char * path)
{

	glGenVertexArrays(1, &vertexArrayID);               //n���� ����(vertex) �迭 ��ü �̸��� �迭�� ��ȯ
	glBindVertexArray(vertexArrayID);                  //����(vertex) �迭 ��ü�� name �迭�� ���ε�



	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &uvBuffer);


	//UI �������� ������ ���� �����Ƿ� ���� ó���� �����ع�����
	Vec2 ul = Vec2(pos.x, pos.y + textureHeight*scale.y);
	Vec2 ur = Vec2(pos.x + textureWidth*scale.x, pos.y + textureHeight*scale.y);
	Vec2 dr = Vec2(pos.x + textureWidth*scale.x, pos.y);
	Vec2 dl = Vec2(pos.x, pos.y);

	Vec2 udl = Vec2(0.0f, 1.0f);
	Vec2 udr = Vec2(1.0f, 1.0f);
	Vec2 uur = Vec2(1.0f, 0.0f);
	Vec2 uul = Vec2(0.0f, 0.0f);

	//�ﰢ��1
	v.push_back(ul);
	v.push_back(dl);
	v.push_back(ur);
	//�ﰢ��2
	v.push_back(dr);
	v.push_back(ur);
	v.push_back(dl);

	u.push_back(uul);
	u.push_back(udl);
	u.push_back(uur);

	u.push_back(udr);
	u.push_back(uur);
	u.push_back(udl);

	glGenBuffers(1, &vertexBuffer);                           //���� ����
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);               //�� ���۸� ������
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(Vec2), &v[0].x, GL_STATIC_DRAW);   //���ۿ� ������ ����

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, u.size() * sizeof(Vec2), &u[0].x, GL_STATIC_DRAW);


	return true;
}

void UI::Update()
{
}

void UI::LateUpdate()
{
}

void UI::Destroy()
{
	isDestroyed = true;
}

void UI::PopOut()
{
	isDestroyed = true;
	isPopp = true;
}


GLuint UI::LoadPNG(const char* path)
{
	int w, h;
	unsigned char* image = LoadPNGinPath(path, &w, &h, 0, 4);//RGB : 3, RGBA : 4
	GLuint textureID = -1;
	if (!image) {
		printf("%s PNG �̹��� �ε� ����!\n", path);
		return textureID;
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	free((void*)image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	textureWidth = w;
	textureHeight = h;
	return textureID;
}