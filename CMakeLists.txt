cmake_minimum_required(VERSION 3.12...3.25)

project(
  pascha-cli
  VERSION 2.0
  LANGUAGES CXX
)

# Only in main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  set(CMAKE_CXX_EXTENSIONS OFF)
  set(CMAKE_CXX_STANDARD 20)

  # For folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing
  option(BUILD_TESTING "Build tests" OFF)
  include(CTest)
endif()

include(FetchContent)

# Statically build for Windows
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(BUILD_FOR_WINDOWS TRUE)
endif()
option(STATIC_BUILD "Build statically" ${BUILD_FOR_WINDOWS})

if (STATIC_BUILD AND BUILD_FOR_WINDOWS)
  set(CMAKE_EXE_LINKER_FLAGS "-static -mconsole")
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" CONFIG)
  set(CMAKE_BUILD_SHARED_LIBS OFF)
endif()

# Build library
add_subdirectory(src)

# Test only in main project
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR PASCHA_GUI_BUILD_TESTING)
    AND BUILD_TESTING)
  add_subdirectory(test)
endif()

add_subdirectory(app)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "pascha")

install(TARGETS pascha-cli)

install(FILES pascha.1.gz DESTINATION ${CMAKE_INSTALL_PREFIX}/share/man/man1)

add_custom_target(uninstall COMMAND xargs rm -vf < install_manifest.txt)
