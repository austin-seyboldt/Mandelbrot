#pragma once
#include <CL/cl.hpp>
#include <string>
#include <fstream>

cl::Program createProgram(const std::string& file);