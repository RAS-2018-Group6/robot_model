cmake_minimum_required(VERSION 2.8.3)
project(robot_model)

find_package(catkin REQUIRED COMPONENTS roscpp visualization_msgs tf nav_msgs)

catkin_package(
  DEPENDS
  CATKIN_DEPENDS roscpp visualization_msgs tf
)

include_directories(
  include ${catkin_INCLUDE_DIRS}
)


add_executable(base_link_model src/cube_model.cpp)
target_link_libraries(base_link_model ${catkin_LIBRARIES})


add_executable(broadcast_position src/pos_broadcaster.cpp)
target_link_libraries(broadcast_position ${catkin_LIBRARIES})

add_executable(broadcast_odom src/odom_broadcaster.cpp)
target_link_libraries(broadcast_odom ${catkin_LIBRARIES})
