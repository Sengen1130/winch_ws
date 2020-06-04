#include </home/pi/winch_ws/src/system_control/include/constant_velocity_control.hpp>
#include </home/pi/winch_ws/src/system_control/include/digital_to_analog.hpp>
#include </home/pi/winch_ws/src/system_control/include/digital_filter.hpp>
#include </home/pi/winch_ws/src/system_control/include/computed_torque.hpp>
#include </home/pi/winch_ws/src/system_control/include/interpolation_function.hpp>
#include </home/pi/winch_ws/src/system_control/include/kinematics.hpp>
#include <ros/ros.h>
#include <cmath>
#include <iostream>

bool interrupted = false;

//(ctr+c)
void
mySigintHandler(int sig)
{
    interrupted = true;
}

ConstVel::ConstVel(){
    ros::NodeHandle nh; //ノードハンドラの作成
    wire_length_pub = nh.advertise<std_msgs::Float64>("wire_length_constVel", 10);                          //winch1のワイヤ長さpublish宣言         /*winch1 to winch◯　◯:winch番号*/
    record_pub = nh.advertise<system_control::Record>("record_data_winch1", 100);                         //winch1の目標長さと実際の長さpublish宣言        /*winch1 to winch◯　◯:winch番号*/
    rotary_encoder_sub = nh.subscribe("count_winch1", 100, &ConstVel::rotary_encoder_callback, this);              //ロータリーエンコーダsubscribe宣言     /*winch1 to winch◯　◯:winch番号*/
    start_time_sub = nh.subscribe("start_time", 10, &ConstVel::start_time_callback, this);                         //開始時刻のsubscribe宣言
    finish_time_sub = nh.subscribe("finish_time", 10, &ConstVel::finish_time_callback, this);                      //終了時刻のsubscribe宣言
    finLen_constVel_sub = nh.subscribe("finLen_constVel", 10, &ConstVel::finLen_constVel_callback, this);                         //開始時刻のsubscribe宣言
    
    wire_length_pub.publish(msg_length);                    //winch1のワイヤ長さpublish
    record_pub.publish(msg_record);
};

//ロータリーエンコーダからカウント値を得る
void ConstVel::rotary_encoder_callback(const std_msgs::Int32::ConstPtr count_msg)
{
    curCount = count_msg->data;
}

//関数の説明
//開始時間の同期に必要な開始時刻のsubscribe
void ConstVel::start_time_callback(const std_msgs::Float64::ConstPtr start_time_msg)
{
    start_time = start_time_msg->data;
}

//関数の説明
//終了時間の同期に必要な終了時刻のsubscribe
void ConstVel::finish_time_callback(const std_msgs::Float64::ConstPtr finish_time_msg)
{
    finish_time = finish_time_msg->data;
}

//
//
void ConstVel::finLen_constVel_callback(const std_msgs::Float64::ConstPtr finLen_constVel_msg)
{
    finLen_constVel = finLen_constVel_msg->data;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "constant_velocity_control"); //node名(node名の重複はNG)
    
    ConstVel constVel;
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

    constVel.setupTime1 = ros::Time::now() + ros::Duration(0.5);
    constVel.setupTime2 = ros::Time::now() + ros::Duration(1.0);

    //条件実行文の説明
    while (ros::Time::now() < constVel.setupTime1)
    {
        d2a.set_analog(d2a.volt_to_int16(2.55), d2a.writeBuf, d2a.fd);
        constVel.prevDesCount = constVel.curCount;
        constVel.prevCount2 = constVel.curCount;
        constVel.iniLen_constVel = constVel.d * constVel.PI * constVel.curCount / 4096.0; /*iniLen1 to iniLen◯　◯:winch番号*/
        constVel.msg_length.data = constVel.iniLen_constVel;                              /*iniLen1 to iniLen◯　◯:winch番号*/
        ros::spinOnce();                                              //購読する際に必要,callbackが呼ばれる
    }

    //条件実行文の説明
    while (ros::Time::now() < constVel.setupTime2)
    {
        d2a.set_analog(d2a.volt_to_int16(2.45), d2a.writeBuf, d2a.fd);
        constVel.prevDesCount = constVel.curCount;
        constVel.prevCount2 = constVel.curCount;
        constVel.iniLen_constVel = constVel.d * constVel.PI * constVel.curCount / 4096.0; /*iniLen1 to iniLen◯　◯:winch番号*/
        constVel.msg_length.data = constVel.iniLen_constVel;                              /*iniLen1 to iniLen◯　◯:winch番号*/
        ros::spinOnce();                                              //購読する際に必要,callbackが呼ばれる
    }

    constVel.t0 = ros::Time::now();                                        //交点制御開始時間
    constVel.desTime = constVel.finish_time - constVel.start_time;               //交点制御終了時間
    constVel.restTime = constVel.start_time - constVel.t0.toSec();               //開始時刻までの時間
    constVel.sleepTime = ros::Time::now() + ros::Duration(constVel.restTime); //開始時刻

    while (ros::Time::now() < constVel.sleepTime)
    {
        constVel.prevCount1 = constVel.prevCount2;
        d2a.set_analog(d2a.volt_to_int16(2.50), d2a.writeBuf, d2a.fd);
        constVel.msg_length.data = constVel.iniLen_constVel;           /*iniLen1 to iniLen◯　◯:winch番号*/
        ros::spinOnce();                           //購読する際に必要,callbackが呼ばれる
    }

    constVel.T0 = ros::Time::now();
    constVel.prevTime = constVel.T0; //prevTimeの設定
    
    /////////////////////////////////
    constVel.iniLen_constVel = 5.0;
    /////////////////////////////////

    //条件実行文の説明
    //直線軌道
    //
    while (ros::ok() && !interrupted)
    {
        constVel.curTime = ros::Time::now();                      //現在時刻
        constVel.diff = (constVel.curTime - constVel.prevTime).toSec(); //時間差分
        constVel.curLen = (constVel.d * constVel.PI * constVel.curCount) / 4096.0;     //現在の長さ
        constVel.curDesLen = constVel.iniLen_constVel - interpolation.liner(constVel.desTime, (constVel.curTime - constVel.T0).toSec(), (constVel.iniLen_constVel - constVel.finLen_constVel)); //現在の目標長さ
        constVel.curDesCount = (constVel.curDesLen * 4096.0) / (constVel.d * constVel.PI);
        constVel.curDesCountVel = (constVel.curDesCount - constVel.prevDesCount) / constVel.diff;
        constVel.curDesCountAcc = (constVel.curDesCountVel - constVel.prevDesCountVel) / constVel.diff;
        constVel.inpCountVel = filter.second_order_backward_diff(constVel.curCount, constVel.prevCount1, constVel.prevCount2); //RCフィルターへの入力カウント速度
        constVel.curCountVel = filter.low_pass_filter(constVel.inpCountVel, constVel.inpCountVel1, constVel.inpCountVel2, constVel.outCountVel1, constVel.outCountVel2);
        constVel.input = torque.input_volt(constVel.curDesCount, constVel.curDesCountVel, constVel.curCount, constVel.curCountVel, constVel.curDesCountAcc); //モータドライバへの入力電圧
        d2a.set_analog(d2a.volt_to_int16(constVel.input), d2a.writeBuf, d2a.fd);

        if (constVel.counter == 10)
        {
            constVel.msg_record.curTime = (constVel.curTime - constVel.T0).toSec();
            constVel.msg_record.curLen = constVel.curLen;
            constVel.msg_record.curDesLen = constVel.curDesLen;

            constVel.counter = 0;
        }
        else
        {
            constVel.counter++;
        }

        constVel.prevCount2 = constVel.prevCount1;
        constVel.prevCount1 = constVel.curCount;
        constVel.inpCountVel2 = constVel.inpCountVel1;
        constVel.inpCountVel1 = constVel.inpCountVel;
        constVel.outCountVel2 = constVel.outCountVel1;
        constVel.outCountVel1 = constVel.curCountVel;
        constVel.prevDesCount = constVel.curDesCount;
        constVel.prevDesCountVel = constVel.curCountVel;
        constVel.prevTime = constVel.curTime;

        ros::spinOnce(); //購読する際に必要,callbackが呼ばれる
        rate.sleep();    //ros::Rateオブジェクトを10Hzの発信が行えるように残り時間をスリープするために使う

        //条件実行文の説明
        //現在の時間が終了時刻を過ぎたら処理終了
        if ((constVel.curTime - constVel.T0).toSec() > constVel.desTime)
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
