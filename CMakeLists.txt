cmake_minimum_required (VERSION 3.20)

project (forward_list LANGUAGES C VERSION 1.0)

include(CTest)
enable_testing()

include(${CMAKE_SOURCE_DIR}/cmake/option.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/CompilerWarnings.cmake)

set_choice (CMAKE_BUILD_TYPE "Debug;Release;MinSizeRel;RelWithDebInfo" "Debug" "Choose type of build")

set (SRCS
	src/forward_list.c
)

set (HEADERS
    include/forward_list.h
)

if (BUILD_TESTING)
    add_subdirectory(${CMAKE_SOURCE_DIR}/test)
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

SET(CPACK_BINARY_DEB TRUE)
SET(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
SET(CPACK_SET_DESTDIR TRUE)
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "quentin.horgues@outllok.fr")

SET(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6")
SET(CPACK_PACKAGE_VENDOR "Horgues")
# make postinst run after install                                                #

include(CPack)