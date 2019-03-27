

#include "glad/glad.h"

#include "sp_shader.h"
#include "sp_gl_err.h"

#include <fstream>
#include <iostream>
#include <sstream>

SPShader::SPShader() {}

SPShader::SPShader(std::string& vert_src, std::string& frag_src) {

	const char* vert_code = vert_src.c_str();
	const char* frag_code = frag_src.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER); spCheckGLError();
	glShaderSource(vertex, 1, &vert_code, NULL); spCheckGLError();
	glCompileShader(vertex); spCheckGLError();
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success); spCheckGLError();
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	fragment = glCreateShader(GL_FRAGMENT_SHADER); spCheckGLError();
	glShaderSource(fragment, 1, &frag_code, NULL); spCheckGLError();
	glCompileShader(fragment); spCheckGLError();
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success); spCheckGLError();
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// shader Program
	m_id = glCreateProgram(); spCheckGLError();
	glAttachShader(m_id, vertex); spCheckGLError();
	glAttachShader(m_id, fragment); spCheckGLError();
	glLinkProgram(m_id); spCheckGLError();
	// print linking errors if any
	glGetProgramiv(m_id, GL_LINK_STATUS, &success); spCheckGLError();
	if (!success)
	{
		glGetProgramInfoLog(m_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex); spCheckGLError();
	glDeleteShader(fragment); spCheckGLError();

}

void SPShader::use() {
	glUseProgram(m_id);
}

u32 SPShader::getUniformLocation(const std::string& name) {
	return glGetUniformLocation(m_id, name.c_str()); spCheckGLError();
}

void SPShader::setUniformValue(u32 u, GLboolean val) {

}

void SPShader::setUniformValue(u32 u, GLint val) {
	glUseProgram(m_id);
	glUniform1i(u, val); spCheckGLError();
}

void SPShader::setUniformValue(u32 u, GLfloat val) {
	glUseProgram(m_id);
	glUniform1f(u, val); spCheckGLError();
}

u32 SPShader::id() {
	return m_id;
}