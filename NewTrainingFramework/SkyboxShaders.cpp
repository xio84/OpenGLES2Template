#include "stdafx.h"
#include "SkyboxShaders.h"

int SkyboxShaders::Init(char* fileVertexShader, char* fileFragmentShader)
{
	m_vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if (m_vertexShader == 0)
	{
		return -1;
	}

	m_fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if (m_fragmentShader == 0)
	{
		glDeleteShader(m_vertexShader);
		return -2;
	}

	m_program = esLoadProgram(m_vertexShader, m_fragmentShader);

	//finding location of attributes
	m_attributes.position = glGetAttribLocation(m_program, "a_posL");

	//finding location of uniforms
	m_uniforms.texture = glGetUniformLocation(m_program, "u_texture");
	m_uniforms.wvp = glGetUniformLocation(m_program, "u_wvp");

	return 0;
}

GLuint SkyboxShaders::GetProgram() const
{
	return m_program;
}

SkyboxShaders::Attributes SkyboxShaders::GetAttributes() const
{
	return m_attributes;
}

SkyboxShaders::Uniforms SkyboxShaders::GetUniforms() const
{
	return m_uniforms;
}

SkyboxShaders::~SkyboxShaders()
{
	glDeleteProgram(m_program);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
}
