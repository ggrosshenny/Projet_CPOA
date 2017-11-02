cmake_minimum_required(VERSION 3.0)

project(test_image LANGUAGES CXX)

add_executable(test_img2D test_img2D.cpp)

target_include_directories(test_img2D PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(test_img2D image )

