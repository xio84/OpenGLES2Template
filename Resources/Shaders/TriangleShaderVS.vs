attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec3 a_norm;

uniform mat4 u_wvp;

varying vec2 v_uv;
varying vec3 v_pos;
varying vec3 v_norm;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_wvp * posL;
	v_uv = a_uv;
	v_pos = a_posL;
	v_norm = a_norm;
}
   