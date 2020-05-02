; Auto-generated. Do not edit!


(cl:in-package system_control-msg)


;//! \htmlinclude Record.msg.html

(cl:defclass <Record> (roslisp-msg-protocol:ros-message)
  ((curTime
    :reader curTime
    :initarg :curTime
    :type cl:float
    :initform 0.0)
   (curLen
    :reader curLen
    :initarg :curLen
    :type cl:float
    :initform 0.0)
   (curDesLen
    :reader curDesLen
    :initarg :curDesLen
    :type cl:float
    :initform 0.0))
)

(cl:defclass Record (<Record>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Record>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Record)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name system_control-msg:<Record> is deprecated: use system_control-msg:Record instead.")))

(cl:ensure-generic-function 'curTime-val :lambda-list '(m))
(cl:defmethod curTime-val ((m <Record>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader system_control-msg:curTime-val is deprecated.  Use system_control-msg:curTime instead.")
  (curTime m))

(cl:ensure-generic-function 'curLen-val :lambda-list '(m))
(cl:defmethod curLen-val ((m <Record>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader system_control-msg:curLen-val is deprecated.  Use system_control-msg:curLen instead.")
  (curLen m))

(cl:ensure-generic-function 'curDesLen-val :lambda-list '(m))
(cl:defmethod curDesLen-val ((m <Record>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader system_control-msg:curDesLen-val is deprecated.  Use system_control-msg:curDesLen instead.")
  (curDesLen m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Record>) ostream)
  "Serializes a message object of type '<Record>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'curTime))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'curLen))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'curDesLen))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Record>) istream)
  "Deserializes a message object of type '<Record>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'curTime) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'curLen) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'curDesLen) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Record>)))
  "Returns string type for a message object of type '<Record>"
  "system_control/Record")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Record)))
  "Returns string type for a message object of type 'Record"
  "system_control/Record")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Record>)))
  "Returns md5sum for a message object of type '<Record>"
  "735e1749b0f1796a905e67b9dfc3aa99")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Record)))
  "Returns md5sum for a message object of type 'Record"
  "735e1749b0f1796a905e67b9dfc3aa99")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Record>)))
  "Returns full string definition for message of type '<Record>"
  (cl:format cl:nil "float64 curTime~%float64 curLen~%float64 curDesLen~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Record)))
  "Returns full string definition for message of type 'Record"
  (cl:format cl:nil "float64 curTime~%float64 curLen~%float64 curDesLen~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Record>))
  (cl:+ 0
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Record>))
  "Converts a ROS message object to a list"
  (cl:list 'Record
    (cl:cons ':curTime (curTime msg))
    (cl:cons ':curLen (curLen msg))
    (cl:cons ':curDesLen (curDesLen msg))
))
