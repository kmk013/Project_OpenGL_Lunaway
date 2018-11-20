#version 330 core

//���� �޾ƿ��� �κ��Դϴ�.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

//���� �������� �κ��Դϴ�.
out vec2 UV;

// �������� ���� ���� �޾ƿ� �κ��Դϴ�. (glUniform�Լ�)
// �׷��ȸŴ����� DrawScene�Լ��� ��İ��Դϴ�.
uniform mat4 MVP;

void main(){

	//����� ����Ͽ� �����մϴ�..
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
	
	// UV���� �޾Ƽ� �������ϴ�. gl�� UV�� ó���� �� �ְ� �մϴ�.
	UV = vertexUV;
}

