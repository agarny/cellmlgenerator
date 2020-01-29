cmake_minimum_required(VERSION 3.14)

project(CellMLGenerator)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(libCellML REQUIRED)

set(CMAKE_CXX_STANDARD 11)

include_directories(
    ${LIBCELLML_INCLUDE_DIR}
    ${LIBCELLML_MODULE_DIR}
)

add_executable(${CMAKE_PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${LIBCELLML_LIBRARY}
)
