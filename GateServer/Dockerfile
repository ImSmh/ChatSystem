# 使用官方的 C++17 基础镜像
FROM ubuntu:22.04

# 设置环境变量
ENV DEBIAN_FRONTEND=noninteractive
ENV WORKDIR=/workspace

# 安装必要的工具和库
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libboost-filesystem-dev \
    libboost-all-dev \
    libjsoncpp-dev \
    libyaml-cpp-dev \
    libmysqlcppconn-dev \
    autoconf \
    libtool \
    pkg-config \
    libprotobuf-dev \
    protobuf-compiler \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# 增加 Git 缓冲区大小
RUN git config --global http.postBuffer 524288000

# 安装 Hiredis
RUN git clone https://github.com/redis/hiredis.git /tmp/hiredis \
    && cd /tmp/hiredis \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make \
    && make install \
    && ldconfig \
    && rm -rf /tmp/hiredis

# 安装 Redis-plus-plus
RUN git clone --depth 1 https://github.com/sewenew/redis-plus-plus.git /tmp/redis-plus-plus \
    && cd /tmp/redis-plus-plus \
    && mkdir build \
    && cd build \
    && cmake .. -DCMAKE_BUILD_TYPE=Release \
    && make \
    && make install \
    && ldconfig \
    && rm -rf /tmp/redis-plus-plus

RUN git clone https://gitee.com/imsmh/grpc.git /tmp/grpc
# 构建 gRPC
RUN cd /tmp/grpc \
    && cd build \
    && rm -rf ./* \
    && cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local .. \
    && make -j$(nproc) \
    && make install \
    && ldconfig \
    && rm -rf /tmp/grpc

# 创建工作目录
RUN mkdir -p $WORKDIR

# 将当前目录下的所有文件复制到工作空间
COPY . $WORKDIR

# 进入工作目录并构建项目
WORKDIR $WORKDIR/build
RUN rm -rf *
RUN cmake .. && make

# 设置入口点
CMD ["./GateServer"]
