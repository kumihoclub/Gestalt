

#include "glad/glad.h"

#include "sp_shader.h"
#include "sp_gl_err.h"

#include <fstream>
#include <iostream>
#include <sstream>

SPShader::SPShader() {}

SPShader::SPShader(std::string& vert_src, std::string& frag_src) {
	// 1. retrieve the vertex/fragment source code from filePath
	//std::string vertexCode;
	//std::string fragmentCode;
	//std::ifstream vShaderFile;
	//std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	//vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	/*fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();*/
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

/*SPShader::SPShader() {}

SPShader::SPShader(const char* src, SPShaderType type) {
	load(src, type);
}

SPShader::~SPShader() {}

void SPShader::load(const char* src, SPShaderType type) {
	if (m_handle != 0) {
		glDeleteShader(m_handle); spCheckGLError();
		m_handle = 0;
	}

	// Create the shader objects
	if (type == SP_SHADER_TYPE_VERT) {
		m_type = SP_SHADER_TYPE_VERT;
		m_handle = glCreateShader(GL_VERTEX_SHADER); spCheckGLError();
	}
	else if (type == SP_SHADER_TYPE_FRAG) {
		m_type = SP_SHADER_TYPE_FRAG;
		m_handle = glCreateShader(GL_FRAGMENT_SHADER); spCheckGLError();
	}

	// Load the shader file contents into a vector
	/*std::ifstream shader_stream(src, std::ios_base::binary);
	std::ostringstream shader_source;
	shader_source << shader_stream.rdbuf();
	auto shader_str = shader_source.str();
	const char* shader_c_str = shader_str.c_str();
	const GLchar* src_raw = (const GLchar*)src;
	glShaderSource(m_handle, 1, &src_raw, NULL); spCheckGLError();
	//shader_stream.close();
	glCompileShader(m_handle); spCheckGLError();

	int  success;
	char log[512];
	glGetShaderiv(m_handle, GL_COMPILE_STATUS, &success); spCheckGLError();
	if (!success) {
		glGetShaderInfoLog(m_handle, 512, NULL, log); spCheckGLError();
		std::cout << "Shader compilation failed : " << log << std::endl; // yeah I know this is bad
		glDeleteShader(m_handle); spCheckGLError();
		m_handle = 0;
	}

}

u32 SPShader::handle() {
	return m_handle;
}

SPShaderType SPShader::get_type() { 
	return m_type;
}

void SPShader::destory() {
	if (m_handle != 0) {
		glDeleteShader(m_handle);
	}
}

SPShaderProgram::SPShaderProgram() {}

SPShaderProgram::SPShaderProgram(SPShader* vert, SPShader* frag) {
	link(vert, frag);
}

SPShaderProgram::~SPShaderProgram() {
	if (m_handle != 0) {
		glDeleteShader(m_handle);
	}
}

void SPShaderProgram::link(SPShader* vert, SPShader* frag) {
	if (m_handle != 0) {
		glDeleteProgram(m_handle);
		m_handle = 0;
	}
	if (vert->get_type() == SP_SHADER_TYPE_VERT && frag->get_type() == SP_SHADER_TYPE_FRAG) {
		if (vert->handle() != 0 && frag->handle() != 0) {
			m_handle = glCreateProgram();
			glAttachShader(m_handle, vert->handle()); spCheckGLError();
			glAttachShader(m_handle, frag->handle()); spCheckGLError();
			glLinkProgram(m_handle); spCheckGLError(); 

			int  success;
			char log[512];
			glGetProgramiv(m_handle, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(m_handle, 512, NULL, log);
				std::cout << "Shader program link failed : " << log << std::endl; // yeah I know this is bad
				glDeleteProgram(m_handle);
				m_handle = 0;
			}
		}
	}
}

void SPShaderProgram::use() {
	glUseProgram(m_handle);
}

u32 SPShaderProgram::handle() {
	return m_handle;
}

void SPShaderProgram::destory() {
	if (m_handle != 0) {
		glDeleteProgram(m_handle);
	}
}*/