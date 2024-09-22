cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(MyProject VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 启用调试信息
set(CMAKE_BUILD_TYPE Debug)

# 查找所需的库
find_package(Boost REQUIRED COMPONENTS filesystem system thread)
find_package(Threads REQUIRED)
# find_package(jsoncpp REQUIRED)
find_package(hiredis REQUIRED)
# find_package(MySQL REQUIRED) # 如果使用 MySQL Connector/C++

# 添加 gRPC 和 Protobuf
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

# 包含目录
include_directories(
    include
    ${Boost_INCLUDE_DIRS}
    #    ${jsoncpp_INCLUDE_DIRS}
    /usr/include/jsoncpp
    ${hiredis_INCLUDE_DIRS}
    ${Protobuf_INCLUDE_DIRS}
    ${gRPC_INCLUDE_DIRS}
)

# 源文件
set(SOURCES
    src/main.cpp
    src/message.grpc.pb.cc
    src/message.pb.cc
    src/AsioIOServicePool.cpp
    src/CServer.cpp
    src/LogicSystem.cpp
    src/MysqlDao.cpp
    src/RedisMgr.cpp
    src/VarifyGrpcClient.cpp  
    src/ConfigMgr.cpp
    src/HttpConnection.cpp
    src/MysqlMgr.cpp
    src/StatusGrpcClient.cpp
)

# 可执行文件
add_executable(GateServer ${SOURCES})

# 链接库
target_link_libraries(GateServer
    PRIVATE
        ${Boost_LIBRARIES}
	# ${jsoncpp_LIBRARIES}
	jsoncpp
        ${hiredis_LIBRARIES}
        ${Protobuf_LIBRARIES}
        gRPC::grpc++
        gRPC::grpc
        ${CMAKE_THREAD_LIBS_INIT}
        mysqlcppconn  # 如果需要 MySQL，请确保已安装并取消注释
)

# 添加自定义命令来复制文件
add_custom_command(TARGET GateServer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/src/config.ini
    $<TARGET_FILE_DIR:GateServer>/config.ini
)

# 如果需要，可以设置安装规则
install(TARGETS GateServer DESTINATION bin)

