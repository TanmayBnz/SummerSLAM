cmake_minimum_required(VERSION 3.5)
project(environment)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Required dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

# Include directories
include_directories(
  include
  ${OpenCV_INCLUDE_DIRS}
)

# Add the executable
add_executable(environment_node src/environment.cpp)

# Link libraries and dependencies
ament_target_dependencies(
  environment_node
  rclcpp
  sensor_msgs
  std_msgs
  cv_bridge
  OpenCV
)

# Install the node
install(TARGETS
  environment_node
  DESTINATION lib/${PROJECT_NAME}
)
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}/
)

install(DIRECTORY utils/
  DESTINATION share/${PROJECT_NAME}/utils
)


# Export package
ament_package()
