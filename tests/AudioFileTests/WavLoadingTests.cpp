#ifndef WAV_LOADING_TESTS
#define WAV_LOADING_TESTS
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

//=============================================================
BOOST_AUTO_TEST_SUITE(WavLoadingTests)

//=============================================================
BOOST_AUTO_TEST_CASE(WavLoadingTests_1)
{
    BOOST_CHECK_EQUAL (2.0 + 2.0, 4.0);
}

BOOST_AUTO_TEST_SUITE_END()

#endif
