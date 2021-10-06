#include <string>
#include <codecvt>
#include <locale>

using convert_t = std::codecvt_utf8<wchar_t>;
std::wstring_convert<convert_t, wchar_t> strconverter;


namespace StringHelper
{
    /// <summary>
    /// Converts a wstring into a C++ string object
    /// </summary>
    /// <param name="wstr"></param>
    /// <returns></returns>
    std::string to_string(std::wstring wstr)
    {
        return strconverter.to_bytes(wstr);
    }

    /// <summary>
    /// Converts a C++ string object into a wstring
    /// </summary>
    /// <param name="str"></param>
    /// <returns></returns>
    std::wstring to_wstring(std::string str)
    {
        return strconverter.from_bytes(str);
    }
}
