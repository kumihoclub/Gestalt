# Gestalt

Results of a (very) staggered 3 month scrum sprint to create tech for a very specific game.

All code is licensed MIT, but I would not recommened using this in production. There are many caveats

### Features:
*CastleDB sprite loading (requires sprite page, open example salt.dat database file in bin as an example)
*Sprite batching by texture
*Simple struct-based workflow for getting something up quickly.
*Timing semantics via a simple Alarm type
*Trivial keyboard input checking via a key-type that can be created on the fy, no polling required in sim.
*Font rendering
*Screen and world anchoring for props (Screen anchoring mainly for UI)


### Caveats:
*Single pass rendering, no post processing possible.
*No map format (was planned via CastleDB, but never reached that point)
*Hard framecap that doesnt account for stuttering
*MVP generation is 100% cpu side.
*No physics (even though Box2d is in the repo..)

There are many derelict dependencies in the repo from experimentation/brainstorming, the actual dependencies are as follows

*opengl+glad (targeted 3.3 core)
*SDL2
*glm
*nlohmann json.hpp
*stb_image.h
*stb_truetype.h
*stb_rectpack.h
*CastleDB
