cmake_minimum_required(VERSION 4.0.1 FATAL_ERROR)

set(EDITOR_PROJECT_NAME SpesEngineEditor)

add_executable(${EDITOR_PROJECT_NAME}
	src/main.c
)

target_link_libraries(${EDITOR_PROJECT_NAME} SpesEngineCore)
target_compile_features(${EDITOR_PROJECT_NAME} PUBLIC cxx_std_23)

set_target_properties(${EDITOR_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUR_DIRECTORY ${CMKAE_BINARY_DIR}/bin/)