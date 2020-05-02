#include <ros/ros.h>
#include <math.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>
#include <linux/i2c-dev.h>
#include <time.h>
#include <stdio.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float64.h>
#include <sensor/adder.h>       //ポテンショメータの自作変数(alpha, beta)
#include <system_control/Record.h>      //rosbag record用
#include <system_control/Timing.h>

//D/A converter用変数
#define DAC_MAX 4096
#define DAC_VDD 5.0
int fd;
int mcp4725_address = 0x60;     //D/Aコンバータのアドレス
uint8_t writeBuf[3];

//グローバル変数
double d = 0.04;        //ユニットのドラム径        /*星さんのユニットの場合 d=0.6262*/
double PI = 3.14;       //円周率
double winchPos1[] = {0, 0, 0};     //winch1の設置位置
double winchPos2[] = {5.0, 0, 0};     //winch3の設置位置
double winchPos3[] = {2.5, 5.0, 0};     //winch4の設置位置
bool interrupted = false;
int counter = 10;
double iniLen1;     //winch1のワイヤ初期長さ
double iniLen2;     //winch2のワイヤ初期長さ
double iniLen3;     //winch3のワイヤ初期長さ
geometry_msgs::Vector3 finDesPos;       //目標位置
double start_time;      //開始時刻
double finish_time;     //終了時刻

double prevI = 0;

double curDesCount;     //現在の目標カウント値
double prevDesCount;        //一つ前の目標カウント値
double curDesCountVel;      //現在の目標カウント速度
double prevDesCountVel;     //一つ前の目標カウント速度
double curDesCountAcc;      //現在の目標カウント加速度

double curCount;        //現在のカウント値
double prevCount2 = 0;      //二つ前のカウント値
double prevCount1 = 0;      //一つ前のカウント値
double inpCountVel2 = 0;        //二つ前のRCフィルターへの入力カウント速度
double inpCountVel1 = 0;        //一つ前のRCフィルターへの入力カウント速度
double outCountVel2 = 0;        //二つ前のRCフィルターからの出力カウント速度
double outCountVel1 = 0;        //一つ前のRCフィルターからの出力カウント速度
double curCountVel;     //現在のカウント速度

//関数の説明
//signalhandlerの設定
//void:戻り値を必要としない型
//interrupted:割り込み(ctr+c)
void mySigintHandler(int sig)
{
  interrupted = true;
}

//関数の説明
//D/A convert
//0v - 5.0vを0 - 4096へ変換する
//
//変数について
//volt:電圧
int16_t volt_to_int16(double volt){
    volt = volt / DAC_VDD * DAC_MAX;
    return int16_t (volt);
}

//関数の説明
//i2c通信の設定
//
//変数について
//
void set_analog(int16_t input_int16, uint8_t i2c_buffer[3], int fd){
    i2c_buffer[1] = input_int16 >> 4;       //MSB 11-4 shift right 4 places
    i2c_buffer[2] = input_int16 << 4;       //LSB 3-0 shift left 4 places

    if(write(fd, i2c_buffer, 3) != 3){
        perror("write to register 1");
        exit (1);
    }
    return;
}


//関数の説明
//ロータリーエンコーダからカウント値を得る
//
//変数について
//count_msg:ロータリエンコーダから得たカウンタ値, 
void rotary_encoder_callback(const std_msgs::Int32::ConstPtr count_msg){
    curCount = count_msg->data;
}

//関数の説明
//交点の軌道生成に使用する台形速度曲線
//各時間毎の目標位置を出力する
//accTは任意に決めている
//
//変数の説明
//accT:加減速時間, desT:目標位置到達時間, t:現在の時間, desX:desT時の目標位置
double trapezoidal_velocity_curve(double desTime, double curTime, double desX){
    double accTime = 0.20 * desTime;
    double vel = desX / (desTime - accTime);
    
    if(accTime > curTime){
        return 0.50 * (vel / accTime) * pow(curTime, 2);
    }
    
    if(curTime > accTime && (desTime - accTime) > curTime){
        return 0.50 * accTime * vel + (curTime - accTime) * vel;
    }
    
    if(curTime > (desTime - accTime)){
        return desX - 0.50 * (vel / accTime) * pow((desTime - curTime), 2);
    }
    
    if (curTime > desTime){
        return desX;
    }
    
}


//関数の説明
//winch三台での順運動学
//交点の位置(pos.x, pos.y, pos.zの位置を出力)
//
//変数について
//w1:winch1のワイヤ長さ, w3:winch3のワイヤ長さ, w4:winch4のワイヤ長さ
//winchPos1:winch1の位置, winchPos3:winch3の位置, winchPos4:winch4の位置 
geometry_msgs::Vector3 foward_kinematics(double w1, double w2, double w3){
    geometry_msgs::Vector3 pos;

    pos.x = (pow(w1, 2) - pow(w2, 2) + pow(winchPos2[0], 2)) / (2 * winchPos2[0]);
    pos.y = (winchPos2[0] * pow(w2, 2) - winchPos2[0] * pow(w3, 2) + winchPos2[0] * pow(winchPos3[1], 2) + winchPos2[0] * pow(winchPos3[0], 2) - pow(winchPos2[0], 3) + (winchPos2[0] - winchPos3[0]) * (pow(w1, 2) - pow(w2, 2) + pow(winchPos2[0], 2))) / (2 * winchPos2[0] * winchPos3[1]);
    pos.z = sqrt(abs(pow(w1, 2) - (pow(pos.x, 2) + pow(pos.y, 2))));

    return pos;
}

//関数の説明
//winch三台での逆運動学
//winchのワイヤ長さを出力
//
//変数について
//desPos:交点の目標位置
double inverse_kinematics(geometry_msgs::Vector3 desPos){
    double wireLen = sqrt(pow((desPos.x - winchPos1[0]), 2) + pow((desPos.y - winchPos1[1]), 2) + pow((desPos.z - winchPos1[2]), 2));       /*winchPos1 to winchPos◯　◯:winch番号*/
    
    return wireLen;
}

//関数の説明
//2nd order backward diff
double second_order_backward_diff(double count, double count_prev1, double count_prev2){
     double vel = (3 * count - 4 * count_prev1 + count_prev2) / 0.002;
     
     return vel;
}

//関数の説明
//双二次ローパスフィルター
double low_pass_filter(double input , double prevInput1, double prevInput2, double prevOutput1, double prevOutput2){
    double samplerate = 1000;       //サンプリング周波数
    double freq = 2.0;      //カットオフ周波数
    double q = 0.70710;     //フィルタのQ値
    double omega = 2.0 * 3.14159265 * freq / samplerate;
    double alpha = sin(omega) / (2.0 * q);
    double a0 = 1.0 + alpha;
    double a1 = -2.0 * cos(omega);
    double a2 = 1.0 -alpha;
    double b0 = (1.0 -cos(omega)) / 2.0;
    double b1 = 1.0 - cos(omega);
    double b2 = (1.0 - cos(omega)) / 2.0;
    
    double output = b0 / a0 * input + b1 / a0 * prevInput1 + b2 / a0 * prevInput2 - a1 / a0 * prevOutput1 - a2 / a0 * prevOutput2;      //入力信号にフィルタを適用し、出力信号として書き出す
    return output;
}

//関数の説明
//モータに入力する電圧を出力する
//計算トルク法(PD制御)を使用
//モータドライバの使用上、0v-5v入力なのでリミットをかけた
//2.5vの時、モータへの出力電圧は0v
//
//変数の説明
//Kp, Kd:ゲイン
double input_volt(double curDesCount, double curDesCountVel, double curCount, double curCountVel, double curDesCountAcc){
    double Kp = 150000;     //Pゲイン
    double Kd = 10000;       //Dゲイン
    double Kv = 5;         //Iゲイン
    double Ki = 29.2;       //トルク定数
    double Kf = (7740 / 12000);     //無負荷回転数÷最大許容回転数
    double R = 0.583;       //モータの内部抵抗
    double m = 0.0035;      //ドラム質量[kg]
    double inertia_term = 0.5 * m * pow(0.5 * d, 2);        //慣性項

    double P = Kp * (curDesCount - curCount);
    double I = Kv * (curDesCount - curCount) + prevI;
    double D = Kd * (curDesCountVel - curCountVel);
    prevI = I;
    double torque = inertia_term * (curDesCountAcc + P + D + I);        //トルク
    double input_volt = 2.50 + ((R * torque) / Ki); // + (Kf * curDesCountVel);       //モータドライバが入力2.5Vで出力0vなので、2.5v足す
    
    //条件実行文の説明
    //モータドライバの最低入力電圧が0vなのでリミットをかける
    //入力電圧が0.2v以下の場合は0.2vを返す
    if(input_volt < 0.20){
        return input_volt = 0.20;
    }
    
    //条件実行文の説明
    //入力電圧が0.2v以上、4.8v以下の場合はinput_voltを返す
    if(input_volt > 0.20 && input_volt < 4.80){
        return input_volt;
    }

    //条件実行文の説明
    //モータドライバの最低入力電圧が5vなのでリミットをかける
    //入力電圧が4.8v以下の場合は4.8vを返す    
    if(input_volt > 4.80){
        return input_volt = 4.80;
    }       
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "calibrate_1to2");       //node名(node名の重複はNG)        /*winch1 to winch◯　◯:winch番号*/
    ros::NodeHandle nh;     //ノードハンドラの作成
    ros::Subscriber rotary_encoder_sub = nh.subscribe("count_winch1", 100, rotary_encoder_callback);       //ロータリーエンコーダsubscribe宣言     /*winch1 to winch◯　◯:winch番号*/
    ros::Rate rate(1000);       //プログラム実行周期

    //条件実行文の説明
    //
    //
    if((fd = open("/dev/i2c-1", O_RDWR)) < 0){
        printf("Error: Could'nt open device! %d\n", fd);
        exit (1);
    }

    //条件実行文の説明
    //
    //
    if(ioctl(fd, I2C_SLAVE, mcp4725_address) < 0){
        printf("Error: Couldn't find device on address!\n");
        exit (1);
    }

    writeBuf[0] = 0b01000000;
    writeBuf[1] = 0b00000000;
    writeBuf[2] = 0b00000000;

    std::cout << "volt = 0" << "\n" ;       
    set_analog(volt_to_int16(2.50), writeBuf, fd);
    ros::Duration(6.0).sleep();
    
    std::cout << "rotary_encoder_setup" << "\n" ;
    ros::Time setupTime1 = ros::Time::now() + ros::Duration(0.2);
    ros::Time setupTime2 = ros::Time::now() + ros::Duration(0.45);    
    
    //条件実行文の説明
    while(ros::Time::now() < setupTime1){
        set_analog(volt_to_int16(2.60), writeBuf, fd);
        double iniCount = curCount;     //winch1の初期長さを求めるのに必要
        prevDesCount = curCount;
        prevCount2 = curCount;
        iniLen1 = d * PI * iniCount / 4096.0;       /*iniLen1 to iniLen◯　◯:winch番号*/
        ros::spinOnce();        //購読する際に必要,callbackが呼ばれる
    }
    
        //条件実行文の説明
    while(ros::Time::now() < setupTime2){
        set_analog(volt_to_int16(2.40), writeBuf, fd);
        double iniCount = curCount;     //winch1の初期長さを求めるのに必要
        prevDesCount = curCount;
        prevCount2 = curCount;
        iniLen1 = d * PI * iniCount / 4096.0;       /*iniLen1 to iniLen◯　◯:winch番号*/
        ros::spinOnce();        //購読する際に必要,callbackが呼ばれる
    }
    
    ros::Time t0 = ros::Time::now();      //交点制御開始時間
    double desTime = 125;      //交点制御終了時間
    double restTime = 5;       //開始時刻までの時間
    ros::Time sleepTime = ros::Time::now() + ros::Duration(restTime);       //開始時刻
    
    std::cout << "volt = 0" << "\n" ;
    while(ros::Time::now() < sleepTime){
        iniLen2 = 5;
        iniLen3 = 5.59;
        finDesPos.x = 5;
        finDesPos.y = 0;
        finDesPos.z = 0;
        prevCount1 = prevCount2;
        set_analog(volt_to_int16(2.50), writeBuf, fd);
        ros::spinOnce();        //購読する際に必要,callbackが呼ばれる
    }
    
    std::cout << "finDesPos = " << finDesPos << "\n";
    ros::Time T0 = ros::Time::now();
    ros::Time prevTime = T0;       //prevTimeの設定
    
    //条件実行文の説明
    //直線軌道
    //
    while(ros::ok()&& !interrupted){
        ros::Time curTime = ros::Time::now();       //現在時刻 
        double diff = (curTime - prevTime).toSec();     //時間差分
        geometry_msgs::Vector3 curDesPos;
        geometry_msgs::Vector3 iniPos = foward_kinematics(iniLen1, iniLen2, iniLen3);
        curDesPos.x = iniPos.x + trapezoidal_velocity_curve(desTime, (curTime - T0).toSec(), (finDesPos.x - iniPos.x));
        curDesPos.y = iniPos.y + trapezoidal_velocity_curve(desTime, (curTime - T0).toSec(), (finDesPos.y - iniPos.y));
        curDesPos.z = iniPos.z + trapezoidal_velocity_curve(desTime, (curTime - T0).toSec(), (finDesPos.z - iniPos.z));
        double curDesLen = inverse_kinematics(curDesPos);       //現在の目標長さ
        double curLen = (d * PI * curCount) / 4096.0;       //現在の長さ
        curDesCount = (curDesLen * 4096.0) / (d * PI);      
        curDesCountVel = (curDesCount - prevDesCount) / diff;
        curDesCountAcc = (curDesCountVel - prevDesCountVel) / diff;
        double inpCountVel = second_order_backward_diff(curCount, prevCount1, prevCount2);      //RCフィルターへの入力カウント速度
        curCountVel = low_pass_filter(inpCountVel, inpCountVel1, inpCountVel2, outCountVel1, outCountVel2);

        double input = input_volt(curDesCount, curDesCountVel, curCount, curCountVel, curDesCountAcc);      //モータドライバへの入力電圧
        set_analog(volt_to_int16(input), writeBuf, fd);
        
        if(counter == 100){
            std::cout << "curLen = " << curLen << "\n";
            counter = 0;   
        }
        
        else{
            counter++;
        }
        
        prevCount2 = prevCount1;        
        prevCount1 = curCount;     
        inpCountVel2 = inpCountVel1;        
        inpCountVel1 = inpCountVel;     
        outCountVel2 = outCountVel1;        
        outCountVel1 = curCountVel;     
        
        prevDesCount = curDesCount;
        prevDesCountVel = curCountVel;
        prevTime = curTime;     
        ros::spinOnce();        //購読する際に必要,callbackが呼ばれる
        rate.sleep();       //ros::Rateオブジェクトを10Hzの発信が行えるように残り時間をスリープするために使う
        
        //条件実行文の説明
        //現在の時間が終了時刻を過ぎたら処理終了
        if((curTime - T0).toSec() > desTime){
            interrupted = true;
        }

    }

    std::cout << "volt = 0" << "\n" ;       //モータへの出力電圧0v
    set_analog(volt_to_int16(2.50), writeBuf, fd);

    close(fd);
    return 0;

} 
