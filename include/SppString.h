#pragma once

#include <string>
#include <vector>

namespace spp
{

/*!
 * @class String
 * @brief String operations
 */
class String
{
public:
    /// Split a string at the delimiters
    static std::vector<std::string> split(const std::string &stringToSplit, char delimiter);

    /// Contains the string a character?
    static bool contains(const std::string &str, char charToFind);
};

} /* namespace spp */