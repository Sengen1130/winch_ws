#ifndef DIGITAL_FILTER_HPP
#define DIGITAL_FILTER_HPP

#include <cmath>

class DigitalFilter
{
public:
    double vel;
    double samplerate = 1000; //サンプリング周波数
    double freq = 2.0;        //カットオフ周波数
    double q = 0.70710;       //フィルタのQ値
    double omega = 2.0 * 3.14159265 * freq / samplerate;
    double alpha = sin(omega) / (2.0 * q);
    double a0 = 1.0 + alpha;
    double a1 = -2.0 * cos(omega);
    double a2 = 1.0 - alpha;
    double b0 = (1.0 - cos(omega)) / 2.0;
    double b1 = 1.0 - cos(omega);
    double b2 = (1.0 - cos(omega)) / 2.0;

    //関数の説明
    //2nd order backward diff
    double second_order_backward_diff(double count, double count_prev1, double count_prev2)
    {
        vel = (3 * count - 4 * count_prev1 + count_prev2) / 0.002;

        return vel;
    }

    //関数の説明
    //双二次ローパスフィルター
    double low_pass_filter(double input, double prevInput1, double prevInput2, double prevOutput1, double prevOutput2)
    {
        double output = b0 / a0 * input + b1 / a0 * prevInput1 + b2 / a0 * prevInput2 - a1 / a0 * prevOutput1 - a2 / a0 * prevOutput2; //入力信号にフィルタを適用し、出力信号として書き出す
        return output;
    }
};

#endif // DIGITAL_FILTER_HPP