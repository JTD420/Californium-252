// Copyright (c) 2011-2020 The Californium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <test/util/setup_common.h>
#include <util/strencodings.h>

#include <boost/test/unit_test.hpp>
#include <string>

using namespace std::literals;

BOOST_FIXTURE_TEST_SUITE(base64_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(base64_testvectors)
{
    static const std::string vstrIn[]  = {"","f","fo","foo","foob","fooba","foobar"};
    static const std::string vstrOut[] = {"","Zg==","Zm8=","Zm9v","Zm9vYg==","Zm9vYmE=","Zm9vYmFy"};
    for (unsigned int i=0; i<sizeof(vstrIn)/sizeof(vstrIn[0]); i++)
    {
        std::string strEnc = EncodeBase64(vstrIn[i]);
        BOOST_CHECK_EQUAL(strEnc, vstrOut[i]);
        std::string strDec = DecodeBase64(strEnc);
        BOOST_CHECK_EQUAL(strDec, vstrIn[i]);
    }

    // Decoding strings with embedded NUL characters should fail
    bool failure;
    (void)DecodeBase64("invalid\0"s, &failure);
    BOOST_CHECK(failure);
    (void)DecodeBase64("nQB/pZw="s, &failure);
    BOOST_CHECK(!failure);
    (void)DecodeBase64("nQB/pZw=\0invalid"s, &failure);
    BOOST_CHECK(failure);
    (void)DecodeBase64("nQB/pZw=invalid\0"s, &failure);
    BOOST_CHECK(failure);
}

BOOST_AUTO_TEST_SUITE_END()
