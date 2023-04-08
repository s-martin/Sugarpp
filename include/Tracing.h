#pragma once

#include <string>

namespace spp
{

/** Tracing and Logging
 * 
 * 
 */
class Tracing
{
public:
    Tracing(const std::string &file, std::string location);
    virtual ~Tracing();
	Tracing(const Tracing& other) = delete;
	Tracing(Tracing&& other) noexcept = delete;
	Tracing& operator=(const Tracing& other) = delete;
	Tracing& operator=(Tracing&& other) noexcept = delete;


private:
    void initialize();
    
    void logEntry(const std::string &entry);

    std::string where;
};

} /* namespace spp */