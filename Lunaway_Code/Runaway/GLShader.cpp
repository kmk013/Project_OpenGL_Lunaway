#include "stdafx.h"
#include "GLShader.h"

GLShader::GLShader(GLenum shaderType)
{
	mType = shaderType;
	mID = glCreateShader(shaderType);
	mCode = NULL;
}

GLShader::~GLShader()
{
	if (mCode)
		delete[] mCode;
	glDeleteShader(mID);
}

bool GLShader::Load(const wchar_t* fileName)
{
	mCode = FileRead(fileName);
	if (mCode)
		return true;
	else {
		printf("쉐이더 로드 실패\n");
		return false;
	}
}

bool GLShader::Compile(void)
{
	if (mCode == NULL)
		return false;
	const char* code = mCode;

	glShaderSource(mID, 1, &code, NULL);
	glCompileShader(mID);

	int param;
	glGetShaderiv(mID, GL_COMPILE_STATUS, &param);
	if (param == GL_TRUE)
		return true;
	else
	{
		printf("쉐이더 컴파일 실패 GLShaderType : %x \n", mType);
		return false;
	}
}

GLuint GLShader::GetID()
{
	return mID;
}

char * GLShader::FileRead(const wchar_t* fileName)
{
	FILE *fp;
	char *content = NULL;
	const wchar_t* rt = L"rt";

	int count = 0;


	_wfopen_s(&fp, fileName, rt);
	if (fp != NULL)
	{
		fseek(fp, 0, SEEK_END);
		count = ftell(fp);
		rewind(fp);
		if (count > 0)
		{
			content = new char[count + 1];
			count = fread(content, sizeof(char), count, fp);
			content[count] = '\0';
		}
		fclose(fp);
	}

	return content;
}
