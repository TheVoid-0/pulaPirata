# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (Tutorials)

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


# Tutorial 2
add_executable(tutorial02_red_triangle 
	tutorial02_red_triangle/tutorial02.cpp
	common/shader.cpp
	common/shader.hpp
	
	tutorial02_red_triangle/SimpleFragmentShader.fragmentshader
	tutorial02_red_triangle/SimpleVertexShader.vertexshader
)
target_link_libraries(tutorial02_red_triangle
	${ALL_LIBS}
)

# TransformacaoGeometricaExemplo
add_executable(TransformacaoGeometricaExemplo
	TransformacaoGeometricaExemplo/transformacao2D.cpp
	common/shader.cpp
	common/shader.hpp

	TransformacaoGeometricaExemplo/SimpleFragmentShader.fragmentshader
	TransformacaoGeometricaExemplo/SimpleVertexShader.vertexshader
)
target_link_libraries(TransformacaoGeometricaExemplo
	${ALL_LIBS}
)

# animacao
add_executable(animacao
	animacao/animacao.cpp
	common/shader.cpp
	common/shader.hpp

	animacao/SimpleFragmentShader.fragmentshader
	animacao/SimpleVertexShader.vertexshader
)
target_link_libraries(animacao
	${ALL_LIBS}
)

# template_prova1
add_executable(template_prova1
	template_prova1/keyboardMouse.cpp
	common/shader.cpp
	common/shader.hpp

	template_prova1/SimpleFragmentShader.fragmentshader
	template_prova1/SimpleVertexShader.vertexshader
)
target_link_libraries(template_prova1
	${ALL_LIBS}
	ANTTWEAKBAR_116_OGLCORE_GLFW
)


# Bullet Hell
add_executable(bullet_hell 
    bullet_hell/bullet_hell.cpp
    common/shader.cpp
    common/shader.hpp
    common/text2D.cpp
    common/texture.cpp

    bullet_hell/SimpleVertexShader.vertexshader
    bullet_hell/SimpleFragmentShader.fragmentshader
)
target_link_libraries(bullet_hell
    ${ALL_LIBS}
    ANTTWEAKBAR_116_OGLCORE_GLFW
)


# gato
add_executable(gato
	gato/gato.cpp
	common/shader.cpp
	common/shader.hpp

	gato/SimpleFragmentShader.fragmentshader
	gato/SimpleVertexShader.vertexshader
)
target_link_libraries(gato
	${ALL_LIBS}
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

# Xcode and Visual working directories
set_target_properties(animacao PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/animacao/")
create_target_launcher(animacao WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/animacao/")

# Xcode and Visual working directories
set_target_properties(template_prova1 PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/template_prova1/")
create_target_launcher(template_prova1 WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/template_prova1/")

# Xcode and Visual working directories
set_target_properties(bullet_hell PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bullet_hell/")
create_target_launcher(bullet_hell WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bullet_hell/")

# Xcode and Visual working directories
set_target_properties(gato PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/gato/")
create_target_launcher(gato WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/gato/")


	
# Xcode and Visual working directories
set_target_properties(tutorial02_red_triangle PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/")
create_target_launcher(tutorial02_red_triangle WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/")
create_default_target_launcher(tutorial02_red_triangle WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/") # tut 1 is not the default or people would complain that tut 2 doesn't work

add_executable(diovanna_prova1
	diovanna_prova1/keyboardMouse.cpp
	common/shader.cpp
	common/shader.hpp

	diovanna_prova1/SimpleFragmentShader.fragmentshader
	diovanna_prova1/SimpleVertexShader.vertexshader
)
target_link_libraries(diovanna_prova1
	${ALL_LIBS}
	ANTTWEAKBAR_116_OGLCORE_GLFW
)

# Xcode and Visual working directories
set_target_properties(diovanna_prova1 PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/diovanna_prova1/")
create_target_launcher(diovanna_prova1 WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/diovanna_prova1/")


# fps
add_executable(fps
	fps/template.cpp
	common/shader.cpp
	common/shader.hpp

	fps/SimpleFragmentShader.fragmentshader
	fps/SimpleVertexShader.vertexshader
)
target_link_libraries(fps
	${ALL_LIBS}
)

# Xcode and Visual working directories
set_target_properties(fps PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/fps/")
create_target_launcher(fps WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/fps/")