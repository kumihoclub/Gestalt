#pragma once

#include "sp_common.h"
#include "sp_shader.h"

#include <string>

class SPShaderCache {
public:
	void init();
	void shutdown();
	static void compileShader(std::string& vert_src, std::string frag_src, std::string& name);
	static SPShader* fetchShader(const std::string name);

private:

};