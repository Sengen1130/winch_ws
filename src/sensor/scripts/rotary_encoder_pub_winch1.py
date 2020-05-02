#!/usr/bin/env python
#coding:utf-8

from RPi import GPIO            
import rospy
from std_msgs.msg import Float64
import time

rospy.init_node('rotary_encoder_winch3')           #ノード名の設定
count_pub = rospy.Publisher('rotary_encoder_count_winch3', Float64, queue_size=10)               #エンコーダカウント値publish 
rate = rospy.Rate(100)

clk = 5         #A相のピン名
dt = 6          #B相のピン名

GPIO.setmode(GPIO.BCM)          #拡張コネクタのピン番号をCPUのピン名で指定
GPIO.setup(clk, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)              #使用するGPIOピンの設定(プルダウン)
GPIO.setup(dt, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)              #使用するGPIPピンの設定(プルダウン)

counter = 0
clkLastState = GPIO.input(clk)     
       
try:

        while True:
            clkState = GPIO.input(clk)
            dtState = GPIO.input(dt)
    
            if clkState != clkLastState:            #入力があった場合のみ
                if dtState != clkState:         #A相とB相の状態が異なる場合
                    counter += 0.5          #反時計回り
                else:
                    counter -= 0.5          #時計回り
                print(counter)
        
            clkLastState = clkState
            count_pub.publish(counter)
            rate.sleep()
            
finally:
    GPIO.cleanup()          #チャンネルで使用したGPIOを解放する
