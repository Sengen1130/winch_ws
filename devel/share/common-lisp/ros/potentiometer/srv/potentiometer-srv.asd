
(cl:in-package :asdf)

(defsystem "potentiometer-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "SendTime" :depends-on ("_package_SendTime"))
    (:file "_package_SendTime" :depends-on ("_package"))
  ))