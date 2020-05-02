; Auto-generated. Do not edit!


(cl:in-package sensor-srv)


;//! \htmlinclude SendTime-request.msg.html

(cl:defclass <SendTime-request> (roslisp-msg-protocol:ros-message)
  ((second
    :reader second
    :initarg :second
    :type cl:integer
    :initform 0)
   (nsecond
    :reader nsecond
    :initarg :nsecond
    :type cl:integer
    :initform 0))
)

(cl:defclass SendTime-request (<SendTime-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SendTime-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SendTime-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name sensor-srv:<SendTime-request> is deprecated: use sensor-srv:SendTime-request instead.")))

(cl:ensure-generic-function 'second-val :lambda-list '(m))
(cl:defmethod second-val ((m <SendTime-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sensor-srv:second-val is deprecated.  Use sensor-srv:second instead.")
  (second m))

(cl:ensure-generic-function 'nsecond-val :lambda-list '(m))
(cl:defmethod nsecond-val ((m <SendTime-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sensor-srv:nsecond-val is deprecated.  Use sensor-srv:nsecond instead.")
  (nsecond m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SendTime-request>) ostream)
  "Serializes a message object of type '<SendTime-request>"
  (cl:let* ((signed (cl:slot-value msg 'second)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'nsecond)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SendTime-request>) istream)
  "Deserializes a message object of type '<SendTime-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'second) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'nsecond) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SendTime-request>)))
  "Returns string type for a service object of type '<SendTime-request>"
  "sensor/SendTimeRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SendTime-request)))
  "Returns string type for a service object of type 'SendTime-request"
  "sensor/SendTimeRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SendTime-request>)))
  "Returns md5sum for a message object of type '<SendTime-request>"
  "586a87d88cd92bac79b2ab245f6dd834")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SendTime-request)))
  "Returns md5sum for a message object of type 'SendTime-request"
  "586a87d88cd92bac79b2ab245f6dd834")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SendTime-request>)))
  "Returns full string definition for message of type '<SendTime-request>"
  (cl:format cl:nil "int32 second~%int32 nsecond~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SendTime-request)))
  "Returns full string definition for message of type 'SendTime-request"
  (cl:format cl:nil "int32 second~%int32 nsecond~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SendTime-request>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SendTime-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SendTime-request
    (cl:cons ':second (second msg))
    (cl:cons ':nsecond (nsecond msg))
))
;//! \htmlinclude SendTime-response.msg.html

(cl:defclass <SendTime-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SendTime-response (<SendTime-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SendTime-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SendTime-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name sensor-srv:<SendTime-response> is deprecated: use sensor-srv:SendTime-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SendTime-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sensor-srv:success-val is deprecated.  Use sensor-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SendTime-response>) ostream)
  "Serializes a message object of type '<SendTime-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SendTime-response>) istream)
  "Deserializes a message object of type '<SendTime-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SendTime-response>)))
  "Returns string type for a service object of type '<SendTime-response>"
  "sensor/SendTimeResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SendTime-response)))
  "Returns string type for a service object of type 'SendTime-response"
  "sensor/SendTimeResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SendTime-response>)))
  "Returns md5sum for a message object of type '<SendTime-response>"
  "586a87d88cd92bac79b2ab245f6dd834")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SendTime-response)))
  "Returns md5sum for a message object of type 'SendTime-response"
  "586a87d88cd92bac79b2ab245f6dd834")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SendTime-response>)))
  "Returns full string definition for message of type '<SendTime-response>"
  (cl:format cl:nil "bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SendTime-response)))
  "Returns full string definition for message of type 'SendTime-response"
  (cl:format cl:nil "bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SendTime-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SendTime-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SendTime-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SendTime)))
  'SendTime-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SendTime)))
  'SendTime-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SendTime)))
  "Returns string type for a service object of type '<SendTime>"
  "sensor/SendTime")