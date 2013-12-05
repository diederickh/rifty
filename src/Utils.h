#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <stdio.h>
#include <stdint.h>
#include <glm/glm.hpp>

#include <ApplicationServices/ApplicationServices.h>

struct RiftyConfig {
    std::string data_path;
    int win_w;
    int win_h;
};

extern RiftyConfig rifty_config;

static std::string datapath() {
  return rifty_config.data_path;
}

static void print(glm::mat4& m) {
  printf("%f, %f, %f, %f\n", m[0][0], m[1][0], m[2][0], m[3][0]);
  printf("%f, %f, %f, %f\n", m[0][1], m[1][1], m[2][1], m[3][1]);
  printf("%f, %f, %f, %f\n", m[0][2], m[1][2], m[2][2], m[3][2]);
  printf("%f, %f, %f, %f\n", m[0][3], m[1][3], m[2][3], m[3][3]);
}

static std::string GetFromResources( const std::string& filename )
{
#if defined( WIN32 )
    return "data/" + filename;
#else
    char path[ 4096 ];
    CFURLRef url = ::CFBundleCopyResourcesDirectoryURL( ::CFBundleGetMainBundle() );
    ::CFURLGetFileSystemRepresentation( url, true, (UInt8*)path, 4096 );
    ::CFRelease( url );
    return std::string( path ) + "/" + filename;
#endif
}


static char* FileRead( const char* filename )
{
	FILE* fp = NULL;
	char* content = NULL;
	int count = 0;
    
//	if( !filename )
    {
		fp = fopen( filename, "rt" );
		if( fp )
		{
			fseek( fp, 0, SEEK_END );
			count = ftell( fp );
			rewind( fp );
			if( count > 0 )
			{
				content = new char[count+1];
				count = fread( content, sizeof(char), count, fp );
				content[count] = '\0';
			}
			fclose( fp );
		}
	}
    
	return content;
}


#endif
