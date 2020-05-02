#include <ros/ros.h>
#include <math.h>
#include <iostream>    
#include <geometry_msgs/Vector3.h>
    
double winchPos1[] = {0, 0, 0};
double winchPos2[] = {5.0, 0, 0};
double winchPos3[] = {2.5, 5.0, 0};
geometry_msgs::Vector3 wireLen;
geometry_msgs::Vector3 pos;

geometry_msgs::Vector3 foward_kinematics(){
    pos.x = (pow(wireLen.x, 2) - pow(wireLen.y, 2) + pow(winchPos2[0], 2)) / (2 * winchPos2[0]);
    pos.y = (winchPos2[0] * pow(wireLen.y, 2) - winchPos2[0] * pow(wireLen.z, 2) + winchPos2[0] * pow(winchPos3[1], 2) + winchPos2[0] * pow(winchPos3[0], 2) - pow(winchPos2[0], 3) + (winchPos2[0] - winchPos3[0]) * (pow(wireLen.x, 2) - pow(wireLen.y, 2) + pow(winchPos2[0], 2))) / (2 * winchPos2[0] * winchPos3[1]);
    pos.z = sqrt(abs(pow(wireLen.x, 2) - (pow(pos.x, 2) + pow(pos.y, 2))));
    
    std::cout << pos.x <<"\n";
    std::cout << pos.y <<"\n";
    std::cout << pos.z <<"\n";
    
    return pos;
}

geometry_msgs::Vector3 inverse_kinematics(){
	wireLen.x = sqrt(pow((pos.x - winchPos1[0]), 2) + pow((pos.y - winchPos1[1]), 2) + pow((pos.z - winchPos1[2]), 2));
	wireLen.y = sqrt(pow((pos.x - winchPos2[0]), 2) + pow((pos.y - winchPos2[1]), 2) + pow((pos.z - winchPos2[2]), 2));
	wireLen.z = sqrt(pow((pos.x - winchPos3[0]), 2) + pow((pos.y - winchPos3[1]), 2) + pow((pos.z - winchPos3[2]), 2));
	
	std::cout << wireLen.x << "\n";
	std::cout << wireLen.y << "\n";
	std::cout << wireLen.z << "\n";
	
    return wireLen;
}

int main(int argc, char** argv){
    ros::init(argc, argv, "test_kinematics");
    
    pos.x = 2.5;
    pos.y = 1;
    pos.z = 0.5;
    
    geometry_msgs::Vector3 length = inverse_kinematics();
    geometry_msgs::Vector3 position = foward_kinematics();
}

   
