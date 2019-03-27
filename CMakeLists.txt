cmake_minimum_required(VERSION 3.6)
project (gestalt_project)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(cmake_cxx_standard 17)

set(GESTALT_SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_window.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_renderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_shader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_prop.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_frame.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_render_text.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_shader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_font_cache.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_shader_cache.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_alarm.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_database.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_sim.cpp
	)

set(SIM_SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/sim/src/game_state.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sim/src/menu_state.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sim/src/test_sim.cpp
	)

add_executable(gestalt_project main.cpp ${GESTALT_SRCS} ${SIM_SRCS})

set_property(TARGET gestalt_project PROPERTY CXX_STANDARD 17)
set_property(TARGET gestalt_project PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(gestalt_project
	opengl32.lib
	${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL2/lib/SDL2.lib
	${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL2/lib/SDL2main.lib
	)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/dep
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt
	${CMAKE_CURRENT_SOURCE_DIR}/sim
	)

set_target_properties(gestalt_project PROPERTIES COMPILE_FLAGS "/MD")