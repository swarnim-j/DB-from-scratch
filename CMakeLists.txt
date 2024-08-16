cmake_minimum_required(VERSION 3.10)
project(NetworkedDatabase)

set(CMAKE_CXX_STANDARD 17)

# Add executable for the server
add_executable(server src/server/main.cpp)
target_include_directories(server PRIVATE include/server include/common)

# Add executable for the client
add_executable(client src/client/main.cpp)
target_include_directories(client PRIVATE include/client include/common)

# Add common library
add_library(common src/common/database.cpp src/common/protocol.cpp)
target_include_directories(common PRIVATE include/common)
target_link_libraries(server common)
target_link_libraries(client common)