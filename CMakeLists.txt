cmake_minimum_required (VERSION 3.20)

project (forward_list LANGUAGES C VERSION 2.0)

#include(CTest)
#enable_testing()

include(${CMAKE_SOURCE_DIR}/cmake/option.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/CompilerWarnings.cmake)

set_choice (CMAKE_BUILD_TYPE "Debug;Release;MinSizeRel;RelWithDebInfo" "Debug" "Choose type of build")

set (SRCS
	src/forward_list.c
)

set (HEADERS
    include/forward_list.h
)

set_sanitizer()

option(BUILD_TEST "Build exemple" ON)
if (BUILD_TEST)
    add_subdirectory(${CMAKE_SOURCE_DIR}/test)
endif()

option(BUILD_DOC "Build documentation" ON)
if (BUILD_DOC)
    add_subdirectory(${CMAKE_SOURCE_DIR}/docs)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

set (CMAKE_C_STANDARD 17)
set (CMAKE_C_STANDARD_REQUIRED ON)

add_library (${PROJECT_NAME} STATIC ${SRCS} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${HEADERS})
set_target_warnings(${PROJECT_NAME})

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME} ARCHIVE)
install(TARGETS ${PROJECT_NAME} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# generate a DEB when cpack is run
SET(CPACK_GENERATOR "DEB")
SET(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
SET(CPACK_SET_DESTDIR TRUE)
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "quentin.horgues@outlook.fr")
SET(CPACK_PACKAGE_VERSION_MAJOR "2")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6")
SET(CPACK_PACKAGE_VENDOR "Quentin Horgues")
    

include(CPack)
