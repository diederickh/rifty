#include "PCH.h"

Shader::Shader()
: source(NULL)
{
}

Shader::Shader( GLenum shaderType )
: source(NULL)
, type(shaderType)
, id(0)
{
}

Shader::Shader( GLenum shaderType, const char* filename )
: source(NULL)
, type(shaderType)
, id(0)
{
	id = glCreateShader( shaderType );
	Init( shaderType, filename );
}

Shader::Shader( GLenum shaderType, const char* source, int length )
: source(NULL)
, type(shaderType)
, id(0)
{
	id = glCreateShader( shaderType );
	Init( shaderType, source, length );
}

Shader::~Shader()
{
    delete [] source;
	glDeleteShader( id );
}

bool Shader::Init( GLenum shaderType, const char* filename )
{
	Load( filename );
	Compile();
	return true;
}

bool Shader::Init( GLenum shaderType, const char* source, int lengthInBytes )
{
    this->source = new char[ lengthInBytes ];
    memcpy( this->source, source, lengthInBytes );
    const char* code = source;
	glShaderSource( id , 1, &code, NULL );

	if( !Compile() ) return false;
	return true;
}

bool Shader::Load( const char* filename )
{
	source = FileRead( filename );
    PrintInfoLog();
	if( source )
        return true;
	return false;
}

bool Shader::Compile()
{
	if( !source )
        return false;

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