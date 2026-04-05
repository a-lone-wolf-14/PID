cmake_minimum_required(VERSION 3.8)
project(roll_controller)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(yaml-cpp REQUIRED)

# ✅ FIRST define target
add_executable(roll_node
  src/roll_node.cpp
  ert_rtw/roll.cpp
)

# ✅ THEN add include dirs
target_include_directories(roll_node PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/ert_rtw
)

target_link_libraries(roll_node yaml-cpp)

# ✅ dependencies
ament_target_dependencies(roll_node
  rclcpp
  sensor_msgs
  geometry_msgs
  std_msgs
)

# ✅ install
install(TARGETS roll_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()