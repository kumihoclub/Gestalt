#pragma once

#include "glad\glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "sp_common.h"

class SPShader {
public:
	SPShader();
	friend class SPShaderCache;
	void use();
	u32 getUniformLocation(const std::string& name);
	void setUniformValue(u32 u, GLboolean val);
	void setUniformValue(u32 u, GLint val);
	void setUniformValue(u32 u, GLfloat val);
	u32 id();
private:
	SPShader(std::string& vert_src, std::string& frag_src);
	u32 m_id = 0;
};