#version 330 core

//UV값을 받아옵니다.
in vec2 UV;

out vec3 color;

//유니폼으로 텍스쳐를 받아옵니다.
uniform sampler2D myTexture;

void main(){
	//내보낼 color값으로 gl이 처리할 것입니다.
	color = texture(myTexture, UV).rgb;
}