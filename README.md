# Gestalt

Staggered developement of a game releated framework

All code is licensed MIT, but I would not recommened using this in production.

### Current Features:
* CastleDB sprite loading (requires sprite page, open example salt.dat database file located in bin as an example)
* Draw batching by texture/shader
* Simple struct-based prop/entity/gameobject workflow for getting something up quickly.
* Timing semantics via a simple Alarm type
* Trivial keyboard input checking via a key-type that can be created on the fly, no polling required in sim.
* Font rendering with runtime atlas generation
* Screen and world anchoring for props (Screen anchoring mainly for UI)
* State stack with transition logic

### Current Caveats:
* Single pass rendering, no post processing possible.
* No map format (was planned via CastleDB, but never reached that point)
* Hard framecap that doesnt account for stuttering
* MVP generation and vertex transformation is 100% cpu side
* No physics
* Non SDF font atlas generation

### Dependencies
* OpenGL+glad (targeted 3.3 core)
* SDL2
* glm
* nlohmann json.hpp
* stb_image.h
* stb_truetype.h
* stb_rectpack.h
* CastleDB
