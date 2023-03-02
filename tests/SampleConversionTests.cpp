#include "doctest.h"
#include <iostream>
#include <vector>
#include <AudioFile.h>

//=============================================================
TEST_SUITE ("SampleConversionTests::8-bit Conversions")
{
    //=============================================================
    TEST_CASE ("8-bit Signed Conversions::signedByteToSample (float)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::signedByteToSample (127), 1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::signedByteToSample (63), doctest::Approx (0.4960629921f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::signedByteToSample (0), 0.f);
        REQUIRE_EQ (AudioSampleConverter<float>::signedByteToSample (-63), doctest::Approx (-0.4960629921f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::signedByteToSample (-127), -1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::signedByteToSample (-128), doctest::Approx (-1.007874015748f).epsilon (0.0001));
    }
    
    //=============================================================
    TEST_CASE ("8-bit Signed Conversions::signedByteToSample (double)")
    {
        REQUIRE_EQ (AudioSampleConverter<double>::signedByteToSample (127), 1.);
        REQUIRE_EQ (AudioSampleConverter<double>::signedByteToSample (63), doctest::Approx (0.4960629921).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::signedByteToSample (0), 0.);
        REQUIRE_EQ (AudioSampleConverter<double>::signedByteToSample (-63), doctest::Approx (-0.4960629921).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::signedByteToSample (-127), -1.);
        REQUIRE_EQ (AudioSampleConverter<double>::signedByteToSample (-128), doctest::Approx (-1.007874015748).epsilon (0.0001));
    }
    
    //=============================================================
    TEST_CASE ("8-bit Signed Conversions::sampleToSignedByte (float)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSignedByte (1.f), 127);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSignedByte (0.5f), 63);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSignedByte (0.f), 0);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSignedByte (-0.5f), -63);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSignedByte (-1.f), -127);
    }
    
    //=============================================================
    TEST_CASE ("8-bit Signed Conversions::sampleToSignedByte (double)")
    {
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSignedByte (1.), 127);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSignedByte (0.5), 63);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSignedByte (0.), 0);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSignedByte (-0.5), -63);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSignedByte (-1.), -127);
    }
    
    //=============================================================
    TEST_CASE ("8-bit Unsigned Conversions::unsignedByteToSample (float)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::unsignedByteToSample (255), 1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::unsignedByteToSample (191), doctest::Approx (0.4960629921f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::unsignedByteToSample (128), 0.f);
        REQUIRE_EQ (AudioSampleConverter<float>::unsignedByteToSample (65), doctest::Approx (-0.4960629921f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::unsignedByteToSample (1), -1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::unsignedByteToSample (0), doctest::Approx (-1.007874015748f).epsilon (0.0001));
    }
    
    //=============================================================
    TEST_CASE ("8-bit Unsigned Conversions::unsignedByteToSample (double)")
    {
        REQUIRE_EQ (AudioSampleConverter<double>::unsignedByteToSample (255), 1.);
        REQUIRE_EQ (AudioSampleConverter<double>::unsignedByteToSample (191), doctest::Approx (0.4960629921).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::unsignedByteToSample (128), 0.);
        REQUIRE_EQ (AudioSampleConverter<double>::unsignedByteToSample (65), doctest::Approx (-0.4960629921).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::unsignedByteToSample (1), -1.);
        REQUIRE_EQ (AudioSampleConverter<double>::unsignedByteToSample (0), doctest::Approx (-1.007874015748).epsilon (0.0001));
    }
    
    //=============================================================
    TEST_CASE ("8-bit Signed Conversions::sampleToUnsignedByte (float)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToUnsignedByte (1.f), 255);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToUnsignedByte (0.5f), 191);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToUnsignedByte (0.f), 128);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToUnsignedByte (-0.5f), 64);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToUnsignedByte (-1.f), 1);
    }
    
    //=============================================================
    TEST_CASE ("8-bit Signed Conversions::sampleToUnsignedByte (double)")
    {
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToUnsignedByte (1.), 255);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToUnsignedByte (0.5), 191);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToUnsignedByte (0.), 128);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToUnsignedByte (-0.5), 64);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToUnsignedByte (-1.), 1);
    }
}

//=============================================================
TEST_SUITE ("SampleConversionTests::16-bit Conversions")
{
    //=============================================================
    TEST_CASE ("16-bit Conversions::sixteenBitIntToSample (float)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::sixteenBitIntToSample (32767), 1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::sixteenBitIntToSample (16383), doctest::Approx (0.4999847407f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::sixteenBitIntToSample (0), 0.f);
        REQUIRE_EQ (AudioSampleConverter<float>::sixteenBitIntToSample (-16383), doctest::Approx (-0.4999847407f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::sixteenBitIntToSample (-32767), -1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::sixteenBitIntToSample (-32768), doctest::Approx (-1.00003f).epsilon (0.0001));
    }
    
    //=============================================================
    TEST_CASE ("16-bit Conversions::sixteenBitIntToSample (double)")
    {
        REQUIRE_EQ (AudioSampleConverter<double>::sixteenBitIntToSample (32767), 1.);
        REQUIRE_EQ (AudioSampleConverter<double>::sixteenBitIntToSample (16383), doctest::Approx (0.4999847407).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::sixteenBitIntToSample (0), 0.);
        REQUIRE_EQ (AudioSampleConverter<double>::sixteenBitIntToSample (-16383), doctest::Approx (-0.4999847407).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::sixteenBitIntToSample (-32767), -1.);
        REQUIRE_EQ (AudioSampleConverter<double>::sixteenBitIntToSample (-32768), doctest::Approx (-1.00003).epsilon (0.0001));
    }
    
    //=============================================================
    TEST_CASE ("16-bit Conversions::sampleToSixteenBitInt (float)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSixteenBitInt (1.f), 32767);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSixteenBitInt (0.5f), 16383);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSixteenBitInt (0.f), 0);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSixteenBitInt (-0.5f), -16383);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSixteenBitInt (-1.f), -32767);
    }
    
    //=============================================================
    TEST_CASE ("16-bit Conversions::sampleToSixteenBitInt (double)")
    {
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSixteenBitInt (1.), 32767);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSixteenBitInt (0.5), 16383);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSixteenBitInt (0.), 0);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSixteenBitInt (-0.5), -16383);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSixteenBitInt (-1.), -32767);
    }
}

//=============================================================
TEST_SUITE ("SampleConversionTests::24-bit Conversions")
{
    //=============================================================
    TEST_CASE ("24-bit Conversions::sixteenBitIntToSample (float)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::twentyFourBitIntToSample (8388607), 1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::twentyFourBitIntToSample (4194303), doctest::Approx (0.5f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::twentyFourBitIntToSample (0), 0.f);
        REQUIRE_EQ (AudioSampleConverter<float>::twentyFourBitIntToSample (-4194303), doctest::Approx (-0.5f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::twentyFourBitIntToSample (-8388607), -1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::twentyFourBitIntToSample (-8388608), doctest::Approx (-1.0000001192f).epsilon (0.0001));
    }
    
    //=============================================================
    TEST_CASE ("24-bit Conversions::sixteenBitIntToSample (double)")
    {
        REQUIRE_EQ (AudioSampleConverter<double>::twentyFourBitIntToSample (8388607), 1.);
        REQUIRE_EQ (AudioSampleConverter<double>::twentyFourBitIntToSample (4194303), doctest::Approx (0.5).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::twentyFourBitIntToSample (0), 0.);
        REQUIRE_EQ (AudioSampleConverter<double>::twentyFourBitIntToSample (-4194303), doctest::Approx (-0.5).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::twentyFourBitIntToSample (-8388607), -1.);
        REQUIRE_EQ (AudioSampleConverter<double>::twentyFourBitIntToSample (-8388608), doctest::Approx (-1.0000001192).epsilon (0.0001));
    }
    
    //=============================================================
    TEST_CASE ("24-bit Conversions::sampleToTwentyFourBitInt (float)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToTwentyFourBitInt (1.f), 8388607);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToTwentyFourBitInt (0.5f), 4194303);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToTwentyFourBitInt (0.f), 0);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToTwentyFourBitInt (-0.5f), -4194303);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToTwentyFourBitInt (-1.f), -8388607);
    }
    
    //=============================================================
    TEST_CASE ("24-bit Conversions::sampleToTwentyFourBitInt (double)")
    {
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToTwentyFourBitInt (1.), 8388607);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToTwentyFourBitInt (0.5), 4194303);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToTwentyFourBitInt (0.), 0);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToTwentyFourBitInt (-0.5), -4194303);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToTwentyFourBitInt (-1.), -8388607);
    }
}
