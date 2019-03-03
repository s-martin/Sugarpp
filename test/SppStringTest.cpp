#include <boost/test/unit_test.hpp>

#include "SppString.h"

BOOST_AUTO_TEST_SUITE(UnitTest)

BOOST_AUTO_TEST_CASE(split_001)
{
    auto res1 = spp::String::split("to;be;splitted;", ';');
    BOOST_REQUIRE_EQUAL(3, res1.size());
    BOOST_CHECK_EQUAL("to", res1.at(0));
    BOOST_CHECK_EQUAL("be", res1.at(1));
    BOOST_CHECK_EQUAL("splitted", res1.at(2));

    auto res2 = spp::String::split("splitted;", ';');
    BOOST_REQUIRE_EQUAL(1, res2.size());
    BOOST_CHECK_EQUAL("splitted", res2.at(0));

    auto res3 = spp::String::split("to;be;splitted;", ',');
    BOOST_REQUIRE(res3.empty());
}

BOOST_AUTO_TEST_CASE(contains_001)
{
    BOOST_CHECK(spp::String::contains("to;be;contained;", ';'));
    BOOST_CHECK(spp::String::contains("to;be", ';'));
    BOOST_CHECK(spp::String::contains(";", ';'));
    BOOST_CHECK(!spp::String::contains("to;be;contained;", ','));
}

BOOST_AUTO_TEST_SUITE_END()