;; Auto-generated. Do not edit!


(when (boundp 'system_control::Timing)
  (if (not (find-package "SYSTEM_CONTROL"))
    (make-package "SYSTEM_CONTROL"))
  (shadow 'Timing (find-package "SYSTEM_CONTROL")))
(unless (find-package "SYSTEM_CONTROL::TIMING")
  (make-package "SYSTEM_CONTROL::TIMING"))

(in-package "ROS")
;;//! \htmlinclude Timing.msg.html


(defclass system_control::Timing
  :super ros::object
  :slots (_start_time _finish_time ))

(defmethod system_control::Timing
  (:init
   (&key
    ((:start_time __start_time) 0.0)
    ((:finish_time __finish_time) 0.0)
    )
   (send-super :init)
   (setq _start_time (float __start_time))
   (setq _finish_time (float __finish_time))
   self)
  (:start_time
   (&optional __start_time)
   (if __start_time (setq _start_time __start_time)) _start_time)
  (:finish_time
   (&optional __finish_time)
   (if __finish_time (setq _finish_time __finish_time)) _finish_time)
  (:serialization-length
   ()
   (+
    ;; float64 _start_time
    8
    ;; float64 _finish_time
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _start_time
       (sys::poke _start_time (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _finish_time
       (sys::poke _finish_time (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _start_time
     (setq _start_time (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _finish_time
     (setq _finish_time (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get system_control::Timing :md5sum-) "77c54173386f0b1fc790cabaf77fbe5d")
(setf (get system_control::Timing :datatype-) "system_control/Timing")
(setf (get system_control::Timing :definition-)
      "float64 start_time
float64 finish_time

")



(provide :system_control/Timing "77c54173386f0b1fc790cabaf77fbe5d")


