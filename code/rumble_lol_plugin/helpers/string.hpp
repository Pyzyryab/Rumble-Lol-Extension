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

    /// Created to be able to compare char* on std data structures. In detail, to allow the .find() method of the std::map DS to match
    /// keys with the type const char*.
    /// A char* it's just a pointer to a C-String style, which are just contiguous characters on a chuck of memory, that's why the find method
    /// fails trying to find a char* key against a passed in char*, because it's comparing memory addreses, not string values.
    /// </summary>
    struct cmp_str
    {
        bool operator()(char const* a, char const* b) const;
    };
}
