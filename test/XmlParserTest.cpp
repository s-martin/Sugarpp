#include <boost/test/unit_test.hpp>

#include "XmlParser.h"

BOOST_AUTO_TEST_SUITE(UnitTest)

class XmlFixture
{
public:
	std::string xmlString1;
	std::string xmlString2;
	std::string xmlString3;

	XmlFixture()
	{
		xmlString1 = "<Ex><StringVal>String123</StringVal><Num>234</Num></Ex>";
		xmlString2 = "<Ex><StringVal>String123</StringVal><Num>234</Num></Ex>"; // TODO complex tree
		xmlString3 = "<Ex><StringVal Attr=\"AttrVal\" NumAttr=\"12345\">String123</StringVal><Num>234</Num></Ex>";
	}
};

BOOST_FIXTURE_TEST_CASE(getDocument_001, XmlFixture)
{
    spp::XmlParser parser;
    auto res1 = parser.getDocument(xmlString1);
    BOOST_REQUIRE(res1);
}

BOOST_FIXTURE_TEST_CASE(getStringValue_001, XmlFixture)
{
	spp::XmlParser parser;
	auto doc = parser.getDocument(xmlString1);
	BOOST_REQUIRE(doc);

	BOOST_CHECK_EQUAL(parser.getStringValue(doc->getDocumentElement(), "StringVal"), "String123");
}

BOOST_FIXTURE_TEST_CASE(getStringValue_002, XmlFixture)
{
	// error cases

	spp::XmlParser parser;
	auto doc = parser.getDocument(xmlString1);
	BOOST_REQUIRE(doc);

	BOOST_CHECK(parser.getStringValue(doc->getDocumentElement(), "blaablubb").empty());
}

BOOST_FIXTURE_TEST_CASE(getNumericValue_001, XmlFixture)
{
	spp::XmlParser parser;
	auto doc = parser.getDocument(xmlString1);
	BOOST_REQUIRE(doc);
	BOOST_CHECK_EQUAL(parser.getNumericValue<int>(doc->getDocumentElement(), "Num"), int(234));
}

BOOST_FIXTURE_TEST_CASE(getNumericValue_002, XmlFixture)
{
	// error cases

	spp::XmlParser parser;
	auto doc = parser.getDocument(xmlString1);
	BOOST_REQUIRE(doc);
	BOOST_CHECK_EQUAL(parser.getNumericValue<double>(doc->getDocumentElement(), "Num"), double(234));
	BOOST_CHECK_EQUAL(parser.getNumericValue<int>(doc->getDocumentElement(), "StringVal"), spp::UNDEFINED_NUM);
	BOOST_CHECK_EQUAL(parser.getNumericValue<int>(doc->getDocumentElement(), "blablubb"), spp::UNDEFINED_NUM);
}

BOOST_FIXTURE_TEST_CASE(getStringAttribute_001, XmlFixture)
{
	spp::XmlParser parser;
	auto doc = parser.getDocument(xmlString3);
	BOOST_REQUIRE(doc);

	BOOST_CHECK_EQUAL(parser.getStringAttribute(doc->getDocumentElement(), /*"StringVal",*/ "Attr"), "AttrVal");
}

BOOST_FIXTURE_TEST_CASE(getStringAttribute_002, XmlFixture)
{
	// error cases

	spp::XmlParser parser;
	auto doc = parser.getDocument(xmlString3);
	BOOST_REQUIRE(doc);

	BOOST_CHECK(parser.getStringAttribute(doc->getDocumentElement(), /*"StringVal",*/ "blubb").empty());
	BOOST_CHECK(parser.getStringAttribute(doc->getDocumentElement(), /*"StringVal",*/ "").empty());
	BOOST_CHECK(parser.getStringAttribute(doc->getDocumentElement(), /*"Num", */"Attr1").empty());
}

BOOST_FIXTURE_TEST_CASE(getNumericAttribute_001, XmlFixture)
{
	spp::XmlParser parser;
	auto doc = parser.getDocument(xmlString3);
	BOOST_REQUIRE(doc);
	BOOST_CHECK_EQUAL(parser.getNumericAttribute<int>(doc->getDocumentElement(), "StringVal", "NumAttr"), int(12345));
}

BOOST_FIXTURE_TEST_CASE(getNumericAttribute_002, XmlFixture)
{
	// error cases

	spp::XmlParser parser;
	auto doc = parser.getDocument(xmlString3);
	BOOST_REQUIRE(doc);
	BOOST_CHECK_EQUAL(parser.getNumericAttribute<int>(doc->getDocumentElement(), "StringVal", "Attr"), spp::UNDEFINED_NUM);
	BOOST_CHECK_EQUAL(parser.getNumericAttribute<int>(doc->getDocumentElement(), "StringVal", ""), spp::UNDEFINED_NUM);
}


BOOST_AUTO_TEST_SUITE_END()