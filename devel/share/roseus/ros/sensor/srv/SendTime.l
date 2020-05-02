;; Auto-generated. Do not edit!


(when (boundp 'sensor::SendTime)
  (if (not (find-package "SENSOR"))
    (make-package "SENSOR"))
  (shadow 'SendTime (find-package "SENSOR")))
(unless (find-package "SENSOR::SENDTIME")
  (make-package "SENSOR::SENDTIME"))
(unless (find-package "SENSOR::SENDTIMEREQUEST")
  (make-package "SENSOR::SENDTIMEREQUEST"))
(unless (find-package "SENSOR::SENDTIMERESPONSE")
  (make-package "SENSOR::SENDTIMERESPONSE"))

(in-package "ROS")





(defclass sensor::SendTimeRequest
  :super ros::object
  :slots (_second _nsecond ))

(defmethod sensor::SendTimeRequest
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

(defclass sensor::SendTimeResponse
  :super ros::object
  :slots (_success ))

(defmethod sensor::SendTimeResponse
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

(defclass sensor::SendTime
  :super ros::object
  :slots ())

(setf (get sensor::SendTime :md5sum-) "586a87d88cd92bac79b2ab245f6dd834")
(setf (get sensor::SendTime :datatype-) "sensor/SendTime")
(setf (get sensor::SendTime :request) sensor::SendTimeRequest)
(setf (get sensor::SendTime :response) sensor::SendTimeResponse)

(defmethod sensor::SendTimeRequest
  (:response () (instance sensor::SendTimeResponse :init)))

(setf (get sensor::SendTimeRequest :md5sum-) "586a87d88cd92bac79b2ab245f6dd834")
(setf (get sensor::SendTimeRequest :datatype-) "sensor/SendTimeRequest")
(setf (get sensor::SendTimeRequest :definition-)
      "int32 second
int32 nsecond
---
bool success
")

(setf (get sensor::SendTimeResponse :md5sum-) "586a87d88cd92bac79b2ab245f6dd834")
(setf (get sensor::SendTimeResponse :datatype-) "sensor/SendTimeResponse")
(setf (get sensor::SendTimeResponse :definition-)
      "int32 second
int32 nsecond
---
bool success
")



(provide :sensor/SendTime "586a87d88cd92bac79b2ab245f6dd834")


