#!/usr/bin/env python
# -*- coding:utf-8 -*-

from RPi import GPIO            
import time		# time ライブラリをインポート
import spidev		# spi ライブラリをインポート
from sensor.msg import adder
from std_msgs.msg import Int32
import rospy

class Sensor(object):
	
	def __init__(self):
		self.angle_pub = rospy.Publisher('twoangles_winch3', adder, queue_size=10)
		self.count_pub = rospy.Publisher('encoder_count_winch3', Int32, queue_size=10)
	

	def rotary_encoder(self):
		rate = rospy.Rate(100)
		A = 5         #A相のピン名
		B = 6          #B相のピン名

		GPIO.setmode(GPIO.BCM)          #拡張コネクタのピン番号をCPUのピン名で指定
		GPIO.setup(A, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)              #使用するGPIOピンの設定(プルダウン)
		GPIO.setup(B, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)              #使用するGPIPピンの設定(プルダウン)

		counter = 0
		clkLastState = GPIO.input(A)            

		while not rospy.is_shutdown():
			clkState = GPIO.input(A)
			dtState = GPIO.input(B)
			
			if clkState != clkLastState:            #入力があった場合のみ
				if dtState != clkState:         #A相とB相の状態が異なる場合
						counter += 0.5          #反時計回り
				else:
						counter -= 0.5          #時計回り
				print(counter)
				
			clkLastState = clkState
			self.count_pub.publish(counter)
			rate.sleep()
			
		GPIO.cleanup()          #チャンネルで使用したGPIOを解放する
		
	def potentiometer(self):
		rate = rospy.Rate(100)
		spi = spidev.SpiDev()		# SpiDev オブジェクトのインスタンスを生成
		spi.open(0, 0)			# ポート0、デバイス0のSPI をオープン
		spi.max_speed_hz=1000000		# 最大クロックスピードを1MHz に設定
		spi.bits_per_word=8		# 1 ワードあたり8ビットに設定
		dummy = 0xff		# ダミーデータを設定（1111 1111）
		start = 0x47		# スタートビットを設定（0100 0111）
		sgl = 0x20		# シングルエンドモードを設定 （0010 0000）
		ch0 = 0x00		# ch0 を選択（0000 0000）
		ch1 = 0x10		# ch1 を選択（0001 0000）
		msbf = 0x08		# MSB ファーストモードを選択（0000 1000）

		# IC からデータを取得する関数を定義
		def measure(ch):
			ad = spi.xfer2( [ (start + sgl + ch + msbf), dummy ] )		# SPI インターフェイスでデータの送受信を行う
			val = ( ( ( (ad[0] & 0x03) << 8) + ad[1] ) * 3.3 ) / 1023		# 受信した2バイトのデータを10 ビットデータにまとめる
			return val		# 結果を返す
			
		while not rospy.is_shutdown():
			ANGLE = adder()
			mes_ch1 = measure(ch0)		# 関数を呼び出してch0 のデータを取得
			mes_ch2 = measure(ch1)		# 関数を呼び出してch1 のデータを取得
			angle1 = -(mes_ch1 * 280 / 3.3 - 101)
			angle2 = mes_ch2 * 330 / 3.3 - 205
			ANGLE.angle1 = angle1
			ANGLE.angle2 = angle2
			self.angle_pub.publish(ANGLE)
			print ('alpha = %d' % angle1,'[deg], beta = %d' % angle2,'[deg]')		# 結果を表示
			rate.sleep()
			
		spi.close()		# SPI を開放
	
if __name__ == '__main__':  
	rospy.init_node('calculate_winch3')
	sensor = Sensor()
	#sensor.rotary_encoder()
	sensor.potentiometer()
	

