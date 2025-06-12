set(SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/ShaderLoader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ShaderLoader.h
)


target_sources(${PROJECT_NAME}
        PRIVATE
        ${SOURCE_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
