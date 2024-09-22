#include "ConfigMgr.h"

ConfigMgr::ConfigMgr()
{
	// 获取当前工作目录
	boost::filesystem::path current_path = boost::filesystem::current_path();
	// 构建 config.ini 文件的完整路径
	boost::filesystem::path config_path = current_path / "config.ini";
	std::cout << "Config path: " << config_path << std::endl;

	// 使用 Boost.PropertyTree 来读取 INI 文件
	boost::property_tree::ptree pt;
	boost::property_tree::read_ini(config_path.string(), pt);

	// 遍历 INI 文件中所有的 section
	for (const auto& section_pair : pt) {
		const std::string& section_name = section_pair.first;
		const boost::property_tree::ptree& section_tree = section_pair.second;

		// 对于每个 section，遍历其所有的 kv 对
		std::map<std::string, std::string> section_config;
		for (const auto& key_value_pair : section_tree) {
			const std::string& key = key_value_pair.first;
			const std::string& value = key_value_pair.second.get_value<std::string>();
			section_config[key] = value;
		}
		SectionInfo sectionInfo;
		sectionInfo._section_datas = section_config;
		_config_map[section_name] = sectionInfo;
	}

	for (const auto& section_entry : _config_map) {
		const std::string& section_name = section_entry.first;
		SectionInfo section_config = section_entry.second;
		std::cout << "[" << section_name << "]" << std::endl;
		for (const auto& key_value_pair : section_config._section_datas) {
			std::cout << key_value_pair.first << " = " << key_value_pair.second << std::endl;
		}
	}
}
