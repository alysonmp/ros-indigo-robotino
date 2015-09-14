; Auto-generated. Do not edit!


(cl:in-package robotino_local_move-msg)


;//! \htmlinclude LocalMoveActionGoal.msg.html

(cl:defclass <LocalMoveActionGoal> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (goal_id
    :reader goal_id
    :initarg :goal_id
    :type actionlib_msgs-msg:GoalID
    :initform (cl:make-instance 'actionlib_msgs-msg:GoalID))
   (goal
    :reader goal
    :initarg :goal
    :type robotino_local_move-msg:LocalMoveGoal
    :initform (cl:make-instance 'robotino_local_move-msg:LocalMoveGoal)))
)

(cl:defclass LocalMoveActionGoal (<LocalMoveActionGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LocalMoveActionGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LocalMoveActionGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robotino_local_move-msg:<LocalMoveActionGoal> is deprecated: use robotino_local_move-msg:LocalMoveActionGoal instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <LocalMoveActionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robotino_local_move-msg:header-val is deprecated.  Use robotino_local_move-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'goal_id-val :lambda-list '(m))
(cl:defmethod goal_id-val ((m <LocalMoveActionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robotino_local_move-msg:goal_id-val is deprecated.  Use robotino_local_move-msg:goal_id instead.")
  (goal_id m))

(cl:ensure-generic-function 'goal-val :lambda-list '(m))
(cl:defmethod goal-val ((m <LocalMoveActionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robotino_local_move-msg:goal-val is deprecated.  Use robotino_local_move-msg:goal instead.")
  (goal m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LocalMoveActionGoal>) ostream)
  "Serializes a message object of type '<LocalMoveActionGoal>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goal_id) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goal) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LocalMoveActionGoal>) istream)
  "Deserializes a message object of type '<LocalMoveActionGoal>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goal_id) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goal) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LocalMoveActionGoal>)))
  "Returns string type for a message object of type '<LocalMoveActionGoal>"
  "robotino_local_move/LocalMoveActionGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LocalMoveActionGoal)))
  "Returns string type for a message object of type 'LocalMoveActionGoal"
  "robotino_local_move/LocalMoveActionGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LocalMoveActionGoal>)))
  "Returns md5sum for a message object of type '<LocalMoveActionGoal>"
  "68a36fa3b32a4bc7c7deca214daf5836")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LocalMoveActionGoal)))
  "Returns md5sum for a message object of type 'LocalMoveActionGoal"
  "68a36fa3b32a4bc7c7deca214daf5836")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LocalMoveActionGoal>)))
  "Returns full string definition for message of type '<LocalMoveActionGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%~%Header header~%actionlib_msgs/GoalID goal_id~%LocalMoveGoal goal~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: actionlib_msgs/GoalID~%# The stamp should store the time at which this goal was requested.~%# It is used by an action server when it tries to preempt all~%# goals that were requested before a certain time~%time stamp~%~%# The id provides a way to associate feedback and~%# result message with specific goal requests. The id~%# specified must be unique.~%string id~%~%~%================================================================================~%MSG: robotino_local_move/LocalMoveGoal~%# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%float32 move_x		# in meters~%float32 move_y		# in meters~%float32 rotation	# in rad~%uint8 movementType	~%# 0 -> Translational Movement (move_phi should be equal to zero)~%# 1 -> Rotational Movement (move_x and move_y should be equal to zero)~%# 2 -> Translational and Rotational Moviment (at the same time)~%# 3 -> Tangent Moviment (move_x must be iqual to move_y)~%~%#bool ignore_rotation #if true robot is not rotated after moving. if false robot is rotated \"rotation\" relative to the starting orientation~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LocalMoveActionGoal)))
  "Returns full string definition for message of type 'LocalMoveActionGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%~%Header header~%actionlib_msgs/GoalID goal_id~%LocalMoveGoal goal~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: actionlib_msgs/GoalID~%# The stamp should store the time at which this goal was requested.~%# It is used by an action server when it tries to preempt all~%# goals that were requested before a certain time~%time stamp~%~%# The id provides a way to associate feedback and~%# result message with specific goal requests. The id~%# specified must be unique.~%string id~%~%~%================================================================================~%MSG: robotino_local_move/LocalMoveGoal~%# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%float32 move_x		# in meters~%float32 move_y		# in meters~%float32 rotation	# in rad~%uint8 movementType	~%# 0 -> Translational Movement (move_phi should be equal to zero)~%# 1 -> Rotational Movement (move_x and move_y should be equal to zero)~%# 2 -> Translational and Rotational Moviment (at the same time)~%# 3 -> Tangent Moviment (move_x must be iqual to move_y)~%~%#bool ignore_rotation #if true robot is not rotated after moving. if false robot is rotated \"rotation\" relative to the starting orientation~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LocalMoveActionGoal>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goal_id))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goal))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LocalMoveActionGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'LocalMoveActionGoal
    (cl:cons ':header (header msg))
    (cl:cons ':goal_id (goal_id msg))
    (cl:cons ':goal (goal msg))
))