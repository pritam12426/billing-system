cmake_minimum_required(VERSION 3.30)

project(
	"shop" 
	VERSION 0.1.0
	DESCRIPTION "Small Shop billing system for Project"
	HOMEPAGE_URL "https://github.com/pritam12426/utf-8-text-editor"
	LANGUAGES CXX
)

set(SRC "src/main.cpp")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_executable(${PROJECT_NAME} ${SRC})

find_package (SQLite3)
if (SQLITE3_FOUND)
	include_directories(${SQLITE3_INCLUDE_DIRS})
	target_link_libraries (${PROJECT_NAME} ${SQLITE3_LIBRARIES})
endif (SQLITE3_FOUND)

