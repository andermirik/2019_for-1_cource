#pragma once
#include <vector>
class Config
{
private:
	std::vector<std::string> files;
	std::vector<int> count_strs_files = {
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0 
	};
public:
	void ReadConfig();
	bool CheckResourceFiles();
	std::vector<std::string>& Files();
	std::vector<int>& CountLinesFiles();
	Config() {}
	Config(const Config&) = delete;
	Config&operator=(Config&) = delete;
	
	static Config& get() {
		static Config  instance;
		return instance;
	}
};
