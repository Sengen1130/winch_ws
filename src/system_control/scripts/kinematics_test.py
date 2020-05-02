#!/usr/bin/env python
#coding:utf-8

import math

class Kinematics(object):

	def inverse_kinematics(self):
		self.winchPos1 = {'x':0, 'y':0, 'z':0}       #winch:ウインチ位置
		self.winchPos3 = {'x':3, 'y':0, 'z':0}       #winch:ウインチ位置
		self.winchPos4 = {'x':1.5, 'y':2.6, 'z':0}       #winch:ウインチ位置
		
		self.iniPosx = 2
		self.iniPosy = 3
		self.iniPosz = 1
		
		self.iniLen1 = math.sqrt((self.iniPosx - self.winchPos1['x'])**2 + (self.iniPosy - self.winchPos1['y'])**2 + (self.iniPosz - self.winchPos1['z'])**2)
		self.iniLen3 = math.sqrt((self.iniPosx - self.winchPos3['x'])**2 + (self.iniPosy - self.winchPos3['y'])**2 + (self.iniPosz - self.winchPos3['z'])**2)
		self.iniLen4 = math.sqrt((self.iniPosx - self.winchPos4['x'])**2 + (self.iniPosy - self.winchPos4['y'])**2 + (self.iniPosz - self.winchPos4['z'])**2)
		
		print(self.iniLen1)
		print(self.iniLen3)
		print(self.iniLen4)

	def forward_kinematics(self):
		#交点の初期位置
		iniPosx = (self.iniLen1**2 - self.iniLen3**2 + self.winchPos3['x']**2) / (2 * self.winchPos3['x'])
		iniPosy = (self.winchPos3['x'] * self.iniLen3**2 - self.winchPos3['x'] * self.iniLen4**2 + self.winchPos3['x'] * self.winchPos4['y']**2 + self.winchPos3['x'] * self.winchPos4['x']**2 - self.winchPos3['x']**3 + (self.winchPos3['x'] - self.winchPos4['x']) * (self.iniLen1**2 - self.iniLen3**2 + self.winchPos3['x']**2)) / (2 * self.winchPos3['x'] * self.winchPos4['y'])
		iniPosz = math.sqrt(self.iniLen1**2 - (iniPosx**2 + iniPosy**2))
		
		#
		print(iniPosx)
		print(iniPosy)
		print(iniPosz)

if __name__ == '__main__':
	kinematics = Kinematics()
	kinematics.inverse_kinematics()
	kinematics.forward_kinematics()
