FROM espressif/idf:v5.3.1

ARG CONTAINER_USER=esp
ARG USER_UID=1051
ARG USER_GID=1051
ENV IDF_TARGET=esp32s3

ENV IDF_GIT_SAFE_DIR=/workspaces/ESP32s3-hal

RUN apt-get update \
    && apt install -y -q \
    cmake \
    git \
    libglib2.0-0 \
    libnuma1 \
    libpixman-1-0 \
    && rm -rf /var/lib/apt/lists/*

RUN groupadd --gid $USER_GID $CONTAINER_USER \
    && adduser --uid $USER_UID --gid $USER_GID --disabled-password --gecos "" ${CONTAINER_USER} \
    && usermod -a -G root $CONTAINER_USER && usermod -a -G dialout $CONTAINER_USER


RUN chmod -R 775 /opt/esp/python_env/
# RUN chown :${CONTAINER_USER} /dev/ttyUSB0

USER ${CONTAINER_USER}
ENV USER=${CONTAINER_USER}
WORKDIR /home/${CONTAINER_USER}

RUN echo "source /opt/esp/idf/export.sh > /dev/null 2>&1" >> ~/.bashrc


ENTRYPOINT [ "/opt/esp/entrypoint.sh" ]

CMD ["/bin/bash", "-c"]