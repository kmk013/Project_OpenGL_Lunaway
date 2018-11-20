#version 330 core

layout(location = 0) in vec2 vertexPosition_screenspace;
layout(location = 1) in vec2 vertexUV;

uniform vec2 screenWH;

out vec2 UV;

void main(){

   // [0..800][0..600]À» [-1..1][-1..1]·Î ¸¸µê
   vec2 vertexPosition_homoneneousspace = vertexPosition_screenspace - screenWH;
   vertexPosition_homoneneousspace /= screenWH;
   gl_Position =  vec4(vertexPosition_homoneneousspace,0,1);
   
   UV = vertexUV;
}