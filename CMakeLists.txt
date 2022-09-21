cmake_minimum_required(VERSION 3.24)
project(
  dpp_owo_bot
  VERSION 0.1.0
  LANGUAGES CXX)
# C++ 17 ISO standard
set(CMAKE_CXX_STANDARD 17)
# Require standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set release build
set(CMAKE_BUILD_TYPE Release)
# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
# Add DPP subdirectory
set(DPP_DIR "${PROJECT_SOURCE_DIR}/libs/DPP")
add_subdirectory("${DPP_DIR}")
# create executable from src/
include_directories("${PROJECT_SOURCE_DIR}/include")
file(GLOB_RECURSE PROJECT_GLOBBED_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} "${PROJECT_GLOBBED_SOURCES}")
# Link DPP
target_link_libraries(${PROJECT_NAME} dpp)
# Include DPP
target_include_directories(${PROJECT_NAME} PRIVATE "${DPP_DIR}/include")
