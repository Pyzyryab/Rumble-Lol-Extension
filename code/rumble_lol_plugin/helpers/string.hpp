#pragma once

#include <string> 
#include <vector> 
#include <sstream> 
#include <codecvt>
#include <locale>

namespace StringHelper {
	std::string to_string(std::wstring wstr);
	std::wstring to_wstring(std::string str);
    std::vector<std::string>& split_by_delimiter(const std::string& input, char delimiter, std::vector<std::string>& output);
}
