#!/usr/bin/env python
# -*- coding:utf-8 -*-

import rospy
import time		# time ライブラリをインポート
from sensor.msg import adder
from std_msgs.msg import Int32


class SensorDisplay(object):
	def __init__(self):
		self.angle_sub = rospy.Subscriber('twoangles_winch3', adder, self.potentiometer_callback)
        self.count_sub = rospy.Subscriber('rotary_encoder_count_winch3', Int32, self.encoder_callback)
        
	def encoder_callback(self,encoder_msg):
		self.count = encoder_msg.data
		print(self.count)
		
	def potentiometer_callback(self,angle_msg):
		self.alpha = angle_msg.angle1        #alpha:ジンバル縦ふり
        self.beta = angle_msg.angle2      #beta:ジンバル横ふり
        print('alpha = %d' % self.alpha,'[deg], beta = %d' % self.beta,'[deg]')
        

if __name__ == '__main__':  
	rospy.init_node('sensor_display')
	sensor_display = SensorDisplay()
	sensor_display.display()
