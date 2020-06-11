#include </home/pi/winch_ws/src/system_control/include/x_axis_position_control.hpp>
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

XAxisPos::XAxisPos(){
    ros::NodeHandle nh; //ノードハンドラの作成
    record_pub = nh.advertise<system_control::Record>("record_data_winch1", 100);                         //winch1の目標長さと実際の長さpublish宣言        /*winch1 to winch◯　◯:winch番号*/
    rotary_encoder_sub = nh.subscribe("count_winch1", 100, &XAxisPos::rotary_encoder_callback, this);              //ロータリーエンコーダsubscribe宣言     /*winch1 to winch◯　◯:winch番号*/
    wire_length_constVel_sub = nh.subscribe("wire_length_constVel", 10, &XAxisPos::wire_length_constVel_callback, this); //winch2のワイヤ長さsubscribe宣言      /*winch2 to winch◯　◯:winch番号以外のもの*/
    start_time_sub = nh.subscribe("start_time", 10, &XAxisPos::start_time_callback, this);                         //開始時刻のsubscribe宣言
    finish_time_sub = nh.subscribe("finish_time", 10, &XAxisPos::finish_time_callback, this);                      //終了時刻のsubscribe宣言
    finish_x_axis_position_sub = nh.subscribe("finish_x_axis_position", 10, &XAxisPos::finish_x_axis_position_callback, this);          //目標交点位置のsubscribe宣言
    finLen_constVel_sub = nh.subscribe("finLen_constVel", 10, &XAxisPos::finLen_constVel_callback, this);                         //開始時刻のsubscribe宣言
};

//ロータリーエンコーダからカウント値を得る
void XAxisPos::rotary_encoder_callback(const std_msgs::Int32::ConstPtr count_msg)
{
    curCount = count_msg->data;
}

//winch2のワイヤ初期長さsubscribe
//順運動学を用いて、初期位置を求めるのに必要
void XAxisPos::wire_length_constVel_callback(const std_msgs::Float64::ConstPtr wire_length_constVel_msg)
{
    iniLen_constVel = wire_length_constVel_msg->data; /*winch2 to winch◯　◯:winch番号以外のもの*/
}

//関数の説明
//開始時間の同期に必要な開始時刻のsubscribe
void XAxisPos::start_time_callback(const std_msgs::Float64::ConstPtr start_time_msg)
{
    start_time = start_time_msg->data;
}

//関数の説明
//終了時間の同期に必要な終了時刻のsubscribe
void XAxisPos::finish_time_callback(const std_msgs::Float64::ConstPtr finish_time_msg)
{
    finish_time = finish_time_msg->data;
}

//関数について
//目標位置のsubscribe
void XAxisPos::finish_x_axis_position_callback(const std_msgs::Float64::ConstPtr finPosX_msg)
{
    finPosX = finPosX_msg->data;
}

//
//
void XAxisPos::finLen_constVel_callback(const std_msgs::Float64::ConstPtr finLen_constVel_msg)
{
    finLen_constVel = finLen_constVel_msg->data;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "x_axis_position_control"); //node名(node名の重複はNG)        /*winch1 to winch◯　◯:winch番号*/
    
    XAxisPos xAxisPos;
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

    xAxisPos.setupTime1 = ros::Time::now() + ros::Duration(0.5);
    xAxisPos.setupTime2 = ros::Time::now() + ros::Duration(1.0);

    //条件実行文の説明
    while (ros::Time::now() < xAxisPos.setupTime1)
    {
        d2a.set_analog(d2a.volt_to_int16(2.55), d2a.writeBuf, d2a.fd);
        xAxisPos.prevDesCount = xAxisPos.curCount;
        xAxisPos.prevCount2 = xAxisPos.curCount;
        xAxisPos.iniLen_xAxisPos = xAxisPos.d * xAxisPos.PI * xAxisPos.curCount / 4096.0; /*iniLen1 to iniLen◯　◯:winch番号*/
        ros::spinOnce();                                              //購読する際に必要,callbackが呼ばれる
    }

    //条件実行文の説明
    while (ros::Time::now() < xAxisPos.setupTime2)
    {
        d2a.set_analog(d2a.volt_to_int16(2.45), d2a.writeBuf, d2a.fd);
        xAxisPos.prevDesCount = xAxisPos.curCount;
        xAxisPos.prevCount2 = xAxisPos.curCount;
        xAxisPos.iniLen_xAxisPos = xAxisPos.d * xAxisPos.PI * xAxisPos.curCount / 4096.0; /*iniLen1 to iniLen◯　◯:winch番号*/
        ros::spinOnce();                                              //購読する際に必要,callbackが呼ばれる
    }

    xAxisPos.t0 = ros::Time::now();                                        //交点制御開始時間
    xAxisPos.desTime = xAxisPos.finish_time - xAxisPos.start_time;               //交点制御終了時間
    xAxisPos.restTime = xAxisPos.start_time - xAxisPos.t0.toSec();               //開始時刻までの時間
    xAxisPos.sleepTime = ros::Time::now() + ros::Duration(xAxisPos.restTime); //開始時刻

    while (ros::Time::now() < xAxisPos.sleepTime)
    {
        xAxisPos.prevCount1 = xAxisPos.prevCount2;
        d2a.set_analog(d2a.volt_to_int16(2.50), d2a.writeBuf, d2a.fd);
        ros::spinOnce();                           //購読する際に必要,callbackが呼ばれる
    }

    xAxisPos.T0 = ros::Time::now();
    xAxisPos.prevTime = xAxisPos.T0; //prevTimeの設定
    
    /////////////////////////////////////
    xAxisPos.iniLen_constVel = 5.0; 
    xAxisPos.iniLen_xAxisPos = 5.0;
    ////////////////////////////////////

    //条件実行文の説明
    //直線軌道
    //
    while (ros::ok() && !interrupted)
    {
        xAxisPos.curTime = ros::Time::now();                      //現在時刻
        xAxisPos.diff = (xAxisPos.curTime - xAxisPos.prevTime).toSec(); //時間差分
        xAxisPos.iniPosX = kinematics.x_axis_foward_kinematics(xAxisPos.iniLen_constVel, xAxisPos.iniLen_xAxisPos);
        xAxisPos.curDesPosX = xAxisPos.iniPosX + interpolation.liner(xAxisPos.desTime, (xAxisPos.curTime - xAxisPos.T0).toSec(), (xAxisPos.iniPosX - xAxisPos.finPosX));
        xAxisPos.curLen = (xAxisPos.d * xAxisPos.PI * xAxisPos.curCount) / 4096.0;     //現在の長さ
        xAxisPos.curLen_constVel = xAxisPos.iniLen_constVel - interpolation.liner(xAxisPos.desTime, (xAxisPos.curTime - xAxisPos.T0).toSec(), xAxisPos.finLen_constVel);
        xAxisPos.curDesLen = kinematics.x_axis_inverse_kinematics(xAxisPos.curLen_constVel, xAxisPos.curDesPosX); //現在の目標長さ
        xAxisPos.curDesCount = (xAxisPos.curDesLen * 4096.0) / (xAxisPos.d * xAxisPos.PI);
        xAxisPos.curDesCountVel = (xAxisPos.curDesCount - xAxisPos.prevDesCount) / xAxisPos.diff;
        xAxisPos.curDesCountAcc = (xAxisPos.curDesCountVel - xAxisPos.prevDesCountVel) / xAxisPos.diff;
        xAxisPos.inpCountVel = filter.second_order_backward_diff(xAxisPos.curCount, xAxisPos.prevCount1, xAxisPos.prevCount2); //RCフィルターへの入力カウント速度
        xAxisPos.curCountVel = filter.low_pass_filter(xAxisPos.inpCountVel, xAxisPos.inpCountVel1, xAxisPos.inpCountVel2, xAxisPos.outCountVel1, xAxisPos.outCountVel2);
        xAxisPos.input = torque.input_volt(xAxisPos.curDesCount, xAxisPos.curDesCountVel, xAxisPos.curCount, xAxisPos.curCountVel, xAxisPos.curDesCountAcc); //モータドライバへの入力電圧
        d2a.set_analog(d2a.volt_to_int16(xAxisPos.input), d2a.writeBuf, d2a.fd);

        if (xAxisPos.counter == 10)
        {
            xAxisPos.msg_record.curTime = (xAxisPos.curTime - xAxisPos.T0).toSec();
            xAxisPos.msg_record.curLen = xAxisPos.curLen;
            xAxisPos.msg_record.curDesLen = xAxisPos.curDesLen;
            xAxisPos.record_pub.publish(xAxisPos.msg_record);
            //std::cout <<"curDesLen="<<xAxisPos.curDesLen<<"\n";
            //std::cout <<"curLen_constVel="<<xAxisPos.curLen_constVel<<"\n";
            //std::cout <<"curDesPosX="<<xAxisPos.curDesPosX<<"\n";            
            xAxisPos.counter = 0;
        }
        else
        {
            xAxisPos.counter++;
        }

        xAxisPos.prevCount2 = xAxisPos.prevCount1;
        xAxisPos.prevCount1 = xAxisPos.curCount;
        xAxisPos.inpCountVel2 = xAxisPos.inpCountVel1;
        xAxisPos.inpCountVel1 = xAxisPos.inpCountVel;
        xAxisPos.outCountVel2 = xAxisPos.outCountVel1;
        xAxisPos.outCountVel1 = xAxisPos.curCountVel;
        xAxisPos.prevDesCount = xAxisPos.curDesCount;
        xAxisPos.prevDesCountVel = xAxisPos.curCountVel;
        xAxisPos.prevTime = xAxisPos.curTime;

        ros::spinOnce(); //購読する際に必要,callbackが呼ばれる
        rate.sleep();    //ros::Rateオブジェクトを10Hzの発信が行えるように残り時間をスリープするために使う

        //条件実行文の説明
        //現在の時間が終了時刻を過ぎたら処理終了
        if ((xAxisPos.curTime - xAxisPos.T0).toSec() > xAxisPos.desTime)
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
