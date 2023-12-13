#include <string> 
#include <vector> 
#include <sstream> 
#include <codecvt>
#include <locale>

#include <rumble_lol_plugin/helpers/string.hpp>

// Convenient namespace simplifications
using convert_t = std::codecvt_utf8<wchar_t>;
std::wstring_convert<convert_t, wchar_t> strconverter;

/// <summary>
/// Converts a wstring into a C++ string object
/// </summary>
/// <param name="wstr"></param>
/// <returns></returns>
std::string StringHelper::to_string(std::wstring wstr)
{
    return strconverter.to_bytes(wstr);
}

/// <summary>
/// Converts a C++ string object into a wstring
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
std::wstring StringHelper::to_wstring(std::string str)
{
    return strconverter.from_bytes(str);
}

/// <summary>
/// Splits an stardand C++ string object into a std::vec<string>, receiving a reference to the string,
/// a character as a delimitter and an std::vector<string> as an output container.
/// </summary>
std::vector<std::string>& StringHelper::split_by_delimiter(const std::string& input, char delimiter, std::vector<std::string>& output)
{
    // construct a stream from the string 
    std::stringstream ss(input);

    std::string s;
    while (std::getline(ss, s, delimiter)) {
        output.push_back(s);
    }

    return output;
}
