find_package(Boost 1.36.0)

include_directories(${Boost_INCLUDE_DIRS})

add_executable (server server.cpp)
target_link_libraries(server ${Boost_LIBRARIES})