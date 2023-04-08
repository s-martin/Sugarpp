
#include "Tracing.h"

namespace spp
{

/** Construct a new Tracing:: Tracing object
 * 
 * @param file 
 * @param location 
 */
Tracing::Tracing(const std::string &file, std::string location) :
    where(std::move(location))
{
    logEntry("==> ENTER " + where + " at " + file);
}

Tracing::~Tracing()
{
    logEntry("==> EXIT " + where);
}

void Tracing::initialize()
{

}

void Tracing::logEntry(const std::string &entry)
{

}

} /* namespace spp */