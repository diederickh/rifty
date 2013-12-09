#pragma once

#include <string>
#include <map>


// Decls
class Shader;


struct Uniform
{
    std::string     name;
    int             location;
    int             size;
};
struct ShaderAttribute
{
    std::string     name;
    int             location;
};

typedef std::map<std::string, Uniform*> UniformMap;
typedef std::map<std::string, ShaderAttribute*> ShaderAttributeMap;

class ShaderProgram
{
protected:
	GLuint                              id;
    int                                 numParams;
    int                                 numAttributes;
    
    Uniform**                           uniformsArray;
	UniformMap                          uniformsMap;
    ShaderAttribute**                   attrArray;
	ShaderAttributeMap                  attrMap;

    std::vector<Shader*>                shadersArray;
    
public:
	ShaderProgram();
	virtual ~ShaderProgram();
	void	Init();
	void	AttachShader( Shader* shader );
	void	DetachShader( Shader* shader );
	bool	Link();
	void	PrintInfoLog();

	inline void Bind() { glUseProgram( id ); }
	inline void Unbind() { glUseProgram( 0 ); }

    std::string		GetInfoLog();
	GLuint			GetId()         { return id; }
    
    void BindAttribute( const char* name, int location );
    
    ShaderAttribute* GetAttribute( const char* name ) { return attrMap[name]; }

    void SetFloat( const char* name, float value );
    void SetFloat( const char* name, int count, float* values );
    void SetVector2( const char* name, int count, float* values );
    void SetVector3( const char* name, int count, float* values );
    void SetVector4( const char* name, int count, float* values );
    void SetInteger( const char* name, int value );
    void SetInteger( const char* name, int count, int* values );
    void SetVector2i( const char* name, int count, int* values );
    void SetVector3i( const char* name, int count, int* values );
    void SetVector4i( const char* name, int count, int* values );
    void SetBoolean( const char* name, bool value );
    void SetMatrix3( const char* name, int count, float* values );
    void SetMatrix4( const char* name, int count, float* values, bool transpose=false );
    void SetMatrix4( const char* name, float* values, bool transpose=false );
    
    void PrintParameters();

private:
    void    RetrieveParameters();
    void    RetrieveAttributes();
};
