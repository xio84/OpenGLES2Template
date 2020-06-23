attribute vec4 a_posL;
uniform mat4 u_wvp;
varying vec4 v_pos;

void main()
{
	gl_Position = u_wvp * a_posL;
	v_pos = a_posL;
}
   