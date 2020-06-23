#pragma once
#include "../Utilities/utilities.h"

class SkyboxShaders
{
public:
	struct Attributes
	{
		GLint position;
	};

	struct Uniforms
	{
		GLint texture;
		GLint wvp;
	};

private:
	GLuint		m_program;
	GLuint		m_vertexShader;
	GLuint		m_fragmentShader;

	Attributes	m_attributes;
	Uniforms	m_uniforms;

public:
	int			Init(char* fileVertexShader, char* fileFragmentShader);

	// Getters
	GLuint		GetProgram() const;
	Attributes	GetAttributes() const;
	Uniforms	GetUniforms() const;

	~SkyboxShaders();
};

