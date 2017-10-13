# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "multiple_robots_stage: 5 messages, 2 services")

set(MSG_I_FLAGS "-Imultiple_robots_stage:/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(multiple_robots_stage_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/NavigationActivityStatus.msg" NAME_WE)
add_custom_target(_multiple_robots_stage_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "multiple_robots_stage" "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/NavigationActivityStatus.msg" ""
)

get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPosition.msg" NAME_WE)
add_custom_target(_multiple_robots_stage_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "multiple_robots_stage" "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPosition.msg" "geometry_msgs/Point:geometry_msgs/PoseStamped:geometry_msgs/Quaternion:std_msgs/Header:geometry_msgs/Pose"
)

get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPositionSimple.msg" NAME_WE)
add_custom_target(_multiple_robots_stage_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "multiple_robots_stage" "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPositionSimple.msg" "geometry_msgs/Pose2D"
)

get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PatrolStatus.msg" NAME_WE)
add_custom_target(_multiple_robots_stage_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "multiple_robots_stage" "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PatrolStatus.msg" "geometry_msgs/Pose2D"
)

get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/RobotStatus.msg" NAME_WE)
add_custom_target(_multiple_robots_stage_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "multiple_robots_stage" "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/RobotStatus.msg" ""
)

get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/CrashRobot.srv" NAME_WE)
add_custom_target(_multiple_robots_stage_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "multiple_robots_stage" "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/CrashRobot.srv" ""
)

get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/RobotPose.srv" NAME_WE)
add_custom_target(_multiple_robots_stage_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "multiple_robots_stage" "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/RobotPose.srv" "geometry_msgs/Pose2D"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPositionSimple.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multiple_robots_stage
)
_generate_msg_cpp(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PatrolStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multiple_robots_stage
)
_generate_msg_cpp(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/NavigationActivityStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multiple_robots_stage
)
_generate_msg_cpp(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/RobotStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multiple_robots_stage
)
_generate_msg_cpp(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPosition.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multiple_robots_stage
)

### Generating Services
_generate_srv_cpp(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/RobotPose.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multiple_robots_stage
)
_generate_srv_cpp(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/CrashRobot.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multiple_robots_stage
)

### Generating Module File
_generate_module_cpp(multiple_robots_stage
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multiple_robots_stage
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(multiple_robots_stage_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(multiple_robots_stage_generate_messages multiple_robots_stage_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/NavigationActivityStatus.msg" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_cpp _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPosition.msg" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_cpp _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPositionSimple.msg" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_cpp _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PatrolStatus.msg" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_cpp _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/RobotStatus.msg" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_cpp _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/CrashRobot.srv" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_cpp _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/RobotPose.srv" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_cpp _multiple_robots_stage_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multiple_robots_stage_gencpp)
add_dependencies(multiple_robots_stage_gencpp multiple_robots_stage_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multiple_robots_stage_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPositionSimple.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multiple_robots_stage
)
_generate_msg_lisp(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PatrolStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multiple_robots_stage
)
_generate_msg_lisp(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/NavigationActivityStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multiple_robots_stage
)
_generate_msg_lisp(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/RobotStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multiple_robots_stage
)
_generate_msg_lisp(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPosition.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multiple_robots_stage
)

### Generating Services
_generate_srv_lisp(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/RobotPose.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multiple_robots_stage
)
_generate_srv_lisp(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/CrashRobot.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multiple_robots_stage
)

### Generating Module File
_generate_module_lisp(multiple_robots_stage
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multiple_robots_stage
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(multiple_robots_stage_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(multiple_robots_stage_generate_messages multiple_robots_stage_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/NavigationActivityStatus.msg" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_lisp _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPosition.msg" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_lisp _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPositionSimple.msg" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_lisp _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PatrolStatus.msg" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_lisp _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/RobotStatus.msg" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_lisp _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/CrashRobot.srv" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_lisp _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/RobotPose.srv" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_lisp _multiple_robots_stage_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multiple_robots_stage_genlisp)
add_dependencies(multiple_robots_stage_genlisp multiple_robots_stage_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multiple_robots_stage_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPositionSimple.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multiple_robots_stage
)
_generate_msg_py(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PatrolStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multiple_robots_stage
)
_generate_msg_py(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/NavigationActivityStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multiple_robots_stage
)
_generate_msg_py(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/RobotStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multiple_robots_stage
)
_generate_msg_py(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPosition.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multiple_robots_stage
)

### Generating Services
_generate_srv_py(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/RobotPose.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multiple_robots_stage
)
_generate_srv_py(multiple_robots_stage
  "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/CrashRobot.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multiple_robots_stage
)

### Generating Module File
_generate_module_py(multiple_robots_stage
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multiple_robots_stage
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(multiple_robots_stage_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(multiple_robots_stage_generate_messages multiple_robots_stage_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/NavigationActivityStatus.msg" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_py _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPosition.msg" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_py _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PriorityPositionSimple.msg" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_py _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/PatrolStatus.msg" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_py _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/msg/RobotStatus.msg" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_py _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/CrashRobot.srv" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_py _multiple_robots_stage_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/srv/RobotPose.srv" NAME_WE)
add_dependencies(multiple_robots_stage_generate_messages_py _multiple_robots_stage_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multiple_robots_stage_genpy)
add_dependencies(multiple_robots_stage_genpy multiple_robots_stage_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multiple_robots_stage_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multiple_robots_stage)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multiple_robots_stage
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(multiple_robots_stage_generate_messages_cpp std_msgs_generate_messages_cpp)
add_dependencies(multiple_robots_stage_generate_messages_cpp std_srvs_generate_messages_cpp)
add_dependencies(multiple_robots_stage_generate_messages_cpp geometry_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multiple_robots_stage)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multiple_robots_stage
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(multiple_robots_stage_generate_messages_lisp std_msgs_generate_messages_lisp)
add_dependencies(multiple_robots_stage_generate_messages_lisp std_srvs_generate_messages_lisp)
add_dependencies(multiple_robots_stage_generate_messages_lisp geometry_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multiple_robots_stage)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multiple_robots_stage\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multiple_robots_stage
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(multiple_robots_stage_generate_messages_py std_msgs_generate_messages_py)
add_dependencies(multiple_robots_stage_generate_messages_py std_srvs_generate_messages_py)
add_dependencies(multiple_robots_stage_generate_messages_py geometry_msgs_generate_messages_py)
