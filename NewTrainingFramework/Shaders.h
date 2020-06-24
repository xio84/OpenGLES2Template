#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	struct Attributes
	{
		GLint position;
		GLint uv;
		GLint norm;
	};

	struct Uniforms
	{
		GLint texture;
		GLint wvp;
		GLint world;
		GLint envi;
		GLint camPosition;
		GLint shininess;
	};

private:
	GLuint		m_program;
	GLuint		m_vertexShader; 
	GLuint		m_fragmentShader;

	Attributes	m_attributes;
	Uniforms	m_uniforms;

public:
	int			Init( char * fileVertexShader, char * fileFragmentShader );
	
	// Getters
	GLuint		GetProgram() const;
	Attributes	GetAttributes() const;
	Uniforms	GetUniforms() const;
	
	~Shaders();
};