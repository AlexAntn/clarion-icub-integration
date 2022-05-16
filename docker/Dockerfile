ARG START_IMG="icubteamcode/superbuild:v2022.02.0_sources"
FROM $START_IMG

LABEL maintainer="alexandre.gomespereira@iit.it, ana.tanevska@iit.it, laurene.carminatti@iit.it"

ENV DEBIAN_FRONTEND=noninteractive

ARG PROJECTS_DIR=/projects
ARG CMAKE_GENERATOR="Unix Makefiles"
ARG BUILD_TYPE=Release
ARG CMAKE_EXTRA_OPTIONS=-j2
ARG INSTALL_DIR="/usr/local"

ENV CMAKE_PREFIX_PATH=${INSTALL_DIR}

# Install dependencies given in documentation in superbuild
# https://github.com/robotology/robotology-superbuild#linux
#RUN apt-get update &&\
#    apt-get install -y \
#        # MISC
#        bash-completion \
#        git \
#        wget


RUN cd ${PROJECTS_DIR} &&\
    git clone https://github.com/robotology/segmentation &&\
    cd segmentation && mkdir build && cd build &&\
    cmake .. &&\
    make install

RUN cd ${PROJECTS_DIR} &&\
    git clone https://github.com/AlexAntn/clarion-icub-integration.git 

#The EXPOSE instruction does not actually publish the port.
#It functions as a type of documentation between the person who builds the image and the person who runs the container, about which ports are intended to be published.
#To actually publish the port when running the container, use the -p flag on docker run to publish and map one or more ports, or the -P flag to publish all exposed ports and map them to high-order ports.
EXPOSE 10000/tcp 10000/udp

# Some QT-Apps don't show controls without this
ENV QT_X11_NO_MITSHM 1
ENV YARP_COLORED_OUTPUT 1

CMD ["bash"]
