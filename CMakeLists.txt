cmake_minimum_required(VERSION 4.0.1 FATAL_ERROR)

set(PROJECT_NAME SpesEngine)
project(${PROJECT_NAME})

add_subdirectory(SpesEngineCore)
add_subdirectory(SpesEngineEditor)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SpesEngineEditor)