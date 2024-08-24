#pragma once


#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <memory>
#include <iostream>
#include <functional>
#include <map>
#include <unordered_map>
#include <queue>
#include <atomic>

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>

#include <hiredis/hiredis.h>

#include "Singleton.h"
#include "Log.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

static Logger::ptr g_logger = LOG_NAME("GateServer");

enum ErrorCodes {
    Success             = 0,
    Error_Json          = 1001,     // Json解析错误
    RPCFailed           = 1002,     // RPC请求错误
    VarifyExpired       = 1003,     // 验证码过期
    VarifyCodeErr       = 1004,     // 验证码错误
    UserExist           = 1005,     // 用户已存在
    PasswordErr         = 1006,     // 密码错误
    EmailNotMatch       = 1007,     // 邮箱不匹配
    PasswordUpFailed    = 1008,     // 更新密码失败
    PasswordInvalid     = 1009,     // 密码无效
    TokenInvalid        = 1010,     //
    UidInvalid          = 1011,
};


#define CODEPREFIX "code_"


class Defer {
public:
    Defer(std::function<void()> func) : func_(func) { }
    ~Defer() {
        func_();
    }

private:
    std::function<void()> func_;
};
