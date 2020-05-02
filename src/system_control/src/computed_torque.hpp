#ifndef COMPUTED_TORQUE_HPP
#define COMPUTED_TORQUE_HPP

#include <cmath>

class ComputedTorque
{
public:
    double Kp = 150000;         //Pゲイン
    double Kd = 10000;          //Dゲイン
    double Kv = 5;              //Iゲイン
    double Ki = 29.2;           //トルク定数
    double Kf = (7740 / 12000); //無負荷回転数÷最大許容回転数
    double R = 0.583;           //モータの内部抵抗
    double m = 0.0035;          //ドラム質量[kg]
    double d = 0.04;            //ドラム直径
    double prevI = 0;
    double inertia_term = 0.5 * m * pow(0.5 * d, 2); //慣性項
    double P;                                        //比例項(Proportional)
    double I;                                        //積分項(Integral)
    double D;                                        //微分項(Differential)
    double torque;                                   //トルク
    double volt;                               //入力電圧

    //関数の説明
    //モータに入力する電圧を出力する
    //計算トルク法(PD制御)を使用
    //モータドライバの使用上、0v-5v入力なのでリミットをかけた
    //2.5vの時、モータへの出力電圧は0v
    //
    //変数の説明
    //Kp, Kd:ゲイン
    double input_volt(double curDesCount, double curDesCountVel, double curCount, double curCountVel, double curDesCountAcc)
    {

        P = Kp * (curDesCount - curCount);
        I = Kv * (curDesCount - curCount) + prevI;
        D = Kd * (curDesCountVel - curCountVel);
        torque = inertia_term * (curDesCountAcc + P + D + I); //トルク
        volt = 2.50 + ((R * torque) / Ki);              //モータドライバが入力2.5Vで出力0vなので、2.50v足す

        //条件実行文の説明
        //モータドライバの最低入力電圧が0vなのでリミットをかける
        //入力電圧が0.2v以下の場合は0.2vを返す
        if (volt < 0.20)
        {
            return volt = 0.20;
        }

        //条件実行文の説明
        //入力電圧が0.2v以上、4.8v以下の場合はinput_voltを返す
        if (volt > 0.20 && volt < 4.80)
        {
            return volt;
        }

        //条件実行文の説明
        //モータドライバの最低入力電圧が5vなのでリミットをかける
        //入力電圧が4.8v以下の場合は4.8vを返す
        if (volt > 4.80)
        {
            return volt = 4.80;
        }
        prevI = I;
    }

};

#endif // COMPUTED_TORQUE_HPP
