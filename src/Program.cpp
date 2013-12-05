#include "PCH.H"
#include "Program.h"
#include "Shader.h"


ShaderProgram::ShaderProgram(void)
{
	id = -1;
    Init();
}

ShaderProgram::~ShaderProgram(void)
{
    UniformMap::const_iterator it = uniformsMap.begin();
    while( it != uniformsMap.end() )
    {
        delete it->second;
        ++it;
    }
    uniformsMap.clear();

    ShaderAttributeMap::const_iterator ita = attrMap.begin();
    while( ita != attrMap.end() )
    {
        delete ita->second;
        ++ita;
    }
    attrMap.clear();

	glDeleteProgram(id);
}

void ShaderProgram::Init()
{
	id = glCreateProgram();
}

void ShaderProgram::AttachShader( Shader* shader)
{
	glAttachShader( id, shader->GetId() );
}

void ShaderProgram::DetachShader( Shader* shader )
{
	glDetachShader( id, shader->GetId() );
}

bool ShaderProgram::Link()
{
	glLinkProgram(id);

    GLint success;
    glGetProgramiv( id, GL_LINK_STATUS, &success );
    bool isValid = ( success == GL_TRUE );
    if( !isValid )
    {
        PrintInfoLog();
		return false;
    }

    // Get active attributes for attribute map creation
    glGetProgramiv( id, GL_ACTIVE_ATTRIBUTES, &numAttributes );
    attrArray = new ShaderAttribute * [ numAttributes ];

    // Get active uniforms for parameter map creation
    glGetProgramiv( id, GL_ACTIVE_UNIFORMS, &numParams );
    uniformsArray = new Uniform * [ numParams ];
    
    RetrieveAttributes();
    RetrieveParameters();
    
    // Bind attributes
    for( int i=0; i<numAttributes; i++ )
        glBindAttribLocation( id, attrArray[i]->location, attrArray[i]->name.c_str() );
}


void ShaderProgram::BindAttribute( const char* name, int location )
{
    glBindAttribLocation( id, location, name );
}


std::string ShaderProgram::GetInfoLog()
{
    int infologLength = 0;
    int charsWritten  = 0;
    GLchar *infoLog;
    std::string retStr = "";

	glGetProgramiv( id, GL_INFO_LOG_LENGTH, &infologLength );

    if( infologLength > 0 )
    {
        infoLog = new GLchar[ infologLength ];
        glGetProgramInfoLog( id, infologLength, &charsWritten, infoLog );
		retStr.append( infoLog );
		delete [] infoLog;
    }
	return retStr;
}

void ShaderProgram::SetFloat( const char* name, float value )
{
    int location = uniformsMap[name]->location;
    glUniform1f( location, value );
}

void ShaderProgram::SetFloat( const char* name, int count, float* values)
{
    int location = uniformsMap[name]->location;
    glUniform1fv( location, count, values );
}

void ShaderProgram::SetVector2( const char* name, int count, float* values )
{
    int location = uniformsMap[name]->location;
    glUniform2fv( location, count, values );
}

void ShaderProgram::SetVector3( const char* name, int count, float* values )
{
    int location = uniformsMap[name]->location;
    glUniform3fv( location, count, values );
}

void ShaderProgram::SetVector4( const char* name, int count, float* values )
{
    int location = uniformsMap[name]->location;
    glUniform4fv( location, count, values );
}

void ShaderProgram::SetInteger( const char* name, int value )
{
    int location = uniformsMap[name]->location;
    glUniform1i( location, value );
}

void ShaderProgram::SetInteger( const char* name, int count, int* values )
{
    int location = uniformsMap[name]->location;
    glUniform1iv( location, count, values );
}

void ShaderProgram::SetVector2i( const char* name, int count, int* values )
{
    int location = uniformsMap[name]->location;
    glUniform2iv( location, count, values );
}

void ShaderProgram::SetVector3i( const char* name, int count, int* values )
{
    int location = uniformsMap[name]->location;
    glUniform3iv( location, count, values );
}

void ShaderProgram::SetVector4i( const char* name, int count, int* values )
{
    int location = uniformsMap[name]->location;
    glUniform4iv( location, count, values );
}

void ShaderProgram::SetBoolean( const char* name, bool value )
{
    int location = uniformsMap[name]->location;
    glUniform1i( location, value );
}

void ShaderProgram::SetMatrix3( const char* name, int count, float* values )
{
    int location = uniformsMap[name]->location;
    glUniformMatrix3fv( location, count, GL_FALSE, values );
}

void ShaderProgram::SetMatrix4( const char* name, int count, float* values, bool transpose )
{
    int location = uniformsMap[name]->location;
    glUniformMatrix4fv( location, count, transpose, values );
}

void ShaderProgram::SetMatrix4( const char* name, float* values, bool transpose )
{
    int location = uniformsMap[name]->location;
    glUniformMatrix4fv( location, 1, transpose, values );
}

void ShaderProgram::PrintInfoLog()
{
    std::string errStr = GetInfoLog();
    std::cout << errStr << std::endl;
}

void ShaderProgram::RetrieveParameters()
{
    char* uniformName = new char[ 256 ];
    memset( uniformName, 0, 256 );
    //parameters.clear();
    for( int i=0; i<numParams; ++i )
    {
        GLsizei length;
        GLint size;
        GLenum type;
        
        glGetActiveUniform( id, i, 256, &length, &size, &type, uniformName );
        uint32_t locId = glGetUniformLocation( id, uniformName );
        
        Uniform* p = new Uniform();
        p->name = uniformName;
        p->size = size;
        p->location = locId;
        uniformsMap[ p->name ] = p;
        uniformsArray[ i ] = p;
    }
    
    delete [] uniformName;
}

void ShaderProgram::RetrieveAttributes()
{
    // Just for ease of use
    GLint attributeMaxLength = 0;
    glGetProgramiv( id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attributeMaxLength );
    GLchar* attributeName = new GLchar[ attributeMaxLength ];
    memset( attributeName, 0, attributeMaxLength );
    
    for( int i=0; i<numAttributes; ++i )
    {
        GLsizei length;
        GLint size;
        GLenum type;
        
        glGetActiveAttrib( id, i, attributeMaxLength, &length, &size, &type, attributeName );
        int locId = glGetAttribLocation( id, attributeName );
        ShaderAttribute* p = new ShaderAttribute();
        p->name = attributeName;
        p->location = locId;
        attrMap[ p->name ] = p;
        attrArray[ i ] = p;
    }
    
    delete [] attributeName;
}


void ShaderProgram::PrintParameters()
{
    for( int i=0; i<numAttributes; ++i )
    {
        std::cout << "+++  Active Attributes Name: " << i << "/" << numAttributes << " - name: " << attrArray[i]->name << " -location: " << attrArray[i]->location << std::endl;
    }

    for( int i=0; i<numParams; ++i )
    {
        std::cout << "+++  Active Parameter/Uniform Name: " << i << "/" << numParams << " - name: " << uniformsArray[i]->name << " -location: " << uniformsArray[i]->location << std::endl;
    }
}