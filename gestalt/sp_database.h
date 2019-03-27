#pragma once

#include "sp_common.h"
#include "sp_sprite.h"
#include "sp_prop.h"
#include "sp_transform.h"

#include "nlohmann/json.hpp"

#include <string>
#include <vector>
#include <unordered_map>

using json = nlohmann::json;

class SPDatabase {
public:
	void init();
	void shutdown();
	static SPSprite fetchSprite(const std::string name);

private:
	void loadImages();
	void loadSprites();
	void generateDebugSprite();

};