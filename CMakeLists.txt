cmake_minimum_required(VERSION 3.24)
project(HaGameLite)

# set(CMAKE_TOOLCHAIN_FILE /home/henry/emsdk/)
if(EMSCRIPTEN)
    MESSAGE("BUILDING FOR THE WEB")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
# pkg_search_module(GL REQUIRED gl)

set(CMAKE_CXX_STANDARD 20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
MESSAGE("${CMAKE_CURRENT_LIST_DIR}")
find_package(HaGame2 REQUIRED)

add_executable(HaGameLite main.cpp)
target_include_directories(HaGameLite PUBLIC ${HAGAME2_INCLUDE_DIR})
target_link_libraries(HaGameLite ${HAGAME2_LIBRARY})
target_link_libraries(HaGameLite ${GLFW_LIBRARIES})
target_link_libraries(HaGameLite ${OPENGL_LIBRARIES})

# set(CMAKE_TOOLCHAIN_FILE /home/henry/emsdk/)
if(EMSCRIPTEN)
    set_target_properties(HaGameLite PROPERTIES LINK_FLAGS "-DCMAKE_EXE_LINKER_FLAGS=-s -sMAX_WEBGL_VERSION=2 --preload-file ../assets")
endif()