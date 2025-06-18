cmake_minimum_required(VERSION 3.15)
project(PaifuViewer VERSION 0.0.1)

# encode
if (MSVC)
    add_compile_options(/utf-8)
else()
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()
# lang
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# src
aux_source_directory(src/external SOURCES) #TODO: use target_sources() instead
aux_source_directory(src SOURCES) #TODO: use target_sources() instead
add_executable(${PROJECT_NAME} ${SOURCES})
# headers
target_include_directories(${PROJECT_NAME} PUBLIC include)
# package
find_package(raylib REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_INCLUDE_DIRS}/extras)
find_package(nlohmann_json  REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib nlohmann_json::nlohmann_json)
# env
set(RES_DIR ${CMAKE_SOURCE_DIR}/res)
file(COPY ${RES_DIR} DESTINATION ${CMAKE_BINARY_DIR})
target_compile_definitions(${PROJECT_NAME} PRIVATE RES_DIR="${RES_DIR}")
