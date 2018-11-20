#pragma once
#include "GLShader.h"
class GLProgram
{
public:
	GLProgram();
	~GLProgram();
	void AttachShader(GLShader* shader);
	void DetachShader(GLShader* shader);
	void BindAttribLocation(unsigned int index, char* name);
	bool Link();
	void Use();
	unsigned int GetUniformLocation(const char* name);

public:
	GLuint mID;

};

