#include <boost/test/unit_test.hpp>

#include "File.h"

#include <filesystem>

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

BOOST_AUTO_TEST_CASE(write_001)
{
    std::filesystem::remove("./test-data/output.txt");

    std::string input = "FileContentLine1\nFileContentLine2\n";

    BOOST_CHECK(!spp::File::write("C:\\Program Files\\blaaaaaa.txt", input));

    BOOST_CHECK(!spp::File::write("./test-data/output_wrong.txt", ""));

    BOOST_CHECK(!spp::File::write("", input));

    BOOST_REQUIRE(spp::File::write("./test-data/output.txt", input));
    auto res1 = spp::File::read("./test-data/output.txt");
    BOOST_CHECK_EQUAL(res1, input);
}

BOOST_AUTO_TEST_CASE(writeBinary_001)
{
    std::filesystem::remove("./test-data/output.dat");

    std::vector<uint8_t> input { 0x01, 0x02, 0x03, 0x04, 0x00, 0x31, 0x32, 0x33, 0x34 };
    
    BOOST_CHECK(!spp::File::writeBinary("C:\\Program Files\\blaaaaaaXYXX.dat", input));

    BOOST_CHECK(!spp::File::writeBinary("./test-data/output_wrong.dat", {}));

    BOOST_CHECK(!spp::File::writeBinary("", input));

    BOOST_REQUIRE(spp::File::writeBinary("./test-data/output.dat", input));
    auto res1 = spp::File::readBinary("./test-data/output.dat");
    BOOST_CHECK_EQUAL_COLLECTIONS(res1.begin(), res1.end(), input.begin(), input.end());
}

BOOST_AUTO_TEST_SUITE_END()
