#version 330 core

// 들어올 값 (프래그먼트이기 때문에 UV 값)
in vec2 UV;

// 내보낼 값 (프래그먼트이기 때문에 색생 값)
out vec4 color;

// 텍스쳐를 유니폼으로 받아옴
uniform sampler2D myTexture;

void main(){
	color = texture( myTexture, UV );
	
}