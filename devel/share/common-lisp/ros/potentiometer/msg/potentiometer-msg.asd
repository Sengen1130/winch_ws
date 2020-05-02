
(cl:in-package :asdf)

(defsystem "potentiometer-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Log" :depends-on ("_package_Log"))
    (:file "_package_Log" :depends-on ("_package"))
    (:file "adder" :depends-on ("_package_adder"))
    (:file "_package_adder" :depends-on ("_package"))
    (:file "encoder" :depends-on ("_package_encoder"))
    (:file "_package_encoder" :depends-on ("_package"))
  ))