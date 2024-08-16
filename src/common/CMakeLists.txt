# Create a library from the source files
add_library(common
    hash_table.cpp
    file_io.cpp
    query_processor.cpp
)

# Include headers in this directory
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})