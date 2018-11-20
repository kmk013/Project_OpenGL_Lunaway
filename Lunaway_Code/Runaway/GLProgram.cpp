#include "stdafx.h"
#include "GLProgram.h"

//프로그램 오브젝트
//쉐이더를 붙고 땔 수 있는 객체이다.
//셰이더 간의 호환성을 검사할 수 있는 객체이다.

//그래픽카드는 수많은 쉐이더를 실행하기 위한 cpu(?)들로 이루어져있다.
//그들을 활용하기 위해 쉐이더를 사용한다.

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
	//index와 쉐이더의 사용자 정의 특성 변수를 연결합니다 (in asdf, out asdf 등)
	glBindAttribLocation(mID, index, name);
}

bool GLProgram::Link()
{
	//프로그램 객체를 연결합니다.
	//GL_VERTEX_SHADER 쉐이더가 프로그램에 이싸면, 버텍스 프로세서에서 실행될 파일을 생성합니다.
	//GL_GEOMETRY_SHADER 쉐이더가 프로그램에 있다면, 기하학 프로세서에서 실행될 실행 파일을 생성합니다.
	//GL_FRAGMENT_SHADER 쉐이더가 프로그램에 있다면, 프래그먼트 프로세서에서 실행될 샐행 파일을 생성합니다.
	glLinkProgram(mID);
	int param;
	glGetProgramiv(mID, GL_LINK_STATUS, &param);	//링크된 프로그램의 사용 준비가 되었는지 확인합니다.
	if (param == GL_TRUE)
		return true;	
	else {
		return false;
	}
}

void GLProgram::Use()
{
	//이 프로그램 객체를 사용한다고 알립니다.
	glUseProgram(mID);
}

unsigned int GLProgram::GetUniformLocation(const char * name)
{
	return glGetUniformLocation(mID,name);
}
