#ifndef WINCH_HPP
#define WINCH_HPP

#include <ros/ros.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float64.h>
#include <sensor/adder.h>          //ポテンショメータの自作変数(alpha, beta)
#include <system_control/Record.h> //rosbag record用
#include <system_control/Timing.h>
#include <iostream>

class Winch
{
private:
    ros::NodeHandle nh; //ノードハンドラの作成
    ros::Publisher wire_length_pub;                          //winch1のワイヤ長さpublish宣言         /*winch1 to winch◯　◯:winch番号*/
    ros::Publisher record_pub;                         //winch1の目標長さと実際の長さpublish宣言        /*winch1 to winch◯　◯:winch番号*/
    ros::Publisher desPos_pub;                      //winch1の目標交点位置publish宣言        /*winch1 to winch◯　◯:winch番号*/
    ros::Subscriber rotary_encoder_sub;              //ロータリーエンコーダsubscribe宣言     /*winch1 to winch◯　◯:winch番号*/
    ros::Subscriber wire_length_winch2_sub; //winch2のワイヤ長さsubscribe宣言      /*winch2 to winch◯　◯:winch番号以外のもの*/
    ros::Subscriber wire_length_winch3_sub; //winch3のワイヤ長さsubscribe宣言      /*winch3 to winch◯　◯:winch番号以外のもの*/
    ros::Subscriber start_time_sub;                         //開始時刻のsubscribe宣言
    ros::Subscriber finish_time_sub;                      //終了時刻のsubscribe宣言
    ros::Subscriber finish_position_sub;          //目標交点位置のsubscribe宣言
    
public:
    Winch();
    void rotary_encoder_callback(const std_msgs::Int32::ConstPtr count_msg);
    void wire_length_winch2_callback(const std_msgs::Float64::ConstPtr wire_length_winch2_msg);
    void wire_length_winch3_callback(const std_msgs::Float64::ConstPtr wire_length_winch3_msg);
    void start_time_callback(const std_msgs::Float64::ConstPtr start_time_msg);
    void finish_time_callback(const std_msgs::Float64::ConstPtr finish_time_msg);
    void finish_position_callback(const geometry_msgs::Vector3::ConstPtr finPos_msg);
    system_control::Record msg_record;
    std_msgs::Float64 msg_length;

    int counter = 10;
    double d = 0.04;                    //ユニットのドラム径        /*星さんのユニットの場合 d=0.6262*/
    double PI = 3.14;                   //円周率
    double iniLen1;                   //winch1のワイヤ初期長さ
    double iniLen2;                   //winch2のワイヤ初期長さ
    double iniLen3;                   //winch3のワイヤ初期長さ
    double start_time;                //開始時刻
    double finish_time;               //終了時刻
    double desTime;                   //交点制御終了時間
    double restTime;                  //開始時刻までの時間
    double curDesCount;     //現在の目標カウント値
    double prevDesCount;    //一つ前の目標カウント値
    double curDesCountVel;  //現在の目標カウント速度
    double prevDesCountVel; //一つ前の目標カウント速度
    double curDesCountAcc;  //現在の目標カウント加速度
    double curCount;         //現在のカウント値
    double prevCount2 = 0;   //二つ前のカウント値
    double prevCount1 = 0;   //一つ前のカウント値
    double inpCountVel2 = 0; //二つ前のRCフィルターへの入力カウント速度
    double inpCountVel1 = 0; //一つ前のRCフィルターへの入力カウント速度
    double outCountVel2 = 0; //二つ前のRCフィルターからの出力カウント速度
    double outCountVel1 = 0; //一つ前のRCフィルターからの出力カウント速度
    double curCountVel;      //現在のカウント速度
    double inpCountVel;
    double curDesLen; //現在の目標長さ
    double curLen;    //現在の長さ
    double input;
    double diff;       //時間差分
    ros::Time curTime; //現在時刻
    ros::Time setupTime1;
    ros::Time setupTime2;
    ros::Time sleepTime;
    ros::Time t0; //交点制御開始時間
    ros::Time T0;
    ros::Time prevTime; //prevTimeの設定
    geometry_msgs::Vector3 finDesPos; //目標位置
    geometry_msgs::Vector3 curDesPos;
    geometry_msgs::Vector3 iniPos;
    geometry_msgs::Vector3 desPos_msg;
    
};

#endif // WINCH_HPP
