cmake_minimum_required (VERSION 3.20)

project (Test_forward_list LANGUAGES C)

include (cmake/CompilerWarnings.cmake)
include (cmake/option.cmake)

set_choice (CMAKE_BUILD_TYPE "Debug;Release;MinSizeRel;RelWithDebInfo" "Debug" "Choose type of build")

set (SRCS
	src/main.c
)

set (HEADERS
)

add_executable (${PROJECT_NAME} ${SRCS} ${HEADERS})
set_target_warnings(${PROJECT_NAME})
