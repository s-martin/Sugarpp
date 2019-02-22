#pragma once

#include <string>
#include <vector>

namespace spp
{

/*!
 * @class File
 * @brief File I/O operations
 */
class File
{
public:
    /// Read whole text file to a string
    static std::string read(const std::string &path);

    /// Read text file to a list of strings for each line
    static std::vector<std::string> readLines(const std::string &path);

    /// Read whole binary file to a list of bytes
    static std::vector<uint8_t> readBinary(const std::string &path);
};

} /* namespace spp */
