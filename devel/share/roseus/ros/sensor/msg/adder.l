;; Auto-generated. Do not edit!


(when (boundp 'sensor::adder)
  (if (not (find-package "SENSOR"))
    (make-package "SENSOR"))
  (shadow 'adder (find-package "SENSOR")))
(unless (find-package "SENSOR::ADDER")
  (make-package "SENSOR::ADDER"))

(in-package "ROS")
;;//! \htmlinclude adder.msg.html


(defclass sensor::adder
  :super ros::object
  :slots (_angle1 _angle2 ))

(defmethod sensor::adder
  (:init
   (&key
    ((:angle1 __angle1) 0)
    ((:angle2 __angle2) 0)
    )
   (send-super :init)
   (setq _angle1 (round __angle1))
   (setq _angle2 (round __angle2))
   self)
  (:angle1
   (&optional __angle1)
   (if __angle1 (setq _angle1 __angle1)) _angle1)
  (:angle2
   (&optional __angle2)
   (if __angle2 (setq _angle2 __angle2)) _angle2)
  (:serialization-length
   ()
   (+
    ;; int16 _angle1
    2
    ;; int16 _angle2
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int16 _angle1
       (write-word _angle1 s)
     ;; int16 _angle2
       (write-word _angle2 s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16 _angle1
     (setq _angle1 (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _angle2
     (setq _angle2 (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get sensor::adder :md5sum-) "ac081811000950995a96c1d7019e5876")
(setf (get sensor::adder :datatype-) "sensor/adder")
(setf (get sensor::adder :definition-)
      "int16 angle1
int16 angle2

")



(provide :sensor/adder "ac081811000950995a96c1d7019e5876")


