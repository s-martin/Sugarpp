#pragma once

#include "SppDefines.h"

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

#include <memory>
#include <string>
#include <vector>
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

	/// Get string attribute from XML element
	std::string getStringAttribute(const xercesc::DOMNode* currNode, const std::string& attrName) const;
	//std::string getStringAttribute(xercesc::DOMElement *element, const std::string &tagName, const std::string &attributeName) const;

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

	/*!
	* Get numeric attribute from XML element.
	* @param element Current parent element
	* @param tagName Name of XML element
	* @param attributeName Name of XML attribute
	* @returns Numeric value of XML element or UNDEFINED_NUM, if failed
	*/
	template<
		typename T, //real type
		typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
	>
	T getNumericAttribute(xercesc::DOMElement *element, const std::string &tagName, const std::string &attributeName) const
	{
		auto str = getStringAttribute(element, /*tagName,*/ attributeName);
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

	bool isXmlStringEqual(const XMLCh* xmlStr1, const char* str2, bool ignoreCase = false);

	/// Searches for a tag name in children of current element
	xercesc::DOMNode* getChild(const xercesc::DOMElement* currElement, const std::string& nameToFind);

	// TODO could be removed
	/// Searches for a tag name in children of current node
	xercesc::DOMNode* getChild(xercesc::DOMNode* currNode, const std::string& nameToFind);

	/// Searches for all tag names in children of current element
	std::vector<xercesc::DOMNode*> getChildren(const xercesc::DOMElement* currElement, const std::string& nameToFind);

	// TODO could be removed
	/// Searches for all tag names in children of current node
	std::vector<xercesc::DOMNode*> getChildren(xercesc::DOMNode* currNode, const std::string& nameToFind);


private:
    std::unique_ptr<xercesc::XercesDOMParser> m_parser;
};

} /* namespace spp */