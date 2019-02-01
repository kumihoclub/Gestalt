cmake_minimum_required(VERSION 3.6)
project (black_telephone)

enable_language(ASM_MASM) #For angelscript on Win64

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(cmake_cxx_standard 17)

#set_source_files_properties(foo.s PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")

set(BOX2D_DEPS
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Collision/Shapes/b2ChainShape.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Collision/Shapes/b2CircleShape.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Collision/Shapes/b2EdgeShape.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Collision/Shapes/b2PolygonShape.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Collision/b2BroadPhase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Collision/b2CollideCircle.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Collision/b2CollideEdge.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Collision/b2CollidePolygon.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Collision/b2Collision.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Collision/b2Distance.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Collision/b2DynamicTree.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Collision/b2TimeOfImpact.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Common/b2BlockAllocator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Common/b2Draw.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Common/b2Math.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Common/b2Settings.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Common/b2StackAllocator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Common/b2Timer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Contacts/b2CircleContact.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Contacts/b2Contact.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Contacts/b2ContactSolver.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Contacts/b2PolygonContact.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Joints/b2DistanceJoint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Joints/b2FrictionJoint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Joints/b2GearJoint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Joints/b2Joint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Joints/b2MotorJoint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Joints/b2MouseJoint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Joints/b2PulleyJoint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Joints/b2RopeJoint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Joints/b2WeldJoint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/Joints/b2WheelJoint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/b2Body.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/b2ContactManager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/b2Fixture.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/b2Island.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/b2World.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Dynamics/b2WorldCallbacks.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/Box2D/Rope/b2Rope.cpp
)

set(ANGELSCRIPT_DEPS
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/add-on/scriptstdstring/scriptstdstring.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_atomic.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_builder.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_bytecode.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_callfunc.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_callfunc_arm.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_callfunc_mips.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_callfunc_ppc.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_callfunc_ppc_64.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_callfunc_sh4.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_callfunc_x64_gcc.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_callfunc_x64_mingw.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_callfunc_x64_msvc.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_callfunc_x64_msvc_asm.asm
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_callfunc_x86.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_callfunc_xenon.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_compiler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_configgroup.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_context.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_datatype.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_gc.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_generic.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_globalproperty.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_memory.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_module.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_objecttype.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_outputbuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_parser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_restore.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_scriptcode.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_scriptengine.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_scriptfunction.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_scriptnode.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_scriptobject.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_string.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_string_util.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_thread.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_tokenizer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_typeinfo.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dep/angelscript/src/as_variablescope.cpp
	)

set(SP_SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_window.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_renderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_shader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_prop.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_frame.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_render_text.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_shader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_sprite_cache.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_font_cache.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_shader_cache.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt/src/sp_alarm.cpp
	)

set(SIM_SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/sim/src/test_sim.cpp
	)

add_executable(black_telephone main.cpp ${SP_SRCS} ${SIM_SRCS} ${DEP_SRCS} ${GLAD_DEPS} ${ANGELSCRIPT_DEPS} ${BOX2D_DEPS})

set_property(TARGET black_telephone PROPERTY CXX_STANDARD 17)
set_property(TARGET black_telephone PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(black_telephone
	opengl32.lib
	${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL2/lib/SDL2.lib
	${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL2/lib/SDL2main.lib
	${CMAKE_CURRENT_SOURCE_DIR}/dep/freetype/lib/freetype.lib
	)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/dep
	${CMAKE_CURRENT_SOURCE_DIR}/dep/freetype #to avoid having to modify every freetype header
	${CMAKE_CURRENT_SOURCE_DIR}/gestalt
	${CMAKE_CURRENT_SOURCE_DIR}/sim
	)

#Angelscript compiles with /MT
set_target_properties(black_telephone PROPERTIES COMPILE_FLAGS "/MT")

MESSAGE (${CMAKE_CURRENT_SOURCE_DIR})

#install(TARGETS spk DESTINATION bin)