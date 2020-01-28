project(debruijn)
set(CMAKE_CXX_STANDARD 17)
add_executable(debruijn main.cpp)
install(TARGETS debruijn RUNTIME DESTINATION bin)
