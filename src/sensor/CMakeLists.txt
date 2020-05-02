cmake_minimum_required(VERSION 2.8.3)
project(sensor)

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
    adder.msg
 )
 
#dd_compile_options(-std=c++s11)

## Generate actions in the 'action' folder
generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package(
   INCLUDE_DIRS include
   LIBRARIES sensor
   CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
   #DEPENDS system_lib
)

###########
## Build ##
###########

## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)



# add_executable(${PROJECT_NAME}_node src/sensor_node.cpp)
 add_executable(rotary_encoder_winch1 
  src/test_rotary_encoder.cpp
  src/rotary_encoder.hpp
  src/rotary_encoder.cpp
  )
 add_executable(calculator_winch1
  src/calculator_winch1.cpp
  )
  
#add_dependencies(measure_encoder_winch1 ${$PEOJECT_NAME}_EXPORTED_TARGETS}${catkin_EXPORTED_TARGETS})

 target_link_libraries(rotary_encoder_winch1
   ${catkin_LIBRARIES}
 )
 target_link_libraries(calculator_winch1
   ${catkin_LIBRARIES}
 )
 target_link_libraries(rotary_encoder_winch1
  pigpio
 )
 target_link_libraries(rotary_encoder_winch1 
  rt
 )
 target_link_libraries(calculator_winch1
  m
 ) 



