;; Auto-generated. Do not edit!


(when (boundp 'potentiometer::Log)
  (if (not (find-package "POTENTIOMETER"))
    (make-package "POTENTIOMETER"))
  (shadow 'Log (find-package "POTENTIOMETER")))
(unless (find-package "POTENTIOMETER::LOG")
  (make-package "POTENTIOMETER::LOG"))

(in-package "ROS")
;;//! \htmlinclude Log.msg.html


(defclass potentiometer::Log
  :super ros::object
  :slots (_data0 _data1 _data2 _data3 _data4 ))

(defmethod potentiometer::Log
  (:init
   (&key
    ((:data0 __data0) 0.0)
    ((:data1 __data1) 0)
    ((:data2 __data2) 0)
    ((:data3 __data3) 0.0)
    ((:data4 __data4) 0.0)
    )
   (send-super :init)
   (setq _data0 (float __data0))
   (setq _data1 (round __data1))
   (setq _data2 (round __data2))
   (setq _data3 (float __data3))
   (setq _data4 (float __data4))
   self)
  (:data0
   (&optional __data0)
   (if __data0 (setq _data0 __data0)) _data0)
  (:data1
   (&optional __data1)
   (if __data1 (setq _data1 __data1)) _data1)
  (:data2
   (&optional __data2)
   (if __data2 (setq _data2 __data2)) _data2)
  (:data3
   (&optional __data3)
   (if __data3 (setq _data3 __data3)) _data3)
  (:data4
   (&optional __data4)
   (if __data4 (setq _data4 __data4)) _data4)
  (:serialization-length
   ()
   (+
    ;; float64 _data0
    8
    ;; int32 _data1
    4
    ;; int32 _data2
    4
    ;; float64 _data3
    8
    ;; float64 _data4
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _data0
       (sys::poke _data0 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _data1
       (write-long _data1 s)
     ;; int32 _data2
       (write-long _data2 s)
     ;; float64 _data3
       (sys::poke _data3 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _data4
       (sys::poke _data4 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _data0
     (setq _data0 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _data1
     (setq _data1 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _data2
     (setq _data2 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _data3
     (setq _data3 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _data4
     (setq _data4 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get potentiometer::Log :md5sum-) "3bc9c20a1bbcd292f1a59fbbe069fe8d")
(setf (get potentiometer::Log :datatype-) "potentiometer/Log")
(setf (get potentiometer::Log :definition-)
      "float64 data0
int32 data1
int32 data2
float64 data3
float64 data4

")



(provide :potentiometer/Log "3bc9c20a1bbcd292f1a59fbbe069fe8d")


