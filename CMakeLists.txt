cmake_minimum_required(VERSION 3.0.0)
project(game VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)
include(CTest)
enable_testing()


find_library(EASYX_LIBRARY
             NAMES easyx
             PATHS lib/easyx)

add_executable(game app/main.cpp src/character.cpp src/gamerun.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include/)
target_link_libraries(game gdiplus)

include_directories(${CMAKE_SOURCE_DIR}/lib/easyx/include/)
target_link_libraries(game ${CMAKE_SOURCE_DIR}/lib/easyx/lib64/libeasyx.a)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
