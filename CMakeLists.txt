# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (pula_pirata)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# pula_pirata
add_executable(pula_pirata
	pula_pirata/pula_pirata.cpp
	pula_pirata/programHandler.cpp
	pula_pirata/programHandler.hpp
	pula_pirata/classes/Obj.cpp
	pula_pirata/classes/Obj.h
	pula_pirata/classes/Light.cpp
	pula_pirata/classes/Light.h
	pula_pirata/classes/Player.h
	pula_pirata/classes/Player.cpp
	pula_pirata/classes/Match.h
	pula_pirata/classes/Match.cpp
	pula_pirata/classes/Hole.cpp
	pula_pirata/classes/Hole.h
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/text2D.hpp
	common/text2D.cpp

	pula_pirata/TransformVertexShader.vertexshader
	pula_pirata/TextureFragmentShader.fragmentshader
)
target_link_libraries(pula_pirata
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(pula_pirata PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/pula_pirata/")
create_target_launcher(pula_pirata WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/pula_pirata/")