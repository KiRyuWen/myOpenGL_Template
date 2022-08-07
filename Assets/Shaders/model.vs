#version 430 core
layout(location=0)in vec2 pos;
layout(location=1)in vec2 texture_coord;

out vec2 uv;

void main(){
    gl_Position=vec4(pos.x,pos.y,0,1);
    uv=texture_coord;
}