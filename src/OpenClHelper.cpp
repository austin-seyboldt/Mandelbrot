#include "OpenClHelper.h"

cl::Program createProgram(const std::string &file) {
  std::vector<cl::Platform> platforms;
  cl::Platform::get(&platforms);
  _ASSERT(platforms.size() > 0);
  // Get the first platform
  auto platform = platforms.front();

  // Get all the devices
  std::vector<cl::Device> devices;
  platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
  _ASSERT(devices.size() > 0);

  // Get the first device - in this case - only one gpu
  auto device = devices.front();

  // Get the source file for the kernel
  std::ifstream testFile(file);
  std::string testString(std::istreambuf_iterator<char>(testFile),
                         (std::istreambuf_iterator<char>()));

  cl::Program::Sources sources(
      1, std::make_pair(testString.c_str(), testString.length() + 1));

  // Create a new context with the device
  cl::Context context(device);
  // Make a program with the context and the sources
  cl::Program program(context, sources);

  // Builds the program
  program.build("-cl-std=CL1.1");
  return program;
}