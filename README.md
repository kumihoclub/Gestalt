# Gestalt

Halted developement of what was to be a 2D game releated framework.

What I learned from this ths hard way: **make games not engines**.

While there are functional implementations for a lot of the requirements for 2D gamedev in here, most of the methods used in this are naive and were heavily brute forced, 
and because of this I decided to archive this repo and keep it just for references sakes. I myself have moved on from this and while there may be a few snippets here and 
there that may be useful, I would not recommened using this fully for any project. Much better options exist.

All code is licensed MIT.

### Features:
* CastleDB sprite loading (requires sprite page, open example salt.dat database file located in bin as an example)
* Draw batching by texture/shader
* Simple struct-based prop/entity/gameobject workflow for getting something up quickly.
* Timing semantics via a simple Alarm type
* Trivial keyboard input checking via a key-type that can be created on the fly, no polling required in sim.
* Font rendering with runtime atlas generation
* Screen and world anchoring for props (Screen anchoring mainly for UI)
* State stack with transition logic

### Caveats:
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
