;; Auto-generated. Do not edit!


(when (boundp 'listen::listen_results)
  (if (not (find-package "LISTEN"))
    (make-package "LISTEN"))
  (shadow 'listen_results (find-package "LISTEN")))
(unless (find-package "LISTEN::LISTEN_RESULTS")
  (make-package "LISTEN::LISTEN_RESULTS"))

(in-package "ROS")
;;//! \htmlinclude listen_results.msg.html


(defclass listen::listen_results
  :super ros::object
  :slots (_results _index ))

(defmethod listen::listen_results
  (:init
   (&key
    ((:results __results) "")
    ((:index __index) 0)
    )
   (send-super :init)
   (setq _results (string __results))
   (setq _index (round __index))
   self)
  (:results
   (&optional __results)
   (if __results (setq _results __results)) _results)
  (:index
   (&optional __index)
   (if __index (setq _index __index)) _index)
  (:serialization-length
   ()
   (+
    ;; string _results
    4 (length _results)
    ;; int8 _index
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _results
       (write-long (length _results) s) (princ _results s)
     ;; int8 _index
       (write-byte _index s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _results
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _results (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int8 _index
     (setq _index (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _index 127) (setq _index (- _index 256)))
   ;;
   self)
  )

(setf (get listen::listen_results :md5sum-) "d09b62352cfbcede3511b368beb620d8")
(setf (get listen::listen_results :datatype-) "listen/listen_results")
(setf (get listen::listen_results :definition-)
      "string results
int8 index

")



(provide :listen/listen_results "d09b62352cfbcede3511b368beb620d8")


