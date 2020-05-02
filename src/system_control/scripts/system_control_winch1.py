#!/usr/bin/env python
#coding:utf-8

#pythonでのrosライブラリをインポート
import rospy
from std_msgs.msg import Int32
from std_msgs.msg import Float64
from geometry_msgs.msg import Vector3
from sensor.msg import adder
import math
import time
import RPi.GPIO as GPIO     # Rpi.GPIO moduleをインポート


class SystemControl(object):
    #
    def __init__(self):
        self.prevTime = 0       #前回の時間の初期化
        self.R = 0.583       #R:モータの内部抵抗
        self.k = 0.00615     #k:トルク定数
        self.d = 0.04        #d:ドラム径
        self.PI = math.pi        #PI:円周率の近似値
        self.Vmax = 15       #最大電圧
        self.prevCount = 0
        self.prevI = 0
        self.Tp = 0
        self.prevDesCount =0
        self.gain = {'Kp':0.00005, 'Kd':0.00001}        #gain:PIDゲイン
        self.iniLen1 = 3
        self.iniLen4 = 3

        #初期長さ値publish, エンコーダ、ポテンショメータの値subscribe
        self.angle_sub = rospy.Subscriber('twoangles_winch3', adder, self.potentiometer_callback)
        self.count_sub = rospy.Subscriber('encoder_count_winch3', Int32, self.encoder_callback)
        self.start_time_sub = rospy.Subscriber('start_time', Float64, self.start_time_callback)
        self.finish_time_sub = rospy.Subscriber('finish_time', Float64, self.finish_time_callback)
        self.finish_position_sub = rospy.Subscriber('finish_position', Vector3, self.finish_position_callback)
        self.iniLen1_sub = rospy.Subscriber('initial_length_winch1', Float64, self.initial_length_winch1_callback)
        self.iniLen4_sub = rospy.Subscriber('initial_length_winch4', Float64, self.initial_length_winch4_callback)
        self.iniLen3_pub = rospy.Publisher('initial_length_winch3', Float64, queue_size=10)
        
        self.curLen3_pub = rospy.Publisher('curLen3', Float64, queue_size=10)
        self.curDesLen3_pub = rospy.Publisher('curDesLen3', Float64, queue_size=10)

    #モータの初期設定
    def motor_setup(self):
        GPIO.setmode(GPIO.BCM)			# GPIO numbering
        GPIO.setwarnings(False)			# enable warning from GPIO
        AN1 = 12				# set pwm1 pin on MD10-hat
        self.DIG1 = 26				# set dir1 pin on MD10-Hat
        GPIO.setup(AN1, GPIO.OUT)		# set pin as output
        GPIO.setup(self.DIG1, GPIO.OUT)		# set pin as output
        self.p1 = GPIO.PWM(AN1, 1111)			# set pwm for M1
        GPIO.output(self.DIG1, GPIO.LOW)          # Direction can ignore
        self.p1.start(10)                          # set speed for M1 at 0%
        time.sleep(0.1)
        self.iniCount = self.curCount
        self.iniLen3 = self.d * (self.PI / 3600) * self.iniCount     #iniLen:最初の長さ
        self.iniLen3_pub.publish(self.iniLen3)
        self.p1.start(0)
        time.sleep(3)
        
    #    
    def foward_kinematics(self):
        self.winchPos1 = {'x':0, 'y':0, 'z':0}       #winch:ウインチ位置
        self.winchPos3 = {'x':3, 'y':0, 'z':0}       #winch:ウインチ位置
        self.winchPos4 = {'x':1.5, 'y':2.6, 'z':0}       #winch:ウインチ位置
		#交点の初期位置
        self.iniPosx = (self.iniLen1**2 - self.iniLen3**2 + self.winchPos3['x']**2) / (2 * self.winchPos3['x'])
        self.iniPosy = (self.winchPos3['x'] * self.iniLen3**2 - self.winchPos3['x'] * self.iniLen4**2 + self.winchPos3['x'] * self.winchPos4['y']**2 + self.winchPos3['x'] * self.winchPos4['x']**2 - self.winchPos3['x']**3 + (self.winchPos3['x'] - self.winchPos4['x']) * (self.iniLen1**2 - self.iniLen3**2 + self.winchPos3['x']**2)) / (2 * self.winchPos3['x'] * self.winchPos4['y'])
        self.iniPosz = math.sqrt(abs(self.iniLen1**2 - (self.iniPosx**2 + self.iniPosy**2))) 
        
        
    def trapezoidal_velocity_curve(self, t_acc, t_d, t, x_d):
        v = x_d / (t_d - t_acc)
        if t_acc > t:
            return 0.5 * (v / t_acc) * t**2
        
        if t > t_acc and (t_d - t_acc) > t:
            return 0.5 * t_acc * v + (t - t_acc) * v
        
        if t > (t_d - t_acc):
            return x_d - 0.5 * (v / t_acc) * (t_d - t)**2

    #ポテンショメータ読み取り
    def potentiometer_callback(self,angle_msg):
        self.alpha = angle_msg.angle1        #alpha:ジンバル縦ふり
        self.beta = angle_msg.angle2      #beta:ジンバル横ふり
        
    #エンコーダ読み取り
    def encoder_callback(self,count):
        self.Tc = rospy.Time.now().to_sec()
        #エンコーダカウント値読み取り
        self.curCount = count.data       #curCount:現在のエンコーダカウント値
        self.curCountVel = (self.curCount - self.prevCount) / (self.Tc - self.Tp)     #curCountVel:現在のエンコーダカウント値速度     
        self.prevCount = self.curCount        #prevCount:前回のエンコーダカウント値
        self.prevCountVel = self.curCountVel     #prevCount:前回のエンコーダカウント値
        self.Tp = self.Tc
        
    #winch1の初期長さのsubscribe
    def initial_length_winch1_callback(self, iniLen1_msg):
        self.iniLen1 = iniLen1_msg.data

    #winch3の初期長さのsubscribe
    def initial_length_winch4_callback(self, iniLen4_msg):
        self.iniLen4 = iniLen4_msg.data

    #開始時刻,終了時刻のsubscribe
    def start_time_callback(self, start_msg):
        self.start_time = start_msg.data
        
    def finish_time_callback(self, finish_msg):
        self.finish_time = finish_msg.data
        
    #目標位置のsubscribe
    def finish_position_callback(self, finPos_msg):
        self.finPosx = finPos_msg.x
        self.finPosy = finPos_msg.y
        self.finPosz = finPos_msg.z

    #位置制御
    def position_control(self):
        rate = rospy.Rate(100)       #1Hzあたりの実行回数
        s = SystemControl()
        finLen = math.sqrt((self.finPosx - self.winchPos3['x'])**2 + (self.finPosy - self.winchPos3['y'])**2 + (self.finPosz - self.winchPos3['z'])**2)      #foward kinematics finLen:目標長さ
        
        iniTime = rospy.Time.now().to_sec()     #プログラム開始時刻
        duration = self.start_time - iniTime
        time.sleep(duration)
        self.finTime = self.finish_time - iniTime        #目標位置到達時刻
        t_acc = self.finTime * 0.15    
        
        while not rospy.is_shutdown() and rospy.Time.now().to_sec() - iniTime < self.finTime: 

            self.curTime = rospy.Time.now().to_sec() - iniTime   #現在の時間 

            curLen = self.d * (self.PI / 3600) * self.curCount     #curLen:現在のワイヤ長さ
            curAdx = s.trapezoidal_velocity_curve(t_acc, self.finTime, self.curTime, self.finPosx)
            curAdy = s.trapezoidal_velocity_curve(t_acc, self.finTime, self.curTime, self.finPosy)
            curAdz = s.trapezoidal_velocity_curve(t_acc, self.finTime, self.curTime, self.finPosz)
            curDesx = self.iniPosx + curAdx
            curDesy = self.iniPosy + curAdy
            curDesz = self.iniPosz + curAdz
            curDesLen = math.sqrt((curDesx - self.winchPos3['x'])**2 + (curDesy - self.winchPos3['y'])**2 + (curDesz - self.winchPos3['z'])**2)
            curDesCount = (curDesLen * 3600) / (self.d * self.PI)    #curDesLen:現在の目標長さ
            curDesCountVel = (curDesCount - self.prevDesCount) / (self.curTime - self.prevTime)      #curDesLenVel:現在の目標速度 
            
            self.curLen3_pub.publish(curLen)
            self.curDesLen3_pub.publish(curDesLen)
            
            #PD制御
            P = self.gain['Kp'] * (curDesCount - self.curCount)       #P項
            D = self.gain['Kd'] * (curDesCountVel - self.curCountVel)     #D項
            torque = abs(P + D)      #目標トルク
            
            Vout = self.R * torque / self.k + self.k * abs(self.curCountVel) / 10        #出力する目標電圧

            self.prevDesCount = curDesCount

            #目標電圧のリミット
            if Vout > 15:
                Vout = 15
            
            #現在の長さが目標長さより長い場合巻き取り、短い場合繰り出し
            if (P + D) < 0 :        
                pwm = 100 * abs(Vout) / self.Vmax     #pwm比決定
                GPIO.output(self.DIG1, GPIO.HIGH)		# set DIG1 as HIGH, M1B will turn ON
                self.p1.start(pwm)		 	# set speed for M1 at pwm(%)
                
            else:
                pwm = 100 * abs(Vout) / self.Vmax     #pwm比決定
                GPIO.output(self.DIG1, GPIO.LOW)		# set DIG1 as HIGH, M1B will turn ON
                self.p1.start(pwm)		 	# set speed for M1 at pwm(%)
            
            self.prevTime = self.curTime      #prevTime:前回の時間  
            rate.sleep()        #指定周期を保つ
            
        #プログラム終了
        print('program finish')     

        """放電"""
        GPIO.output(self.DIG1, GPIO.LOW)          # Direction can ignore
        self.p1.start(0)                          # set speed for M1 at 0%
        time.sleep(5)

        
if __name__ == '__main__':  

    rospy.init_node('position_control_winch3')      #node名の設定

    #クラスの呼び出し
    system_control = SystemControl()
    system_control.motor_setup()
    system_control.foward_kinematics()
    system_control.position_control()






