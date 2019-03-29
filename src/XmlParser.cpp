
#include "XmlParser.h"

#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/util/PlatformUtils.hpp>

namespace spp
{

XmlParser::XmlParser()
{
    xercesc::XMLPlatformUtils::Initialize();

    m_parser = std::make_unique<xercesc::XercesDOMParser>();
}

XmlParser::~XmlParser()
{
    xercesc::XMLPlatformUtils::Terminate();
}

/*!
 * Get XML document object.
 * @param xml XML string
 * @returns Pointer to XML document or nullptr, if failed
 */
xercesc::DOMDocument * XmlParser::getDocument(const std::string &xml) const
{
    xercesc::MemBufInputSource buffer(reinterpret_cast<const unsigned char*>(xml.c_str()), xml.size(), "myxml (in memory)"); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    m_parser->parse(buffer);
    return m_parser->getDocument(); 
}

/*!
 * Get string value from XML element.
 * @param element Current parent element
 * @param tagName Name of XML element
 * @returns String value of XML element or empty, if failed
 */
std::string XmlParser::getStringValue(xercesc::DOMElement *element, const std::string &tagName) const
{
	if (element == nullptr || tagName.empty())
	{
		return {};
	}

	auto child = element->getFirstElementChild();
	while (child != nullptr)
	{
		if (toStdString(child->getNodeName()) == tagName)
		{
			// TODO are we sure that its always the first child with the text content?
			// TODO to be tested with complex XMl structures
			return toStdString(child->getFirstChild()->getNodeValue());
		}
		child = child->getNextElementSibling();
	}

	return {};
}

/*!
 * Convert to std::string.
 * @param str XMLString to be converted
 * @returns String value or empty, if failed
 */
std::string XmlParser::toStdString(const XMLCh* str) const
{
	if (str == nullptr)
	{
		return {};
	}

	auto temp = xercesc::XMLString::transcode(str);
	std::string retVal(temp);
	xercesc::XMLString::release(&temp);
	return retVal;
}

} /* namespace spp */