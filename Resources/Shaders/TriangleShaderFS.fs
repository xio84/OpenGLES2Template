precision mediump float;
uniform sampler2D u_texture;
uniform samplerCube u_envi;
uniform vec3 u_camPosition;
uniform float u_shininess;
uniform mat4 u_world;

varying vec3 v_pos;
varying vec3 v_norm;
varying vec2 v_uv;

void main()
{
	vec3 toEye = u_camPosition - (mat3(u_world) * v_pos);
	vec3 reflectDir = reflect(normalize(-toEye), normalize(mat3(u_world) * v_norm)); // reflect() in non linear
	vec4 a = textureCube(u_envi, reflectDir);
	vec4 b = texture2D(u_texture, v_uv);
	gl_FragColor = (u_shininess * a) + ((1.0 - u_shininess) * b);
	// gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
