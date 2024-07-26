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

add_executable(${PROJECT_NAME} ${SRC})
