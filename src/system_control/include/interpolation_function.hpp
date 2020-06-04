#ifndef INTERPOLATION_FUNCTION_HPP
#define INTERPOLATION_FUNCTION_HPP

#include <cmath>

class InterpolationFunction
{
public:
    double accTime;
    double vel;

    //関数の説明
    //交点の軌道生成に使用する台形速度曲線
    //各時間毎の目標位置を出力する
    //accTは任意に決めている
    //
    //変数の説明
    //accT:加減速時間, desT:目標位置到達時間, t:現在の時間, desX:desT時の目標位置
    double trapezoidal_velocity_curve(double desTime, double curTime, double desX)
    {
        accTime = 0.20 * desTime;
        vel = desX / (desTime - accTime);

        if (accTime > curTime)
        {
            return 0.50 * (vel / accTime) * pow(curTime, 2);
        }

        if (curTime > accTime && (desTime - accTime) > curTime)
        {
            return 0.50 * accTime * vel + (curTime - accTime) * vel;
        }

        if (curTime > (desTime - accTime))
        {
            return desX - 0.50 * (vel / accTime) * pow((desTime - curTime), 2);
        }

        if (curTime > desTime)
        {
            return desX;
        }
    }
    
    double liner(double desTime, double curTime, double desX)
    {
        return (desX / desTime) * curTime;
    }
};

#endif // INTERPOLATION_FUNCTION_HPP
