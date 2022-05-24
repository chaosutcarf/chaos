FROM ubuntu:20.04
ENV PROJ_DIR=/chaos
WORKDIR ${PROJ_DIR}

ENV DEBIAN_FRONTEND=noninteractive
# ARG APT_GET_SOURCE=mirrors.aliyun.com
ARG APT_GET_SOURCE=mirrors.ustc.edu.cn
RUN sed -i s@/archive.ubuntu.com/@/${APT_GET_SOURCE}/@g /etc/apt/sources.list \
        && sed -i s@/security.ubuntu.com/@/${APT_GET_SOURCE}/@g /etc/apt/sources.list \
        && apt-get update \
        && apt-get install gcc make g++ gfortran cmake wget python3 git sudo -y --no-install-recommends

COPY . $WORKDIR
RUN ${PROJ_DIR}/deps/prepare.sh
ENV DEBIAN_FRONTEND=dialog

# RUN ./chaos/.github/workflows/fix-3rd-url.py
# RUN cd chaos && make release debug

CMD /bin/bash
