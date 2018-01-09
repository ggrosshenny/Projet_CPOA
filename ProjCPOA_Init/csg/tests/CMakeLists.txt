cmake_minimum_required(VERSION 3.0)

project(test_csg LANGUAGES CXX)

add_executable(test_BoundingBox test_BoundingBox.cpp)

target_include_directories(test_BoundingBox PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(test_BoundingBox csg )


add_executable(test_CsgPrimitive test_CsgPrimitive.cpp)

target_include_directories(test_CsgPrimitive PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(test_CsgPrimitive csg )

add_executable(test_CsgOperation test_CsgOperation.cpp)

target_include_directories(test_CsgOperation PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(test_CsgOperation csg )

add_executable(test_CsgTree test_CsgTree.cpp)

target_include_directories(test_CsgTree PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(test_CsgTree csg )
