#!/usr/bin/env python
# -*- coding:utf-8 -*-

# spi ライブラリをインポート
import spidev
import rospy
#pk:std_msgs, msg file:Int16.msg
from std_msgs.msg import Int16
from sensor.msg import adder

# time ライブラリをインポート
import time

#roska
rospy.init_node('potentiometer_winch1')
pub = rospy.Publisher('two_angles_winch1', adder, queue_size=10)
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
    pub.publish(ANGLE)
    print ('alpha = %d' % angle1,'[deg], beta = %d' % angle2,'[deg]')		# 結果を表示
    rate.sleep()
    
spi.close()		# SPI を開放
