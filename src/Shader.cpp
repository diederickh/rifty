#include "PCH.h"

Shader::Shader()
: source(NULL)
{
}

Shader::Shader( GLenum shaderType )
: type(shaderType)
, id(0)
, source(NULL)
{
}

Shader::Shader( GLenum shaderType, const char* filename )
: type(shaderType)
, id(0)
, source(NULL)
{
	id = glCreateShader( shaderType );
	Init( shaderType, filename );
}

Shader::Shader( GLenum shaderType, const char* source, int length )
: type(shaderType)
, id(0)
, source(NULL)
{
	id = glCreateShader( shaderType );
	Init( shaderType, source, length );
}

Shader::~Shader()
{
	glDeleteShader( id );
}

bool Shader::Init( GLenum shaderType, const char* filename )
{
	if( !Load( filename ) ) return false;
	if( !Compile() ) return false;
    delete [] source;
	return true;
}

bool Shader::Init( GLenum shaderType, const char* source, int lengthInBytes )
{
	glShaderSource( id , 1, &source, NULL );
	if( !Compile() ) return false;
	return true;
}

bool Shader::Load( const char* filename )
{
	source = FileRead( filename );
	if( source ) return true;
	return false;
}

bool Shader::Compile()
{
	glCompileShader( id );

	int param;
	glGetShaderiv( id, GL_COMPILE_STATUS, &param );
	if( param == GL_TRUE )
		return true;
	else
	{
        std::string errStr = GetInfoLog();
        std::cout << errStr;
		return false;
	}
}

std::string Shader::GetInfoLog()
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
    std::string retStr;

	glGetShaderiv( id, GL_INFO_LOG_LENGTH, &infologLength );

    if( infologLength > 0 )
    {
        infoLog = new char[ infologLength ];
        glGetShaderInfoLog( id, infologLength, &charsWritten, infoLog );
		retStr = std::string( infoLog );
		delete [] infoLog;
    }
	return retStr;
}


void Shader::PrintInfoLog()
{
    std::string errStr = GetInfoLog();
    std::cout << errStr << std::endl;
}