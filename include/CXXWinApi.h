#pragma once

#include <string>

namespace spp
{

class CXXWinApi
{
public:
    static std::string getFileVersionInfo(const std::string &module = "");
};

} /* namespace spp */