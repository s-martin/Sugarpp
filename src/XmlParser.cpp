
#include "XmlParser.h"

#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNodeList.hpp>

namespace spp
{

XmlParser::XmlParser()
{
    xercesc::XMLPlatformUtils::Initialize();

    m_parser = std::make_unique<xercesc::XercesDOMParser>();
}

XmlParser::~XmlParser()
{
	m_parser.reset();

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
			// TODO to be tested with complex XML structures
			return toStdString(child->getFirstChild()->getNodeValue());
		}
		child = child->getNextElementSibling();
	}

	return {};
}

/*!
 * Get string attribute from XML element.
 * @param element Current parent element
 * @param tagName Name of XML element
 * @param attributeName Name of XML attribute
 * @returns String value of XML attribute or empty, if failed
 */
std::string XmlParser::getStringAttribute(xercesc::DOMElement *element, const std::string &tagName, const std::string &attributeName) const
{
	if (element == nullptr || tagName.empty() || attributeName.empty())
	{
		return {};
	}

	auto child = element->getFirstElementChild();
	while (child != nullptr)
	{
		if (toStdString(child->getNodeName()) == tagName)
		{			
			// TODO check and test reinterpret
			return toStdString(child->getAttribute(reinterpret_cast<const XMLCh*>(attributeName.c_str())));
		}
		child = child->getNextElementSibling();
	}

	return {};
}

std::string XmlParser::getStringAttribute(const xercesc::DOMNode* currNode, const std::string& attrName) const
{
	std::string res;
	XMLCh* xmlStr = xercesc::XMLString::transcode(attrName.c_str());

	try
	{
		auto atts = currNode->getAttributes();
		auto node = atts->getNamedItem(xmlStr);
		if (node && (node->getNodeType() == xercesc::DOMNode::ATTRIBUTE_NODE))
		{
			auto* currAttr = dynamic_cast<xercesc::DOMAttr*>(node);
			res = toStdString(currAttr->getValue());
		}
	}
	catch (xercesc::XMLException& e)
	{
		//char* message = xercesc::XMLString::transcode(e.getMessage());
		//Tracing::error("Unexpected exception in XmlParser::getStringAttribute:\n");
		//Tracing::error(message);
		//XMLString::release(&message);
	}
	xercesc::XMLString::release(&xmlStr);
	return res;
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

/*!
 * Checks, if XML element name is equal with given string.
 * Also releases pointer of XMLCh afterwards.
 *
 * @param xmlStr1 Name of XML element
 * @param str2 String to compare
 * @param ignoreCase Is case of characters ignored, while comparing?
 * @returns True, if comparism successful
 */
bool XmlParser::isXmlStringEqual(const XMLCh* xmlStr1, const char* str2, bool ignoreCase)
{
	XMLCh* xmlStr2 = xercesc::XMLString::transcode(str2);

	bool isEqual = false;

	if (ignoreCase)
	{
		isEqual = (xercesc::XMLString::compareIString(xmlStr1, xmlStr2) == 0);
	}
	else
	{
		isEqual = xercesc::XMLString::equals(xmlStr1, xmlStr2);
	}

	xercesc::XMLString::release(&xmlStr2);

	return isEqual;
}


/*!
 * Get child from element by name and returns the child for further processing.
 *
 * @param currElement Current element (parent)
 * @param nameToFind Name to be found in children tags
 * @returns Pointer to child element (or nullptr, if not found)
 */
xercesc::DOMNode* XmlParser::getChild(const xercesc::DOMElement* currElement, const std::string& nameToFind)
{
	try
	{
		auto * children = currElement->getChildNodes();
		const  XMLSize_t nodeCount = children->getLength();

		for (XMLSize_t i = 0; i < nodeCount; ++i)
		{
			auto * currentNode = children->item(i);
			if (currentNode && (currentNode->getNodeType() == xercesc::DOMNode::ELEMENT_NODE))
			{
				auto* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);

				if (isXmlStringEqual(currentElement->getTagName(), nameToFind.c_str()))
				{
					return currentNode;
				}
			}
		}
	}
	catch (xercesc::XMLException& e)
	{
		char* message = xercesc::XMLString::transcode(e.getMessage());
		//Tracing::error("Unexpected exception in XmlParser::getChild-DOMElement:\n");
		//Tracing::error(message);
		xercesc::XMLString::release(&message);
	}

	return nullptr;
}


/*!
 * Get child from element by name and returns the child for further processing.
 *
 * @param currNode Current node (parent)
 * @param nameToFind Name to be found in children tags
 * @returns Pointer to child element (or nullptr, if not found)
 */
xercesc::DOMNode* XmlParser::getChild(xercesc::DOMNode* currNode, const std::string& nameToFind)
{
	if (currNode && (currNode->getNodeType() == xercesc::DOMNode::ELEMENT_NODE))
	{
		auto* currElement = dynamic_cast<xercesc::DOMElement*>(currNode);

		return getChild(currElement, nameToFind);
	}
	return nullptr;
}

/*!
 * Get all children from element with the same name and returns the children for further processing.
 * This should be used for recurring elements.
 *
 * @param currElement Current element (parent)
 * @param nameToFind Name to be found in children tags
 * @returns List with pointers to child elements (or empty, if not found)
 */
std::vector<xercesc::DOMNode*> XmlParser::getChildren(const xercesc::DOMElement* currElement,
	const std::string& nameToFind)
{
	std::vector<xercesc::DOMNode*> res;
	try
	{
		auto* children = currElement->getChildNodes();
		const  XMLSize_t nodeCount = children->getLength();

		for (XMLSize_t i = 0; i < nodeCount; ++i)
		{
			auto* currentNode = children->item(i);
			if (currentNode && (currentNode->getNodeType() == xercesc::DOMNode::ELEMENT_NODE))
			{
				auto* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);

				if (isXmlStringEqual(currentElement->getTagName(), nameToFind.c_str()))
				{
					res.push_back(currentNode);
				}
			}
		}
	}
	catch (xercesc::XMLException& e)
	{
		char* message = xercesc::XMLString::transcode(e.getMessage());
		//Tracing::error("Unexpected exception in XmlParser::getChild-DOMElement:\n");
		//Tracing::error(message);
		xercesc::XMLString::release(&message);
	}

	return res;
}

/*!
 * Get all children from element with the same name and returns the children for further processing.
 * This should be used for recurring elements.
 *
 * @param currNode Current node (parent)
 * @param nameToFind Name to be found in children tags
 * @returns List with pointers to child elements (or empty, if not found)
 */
std::vector<xercesc::DOMNode*> XmlParser::getChildren(xercesc::DOMNode* currNode,
	const std::string& nameToFind)
{
	if (currNode && (currNode->getNodeType() == xercesc::DOMNode::ELEMENT_NODE))
	{
		auto* currElement = dynamic_cast<xercesc::DOMElement*>(currNode);

		return getChildren(currElement, nameToFind);
	}
	return {};
}


} /* namespace spp */
