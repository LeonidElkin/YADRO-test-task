add_subdirectory(lib)
include_directories(lib)
add_executable(tape-test-task app.cpp)
target_link_libraries(tape-test-task PUBLIC Tape)