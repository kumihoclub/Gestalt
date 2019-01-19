#pragma once

#include "sp_common.h"
#include "sp_sprite.h"
#include "sp_shader.h"

#include "nlohmann/json.hpp"
#include "Box2D/Box2D.h"

#include <string>
#include <vector>
#include <unordered_map>

using json = nlohmann::json;

class SPSpriteCache {
public:
	void init();
	void shutdown();
	static SPSprite fetchSprite(const std::string name);

private:
	void parseAtlasJSON(json& atlas_json);
	u32 generateDebugTexture();

};