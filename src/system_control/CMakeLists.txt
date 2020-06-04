cmake_minimum_required(VERSION 2.8.3)
project(system_control)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

## Generate messages in the 'msg' folder
add_message_files(
    FILES
    Timing.msg
    adder.msg
    Record.msg
 )


## Generate actions in the 'action' folder
generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package(
   INCLUDE_DIRS include
   LIBRARIES system_control
   CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
   #DEPENDS system_lib
)

## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

# add_executable(${PROJECT_NAME}_node src/sensor_node.cpp)
 add_executable(position_control_winch1
  src/position_control_winch1.cpp
  include/computed_torque.hpp
  include/digital_filter.hpp
  include/digital_to_analog.hpp
  include/interpolation_function.hpp
  include/kinematics.hpp
  include/position_control_winch.hpp
  )
  
#add_dependencies(measure_encoder_winch1 ${$PEOJECT_NAME}_EXPORTED_TARGETS}${catkin_EXPORTED_TARGETS})
 target_link_libraries(position_control_winch1
   ${catkin_LIBRARIES}
 )

# add_executable(${PROJECT_NAME}_node src/sensor_node.cpp)
 add_executable(constant_velocity_control
  src/constant_velocity_control.cpp
  include/computed_torque.hpp
  include/digital_filter.hpp
  include/digital_to_analog.hpp
  include/interpolation_function.hpp
  include/kinematics.hpp
  include/constant_velocity_control.hpp
  )
  
#add_dependencies(measure_encoder_winch1 ${$PEOJECT_NAME}_EXPORTED_TARGETS}${catkin_EXPORTED_TARGETS})
 target_link_libraries(constant_velocity_control
   ${catkin_LIBRARIES}
 )

# add_executable(${PROJECT_NAME}_node src/sensor_node.cpp)
 add_executable(x_axis_position_control
  src/x_axis_position_control.cpp
  include/computed_torque.hpp
  include/digital_filter.hpp
  include/digital_to_analog.hpp
  include/interpolation_function.hpp
  include/kinematics.hpp
  include/x_axis_position_control.hpp
  )
  
#add_dependencies(measure_encoder_winch1 ${$PEOJECT_NAME}_EXPORTED_TARGETS}${catkin_EXPORTED_TARGETS})
 target_link_libraries(x_axis_position_control
   ${catkin_LIBRARIES}
 )

 # add_executable(${PROJECT_NAME}_node src/sensor_node.cpp)
 add_executable(test_kinematics
  src/test_kinematics.cpp
  )
  
#add_dependencies(measure_encoder_winch3 ${$PEOJECT_NAME}_EXPORTED_TARGETS}${catkin_EXPORTED_TARGETS})
 target_link_libraries(test_kinematics
   ${catkin_LIBRARIES}
 )
 
# add_executable(${PROJECT_NAME}_node src/sensor_node.cpp)
 add_executable(setup_winch1
  src/setup_winch1.cpp
  )
  
#add_dependencies(measure_encoder_winch3 ${$PEOJECT_NAME}_EXPORTED_TARGETS}${catkin_EXPORTED_TARGETS})
 target_link_libraries(setup_winch1
   ${catkin_LIBRARIES}
 )

# add_executable(${PROJECT_NAME}_node src/sensor_node.cpp)
 add_executable(calibrate_1to2
  src/calibrate_1to2.cpp
  )
  
#add_dependencies(measure_encoder_winch3 ${$PEOJECT_NAME}_EXPORTED_TARGETS}${catkin_EXPORTED_TARGETS})
 target_link_libraries(calibrate_1to2
   ${catkin_LIBRARIES}
 )

# add_executable(${PROJECT_NAME}_node src/sensor_node.cpp)
 add_executable(calibrate_1to3
  src/calibrate_1to3.cpp
  )
  
#add_dependencies(measure_encoder_winch3 ${$PEOJECT_NAME}_EXPORTED_TARGETS}${catkin_EXPORTED_TARGETS})
 target_link_libraries(calibrate_1to3
   ${catkin_LIBRARIES}
 )
