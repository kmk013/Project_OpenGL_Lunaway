#pragma once
#include "stdafx.h"
class GLShader
{
public:
	GLShader(GLenum shaderType);
	~GLShader();
	bool Load(const wchar_t* fileName);
	bool Compile(void);
	GLuint GetID();
	
protected:
	char* GLShader::FileRead(const wchar_t* fileName);

protected:
	GLenum mType;
	GLuint mID;
	char* mCode;
};

