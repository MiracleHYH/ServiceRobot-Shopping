
(cl:in-package :asdf)

(defsystem "listen-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "listen_results" :depends-on ("_package_listen_results"))
    (:file "_package_listen_results" :depends-on ("_package"))
  ))