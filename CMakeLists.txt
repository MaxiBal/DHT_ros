cmake_minimum_required(VERSION 3.0.2)
project(DHT_ROS)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

catkin_package(
 INCLUDE_DIRS include
 CATKIN_DEPENDS roscpp message_filters sensor_msgs nav_msgs geometry_msgs 
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  lib/DHT-sensor-lib
)



add_executable(DHT_ROS 
  src/main.cpp
  lib/DHT-sensor-lib/DHT.cpp
  lib/DHT-sensor-lib/DHT_U.cpp
)