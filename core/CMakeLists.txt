set(LIBRARY_NAME core)

set(SOURCES
    stack.cpp
    frame.cpp
    machine.cpp
)

add_library(${LIBRARY_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARY_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE builder)