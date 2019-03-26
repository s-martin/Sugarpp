#include <boost/test/unit_test.hpp>

#include "CXXWinApi.h"

BOOST_AUTO_TEST_SUITE(UnitTest)

BOOST_AUTO_TEST_CASE(getFileVersionInfo_001)
{
    auto res1 = spp::CXXWinApi::getFileVersionInfo();
    BOOST_CHECK_EQUAL("1.0.0.0", res1);
}

BOOST_AUTO_TEST_SUITE_END()