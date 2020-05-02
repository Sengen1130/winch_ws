; Auto-generated. Do not edit!


(cl:in-package sensor-msg)


;//! \htmlinclude adder.msg.html

(cl:defclass <adder> (roslisp-msg-protocol:ros-message)
  ((angle1
    :reader angle1
    :initarg :angle1
    :type cl:fixnum
    :initform 0)
   (angle2
    :reader angle2
    :initarg :angle2
    :type cl:fixnum
    :initform 0))
)

(cl:defclass adder (<adder>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <adder>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'adder)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name sensor-msg:<adder> is deprecated: use sensor-msg:adder instead.")))

(cl:ensure-generic-function 'angle1-val :lambda-list '(m))
(cl:defmethod angle1-val ((m <adder>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sensor-msg:angle1-val is deprecated.  Use sensor-msg:angle1 instead.")
  (angle1 m))

(cl:ensure-generic-function 'angle2-val :lambda-list '(m))
(cl:defmethod angle2-val ((m <adder>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sensor-msg:angle2-val is deprecated.  Use sensor-msg:angle2 instead.")
  (angle2 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <adder>) ostream)
  "Serializes a message object of type '<adder>"
  (cl:let* ((signed (cl:slot-value msg 'angle1)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'angle2)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <adder>) istream)
  "Deserializes a message object of type '<adder>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'angle1) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'angle2) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<adder>)))
  "Returns string type for a message object of type '<adder>"
  "sensor/adder")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'adder)))
  "Returns string type for a message object of type 'adder"
  "sensor/adder")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<adder>)))
  "Returns md5sum for a message object of type '<adder>"
  "ac081811000950995a96c1d7019e5876")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'adder)))
  "Returns md5sum for a message object of type 'adder"
  "ac081811000950995a96c1d7019e5876")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<adder>)))
  "Returns full string definition for message of type '<adder>"
  (cl:format cl:nil "int16 angle1~%int16 angle2~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'adder)))
  "Returns full string definition for message of type 'adder"
  (cl:format cl:nil "int16 angle1~%int16 angle2~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <adder>))
  (cl:+ 0
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <adder>))
  "Converts a ROS message object to a list"
  (cl:list 'adder
    (cl:cons ':angle1 (angle1 msg))
    (cl:cons ':angle2 (angle2 msg))
))
