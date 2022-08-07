#version 430 core

//out value
out vec4 colors;

//in value
in vec2 uv;

//uniform variable
uniform sampler2D Image;
uniform vec2 resolution;
uniform float time;

void main(){
    
    colors=texture(Image,vec2(uv.x,1.-uv.y))*vec4(
        (sin(uv.x+time)+1.)/2.,
        (cos(uv.y+time)+1.)/2.,
        (cos(uv.x+uv.y+time)+1.)/2.,
    1.);
}