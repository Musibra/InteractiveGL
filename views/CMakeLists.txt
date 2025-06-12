set(SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.h
)


target_sources(${PROJECT_NAME}
        PRIVATE
        ${SOURCE_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
