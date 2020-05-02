#include "winch.hpp"
#include "digital_to_analog.hpp"
#include "digital_filter.hpp"
#include "computed_torque.hpp"
#include "interpolation_function.hpp"
#include "kinematics.hpp"
#include <ros/ros.h>
#include <cmath>
#include <iostream>

bool interrupted = false;

//関数の説明
//signalhandlerの設定
//void:戻り値を必要としない型
//interrupted:割り込み(ctr+c)
void
mySigintHandler(int sig)
{
    interrupted = true;
}

Winch::Winch(){
    wire_length_pub = nh.advertise<std_msgs::Float64>("wire_length_winch1", 10);                          //winch1のワイヤ長さpublish宣言         /*winch1 to winch◯　◯:winch番号*/
    desPos_pub = nh.advertise<geometry_msgs::Vector3>("desire_position_winch1", 10);                      //winch1の目標交点位置publish宣言        /*winch1 to winch◯　◯:winch番号*/
    record_pub = nh.advertise<system_control::Record>("record_data_winch1", 100);                         //winch1の目標長さと実際の長さpublish宣言        /*winch1 to winch◯　◯:winch番号*/
    rotary_encoder_sub = nh.subscribe("count_winch1", 100, &Winch::rotary_encoder_callback, this);              //ロータリーエンコーダsubscribe宣言     /*winch1 to winch◯　◯:winch番号*/
    wire_length_winch2_sub = nh.subscribe("wire_length_winch2", 10, &Winch::wire_length_winch2_callback, this); //winch2のワイヤ長さsubscribe宣言      /*winch2 to winch◯　◯:winch番号以外のもの*/
    wire_length_winch3_sub = nh.subscribe("wire_length_winch3", 10, &Winch::wire_length_winch3_callback, this); //winch3のワイヤ長さsubscribe宣言      /*winch3 to winch◯　◯:winch番号以外のもの*/
    start_time_sub = nh.subscribe("start_time", 10, &Winch::start_time_callback, this);                         //開始時刻のsubscribe宣言
    finish_time_sub = nh.subscribe("finish_time", 10, &Winch::finish_time_callback, this);                      //終了時刻のsubscribe宣言
    finish_position_sub = nh.subscribe("finish_position", 10, &Winch::finish_position_callback, this);          //目標交点位置のsubscribe宣言
    
    wire_length_pub.publish(msg_length);                    //winch1のワイヤ長さpublish
    desPos_pub.publish(desPos_msg);
    record_pub.publish(msg_record);
};

//関数の説明
//ロータリーエンコーダからカウント値を得る
void Winch::rotary_encoder_callback(const std_msgs::Int32::ConstPtr count_msg)
{
    curCount = count_msg->data;
}

//関数の説明
//winch2のワイヤ初期長さsubscribe
//順運動学を用いて、初期位置を求めるのに必要
void Winch::wire_length_winch2_callback(const std_msgs::Float64::ConstPtr wire_length_winch2_msg)
{
    iniLen2 = wire_length_winch2_msg->data; /*winch2 to winch◯　◯:winch番号以外のもの*/
}

//関数の説明
//winch3のワイヤ初期長さsubscribe
//順運動学を用いて、初期位置を求めるのに必要
void Winch::wire_length_winch3_callback(const std_msgs::Float64::ConstPtr wire_length_winch3_msg)
{
    iniLen3 = wire_length_winch3_msg->data; /*winch3 to winch◯　◯:winch番号以外のもの*/
}

//関数の説明
//開始時間の同期に必要な開始時刻のsubscribe
void Winch::start_time_callback(const std_msgs::Float64::ConstPtr start_time_msg)
{
    start_time = start_time_msg->data;
}

//関数の説明
//終了時間の同期に必要な終了時刻のsubscribe
void Winch::finish_time_callback(const std_msgs::Float64::ConstPtr finish_time_msg)
{
    finish_time = finish_time_msg->data;
}

//関数について
//目標位置のsubscribe
void Winch::finish_position_callback(const geometry_msgs::Vector3::ConstPtr finPos_msg)
{
    finDesPos.x = finPos_msg->x;
    finDesPos.y = finPos_msg->y;
    finDesPos.z = finPos_msg->z;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "winch"); //node名(node名の重複はNG)        /*winch1 to winch◯　◯:winch番号*/
    
    Winch winch;
    DigitalToAnalog d2a;
    Kinematics kinematics;
    InterpolationFunction interpolation;
    ComputedTorque torque;
    DigitalFilter filter;

    ros::Rate rate(1000); //プログラム実行周期

    d2a.writeBuf[0] = 0b01000000;
    d2a.writeBuf[1] = 0b00000000;
    d2a.writeBuf[2] = 0b00000000;
    d2a.check_i2c();

    d2a.set_analog(d2a.volt_to_int16(2.50), d2a.writeBuf, d2a.fd);
    std::cout << "volt = 0"
              << "\n";

    ros::Duration(5.0).sleep();

    winch.setupTime1 = ros::Time::now() + ros::Duration(0.5);
    winch.setupTime2 = ros::Time::now() + ros::Duration(1.0);

    //////////////////////////////////
    winch.iniLen2 = 5.0;
    winch.iniLen3 = 5.0;
    //////////////////////////////////

    //条件実行文の説明
    while (ros::Time::now() < winch.setupTime1)
    {
        d2a.set_analog(d2a.volt_to_int16(2.55), d2a.writeBuf, d2a.fd);
        winch.prevDesCount = winch.curCount;
        winch.prevCount2 = winch.curCount;
        winch.iniLen1 = winch.d * winch.PI * winch.curCount / 4096.0; /*iniLen1 to iniLen◯　◯:winch番号*/
        winch.msg_length.data = winch.iniLen1;                              /*iniLen1 to iniLen◯　◯:winch番号*/
        ros::spinOnce();                                              //購読する際に必要,callbackが呼ばれる
    }

    //条件実行文の説明
    while (ros::Time::now() < winch.setupTime2)
    {
        d2a.set_analog(d2a.volt_to_int16(2.45), d2a.writeBuf, d2a.fd);
        winch.prevDesCount = winch.curCount;
        winch.prevCount2 = winch.curCount;
        winch.iniLen1 = winch.d * winch.PI * winch.curCount / 4096.0; /*iniLen1 to iniLen◯　◯:winch番号*/
        winch.msg_length.data = winch.iniLen1;                              /*iniLen1 to iniLen◯　◯:winch番号*/
        ros::spinOnce();                                              //購読する際に必要,callbackが呼ばれる
    }

    winch.t0 = ros::Time::now();                                        //交点制御開始時間
    winch.desTime = winch.finish_time - winch.start_time;               //交点制御終了時間
    winch.restTime = winch.start_time - winch.t0.toSec();               //開始時刻までの時間
    winch.sleepTime = ros::Time::now() + ros::Duration(winch.restTime); //開始時刻

    while (ros::Time::now() < winch.sleepTime)
    {
        winch.prevCount1 = winch.prevCount2;
        d2a.set_analog(d2a.volt_to_int16(2.50), d2a.writeBuf, d2a.fd);
        winch.msg_length.data = winch.iniLen1;           /*iniLen1 to iniLen◯　◯:winch番号*/
        ros::spinOnce();                           //購読する際に必要,callbackが呼ばれる
    }

    winch.T0 = ros::Time::now();
    winch.prevTime = winch.T0; //prevTimeの設定

    //条件実行文の説明
    //直線軌道
    //
    while (ros::ok() && !interrupted)
    {
        winch.curTime = ros::Time::now();                      //現在時刻
        winch.diff = (winch.curTime - winch.prevTime).toSec(); //時間差分
        winch.iniPos = kinematics.foward_kinematics(winch.iniLen1, winch.iniLen2, winch.iniLen3);
        winch.curDesPos.x = winch.iniPos.x + interpolation.trapezoidal_velocity_curve(winch.desTime, (winch.curTime - winch.T0).toSec(), (winch.finDesPos.x - winch.iniPos.x));
        winch.curDesPos.y = winch.iniPos.y + interpolation.trapezoidal_velocity_curve(winch.desTime, (winch.curTime - winch.T0).toSec(), (winch.finDesPos.y - winch.iniPos.y));
        winch.curDesPos.z = winch.iniPos.z;                                // + trapezoidal_velocity_curve(desTime, (curTime - T0).toSec(), (finDesPos.z - iniPos.z));
        winch.curDesLen = kinematics.inverse_kinematics(winch.curDesPos); //現在の目標長さ
        winch.curLen = (winch.d * winch.PI * winch.curCount) / 4096.0;     //現在の長さ
        winch.curDesCount = (winch.curDesLen * 4096.0) / (winch.d * winch.PI);
        winch.curDesCountVel = (winch.curDesCount - winch.prevDesCount) / winch.diff;
        winch.curDesCountAcc = (winch.curDesCountVel - winch.prevDesCountVel) / winch.diff;
        winch.inpCountVel = filter.second_order_backward_diff(winch.curCount, winch.prevCount1, winch.prevCount2); //RCフィルターへの入力カウント速度
        winch.curCountVel = filter.low_pass_filter(winch.inpCountVel, winch.inpCountVel1, winch.inpCountVel2, winch.outCountVel1, winch.outCountVel2);

        winch.input = torque.input_volt(winch.curDesCount, winch.curDesCountVel, winch.curCount, winch.curCountVel, winch.curDesCountAcc); //モータドライバへの入力電圧
        d2a.set_analog(d2a.volt_to_int16(winch.input), d2a.writeBuf, d2a.fd);

        if (winch.counter == 10)
        {
            winch.desPos_msg = winch.curDesPos;


            winch.msg_record.curTime = (winch.curTime - winch.T0).toSec();
            winch.msg_record.curLen = winch.curLen;
            winch.msg_record.curDesLen = winch.curDesLen;

            winch.counter = 0;
        }
        else
        {
            winch.counter++;
        }

        winch.prevCount2 = winch.prevCount1;
        winch.prevCount1 = winch.curCount;
        winch.inpCountVel2 = winch.inpCountVel1;
        winch.inpCountVel1 = winch.inpCountVel;
        winch.outCountVel2 = winch.outCountVel1;
        winch.outCountVel1 = winch.curCountVel;
        winch.prevDesCount = winch.curDesCount;
        winch.prevDesCountVel = winch.curCountVel;
        winch.prevTime = winch.curTime;

        ros::spinOnce(); //購読する際に必要,callbackが呼ばれる
        rate.sleep();    //ros::Rateオブジェクトを10Hzの発信が行えるように残り時間をスリープするために使う

        //条件実行文の説明
        //現在の時間が終了時刻を過ぎたら処理終了
        if ((winch.curTime - winch.T0).toSec() > winch.desTime)
        {
            interrupted = true;
        }
    }

    d2a.set_analog(d2a.volt_to_int16(2.50), d2a.writeBuf, d2a.fd);
    std::cout << "volt = 0"
              << "\n"; //モータへの出力電圧0v


    close(d2a.fd);
    
    return 0;
}
