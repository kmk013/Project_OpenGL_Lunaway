#version 330 core

// ���� �� (�����׸�Ʈ�̱� ������ UV ��)
in vec2 UV;

// ������ �� (�����׸�Ʈ�̱� ������ ���� ��)
out vec4 color;

// �ؽ��ĸ� ���������� �޾ƿ�
uniform sampler2D myTexture;

void main(){
	color = texture( myTexture, UV );
	
}