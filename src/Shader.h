#pragma once

class Shader
{
protected:
	GLenum	type; // GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
	GLuint	id;
	char*	source;

public:
	Shader();
	Shader( GLenum shaderType );
	Shader( GLenum shaderType, const char* filename );
	Shader( GLenum shaderType, const char* source, int length );
	virtual ~Shader();
	bool	Init( GLenum shaderType, const char* filename );
	bool	Init( GLenum shaderType, const char* source, int length );
	bool	Load( const char* filename );
	bool	Compile();
	void	PrintInfoLog();
	
	GLuint	GetId() const { return id; }

private:
    std::string GetInfoLog();
};
