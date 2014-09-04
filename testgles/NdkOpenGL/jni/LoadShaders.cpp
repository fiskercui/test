//////////////////////////////////////////////////////////////////////////////
//
//  --- LoadShaders.cxx ---
//
//////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
//#define GLEW_STATIC
//#include <GL/glew.h>
#include "base/CCLog.h"
#include "LoadShaders.h"
#include "base/CCPlatformMacros.h"

#include "platform/CCFileUtils.h"

USING_NS_CC;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//----------------------------------------------------------------------------

static const GLchar*
ReadShader( const char* filename )
{
#ifdef WIN32
	FILE* infile;
	fopen_s( &infile, filename, "rb" );
#else
    FILE* infile = fopen( filename, "rb" );
#endif // WIN32

    if ( !infile ) {
#ifdef _DEBUG
        std::cerr << "Unable to open file '" << filename << "'" << std::endl;
#endif /* DEBUG */
        return NULL;
    }

    fseek( infile, 0, SEEK_END );
    int len = ftell( infile );
    fseek( infile, 0, SEEK_SET );

    GLchar* source = new GLchar[len+1];

    fread( source, 1, len, infile );
    fclose( infile );

    source[len] = 0;

    return const_cast<const GLchar*>(source);
}

//----------------------------------------------------------------------------


static const char gVertexShader[] =
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

GLuint
LoadShaders( ShaderInfo* shaders )
{
    if ( shaders == NULL ) { return 0; }

    GLuint program = glCreateProgram();

    ShaderInfo* entry = shaders;
    while ( entry->type != GL_NONE ) {
        GLuint shader = glCreateShader( entry->type );

        entry->shader = shader;

//        const GLchar* source = ReadShader( entry->filename );
//        if ( source == NULL ) {
//        	LOGI("load shader filename %s is null", entry->filename);
//            for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
//                glDeleteShader( entry->shader );
//                entry->shader = 0;
//            }
//            return 0;
//        }

        std::string source = FileUtils::getInstance()->getStringFromFile(entry->filename).c_str();
        if (source == "")
        {
        	LOGI("load shader filename %s is null", entry->filename);
            for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
                glDeleteShader( entry->shader );
                entry->shader = 0;
            }
            return 0;
        }


//        const char* pSource = gVertexShader;
        const char* pSource = source.c_str();
//        LOGI("shader source:%s", pSource);
        glShaderSource( shader, 1, &pSource, NULL );
//        delete [] source;

        glCompileShader( shader );

        GLint compiled;
        glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
        if ( !compiled ) {
//#ifdef _DEBUG
            GLsizei len;
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

            GLchar* log = new GLchar[len+1];
            glGetShaderInfoLog( shader, len, &len, log );
//            std::cerr << "Shader compilation failed: " << log << std::endl;
        	LOGI("glGetShaderiv error %s", log);
            delete [] log;
//#endif /* DEBUG */
        	LOGI("glGetShaderiv error %s", entry->filename);
            return 0;
        }

        glAttachShader( program, shader );
        
        ++entry;
    }

#ifdef GL_VERSION_4_1
    if ( GLEW_VERSION_4_1 ) {
        // glProgramParameteri( program, GL_PROGRAM_SEPARABLE, GL_TRUE );
    }
#endif /* GL_VERSION_4_1 */
    
    glLinkProgram( program );

    GLint linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    if ( !linked ) {
//#ifdef _DEBUG
        GLsizei len;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

        GLchar* log = new GLchar[len+1];
        glGetProgramInfoLog( program, len, &len, log );
        std::cerr << "Shader linking failed: " << log << std::endl;
        delete [] log;
//#endif /* DEBUG */

        for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
            glDeleteShader( entry->shader );
            entry->shader = 0;
        }
    	LOGI("glGetProgramiv linked error %s", entry->filename);
        return 0;
    }

    return program;
}

//----------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif // __cplusplus


