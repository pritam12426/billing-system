cmake_minimum_required(VERSION 3.30)

project(
  "shop"
  VERSION 0.1.0
  DESCRIPTION "Small Shop billing system for Project"
  HOMEPAGE_URL "https://github.com/pritam12426/utf-8-text-editor"
  LANGUAGES CXX)

# configure_file(./include/shop_config.h.in ./include/shop_config.h)
# target_include_directories(thing ${CMAKE_CURRENT_LIST_FILE}/include)

set(SRC "src/main.cpp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fansi-escape-codes")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_STANDARD 20)
add_executable(${PROJECT_NAME} ${SRC})

find_package(SQLite3)
include_directories(${SQLite3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SQLite3_LIBRARIES})
message(STATUS ${SQLite3_LIBRARIES})
