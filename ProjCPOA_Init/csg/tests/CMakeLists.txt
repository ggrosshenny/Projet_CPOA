cmake_minimum_required(VERSION 3.0)

project(test_csg LANGUAGES CXX)

add_executable(test_BoundingBox test_BoundingBox.cpp)

target_include_directories(test_BoundingBox PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(test_BoundingBox csg )

