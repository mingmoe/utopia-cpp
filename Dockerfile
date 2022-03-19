# 用于构建utopia的快速环境
FROM archlinux

# define arguments
ARG cmakeBuildType=Debug
ARG cmakeGenerateOptions=""
ARG cmakeBuildOptions="-j2"

# we are NO.1 !
USER root

# update system
RUN pacman-key --init && pacman-key --populate && \
pacman -Syu --quiet --noconfirm && pacman --quiet --noconfirm -S \
clang gcc cmake zip unzip curl tar pkg-config autoconf automake

# work on our home :-)
WORKDIR /root

# copy everywhere
COPY . .

# WELL DONE!
# compile it!
RUN cmake -S . -B ./build -DCMAKE_BUILD_TYPE=$cmakeBuildType $cmakeGenerateOptions
RUN cmake --build ./build $cmakeBuildOptions

# executable
ENTRYPOINT [ "ctest","." ]
