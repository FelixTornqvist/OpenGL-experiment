#version 330

attribute int in_Position;
attribute vec4 in_Color;
 
out vec4 ex_Color;

uniform mat4 mvp;

void main(void) {
    gl_Position = mvp * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
 
    ex_Color = in_Color;
}
