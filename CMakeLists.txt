cmake_minimum_required(VERSION 3.28)
project(InteractiveGL)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(thirdparty/wxWidgets)

set(GLAD_DIR ${CMAKE_SOURCE_DIR}/thirdparty/glad)


add_library(glad STATIC ${GLAD_DIR}/glad.c)
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)

set(SOURCES
        main.cpp
        constants.h
)

if (WIN32)
    add_executable(InteractiveGL WIN32 ${SOURCES})
else()
    add_executable(InteractiveGL ${SOURCES})
endif()

# fetch glm library
include(FetchContent)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG        0.9.9.8
)

FetchContent_MakeAvailable(glm)

target_include_directories(InteractiveGL PUBLIC ${GLAD_DIR}/include)
target_include_directories(InteractiveGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(InteractiveGL
        wx::net
        wx::core
        wx::base
        wx::gl
        glad
        glm::glm
)

add_subdirectory(views)
add_subdirectory(gl)
add_subdirectory(fileio)

if (WIN32)
    file(GLOB WX_DLLS "${CMAKE_BINARY_DIR}/thirdparty/wxWidgets/lib/vc_x64_dll/*.dll")
    foreach(DLL ${WX_DLLS})
        add_custom_command(TARGET InteractiveGL POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${DLL}
                $<TARGET_FILE_DIR:InteractiveGL>
        )
    endforeach()
endif()

# copy assets to the build directory
add_custom_command(TARGET InteractiveGL POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:InteractiveGL>/assets
)
