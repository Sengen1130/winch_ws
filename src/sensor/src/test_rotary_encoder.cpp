#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <sstream>
#include <signal.h>
#include "rotary_encoder.hpp"

ros::Publisher pub;
re_decoder *ref;


void sigHandler(int sig){
  ROS_INFO("OVER");
  usleep(10000);
  ref->re_cancel();
  gpioTerminate();
  ros::shutdown();
}


void callback(int way)
{
  //エンコーダ値の初期化
  static int pos = 0;
  std_msgs::Int32 length;
  pos += way;
  length.data = - pos;
  pub.publish(length);
}

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "rotary_encoder_winch1");
  ros::NodeHandle node;
  signal(SIGINT, sigHandler);
  
  pub =  node.advertise<std_msgs::Int32>("count_winch1",10);

  if (gpioInitialise() < 0) return 1;  
  re_decoder dec(5, 6, callback);
  ref = & dec;
  ros::Rate r(1000);

  while(ros::ok()){
   ros::spinOnce();
   r.sleep();
  }
  dec.re_cancel();
  gpioTerminate();
}
