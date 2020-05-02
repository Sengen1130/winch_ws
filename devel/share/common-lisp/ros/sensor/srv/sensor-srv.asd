
(cl:in-package :asdf)

(defsystem "sensor-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "SendTime" :depends-on ("_package_SendTime"))
    (:file "_package_SendTime" :depends-on ("_package"))
  ))