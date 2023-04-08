
#include "SppString.h"

#include <sstream>

namespace spp
{

/*!
 * Split a string at the delimiters
 * @param stringToSplit String to split
 * @param delimiter Delimiter
 * @returns Vector with splitted elements; Empty, if error occurs
 */
std::vector<std::string> String::split(const std::string &stringToSplit, char delimiter)
{
    if (!contains(stringToSplit, delimiter))
    {
        return {};
    }

    std::vector<std::string> res;
    std::string token;
    std::istringstream str(stringToSplit);

    while (std::getline(str, token, delimiter))
    {
        res.emplace_back(token);
    }

    return res;
}

/*!
 * Contains the string a character?
 * @param str String to check
 * @param charToFind Character to find
 * @retval True Character was found
 * @retval False Character was not found
 */
bool String::contains(const std::string &str, char charToFind)
{
	return (str.find(charToFind) != std::string::npos);
}

} /* namespace spp */
