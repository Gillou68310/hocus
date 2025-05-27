cmake_minimum_required(VERSION 3.30)
project(hocus C)
include(FetchContent)

function(include_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG        ${gitTag}
            GIT_SHALLOW    TRUE
            GIT_PROGRESS   TRUE
    )

    FetchContent_MakeAvailable(${libName})
endfunction()

find_package(SDL3 QUIET)
if (NOT SDL3_FOUND)
    message(STATUS "Getting SDL3 from Github")
    include_dependency(SDL3 https://github.com/libsdl-org/SDL.git release-3.2.14)
else()
    message(STATUS "Using local SDL3")
endif()

find_package(SDL3_ttf QUIET)
if (NOT SDL3_ttf_FOUND)
    message(STATUS "Getting SDL3_ttf from Github")
    include_dependency(SDL3_ttf https://github.com/libsdl-org/SDL_ttf release-3.2.2)
else()
    message(STATUS "Using local SDL3_ttf")
endif()

set(SOURCE_FILES
    ../src/design.c
    ../src/features.c
    ../src/fileio.c
    ../src/globals.c
    ../src/gr.c
    ../src/hocus.c
    ../src/joystick.c
    ../src/menus.c
    ../src/play.c
    ../src/play2.c
    ../src/soundfx.c
    ../src/util.c
    port.c)

add_executable(hocus ${SOURCE_FILES})

target_include_directories(hocus PRIVATE
    ${SDL3_INCLUDE_DIRS}
    ${SDL3_ttf_INCLUDE_DIRS}
    ../include
    .)

target_link_libraries(hocus PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)

if (WIN32)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT hocus)
    target_compile_definitions(hocus PRIVATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE)
    add_custom_command(
            TARGET hocus POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                "$<TARGET_FILE:SDL3::SDL3>" "$<TARGET_FILE_DIR:hocus>"
                "$<TARGET_FILE:SDL3_ttf::SDL3_ttf>" "$<TARGET_FILE_DIR:hocus>"
            VERBATIM
    )
endif()
