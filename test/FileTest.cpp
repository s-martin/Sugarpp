#include <boost/test/unit_test.hpp>

#include "File.h"

BOOST_AUTO_TEST_SUITE(UnitTest)

BOOST_AUTO_TEST_CASE(read_001)
{
    auto res1 = spp::File::read("");
    BOOST_CHECK(res1.empty());

    auto res2 = spp::File::read("./test-data/blubb");
    BOOST_CHECK(res2.empty());

    auto res3 = spp::File::read("./test-data/test.txt");
    BOOST_CHECK(!res3.empty());
    BOOST_CHECK_EQUAL(res3, "Test123\nTest456");
}

BOOST_AUTO_TEST_CASE(readLines_001)
{
    auto res1 = spp::File::readLines("");
    BOOST_CHECK(res1.empty());
    
    auto res2 = spp::File::readLines("./test-data/blubb");
    BOOST_CHECK(res2.empty());

    auto res3 = spp::File::readLines("./test-data/test.txt");
    BOOST_CHECK_EQUAL(res3.size(), 2);
    BOOST_CHECK_EQUAL(res3.at(0), "Test123");
    BOOST_CHECK_EQUAL(res3.at(1), "Test456");
}

BOOST_AUTO_TEST_CASE(readBinary_001)
{
    auto res1 = spp::File::readBinary("");
    BOOST_CHECK(res1.empty());

    auto res2 = spp::File::readBinary("./test-data/blubb");
    BOOST_CHECK(res2.empty());

    auto res3 = spp::File::readBinary("./test-data/test.bin");
    BOOST_REQUIRE_EQUAL(res3.size(), 9);
    std::vector<uint8_t> exp { 0x01, 0x02, 0x03, 0x04, 0x00, 0x31, 0x32, 0x33, 0x34 };
    BOOST_CHECK_EQUAL_COLLECTIONS(res3.begin(), res3.end(), exp.begin(), exp.end());
}

BOOST_AUTO_TEST_SUITE_END()