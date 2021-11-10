add_executable(${PROJECT_NAME} cellGrid.cpp flock.cpp indexBuffer.cpp life.cpp renderer.cpp shader.cpp vertexArray.cpp vertexBuffer.cpp)

target_link_libraries(${PROJECT_NAME} glfw glad)
target_precompile_headers(${PROJECT_NAME} PUBLIC pch.hpp)