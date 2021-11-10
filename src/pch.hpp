#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"
#include "vertexBufferLayout.hpp"
#include "vertexArray.hpp"
#include "shader.hpp"
#include "renderer.hpp"
#include "cellGrid.hpp"
#include "boid.hpp"
#include "flock.hpp"