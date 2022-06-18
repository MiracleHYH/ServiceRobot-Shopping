;; Auto-generated. Do not edit!


(when (boundp 'listen::listen)
  (if (not (find-package "LISTEN"))
    (make-package "LISTEN"))
  (shadow 'listen (find-package "LISTEN")))
(unless (find-package "LISTEN::LISTEN")
  (make-package "LISTEN::LISTEN"))
(unless (find-package "LISTEN::LISTENREQUEST")
  (make-package "LISTEN::LISTENREQUEST"))
(unless (find-package "LISTEN::LISTENRESPONSE")
  (make-package "LISTEN::LISTENRESPONSE"))

(in-package "ROS")





(defclass listen::listenRequest
  :super ros::object
  :slots ())

(defmethod listen::listenRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass listen::listenResponse
  :super ros::object
  :slots (_result ))

(defmethod listen::listenResponse
  (:init
   (&key
    ((:result __result) nil)
    )
   (send-super :init)
   (setq _result __result)
   self)
  (:result
   (&optional __result)
   (if __result (setq _result __result)) _result)
  (:serialization-length
   ()
   (+
    ;; bool _result
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _result
       (if _result (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _result
     (setq _result (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass listen::listen
  :super ros::object
  :slots ())

(setf (get listen::listen :md5sum-) "eb13ac1f1354ccecb7941ee8fa2192e8")
(setf (get listen::listen :datatype-) "listen/listen")
(setf (get listen::listen :request) listen::listenRequest)
(setf (get listen::listen :response) listen::listenResponse)

(defmethod listen::listenRequest
  (:response () (instance listen::listenResponse :init)))

(setf (get listen::listenRequest :md5sum-) "eb13ac1f1354ccecb7941ee8fa2192e8")
(setf (get listen::listenRequest :datatype-) "listen/listenRequest")
(setf (get listen::listenRequest :definition-)
      "
---
bool result
")

(setf (get listen::listenResponse :md5sum-) "eb13ac1f1354ccecb7941ee8fa2192e8")
(setf (get listen::listenResponse :datatype-) "listen/listenResponse")
(setf (get listen::listenResponse :definition-)
      "
---
bool result
")



(provide :listen/listen "eb13ac1f1354ccecb7941ee8fa2192e8")


