; Auto-generated. Do not edit!


(cl:in-package listen-msg)


;//! \htmlinclude listen_results.msg.html

(cl:defclass <listen_results> (roslisp-msg-protocol:ros-message)
  ((results
    :reader results
    :initarg :results
    :type cl:string
    :initform "")
   (index
    :reader index
    :initarg :index
    :type cl:fixnum
    :initform 0))
)

(cl:defclass listen_results (<listen_results>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <listen_results>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'listen_results)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name listen-msg:<listen_results> is deprecated: use listen-msg:listen_results instead.")))

(cl:ensure-generic-function 'results-val :lambda-list '(m))
(cl:defmethod results-val ((m <listen_results>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader listen-msg:results-val is deprecated.  Use listen-msg:results instead.")
  (results m))

(cl:ensure-generic-function 'index-val :lambda-list '(m))
(cl:defmethod index-val ((m <listen_results>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader listen-msg:index-val is deprecated.  Use listen-msg:index instead.")
  (index m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <listen_results>) ostream)
  "Serializes a message object of type '<listen_results>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'results))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'results))
  (cl:let* ((signed (cl:slot-value msg 'index)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <listen_results>) istream)
  "Deserializes a message object of type '<listen_results>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'results) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'results) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'index) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<listen_results>)))
  "Returns string type for a message object of type '<listen_results>"
  "listen/listen_results")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'listen_results)))
  "Returns string type for a message object of type 'listen_results"
  "listen/listen_results")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<listen_results>)))
  "Returns md5sum for a message object of type '<listen_results>"
  "d09b62352cfbcede3511b368beb620d8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'listen_results)))
  "Returns md5sum for a message object of type 'listen_results"
  "d09b62352cfbcede3511b368beb620d8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<listen_results>)))
  "Returns full string definition for message of type '<listen_results>"
  (cl:format cl:nil "string results~%int8 index~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'listen_results)))
  "Returns full string definition for message of type 'listen_results"
  (cl:format cl:nil "string results~%int8 index~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <listen_results>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'results))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <listen_results>))
  "Converts a ROS message object to a list"
  (cl:list 'listen_results
    (cl:cons ':results (results msg))
    (cl:cons ':index (index msg))
))
