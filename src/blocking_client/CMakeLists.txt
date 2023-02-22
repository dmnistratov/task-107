find_package(Boost 1.36.0)
find_package (Threads)

include_directories(${Boost_INCLUDE_DIRS})

add_executable (client client.cpp)
target_link_libraries (client Threads::Threads)
target_link_libraries(client ${Boost_LIBRARIES})