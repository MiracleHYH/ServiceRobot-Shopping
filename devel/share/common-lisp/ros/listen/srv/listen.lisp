; Auto-generated. Do not edit!


(cl:in-package listen-srv)


;//! \htmlinclude listen-request.msg.html

(cl:defclass <listen-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass listen-request (<listen-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <listen-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'listen-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name listen-srv:<listen-request> is deprecated: use listen-srv:listen-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <listen-request>) ostream)
  "Serializes a message object of type '<listen-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <listen-request>) istream)
  "Deserializes a message object of type '<listen-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<listen-request>)))
  "Returns string type for a service object of type '<listen-request>"
  "listen/listenRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'listen-request)))
  "Returns string type for a service object of type 'listen-request"
  "listen/listenRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<listen-request>)))
  "Returns md5sum for a message object of type '<listen-request>"
  "eb13ac1f1354ccecb7941ee8fa2192e8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'listen-request)))
  "Returns md5sum for a message object of type 'listen-request"
  "eb13ac1f1354ccecb7941ee8fa2192e8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<listen-request>)))
  "Returns full string definition for message of type '<listen-request>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'listen-request)))
  "Returns full string definition for message of type 'listen-request"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <listen-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <listen-request>))
  "Converts a ROS message object to a list"
  (cl:list 'listen-request
))
;//! \htmlinclude listen-response.msg.html

(cl:defclass <listen-response> (roslisp-msg-protocol:ros-message)
  ((result
    :reader result
    :initarg :result
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass listen-response (<listen-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <listen-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'listen-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name listen-srv:<listen-response> is deprecated: use listen-srv:listen-response instead.")))

(cl:ensure-generic-function 'result-val :lambda-list '(m))
(cl:defmethod result-val ((m <listen-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader listen-srv:result-val is deprecated.  Use listen-srv:result instead.")
  (result m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <listen-response>) ostream)
  "Serializes a message object of type '<listen-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'result) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <listen-response>) istream)
  "Deserializes a message object of type '<listen-response>"
    (cl:setf (cl:slot-value msg 'result) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<listen-response>)))
  "Returns string type for a service object of type '<listen-response>"
  "listen/listenResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'listen-response)))
  "Returns string type for a service object of type 'listen-response"
  "listen/listenResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<listen-response>)))
  "Returns md5sum for a message object of type '<listen-response>"
  "eb13ac1f1354ccecb7941ee8fa2192e8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'listen-response)))
  "Returns md5sum for a message object of type 'listen-response"
  "eb13ac1f1354ccecb7941ee8fa2192e8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<listen-response>)))
  "Returns full string definition for message of type '<listen-response>"
  (cl:format cl:nil "bool result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'listen-response)))
  "Returns full string definition for message of type 'listen-response"
  (cl:format cl:nil "bool result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <listen-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <listen-response>))
  "Converts a ROS message object to a list"
  (cl:list 'listen-response
    (cl:cons ':result (result msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'listen)))
  'listen-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'listen)))
  'listen-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'listen)))
  "Returns string type for a service object of type '<listen>"
  "listen/listen")