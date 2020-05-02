import RPi.GPIO as GPIO			# using Rpi.GPIO module
from time import sleep			# import function sleep for delay
GPIO.setmode(GPIO.BCM)			# GPIO numbering
GPIO.setwarnings(False)			# enable warning from GPIO
AN1 = 12				# set pwm1 pin on MD10-hat
DIG1 = 26				# set dir1 pin on MD10-Hat
#GPIO.setup(AN2, GPIO.OUT)		# set pin as output
GPIO.setup(AN1, GPIO.OUT)		# set pin as output
#GPIO.setup(DIG2, GPIO.OUT)		# set pin as output
GPIO.setup(DIG1, GPIO.OUT)		# set pin as output
sleep(1)				# delay for 1 seconds
p1 = GPIO.PWM(AN1, 1000)			# set pwm for M1
#p2 = GPIO.PWM(AN2, 500)			# set pwm for M2

#try:					
  #while True:
print("STOP")
GPIO.output(DIG1, GPIO.LOW)          # Direction can ignore
   #GPIO.output(DIG2, GPIO.LOW)          # Direction can ignore
p1.start(0)                          # set speed for M1 at 0%
   #p2.start(0)                          # set speed for M2 at 0%
sleep(5)

#except:					# exit programe when keyboard interupt
   #p1.start(0)				# set speed to 0
   #p2.start(0)				# set speed to 0
					# Control+x to save file and exit
