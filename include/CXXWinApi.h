#pragma once

#include <string>

namespace spp
{

/** C++ API for WINAPI
 * 
 * 
 */
class CXXWinApi
{
public:
    static std::string getFileVersionInfo(const std::string &module = "");
};

} /* namespace spp */