;; Auto-generated. Do not edit!


(when (boundp 'potentiometer::SendTime)
  (if (not (find-package "POTENTIOMETER"))
    (make-package "POTENTIOMETER"))
  (shadow 'SendTime (find-package "POTENTIOMETER")))
(unless (find-package "POTENTIOMETER::SENDTIME")
  (make-package "POTENTIOMETER::SENDTIME"))
(unless (find-package "POTENTIOMETER::SENDTIMEREQUEST")
  (make-package "POTENTIOMETER::SENDTIMEREQUEST"))
(unless (find-package "POTENTIOMETER::SENDTIMERESPONSE")
  (make-package "POTENTIOMETER::SENDTIMERESPONSE"))

(in-package "ROS")





(defclass potentiometer::SendTimeRequest
  :super ros::object
  :slots (_second _nsecond ))

(defmethod potentiometer::SendTimeRequest
  (:init
   (&key
    ((:second __second) 0)
    ((:nsecond __nsecond) 0)
    )
   (send-super :init)
   (setq _second (round __second))
   (setq _nsecond (round __nsecond))
   self)
  (:second
   (&optional __second)
   (if __second (setq _second __second)) _second)
  (:nsecond
   (&optional __nsecond)
   (if __nsecond (setq _nsecond __nsecond)) _nsecond)
  (:serialization-length
   ()
   (+
    ;; int32 _second
    4
    ;; int32 _nsecond
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _second
       (write-long _second s)
     ;; int32 _nsecond
       (write-long _nsecond s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _second
     (setq _second (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _nsecond
     (setq _nsecond (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass potentiometer::SendTimeResponse
  :super ros::object
  :slots (_success ))

(defmethod potentiometer::SendTimeResponse
  (:init
   (&key
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _success __success)
   self)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass potentiometer::SendTime
  :super ros::object
  :slots ())

(setf (get potentiometer::SendTime :md5sum-) "586a87d88cd92bac79b2ab245f6dd834")
(setf (get potentiometer::SendTime :datatype-) "potentiometer/SendTime")
(setf (get potentiometer::SendTime :request) potentiometer::SendTimeRequest)
(setf (get potentiometer::SendTime :response) potentiometer::SendTimeResponse)

(defmethod potentiometer::SendTimeRequest
  (:response () (instance potentiometer::SendTimeResponse :init)))

(setf (get potentiometer::SendTimeRequest :md5sum-) "586a87d88cd92bac79b2ab245f6dd834")
(setf (get potentiometer::SendTimeRequest :datatype-) "potentiometer/SendTimeRequest")
(setf (get potentiometer::SendTimeRequest :definition-)
      "int32 second
int32 nsecond
---
bool success
")

(setf (get potentiometer::SendTimeResponse :md5sum-) "586a87d88cd92bac79b2ab245f6dd834")
(setf (get potentiometer::SendTimeResponse :datatype-) "potentiometer/SendTimeResponse")
(setf (get potentiometer::SendTimeResponse :definition-)
      "int32 second
int32 nsecond
---
bool success
")



(provide :potentiometer/SendTime "586a87d88cd92bac79b2ab245f6dd834")


