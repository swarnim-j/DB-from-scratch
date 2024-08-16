cmake_minimum_required(VERSION 3.10)
project(DatabaseEngine VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source directory
add_subdirectory(src/common)

# Add the main executable
add_executable(database_engine main.cpp)
target_link_libraries(database_engine PRIVATE common)

# Add the test executables
add_executable(test_file_io tests/test_file_io.cpp)
target_link_libraries(test_file_io PRIVATE common)

add_executable(test_query_processor tests/test_query_processor.cpp)
target_link_libraries(test_query_processor PRIVATE common)

add_executable(test_hash_table tests/test_hash_table.cpp)
target_link_libraries(test_hash_table PRIVATE common)