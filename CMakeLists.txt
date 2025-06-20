cmake_minimum_required(VERSION 3.15)
project(PaifuViewer VERSION 0.0.1)

# encode
if (MSVC)
    add_compile_options(/utf-8)
else ()
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif ()
# lang
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# src
aux_source_directory(src SOURCES) #TODO: use target_sources() instead
add_executable(${PROJECT_NAME} ${SOURCES})
# headers
target_include_directories(${PROJECT_NAME} PUBLIC include)
# package
include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
)
FetchContent_Declare(
        raygui
        URL https://github.com/raysan5/raygui/archive/refs/heads/master.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_Declare(
        tinyfiledialogs
        GIT_REPOSITORY https://git.code.sf.net/p/tinyfiledialogs/code
        GIT_TAG master
)
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)
FetchContent_MakeAvailable(raylib)
FetchContent_MakeAvailable(raygui)
FetchContent_MakeAvailable(tinyfiledialogs)
include_directories(${raygui_SOURCE_DIR}/src)
include_directories(
        ${tinyfiledialogs_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
        raylib
        nlohmann_json::nlohmann_json
)
target_sources(${PROJECT_NAME} PRIVATE ${tinyfiledialogs_SOURCE_DIR}/tinyfiledialogs.c)
# env
set(RES_DIR ${CMAKE_SOURCE_DIR}/res)
file(COPY ${RES_DIR} DESTINATION ${CMAKE_BINARY_DIR})
target_compile_definitions(${PROJECT_NAME} PRIVATE RES_DIR="${RES_DIR}")
