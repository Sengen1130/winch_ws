#ifndef DIGITAL_TO_ANALOG_HPP
#define DIGITAL_TO_ANALOG_HPP

#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>
#include <linux/i2c-dev.h>

class DigitalToAnalog
{
public:
    double DAC_MAX = 4096;
    double DAC_VDD = 5.0;

    int fd;
    int mcp4725_address = 0x60; //D/Aコンバータのアドレス
    uint8_t writeBuf[3];

    //関数の説明
    //D/A convert
    //0v - 5.0vを0 - 4096へ変換する
    //
    //変数について
    //volt:電圧
    int16_t volt_to_int16(double volt)
    {
        volt = volt / DAC_VDD * DAC_MAX;
        return int16_t(volt);
    }

    //関数の説明
    //i2c通信の設定
    //
    //変数について
    //
    void set_analog(int16_t input_int16, uint8_t i2c_buffer[3], int fd)
    {
        i2c_buffer[1] = input_int16 >> 4; //MSB 11-4 shift right 4 places
        i2c_buffer[2] = input_int16 << 4; //LSB 3-0 shift left 4 places

        if (write(fd, i2c_buffer, 3) != 3)
        {
            perror("write to register 1");
            exit(1);
        }
        return;
    }

    void check_i2c()
    {

        if ((fd = open("/dev/i2c-1", O_RDWR)) < 0)
        {
            printf("Error: Could'nt open device! %d\n", fd);
            exit(1);
        }

        if (ioctl(fd, I2C_SLAVE, mcp4725_address) < 0)
        {
            printf("Error: Couldn't find device on address!\n");
            exit(1);
        }
    }
};

#endif // DIGITAL_TO_ANALOG_HPP
