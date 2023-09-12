cmake_minimum_required(VERSION 3.15)

project(window_manager VERSION 1.0)

add_subdirectory(src)

add_executable(window_manager main.cpp)
target_link_libraries(window_manager src)

target_link_libraries(window_manager -lX11)

target_include_directories(window_manager PUBLIC
                        "${PROJECT_BINARY_DIR}"
                        "${PROJECT_BINARY_DIR}/include"
                        )