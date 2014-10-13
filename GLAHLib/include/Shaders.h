//Shaders.h
//My Helper functions

#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>

GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
GLuint CreateProgram(const char *a_vertex, const char *a_frag);