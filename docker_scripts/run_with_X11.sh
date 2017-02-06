#!/bin/bash
nvidia-docker run -it \
    --env="DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    -v="/home/davidmrdavid/Desktop/autonomous_drone/autonomous_drone_workspace:/autonomous_drone_workspace" \
    --name="ubuntu_drone_container" \
    ubuntu_drone
