execute_process(COMMAND "/home/ivan/antlab-repo/system_0/ros_simulation/build/navigation-indigo-devel/base_local_planner/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/ivan/antlab-repo/system_0/ros_simulation/build/navigation-indigo-devel/base_local_planner/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
