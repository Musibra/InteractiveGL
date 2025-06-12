set(SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Canvas.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Canvas.h

        ${CMAKE_CURRENT_SOURCE_DIR}/Background.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Background.h

        ${CMAKE_CURRENT_SOURCE_DIR}/Triangle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Triangle.h

        ${CMAKE_CURRENT_SOURCE_DIR}/CanvasOverlayButton.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CanvasOverlayButton.h
)


target_sources(${PROJECT_NAME}
        PRIVATE
        ${SOURCE_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
