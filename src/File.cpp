
#include "File.h"

#include <fstream>
#include <sstream>

namespace spp
{

/*!
 * Read whole text file to a string
 * @param path File path
 * @returns String with file content
 */
std::string File::read(const std::string &path)
{
    if (path.empty())
    {
        return {};
    }

    std::ifstream file(path);
    if (file)
    {
        std::stringstream input;
        input << file.rdbuf();
        file.close();
        return input.str();
    }

    return {};
}

/*!
 * Read text file to a list of strings for each line
 * @param path File path
 * @returns Vector with strings for each line
 */
std::vector<std::string> File::readLines(const std::string &path)
{
    if (path.empty())
    {
        return {};
    }

    std::ifstream file(path);
    if (file)
    {
        std::string line;
        std::vector<std::string> res;
        while(std::getline(file, line))
        {           
            res.emplace_back(line);
        }
        file.close();
        return res;
    }

    return {};
}

/*!
 * Read whole binary file to a list of bytes
 * @param path File path
 * @returns Vector with bytes
 */
std::vector<uint8_t> File::readBinary(const std::string &path)
{
    if (path.empty())
    {
        return {};
    }

    std::ifstream file(path, std::ios::binary);
    if (file)
    {
        std::vector<uint8_t> res(std::istreambuf_iterator<char>(file), {});
        file.close();
        return res;
    }

    return {};
}

/*!
 * Write string to a text file.
 * @param path File path
 * @param content String to write
 * @returns True, if successful
 */
bool File::write(const std::string &path, const std::string &content)
{
    if (path.empty() || content.empty())
    {
        return false;
    }

    std::ofstream file(path);
    if (file)
    {
        file << content;
        file.close();
        return true;
    }
    
    return false;
}

/*!
 * Write list of bytes to a binary file.
 * @param path File path
 * @param content Vector of bytes to write
 * @returns True, if successful
 */
bool File::writeBinary(const std::string &path, std::vector<uint8_t> content)
{
    if (path.empty() || content.empty())
    {
        return false;
    }

    std::ofstream file(path, std::ios::binary);
    if (file)
    {
        file.write(reinterpret_cast<const char*>(&content[0]), content.size());
        file.close();
        return true;
    }

    return false;
}

} /* namespace spp */
