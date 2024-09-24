#include <iostream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <hiredis/hiredis.h>
#include <cassert>

#include "CServer.h"
#include "ConfigMgr.h"
#include "RedisMgr.h"
#include "Singleton.h"
#include "Log.h"

int main()
{
    LOG_INFO(g_logger) << "GateServer is running";

	auto& gCfgMgr = ConfigMgr::Inst();
	std::string gate_port_str = gCfgMgr["GateServer"]["Port"];
	unsigned short port = atoi(gate_port_str.c_str());

	try {
		//unsigned short port = static_cast<unsigned short>(8080);
		net::io_context ioc{ 1 };
		boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
		signals.async_wait([&ioc](const boost::system::error_code& error, int signals_number) {
			if (error) {
				return;
			}
			ioc.stop();
		});
		std::make_shared<CServer>(ioc, port)->Start();
		ioc.run();
	}
	catch (std::exception const& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
