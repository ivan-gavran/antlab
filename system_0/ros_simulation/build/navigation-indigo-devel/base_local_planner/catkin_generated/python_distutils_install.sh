#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
    DESTDIR_ARG="--root=$DESTDIR"
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/ivan/antlab-repo/system_0/ros_simulation/src/navigation-indigo-devel/base_local_planner"

# snsure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/ivan/antlab-repo/system_0/ros_simulation/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/ivan/antlab-repo/system_0/ros_simulation/install/lib/python2.7/dist-packages:/home/ivan/antlab-repo/system_0/ros_simulation/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/ivan/antlab-repo/system_0/ros_simulation/build" \
    "/usr/bin/python" \
    "/home/ivan/antlab-repo/system_0/ros_simulation/src/navigation-indigo-devel/base_local_planner/setup.py" \
    build --build-base "/home/ivan/antlab-repo/system_0/ros_simulation/build/navigation-indigo-devel/base_local_planner" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/ivan/antlab-repo/system_0/ros_simulation/install" --install-scripts="/home/ivan/antlab-repo/system_0/ros_simulation/install/bin"
