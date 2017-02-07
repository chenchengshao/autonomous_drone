# ======================== Dockerfile ======================================
# Maintainer: David Justo
# Description: Dockerfile for the autonomous flying drone project at
#              Zhuowen Tu's Lab
# Sources:
# 1. On the NVIDIA-DOCKER utility: 
#    https://github.com/NVIDIA/nvidia-docker/wiki
# 2. On how to enable X11 forwarding on Docker through NVIDIA-DOCKER
#    http://wiki.ros.org/docker/Tutorials/Hardware%20Acceleration#Using_nvidia-docker
# 3. On getting ROS indigo + Gazebo6 to work together
#    http://gazebosim.org/tutorials?tut=ros_wrapper_versions
# 4. On allowing ROS official packages to be installed
#    http://wiki.ros.org/indigo/Installation/Ubuntu
# ===========================================================================

FROM ubuntu:14.04.5
MAINTAINER github/davidmrdavid

# ========================= Initial setup ===================================
RUN apt-get update -y
RUN apt-get install wget -y

# ========  Enable OSR Foundation (Gazebo) packages to be installed =========
RUN sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
RUN wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add - 
RUN sudo apt-get update

# =================== Enable ROS packages to be installed ====================
RUN sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
RUN sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
RUN sudo apt-get update
RUN sudo apt-get install libgl1-mesa-dev-lts-utopic -y

# =================== Installing Gazebo6 + ROS indigo ======================
RUN sudo apt-get install ros-indigo-gazebo6-ros-pkgs -y

# ==================== NVIDIA-Docker Hooks  =================================
LABEL com.nvidia.volumes.needed="nvidia_driver"
ENV PATH /usr/local/nvidia/bin:${PATH}
ENV LD_LIBRARY_PATH /usr/local/nvidia/lib:/usr/local/nvidia/lib64:${LD_LIBRARY_PATH}

# ==================== ROS Catkin Setup ====================================
RUN /bin/bash -c "source /opt/ros/indigo/setup.bash"

# ==================== Essential Dev Tools =================================
RUN apt-get install vim -y
RUN apt-get install tree -y
RUN apt-get install git -y

EXPOSE 80
