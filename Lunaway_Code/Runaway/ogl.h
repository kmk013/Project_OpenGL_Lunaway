//오픈GL API를 가져왔습니다.
//오픈GL 4.6 버전을 사용하기 위한 헤더파일만을 인클루드합니다.
#pragma once
#include "gl/GL.h"
#include "GL/GLU.h"
#include "gl/glext.h"
#include "GL/wglext.h"

#pragma comment(lib,"opengl32.lib")

void InitGLAPI();
//함수포인터 가져오기
extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLUNIFORM2FVPROC glUniform2fv;