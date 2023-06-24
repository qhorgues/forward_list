cmake_minimum_required (VERSION 3.20)

project (Test_forward_list LANGUAGES C VERSION 2.0)

include (${CMAKE_SOURCE_DIR}/cmake/CompilerWarnings.cmake)
include (${CMAKE_SOURCE_DIR}/cmake/option.cmake)

set_choice (CMAKE_BUILD_TYPE "Debug;Release;MinSizeRel;RelWithDebInfo" "Debug" "Choose type of build")

set (SRCS
	main.c
)

set (HEADERS
)

set_sanitizer()
include_directories(${CMAKE_SOURCE_DIR}/include)

set (CMAKE_C_STANDARD 17)
set (CMAKE_C_STANDARD_REQUIRED ON)

add_executable (${PROJECT_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME} forward_list)
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src/forward_list")
set_target_warnings(${PROJECT_NAME})