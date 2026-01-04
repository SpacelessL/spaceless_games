cmake_minimum_required(VERSION 3.20)
project(spaceless_backend)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 11)

add_subdirectory(dicer)

find_package(drogon CONFIG REQUIRED)
find_package(TBB CONFIG REQUIRED)

add_executable(spaceless_backend
    dicer_games/ATO.hpp
    dicer_games/ATO.cpp
    dicer_games/Oathsworn.hpp
    dicer_games/Oathsworn.cpp
    server.cpp
)

target_include_directories(spaceless_backend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(spaceless_backend PRIVATE Drogon::Drogon dicer TBB::tbb)
