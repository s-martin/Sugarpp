#pragma once

#include "SppDefines.h"

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

#include <string>
#include <charconv>

namespace spp
{

/*!
 * @class XmlParser
 * @brief Utility class for XML parsing using Xerces-C.
 */
class XmlParser
{
public:
    XmlParser();
    virtual ~XmlParser();
	XmlParser(const XmlParser& other) = delete;
	XmlParser(XmlParser&& other) noexcept = delete;
	XmlParser& operator=(const XmlParser& other) = delete;
	XmlParser& operator=(XmlParser&& other) noexcept = delete;

	/// Get XML document object
    xercesc::DOMDocument * getDocument(const std::string &xml) const;

	/// Get string value from XML element
	std::string getStringValue(xercesc::DOMElement *element, const std::string &tagName) const;

	/*!
	* Get numeric value from XML element.
	* @param element Current parent element
	* @param tagName Name of XML element
	* @returns Numeric value of XML element or UNDEFINED_NUM, if failed
	*/
	template<
		typename T, //real type
		typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
	>
	T getNumericValue(xercesc::DOMElement *element, const std::string &tagName) const
	{
		static_assert(std::is_arithmetic<T>::value, "Template type must be numeric");
		
		auto str = getStringValue(element, tagName);
		if (str.empty())
		{
			return spp::UNDEFINED_NUM;
		}

		T result;
		if (auto[p, ec] = std::from_chars(str.data(), str.data() + str.size(), result);	ec == std::errc())
		{
			return result;
		}

		return spp::UNDEFINED_NUM;
	}

	/// Convert to std::string
	std::string toStdString(const XMLCh* str) const;

private:
    std::unique_ptr<xercesc::XercesDOMParser> m_parser;
};

} /* namespace spp */