#include "stdafx.h"
#include "GLProgram.h"

//���α׷� ������Ʈ
//���̴��� �ٰ� �� �� �ִ� ��ü�̴�.
//���̴� ���� ȣȯ���� �˻��� �� �ִ� ��ü�̴�.

//�׷���ī��� ������ ���̴��� �����ϱ� ���� cpu(?)��� �̷�����ִ�.
//�׵��� Ȱ���ϱ� ���� ���̴��� ����Ѵ�.

GLProgram::GLProgram()
{
	mID=glCreateProgram();
}


GLProgram::~GLProgram()
{
	glDeleteProgram(mID);
}

void GLProgram::AttachShader(GLShader * shader)
{
	glAttachShader(mID, shader->GetID());
}

void GLProgram::DetachShader(GLShader * shader)
{
	glDetachShader(mID, shader->GetID());
}

void GLProgram::BindAttribLocation(unsigned int index, char* name)
{
	//index�� ���̴��� ����� ���� Ư�� ������ �����մϴ� (in asdf, out asdf ��)
	glBindAttribLocation(mID, index, name);
}

bool GLProgram::Link()
{
	//���α׷� ��ü�� �����մϴ�.
	//GL_VERTEX_SHADER ���̴��� ���α׷��� �̽θ�, ���ؽ� ���μ������� ����� ������ �����մϴ�.
	//GL_GEOMETRY_SHADER ���̴��� ���α׷��� �ִٸ�, ������ ���μ������� ����� ���� ������ �����մϴ�.
	//GL_FRAGMENT_SHADER ���̴��� ���α׷��� �ִٸ�, �����׸�Ʈ ���μ������� ����� ���� ������ �����մϴ�.
	glLinkProgram(mID);
	int param;
	glGetProgramiv(mID, GL_LINK_STATUS, &param);	//��ũ�� ���α׷��� ��� �غ� �Ǿ����� Ȯ���մϴ�.
	if (param == GL_TRUE)
		return true;	
	else {
		return false;
	}
}

void GLProgram::Use()
{
	//�� ���α׷� ��ü�� ����Ѵٰ� �˸��ϴ�.
	glUseProgram(mID);
}

unsigned int GLProgram::GetUniformLocation(const char * name)
{
	return glGetUniformLocation(mID,name);
}
