#version 330 core

//값을 받아오는 부분입니다.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

//값을 내보내는 부분입니다.
out vec2 UV;

// 유니폼을 통해 값을 받아올 부분입니다. (glUniform함수)
// 그래픽매니저의 DrawScene함수의 행렬값입니다.
uniform mat4 MVP;

void main(){

	//행렬을 계산하여 적용합니다..
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
	
	// UV값을 받아서 내보냅니다. gl이 UV를 처리할 수 있게 합니다.
	UV = vertexUV;
}

