; Auto-generated. Do not edit!


(cl:in-package system_control-msg)


;//! \htmlinclude Timing.msg.html

(cl:defclass <Timing> (roslisp-msg-protocol:ros-message)
  ((start_time
    :reader start_time
    :initarg :start_time
    :type cl:float
    :initform 0.0)
   (finish_time
    :reader finish_time
    :initarg :finish_time
    :type cl:float
    :initform 0.0))
)

(cl:defclass Timing (<Timing>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Timing>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Timing)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name system_control-msg:<Timing> is deprecated: use system_control-msg:Timing instead.")))

(cl:ensure-generic-function 'start_time-val :lambda-list '(m))
(cl:defmethod start_time-val ((m <Timing>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader system_control-msg:start_time-val is deprecated.  Use system_control-msg:start_time instead.")
  (start_time m))

(cl:ensure-generic-function 'finish_time-val :lambda-list '(m))
(cl:defmethod finish_time-val ((m <Timing>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader system_control-msg:finish_time-val is deprecated.  Use system_control-msg:finish_time instead.")
  (finish_time m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Timing>) ostream)
  "Serializes a message object of type '<Timing>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'start_time))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'finish_time))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Timing>) istream)
  "Deserializes a message object of type '<Timing>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'start_time) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'finish_time) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Timing>)))
  "Returns string type for a message object of type '<Timing>"
  "system_control/Timing")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Timing)))
  "Returns string type for a message object of type 'Timing"
  "system_control/Timing")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Timing>)))
  "Returns md5sum for a message object of type '<Timing>"
  "77c54173386f0b1fc790cabaf77fbe5d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Timing)))
  "Returns md5sum for a message object of type 'Timing"
  "77c54173386f0b1fc790cabaf77fbe5d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Timing>)))
  "Returns full string definition for message of type '<Timing>"
  (cl:format cl:nil "float64 start_time~%float64 finish_time~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Timing)))
  "Returns full string definition for message of type 'Timing"
  (cl:format cl:nil "float64 start_time~%float64 finish_time~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Timing>))
  (cl:+ 0
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Timing>))
  "Converts a ROS message object to a list"
  (cl:list 'Timing
    (cl:cons ':start_time (start_time msg))
    (cl:cons ':finish_time (finish_time msg))
))
