#version 330 core

//UV���� �޾ƿɴϴ�.
in vec2 UV;

out vec3 color;

//���������� �ؽ��ĸ� �޾ƿɴϴ�.
uniform sampler2D myTexture;

void main(){
	//������ color������ gl�� ó���� ���Դϴ�.
	color = texture(myTexture, UV).rgb;
}