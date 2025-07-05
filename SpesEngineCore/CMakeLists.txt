cmake_minimum_required(VERSION 4.0.1 FATAL_ERROR)

set(ENGINE_PROJECT_NAME SpesEngineCore)

set(ENGINE_PUBLIC_INCLUDES
	includes/SpesEngineCore/Log.h
	includes/SpesEngineCore/Application.h
)


set (MATH_INCLUDES
	includes/Mathemathics/vec3_float.h
	includes/Mathemathics/mat4_float.h
	includes/Mathemathics/some_func.h
)

set (MATH_SRC
	src/Mathemathics/vec3_float.c
	src/Mathemathics/mat4_float.c
	src/Mathemathics/some_func.c
)


set(ENGINE_PRIVATE_INCLUDES
	includes/SpesEngineCore/Window.h
	includes/SpesEngineCore/ShaderProgram.h
	includes/SpesEngineCore/Events.h
	includes/SpesEngineCore/EventsData.h
	includes/SpesEngineCore/Camera.h
	
	${MATH_INCLUDES}
)

set(ENGINE_PRIVATE_SOURCES
	src/SpesEngineCore/Application.c
	src/SpesEngineCore/Window.c
	src/SpesEngineCore/ShaderProgram.c
	src/SpesEngineCore/Events.c
	src/SpesEngineCore/Camera.c
	
	${MATH_SRC}
)

set(ENGINE_ALL_SOURCES
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PRIVATE_INCLUDES}
	${ENGINE_PRIVATE_SOURCES}
)

add_library(${ENGINE_PROJECT_NAME} STATIC
	${ENGINE_ALL_SOURCES}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
	${ENGINE_ALL_SOURCES}
)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes)
target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE src)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_23)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)

add_subdirectory(../external/assimp ${CMAKE_CURRENT_BINARY_DIR}/assimp)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE assimp)

