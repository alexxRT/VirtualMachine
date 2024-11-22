set(LIBRARY_NAME builder)

set(SOURCES 
    builder.cpp
)

add_library(${LIBRARY_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARY_NAME})