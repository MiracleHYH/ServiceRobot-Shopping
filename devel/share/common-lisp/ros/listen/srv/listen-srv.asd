
(cl:in-package :asdf)

(defsystem "listen-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "listen" :depends-on ("_package_listen"))
    (:file "_package_listen" :depends-on ("_package"))
  ))