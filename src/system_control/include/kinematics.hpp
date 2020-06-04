#ifndef KINEMATICS_HPP
#define KINEMATICS_HPP

#include <ros/ros.h>
#include <cmath>

class Kinematics
{
public:
    double winchPos1[3] = {0, 0, 0};     //winch1の設置位置
    double winchPos2[3] = {5.0, 0, 0};   //winch2の設置位置
    double winchPos3[3] = {2.5, 5.0, 0}; //winch3の設置位置
    double wireLen;
    geometry_msgs::Vector3 pos;
    double posX;
    double w2;

    //winch三台での順運動学
    //交点の位置(pos.x, pos.y, pos.zの位置を出力)
    //
    //変数について
    //w1:winch1のワイヤ長さ, w2:winch2のワイヤ長さ, w3:winch3のワイヤ長さ
    //winchPos1:winch1の位置, winchPos2:winch2の位置, winchPos3:winch3の位置
    geometry_msgs::Vector3 foward_kinematics(double w1, double w2, double w3)
    {
        pos.x = (pow(w1, 2) - pow(w2, 2) + pow(winchPos2[0], 2)) / (2 * winchPos2[0]);
        pos.y = (winchPos2[0] * pow(w2, 2) - winchPos2[0] * pow(w3, 2) + winchPos2[0] * pow(winchPos3[1], 2) + winchPos2[0] * pow(winchPos3[0], 2) - pow(winchPos2[0], 3) + (winchPos2[0] - winchPos3[0]) * (pow(w1, 2) - pow(w2, 2) + pow(winchPos2[0], 2))) / (2 * winchPos2[0] * winchPos3[1]);
        pos.z = sqrt(abs(pow(w1, 2) - (pow(pos.x, 2) + pow(pos.y, 2))));

        return pos;
    }
    
    double x_axis_foward_kinematics(double w1, double w2)
    {
        return posX = (pow(w1, 2) - pow(w2, 2) + pow(winchPos2[0], 2)) / (2 * winchPos2[0]);
    }
    
    //winch三台での逆運動学
    //winchのワイヤ長さを出力
    //
    //変数について
    //desPos:交点の目標位置
    double inverse_kinematics(geometry_msgs::Vector3 desPos)
    {
        wireLen = sqrt(pow((desPos.x - winchPos1[0]), 2) + pow((desPos.y - winchPos1[1]), 2) + pow((desPos.z - winchPos1[2]), 2)); /*winchPos1 to winchPos◯　◯:winch番号*/

        return wireLen;
    }
    
    double x_axis_inverse_kinematics(double w1, double posX)
    {
        return w2 = sqrt(abs(2 * winchPos2[0] * posX - pow(w1, 2) - pow(winchPos2[0], 2)));
    }

};

#endif // KINEMATICS_HPP
