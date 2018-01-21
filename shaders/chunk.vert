#version 330

attribute vec3 in_Position;
attribute vec4 in_Color;
 
out vec4 ex_Color;

uniform mat4 mvp;

void main(void) {
	// int mask = 0x3FF; // 0b0000 0000 0000 0000 0000 0011 1111 1111;
	// int x = in_Position & mask;
	// int y = (in_Position >> 10) & mask;
	// int z = (in_Position >> 20) & mask;

 //    gl_Position = mvp * vec4(x, y, z, 1.0);
 	gl_Position = mvp * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
 
    ex_Color = in_Color;
}
