#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <sensor/adder.h>
#include <sstream>
#include <signal.h>
#include <cmath>
#include <sys/time.h>

class Calculator
{
public:
  Calculator()
  {
    ros::NodeHandle node;
    _enco_sub = node.subscribe("count_winch1",1,&Calculator::callback1,this);
    _pote_sub = node.subscribe("two_angles_winch1",1,&Calculator::callback2,this);
  }
  
  void callback1(const std_msgs::Int32 &encoder_msg)
  {
    L = encoder_msg.data;
  }

  void callback2(const sensor::adder &angle_msg)
  {
    double encoder_v;
    encoder_v = (L1 -L2)/0.1;
    int alpha,beta;
    alpha = angle_msg.angle1;
    beta = angle_msg.angle2;
    int xp,yp,zp;
    xp = L*sin(beta);
    yp = L*cos(beta)*cos(alpha);
    //zp = 20000 - L*math.cos(math.radians(self.beta))*math.sin(math.radians(self.alpha));
    zp = L ;
    //ROS_INFO("%d",L);
    //std::cout << encoder_v << std::endl;
    //std::cout << angle_msg.angle2-150 << std::endl;
    std::cout << L << "," << angle_msg.angle1 << "," << angle_msg.angle2 << std::endl;
    L2 = L1;
    L1 = L;
  }

private:
  ros::Subscriber _pote_sub;
  ros::Subscriber _enco_sub;
  int L=0,L1=0,L2=0;
  struct timeval t;
};

int main(int argc, char **argv)
{
  ros::init(argc,argv,"calculator_winch1");
  Calculator calculator;
  ros::spin();
}
