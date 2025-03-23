cmake_minimum_required(VERSION 3.26)
project(Projekt)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.1.1
)
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 2.5.1
)

FetchContent_MakeAvailable(fmt)


add_executable(Projekt main.cpp Kolo.cpp Pole.cpp Graf.cpp Plansza.cpp)


target_link_libraries(
        Projekt
        sfml-graphics
        sfml-window
        sfml-system
        fmt)


IF (WIN32)
    add_custom_command(TARGET Projekt POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:PJC> $<TARGET_FILE_DIR:PJC>
            COMMAND_EXPAND_LISTS
    )
ENDIF ()
