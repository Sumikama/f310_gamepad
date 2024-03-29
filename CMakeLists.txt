cmake_minimum_required(VERSION 3.8)
project(f310_gamepad)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# src　setting
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(smkm_interfaces REQUIRED)
add_executable(f310_gamepad src/f310_gamepad.cpp)
ament_target_dependencies(f310_gamepad rclcpp sensor_msgs smkm_interfaces)
# target_include_directories(f310_gamepad
#   PUBLIC include
# )
install(TARGETS
  f310_gamepad
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch files.
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()