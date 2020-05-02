;; Auto-generated. Do not edit!


(when (boundp 'system_control::Record)
  (if (not (find-package "SYSTEM_CONTROL"))
    (make-package "SYSTEM_CONTROL"))
  (shadow 'Record (find-package "SYSTEM_CONTROL")))
(unless (find-package "SYSTEM_CONTROL::RECORD")
  (make-package "SYSTEM_CONTROL::RECORD"))

(in-package "ROS")
;;//! \htmlinclude Record.msg.html


(defclass system_control::Record
  :super ros::object
  :slots (_curTime _curLen _curDesLen ))

(defmethod system_control::Record
  (:init
   (&key
    ((:curTime __curTime) 0.0)
    ((:curLen __curLen) 0.0)
    ((:curDesLen __curDesLen) 0.0)
    )
   (send-super :init)
   (setq _curTime (float __curTime))
   (setq _curLen (float __curLen))
   (setq _curDesLen (float __curDesLen))
   self)
  (:curTime
   (&optional __curTime)
   (if __curTime (setq _curTime __curTime)) _curTime)
  (:curLen
   (&optional __curLen)
   (if __curLen (setq _curLen __curLen)) _curLen)
  (:curDesLen
   (&optional __curDesLen)
   (if __curDesLen (setq _curDesLen __curDesLen)) _curDesLen)
  (:serialization-length
   ()
   (+
    ;; float64 _curTime
    8
    ;; float64 _curLen
    8
    ;; float64 _curDesLen
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _curTime
       (sys::poke _curTime (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _curLen
       (sys::poke _curLen (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _curDesLen
       (sys::poke _curDesLen (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _curTime
     (setq _curTime (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _curLen
     (setq _curLen (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _curDesLen
     (setq _curDesLen (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get system_control::Record :md5sum-) "735e1749b0f1796a905e67b9dfc3aa99")
(setf (get system_control::Record :datatype-) "system_control/Record")
(setf (get system_control::Record :definition-)
      "float64 curTime
float64 curLen
float64 curDesLen

")



(provide :system_control/Record "735e1749b0f1796a905e67b9dfc3aa99")


