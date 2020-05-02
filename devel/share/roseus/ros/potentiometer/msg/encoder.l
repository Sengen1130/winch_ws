;; Auto-generated. Do not edit!


(when (boundp 'potentiometer::encoder)
  (if (not (find-package "POTENTIOMETER"))
    (make-package "POTENTIOMETER"))
  (shadow 'encoder (find-package "POTENTIOMETER")))
(unless (find-package "POTENTIOMETER::ENCODER")
  (make-package "POTENTIOMETER::ENCODER"))

(in-package "ROS")
;;//! \htmlinclude encoder.msg.html


(defclass potentiometer::encoder
  :super ros::object
  :slots (_desired _actual ))

(defmethod potentiometer::encoder
  (:init
   (&key
    ((:desired __desired) 0)
    ((:actual __actual) 0)
    )
   (send-super :init)
   (setq _desired (round __desired))
   (setq _actual (round __actual))
   self)
  (:desired
   (&optional __desired)
   (if __desired (setq _desired __desired)) _desired)
  (:actual
   (&optional __actual)
   (if __actual (setq _actual __actual)) _actual)
  (:serialization-length
   ()
   (+
    ;; int32 _desired
    4
    ;; int32 _actual
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _desired
       (write-long _desired s)
     ;; int32 _actual
       (write-long _actual s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _desired
     (setq _desired (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _actual
     (setq _actual (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get potentiometer::encoder :md5sum-) "228bf8fb168564ebccf3e320dc392525")
(setf (get potentiometer::encoder :datatype-) "potentiometer/encoder")
(setf (get potentiometer::encoder :definition-)
      "int32 desired
int32 actual
")



(provide :potentiometer/encoder "228bf8fb168564ebccf3e320dc392525")


