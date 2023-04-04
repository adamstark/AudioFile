#include "doctest.h"
#include <iostream>
#include <vector>
#include <AudioFile.h>

//=============================================================
TEST_SUITE ("SampleConversionTests::8-bit Conversions - signedByteToSample()")
{
    //=============================================================
    TEST_CASE ("8-bit Signed Conversions::signedByteToSample (float & double)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::signedByteToSample (127), 1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::signedByteToSample (63), doctest::Approx (0.4960629921f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::signedByteToSample (0), 0.f);
        REQUIRE_EQ (AudioSampleConverter<float>::signedByteToSample (-63), doctest::Approx (-0.4960629921f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::signedByteToSample (-127), -1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::signedByteToSample (-128), doctest::Approx (-1.007874015748f).epsilon (0.0001));
        
        REQUIRE_EQ (AudioSampleConverter<double>::signedByteToSample (127), 1.);
        REQUIRE_EQ (AudioSampleConverter<double>::signedByteToSample (63), doctest::Approx (0.4960629921).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::signedByteToSample (0), 0.);
        REQUIRE_EQ (AudioSampleConverter<double>::signedByteToSample (-63), doctest::Approx (-0.4960629921).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::signedByteToSample (-127), -1.);
        REQUIRE_EQ (AudioSampleConverter<double>::signedByteToSample (-128), doctest::Approx (-1.007874015748).epsilon (0.0001));
    }
    
    //=============================================================
    TEST_CASE ("8-bit Signed Conversions::signedByteToSample (unsigned integer types)")
    {
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::signedByteToSample (127), 255);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::signedByteToSample (63), 191);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::signedByteToSample (0), 128);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::signedByteToSample (-63), 65);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::signedByteToSample (-127), 1);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::signedByteToSample (-128), 0);
        
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::signedByteToSample (127), 255);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::signedByteToSample (63), 191);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::signedByteToSample (0), 128);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::signedByteToSample (-63), 65);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::signedByteToSample (-127), 1);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::signedByteToSample (-128), 0);
        
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::signedByteToSample (127), 255);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::signedByteToSample (63), 191);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::signedByteToSample (0), 128);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::signedByteToSample (-63), 65);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::signedByteToSample (-127), 1);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::signedByteToSample (-128), 0);
        
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::signedByteToSample (127), 255);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::signedByteToSample (63), 191);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::signedByteToSample (0), 128);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::signedByteToSample (-63), 65);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::signedByteToSample (-127), 1);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::signedByteToSample (-128), 0);
    }
    
    //=============================================================
    TEST_CASE ("8-bit Signed Conversions::signedByteToSample (signed integer types)")
    {
        REQUIRE_EQ (AudioSampleConverter<int8_t>::signedByteToSample (127), 127);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::signedByteToSample (63), 63);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::signedByteToSample (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::signedByteToSample (-63), -63);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::signedByteToSample (-127), -127);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::signedByteToSample (-128), -128);
        
        REQUIRE_EQ (AudioSampleConverter<int16_t>::signedByteToSample (127), 127);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::signedByteToSample (63), 63);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::signedByteToSample (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::signedByteToSample (-63), -63);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::signedByteToSample (-127), -127);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::signedByteToSample (-128), -128);
        
        REQUIRE_EQ (AudioSampleConverter<int32_t>::signedByteToSample (127), 127);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::signedByteToSample (63), 63);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::signedByteToSample (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::signedByteToSample (-63), -63);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::signedByteToSample (-127), -127);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::signedByteToSample (-128), -128);
        
        REQUIRE_EQ (AudioSampleConverter<int64_t>::signedByteToSample (127), 127);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::signedByteToSample (63), 63);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::signedByteToSample (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::signedByteToSample (-63), -63);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::signedByteToSample (-127), -127);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::signedByteToSample (-128), -128);
    }
}

//=============================================================
TEST_SUITE ("SampleConversionTests::8-bit Conversions - sampleToSignedByte()")
{
    //=============================================================
    TEST_CASE ("8-bit Signed Conversions::sampleToSignedByte (float and double)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSignedByte (std::numeric_limits<float>::max()), 127);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSignedByte (1.f), 127);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSignedByte (0.5f), 63);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSignedByte (0.f), 0);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSignedByte (-0.5f), -63);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSignedByte (-1.f), -127);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToSignedByte (std::numeric_limits<float>::lowest()), -127);
        
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSignedByte (std::numeric_limits<float>::max()), 127);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSignedByte (1.), 127);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSignedByte (0.5), 63);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSignedByte (0.), 0);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSignedByte (-0.5), -63);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSignedByte (-1.), -127);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToSignedByte (std::numeric_limits<double>::lowest()), -127);
    }
    
    //=============================================================
    TEST_CASE ("8-bit Signed Conversions::sampleToSignedByte (unsigned integers)")
    {
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::sampleToSignedByte (255), 127);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::sampleToSignedByte (191), 63);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::sampleToSignedByte (128), 0);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::sampleToSignedByte (65), -63);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::sampleToSignedByte (1), -127);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::sampleToSignedByte (0), -128);
        
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSignedByte (std::numeric_limits<uint16_t>::max()), 127);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSignedByte (255), 127);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSignedByte (191), 63);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSignedByte (128), 0);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSignedByte (65), -63);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSignedByte (1), -127);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSignedByte (0), -128);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSignedByte (std::numeric_limits<uint16_t>::min()), -128);
        
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSignedByte (std::numeric_limits<uint32_t>::max()), 127);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSignedByte (255), 127);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSignedByte (191), 63);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSignedByte (128), 0);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSignedByte (65), -63);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSignedByte (1), -127);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSignedByte (0), -128);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSignedByte (std::numeric_limits<uint32_t>::min()), -128);
        
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSignedByte (std::numeric_limits<uint64_t>::max()), 127);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSignedByte (255), 127);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSignedByte (191), 63);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSignedByte (128), 0);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSignedByte (65), -63);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSignedByte (1), -127);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSignedByte (0), -128);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSignedByte (std::numeric_limits<uint64_t>::min()), -128);
    }
    
    //=============================================================
    TEST_CASE ("8-bit Signed Conversions::sampleToSignedByte (signed integers)")
    {
        REQUIRE_EQ (AudioSampleConverter<int8_t>::sampleToSignedByte (127), 127);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::sampleToSignedByte (63), 63);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::sampleToSignedByte (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::sampleToSignedByte (-63), -63);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::sampleToSignedByte (-127), -127);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::sampleToSignedByte (-128), -128);
        
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSignedByte (std::numeric_limits<int16_t>::max()), 127);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSignedByte (127), 127);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSignedByte (63), 63);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSignedByte (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSignedByte (-63), -63);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSignedByte (-127), -127);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSignedByte (-128), -128);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSignedByte (std::numeric_limits<int16_t>::min()), -128);
        
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSignedByte (std::numeric_limits<int32_t>::max()), 127);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSignedByte (127), 127);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSignedByte (63), 63);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSignedByte (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSignedByte (-63), -63);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSignedByte (-127), -127);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSignedByte (-128), -128);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSignedByte (std::numeric_limits<int32_t>::min()), -128);
        
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSignedByte (std::numeric_limits<int64_t>::max()), 127);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSignedByte (127), 127);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSignedByte (63), 63);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSignedByte (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSignedByte (-63), -63);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSignedByte (-127), -127);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSignedByte (-128), -128);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSignedByte (std::numeric_limits<int64_t>::min()), -128);
    }
}
 
//=============================================================
TEST_SUITE ("SampleConversionTests::8-bit Conversions - unsignedByteToSample()")
{
    //=============================================================
    TEST_CASE ("8-bit Unsigned Conversions::unsignedByteToSample (float and double)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::unsignedByteToSample (255), 1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::unsignedByteToSample (191), doctest::Approx (0.4960629921f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::unsignedByteToSample (128), 0.f);
        REQUIRE_EQ (AudioSampleConverter<float>::unsignedByteToSample (65), doctest::Approx (-0.4960629921f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::unsignedByteToSample (1), -1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::unsignedByteToSample (0), doctest::Approx (-1.007874015748f).epsilon (0.0001));
        
        REQUIRE_EQ (AudioSampleConverter<double>::unsignedByteToSample (255), 1.);
        REQUIRE_EQ (AudioSampleConverter<double>::unsignedByteToSample (191), doctest::Approx (0.4960629921).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::unsignedByteToSample (128), 0.);
        REQUIRE_EQ (AudioSampleConverter<double>::unsignedByteToSample (65), doctest::Approx (-0.4960629921).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::unsignedByteToSample (1), -1.);
        REQUIRE_EQ (AudioSampleConverter<double>::unsignedByteToSample (0), doctest::Approx (-1.007874015748).epsilon (0.0001));
    }
    
    //=============================================================
    TEST_CASE ("8-bit Unsigned Conversions::unsignedByteToSample (unsigned integers)")
    {
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::unsignedByteToSample (255), 255);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::unsignedByteToSample (191), 191);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::unsignedByteToSample (128), 128);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::unsignedByteToSample (65), 65);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::unsignedByteToSample (1), 1);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::unsignedByteToSample (0), 0);
        
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::unsignedByteToSample (255), 255);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::unsignedByteToSample (191), 191);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::unsignedByteToSample (128), 128);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::unsignedByteToSample (65), 65);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::unsignedByteToSample (1), 1);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::unsignedByteToSample (0), 0);
        
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::unsignedByteToSample (255), 255);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::unsignedByteToSample (191), 191);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::unsignedByteToSample (128), 128);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::unsignedByteToSample (65), 65);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::unsignedByteToSample (1), 1);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::unsignedByteToSample (0), 0);
        
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::unsignedByteToSample (255), 255);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::unsignedByteToSample (191), 191);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::unsignedByteToSample (128), 128);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::unsignedByteToSample (65), 65);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::unsignedByteToSample (1), 1);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::unsignedByteToSample (0), 0);
    }
    
    //=============================================================
    TEST_CASE ("8-bit Unsigned Conversions::unsignedByteToSample (signed integers)")
    {
        REQUIRE_EQ (AudioSampleConverter<int8_t>::unsignedByteToSample (255), 127);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::unsignedByteToSample (191), 63);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::unsignedByteToSample (128), 0);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::unsignedByteToSample (65), -63);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::unsignedByteToSample (1), -127);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::unsignedByteToSample (0), -128);
        
        REQUIRE_EQ (AudioSampleConverter<int16_t>::unsignedByteToSample (255), 127);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::unsignedByteToSample (191), 63);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::unsignedByteToSample (128), 0);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::unsignedByteToSample (65), -63);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::unsignedByteToSample (1), -127);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::unsignedByteToSample (0), -128);
        
        REQUIRE_EQ (AudioSampleConverter<int32_t>::unsignedByteToSample (255), 127);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::unsignedByteToSample (191), 63);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::unsignedByteToSample (128), 0);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::unsignedByteToSample (65), -63);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::unsignedByteToSample (1), -127);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::unsignedByteToSample (0), -128);
        
        REQUIRE_EQ (AudioSampleConverter<int64_t>::unsignedByteToSample (255), 127);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::unsignedByteToSample (191), 63);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::unsignedByteToSample (128), 0);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::unsignedByteToSample (65), -63);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::unsignedByteToSample (1), -127);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::unsignedByteToSample (0), -128);
    }
}

//=============================================================
TEST_SUITE ("SampleConversionTests::8-bit Conversions - sampleToUnsignedByte()")
{
    //=============================================================
    TEST_CASE ("8-bit Signed Conversions::sampleToUnsignedByte (float and double)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToUnsignedByte (std::numeric_limits<float>::max()), 255);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToUnsignedByte (1.f), 255);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToUnsignedByte (0.5f), 191);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToUnsignedByte (0.f), 128);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToUnsignedByte (-0.5f), 64);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToUnsignedByte (-1.f), 1);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToUnsignedByte (std::numeric_limits<float>::lowest()), 1);
        
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToUnsignedByte (std::numeric_limits<double>::max()), 255);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToUnsignedByte (1.), 255);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToUnsignedByte (0.5), 191);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToUnsignedByte (0.), 128);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToUnsignedByte (-0.5), 64);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToUnsignedByte (-1.), 1);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToUnsignedByte (std::numeric_limits<double>::lowest()), 1);
    }
    
    //=============================================================
    TEST_CASE ("8-bit Signed Conversions::sampleToUnsignedByte (unsigned integers)")
    {
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::sampleToUnsignedByte (255), 255);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::sampleToUnsignedByte (191), 191);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::sampleToUnsignedByte (128), 128);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::sampleToUnsignedByte (65), 65);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::sampleToUnsignedByte (1), 1);
        REQUIRE_EQ (AudioSampleConverter<uint8_t>::sampleToUnsignedByte (0), 0);
        
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToUnsignedByte (std::numeric_limits<uint16_t>::max()), 255);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToUnsignedByte (255), 255);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToUnsignedByte (191), 191);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToUnsignedByte (128), 128);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToUnsignedByte (65), 65);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToUnsignedByte (1), 1);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToUnsignedByte (0), 0);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToUnsignedByte (std::numeric_limits<uint16_t>::min()), 0);
        
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToUnsignedByte (std::numeric_limits<uint32_t>::max()), 255);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToUnsignedByte (255), 255);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToUnsignedByte (191), 191);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToUnsignedByte (128), 128);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToUnsignedByte (65), 65);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToUnsignedByte (1), 1);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToUnsignedByte (0), 0);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToUnsignedByte (std::numeric_limits<uint32_t>::min()), 0);
        
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToUnsignedByte (std::numeric_limits<uint64_t>::max()), 255);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToUnsignedByte (255), 255);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToUnsignedByte (191), 191);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToUnsignedByte (128), 128);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToUnsignedByte (65), 65);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToUnsignedByte (1), 1);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToUnsignedByte (0), 0);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToUnsignedByte (std::numeric_limits<uint64_t>::min()), 0);
    }
    
    //=============================================================
    TEST_CASE ("8-bit Signed Conversions::sampleToUnsignedByte (signed integers)")
    {
        REQUIRE_EQ (AudioSampleConverter<int8_t>::sampleToUnsignedByte (127), 255);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::sampleToUnsignedByte (63), 191);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::sampleToUnsignedByte (0), 128);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::sampleToUnsignedByte (-63), 65);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::sampleToUnsignedByte (-127), 1);
        REQUIRE_EQ (AudioSampleConverter<int8_t>::sampleToUnsignedByte (-128), 0);
        
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToUnsignedByte (std::numeric_limits<int16_t>::max()), 255);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToUnsignedByte (127), 255);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToUnsignedByte (63), 191);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToUnsignedByte (0), 128);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToUnsignedByte (-63), 65);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToUnsignedByte (-127), 1);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToUnsignedByte (-128), 0);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToUnsignedByte (std::numeric_limits<int16_t>::min()), 0);
        
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToUnsignedByte (std::numeric_limits<int32_t>::max()), 255);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToUnsignedByte (127), 255);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToUnsignedByte (63), 191);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToUnsignedByte (0), 128);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToUnsignedByte (-63), 65);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToUnsignedByte (-127), 1);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToUnsignedByte (-128), 0);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToUnsignedByte (std::numeric_limits<int32_t>::min()), 0);
        
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToUnsignedByte (std::numeric_limits<int64_t>::max()), 255);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToUnsignedByte (127), 255);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToUnsignedByte (63), 191);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToUnsignedByte (0), 128);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToUnsignedByte (-63), 65);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToUnsignedByte (-127), 1);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToUnsignedByte (-128), 0);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToUnsignedByte (std::numeric_limits<int64_t>::min()), 0);
    }
}

//=============================================================
TEST_SUITE ("SampleConversionTests::16-bit Conversions")
{
    //=============================================================
    TEST_CASE ("16-bit Conversions::sixteenBitIntToSample (float & double)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::sixteenBitIntToSample (32767), 1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::sixteenBitIntToSample (16383), doctest::Approx (0.4999847407f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::sixteenBitIntToSample (0), 0.f);
        REQUIRE_EQ (AudioSampleConverter<float>::sixteenBitIntToSample (-16383), doctest::Approx (-0.4999847407f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::sixteenBitIntToSample (-32767), -1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::sixteenBitIntToSample (-32768), doctest::Approx (-1.00003f).epsilon (0.0001));
        
        REQUIRE_EQ (AudioSampleConverter<double>::sixteenBitIntToSample (32767), 1.);
        REQUIRE_EQ (AudioSampleConverter<double>::sixteenBitIntToSample (16383), doctest::Approx (0.4999847407).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::sixteenBitIntToSample (0), 0.);
        REQUIRE_EQ (AudioSampleConverter<double>::sixteenBitIntToSample (-16383), doctest::Approx (-0.4999847407).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::sixteenBitIntToSample (-32767), -1.);
        REQUIRE_EQ (AudioSampleConverter<double>::sixteenBitIntToSample (-32768), doctest::Approx (-1.00003).epsilon (0.0001));
    }
    
    //=============================================================
    TEST_CASE ("16-bit Conversions::sixteenBitIntToSample (unsigned integers)")
    {
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sixteenBitIntToSample (32767), 65535);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sixteenBitIntToSample (16383), 49151);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sixteenBitIntToSample (0), 32768);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sixteenBitIntToSample (-16383), 16385);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sixteenBitIntToSample (-32767), 1);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sixteenBitIntToSample (-32768), 0);
        
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sixteenBitIntToSample (32767), 65535);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sixteenBitIntToSample (16383), 49151);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sixteenBitIntToSample (0), 32768);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sixteenBitIntToSample (-16383), 16385);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sixteenBitIntToSample (-32767), 1);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sixteenBitIntToSample (-32768), 0);
        
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sixteenBitIntToSample (32767), 65535);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sixteenBitIntToSample (16383), 49151);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sixteenBitIntToSample (0), 32768);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sixteenBitIntToSample (-16383), 16385);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sixteenBitIntToSample (-32767), 1);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sixteenBitIntToSample (-32768), 0);
    }
    
    //=============================================================
    TEST_CASE ("16-bit Conversions::sixteenBitIntToSample (signed integers)")
    {
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sixteenBitIntToSample (32767), 32767);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sixteenBitIntToSample (16383), 16383);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sixteenBitIntToSample (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sixteenBitIntToSample (-16383), -16383);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sixteenBitIntToSample (-32767), -32767);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sixteenBitIntToSample (-32768), -32768);
        
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sixteenBitIntToSample (32767), 32767);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sixteenBitIntToSample (16383), 16383);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sixteenBitIntToSample (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sixteenBitIntToSample (-16383), -16383);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sixteenBitIntToSample (-32767), -32767);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sixteenBitIntToSample (-32768), -32768);
        
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sixteenBitIntToSample (32767), 32767);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sixteenBitIntToSample (16383), 16383);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sixteenBitIntToSample (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sixteenBitIntToSample (-16383), -16383);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sixteenBitIntToSample (-32767), -32767);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sixteenBitIntToSample (-32768), -32768);
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
    
    //=============================================================
    TEST_CASE ("16-bit Conversions::sampleToSixteenBitInt (unsigned int)")
    {
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSixteenBitInt (std::numeric_limits<uint16_t>::max()), 32767);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSixteenBitInt (65535), 32767);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSixteenBitInt (49151), 16383);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSixteenBitInt (32768), 0);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSixteenBitInt (16385), -16383);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSixteenBitInt (1), -32767);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSixteenBitInt (0), -32768);
        REQUIRE_EQ (AudioSampleConverter<uint16_t>::sampleToSixteenBitInt (std::numeric_limits<uint16_t>::min()), -32768);
        
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSixteenBitInt (std::numeric_limits<uint32_t>::max()), 32767);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSixteenBitInt (65535), 32767);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSixteenBitInt (49151), 16383);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSixteenBitInt (32768), 0);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSixteenBitInt (16385), -16383);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSixteenBitInt (1), -32767);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSixteenBitInt (0), -32768);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToSixteenBitInt (std::numeric_limits<uint32_t>::min()), -32768);
        
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSixteenBitInt (std::numeric_limits<uint64_t>::max()), 32767);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSixteenBitInt (65535), 32767);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSixteenBitInt (49151), 16383);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSixteenBitInt (32768), 0);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSixteenBitInt (16385), -16383);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSixteenBitInt (1), -32767);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSixteenBitInt (0), -32768);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToSixteenBitInt (std::numeric_limits<uint64_t>::min()), -32768);
    }
    
    //=============================================================
    TEST_CASE ("16-bit Conversions::sampleToSixteenBitInt (signed int)")
    {
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSixteenBitInt (std::numeric_limits<int16_t>::max()), 32767);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSixteenBitInt (32767), 32767);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSixteenBitInt (16383), 16383);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSixteenBitInt (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSixteenBitInt (-16383), -16383);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSixteenBitInt (-32767), -32767);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSixteenBitInt (-32768), -32768);
        REQUIRE_EQ (AudioSampleConverter<int16_t>::sampleToSixteenBitInt (std::numeric_limits<int16_t>::lowest()), -32768);
        
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSixteenBitInt (std::numeric_limits<int32_t>::max()), 32767);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSixteenBitInt (32767), 32767);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSixteenBitInt (16383), 16383);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSixteenBitInt (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSixteenBitInt (-16383), -16383);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSixteenBitInt (-32767), -32767);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSixteenBitInt (-32768), -32768);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToSixteenBitInt (std::numeric_limits<int32_t>::lowest()), -32768);
        
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSixteenBitInt (std::numeric_limits<int64_t>::max()), 32767);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSixteenBitInt (32767), 32767);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSixteenBitInt (16383), 16383);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSixteenBitInt (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSixteenBitInt (-16383), -16383);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSixteenBitInt (-32767), -32767);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSixteenBitInt (-32768), -32768);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToSixteenBitInt (std::numeric_limits<int64_t>::lowest()), -32768);
    }
}

//=============================================================
TEST_SUITE ("SampleConversionTests::24-bit Conversions")
{
    //=============================================================
    TEST_CASE ("24-bit Conversions::twentyFourBitIntToSample (float and double)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::twentyFourBitIntToSample (8388607), 1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::twentyFourBitIntToSample (4194303), doctest::Approx (0.5f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::twentyFourBitIntToSample (0), 0.f);
        REQUIRE_EQ (AudioSampleConverter<float>::twentyFourBitIntToSample (-4194303), doctest::Approx (-0.5f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::twentyFourBitIntToSample (-8388607), -1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::twentyFourBitIntToSample (-8388608), doctest::Approx (-1.0000001192f).epsilon (0.0001));
        
        REQUIRE_EQ (AudioSampleConverter<double>::twentyFourBitIntToSample (8388607), 1.);
        REQUIRE_EQ (AudioSampleConverter<double>::twentyFourBitIntToSample (4194303), doctest::Approx (0.5).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::twentyFourBitIntToSample (0), 0.);
        REQUIRE_EQ (AudioSampleConverter<double>::twentyFourBitIntToSample (-4194303), doctest::Approx (-0.5).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::twentyFourBitIntToSample (-8388607), -1.);
        REQUIRE_EQ (AudioSampleConverter<double>::twentyFourBitIntToSample (-8388608), doctest::Approx (-1.0000001192).epsilon (0.0001));
    }
    
    //=============================================================
    TEST_CASE ("24-bit Conversions::twentyFourBitIntToSample (unsigned integers)")
    {
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::twentyFourBitIntToSample (8388607), 16777215);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::twentyFourBitIntToSample (4194303), 12582911);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::twentyFourBitIntToSample (0), 8388608);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::twentyFourBitIntToSample (-4194303), 4194305);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::twentyFourBitIntToSample (-8388607), 1);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::twentyFourBitIntToSample (-8388608), 0);
        
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::twentyFourBitIntToSample (8388607), 16777215);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::twentyFourBitIntToSample (4194303), 12582911);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::twentyFourBitIntToSample (0), 8388608);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::twentyFourBitIntToSample (-4194303), 4194305);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::twentyFourBitIntToSample (-8388607), 1);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::twentyFourBitIntToSample (-8388608), 0);
    }
    
    //=============================================================
    TEST_CASE ("24-bit Conversions::twentyFourBitIntToSample (signed integers)")
    {
        REQUIRE_EQ (AudioSampleConverter<int32_t>::twentyFourBitIntToSample (8388607), 8388607);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::twentyFourBitIntToSample (4194303), 4194303);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::twentyFourBitIntToSample (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::twentyFourBitIntToSample (-4194303), -4194303);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::twentyFourBitIntToSample (-8388607), -8388607);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::twentyFourBitIntToSample (-8388608), -8388608);
        
        REQUIRE_EQ (AudioSampleConverter<int64_t>::twentyFourBitIntToSample (8388607), 8388607);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::twentyFourBitIntToSample (4194303), 4194303);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::twentyFourBitIntToSample (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::twentyFourBitIntToSample (-4194303), -4194303);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::twentyFourBitIntToSample (-8388607), -8388607);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::twentyFourBitIntToSample (-8388608), -8388608);
    }
    
    //=============================================================
    TEST_CASE ("24-bit Conversions::sampleToTwentyFourBitInt (float and double)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToTwentyFourBitInt (1.f), 8388607);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToTwentyFourBitInt (0.5f), 4194303);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToTwentyFourBitInt (0.f), 0);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToTwentyFourBitInt (-0.5f), -4194303);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToTwentyFourBitInt (-1.f), -8388607);
        
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToTwentyFourBitInt (1.), 8388607);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToTwentyFourBitInt (0.5), 4194303);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToTwentyFourBitInt (0.), 0);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToTwentyFourBitInt (-0.5), -4194303);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToTwentyFourBitInt (-1.), -8388607);
    }
    
    //=============================================================
    TEST_CASE ("24-bit Conversions::sampleToTwentyFourBitInt (unsigned integers)")
    {
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToTwentyFourBitInt (std::numeric_limits<uint32_t>::max()), 8388607);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToTwentyFourBitInt (16777215), 8388607);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToTwentyFourBitInt (12582911), 4194303);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToTwentyFourBitInt (8388608), 0);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToTwentyFourBitInt (4194305), -4194303);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToTwentyFourBitInt (1), -8388607);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToTwentyFourBitInt (0), -8388608);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToTwentyFourBitInt (std::numeric_limits<uint32_t>::min()), -8388608);
        
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToTwentyFourBitInt (std::numeric_limits<uint64_t>::max()), 8388607);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToTwentyFourBitInt (16777215), 8388607);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToTwentyFourBitInt (12582911), 4194303);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToTwentyFourBitInt (8388608), 0);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToTwentyFourBitInt (4194305), -4194303);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToTwentyFourBitInt (1), -8388607);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToTwentyFourBitInt (0), -8388608);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToTwentyFourBitInt (std::numeric_limits<uint64_t>::min()), -8388608);
    }
    
    //=============================================================
    TEST_CASE ("24-bit Conversions::sampleToTwentyFourBitInt (signed integers)")
    {
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToTwentyFourBitInt (std::numeric_limits<int32_t>::max()), 8388607);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToTwentyFourBitInt (8388607), 8388607);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToTwentyFourBitInt (4194303), 4194303);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToTwentyFourBitInt (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToTwentyFourBitInt (-4194303), -4194303);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToTwentyFourBitInt (-8388607), -8388607);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToTwentyFourBitInt (-8388608), -8388608);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToTwentyFourBitInt (std::numeric_limits<int32_t>::min()), -8388608);
        
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToTwentyFourBitInt (std::numeric_limits<int64_t>::max()), 8388607);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToTwentyFourBitInt (8388607), 8388607);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToTwentyFourBitInt (4194303), 4194303);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToTwentyFourBitInt (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToTwentyFourBitInt (-4194303), -4194303);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToTwentyFourBitInt (-8388607), -8388607);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToTwentyFourBitInt (-8388608), -8388608);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToTwentyFourBitInt (std::numeric_limits<int64_t>::min()), -8388608);
    }
}

//=============================================================
TEST_SUITE ("SampleConversionTests::32-bit Conversions")
{
    //=============================================================
    TEST_CASE ("32-bit Conversions::thirtyTwoBitIntToSample (float and double)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::thirtyTwoBitIntToSample (2147483647), 1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::thirtyTwoBitIntToSample (1073741824), doctest::Approx (0.5f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::thirtyTwoBitIntToSample (0), 0.f);
        REQUIRE_EQ (AudioSampleConverter<float>::thirtyTwoBitIntToSample (-1073741824), doctest::Approx (-0.5f).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<float>::thirtyTwoBitIntToSample (-2147483647), -1.f);
        REQUIRE_EQ (AudioSampleConverter<float>::thirtyTwoBitIntToSample (-2147483648), doctest::Approx (-1.00000000046566f).epsilon (0.0001));
        
        REQUIRE_EQ (AudioSampleConverter<double>::thirtyTwoBitIntToSample (2147483647), 1.);
        REQUIRE_EQ (AudioSampleConverter<double>::thirtyTwoBitIntToSample (1073741824), doctest::Approx (0.5).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::thirtyTwoBitIntToSample (0), 0.f);
        REQUIRE_EQ (AudioSampleConverter<double>::thirtyTwoBitIntToSample (-1073741824), doctest::Approx (-0.5).epsilon (0.0001));
        REQUIRE_EQ (AudioSampleConverter<double>::thirtyTwoBitIntToSample (-2147483647), -1.);
        REQUIRE_EQ (AudioSampleConverter<double>::thirtyTwoBitIntToSample (-2147483648), doctest::Approx (-1.00000000046566).epsilon (0.0001));
    }
    
    //=============================================================
    TEST_CASE ("32-bit Conversions::thirtyTwoBitIntToSample (unsigned integer)")
    {
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::thirtyTwoBitIntToSample (2147483647), 4294967295);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::thirtyTwoBitIntToSample (1073741824), 3221225472);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::thirtyTwoBitIntToSample (0), 2147483648);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::thirtyTwoBitIntToSample (-1073741824), 1073741824);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::thirtyTwoBitIntToSample (-2147483647), 1);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::thirtyTwoBitIntToSample (-2147483648), 0);
        
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::thirtyTwoBitIntToSample (2147483647), 4294967295);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::thirtyTwoBitIntToSample (1073741824), 3221225472);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::thirtyTwoBitIntToSample (0), 2147483648);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::thirtyTwoBitIntToSample (-1073741824), 1073741824);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::thirtyTwoBitIntToSample (-2147483647), 1);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::thirtyTwoBitIntToSample (-2147483648), 0);
    }
    
    //=============================================================
    TEST_CASE ("32-bit Conversions::thirtyTwoBitIntToSample (signed integer)")
    {
        REQUIRE_EQ (AudioSampleConverter<int32_t>::thirtyTwoBitIntToSample (2147483647), 2147483647);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::thirtyTwoBitIntToSample (1073741824), 1073741824);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::thirtyTwoBitIntToSample (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::thirtyTwoBitIntToSample (-1073741824), -1073741824);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::thirtyTwoBitIntToSample (-2147483647), -2147483647);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::thirtyTwoBitIntToSample (-2147483648), -2147483648);
        
        REQUIRE_EQ (AudioSampleConverter<int64_t>::thirtyTwoBitIntToSample (2147483647), 2147483647);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::thirtyTwoBitIntToSample (1073741824), 1073741824);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::thirtyTwoBitIntToSample (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::thirtyTwoBitIntToSample (-1073741824), -1073741824);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::thirtyTwoBitIntToSample (-2147483647), -2147483647);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::thirtyTwoBitIntToSample (-2147483648), -2147483648LL);
    }
    
    //=============================================================
    TEST_CASE ("32-bit Conversions::sampleToThirtyTwoBitInt (float and double)")
    {
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToThirtyTwoBitInt (std::numeric_limits<float>::max()), 2147483647);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToThirtyTwoBitInt (1.f), 2147483647);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToThirtyTwoBitInt (0.5f), 1073741824);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToThirtyTwoBitInt (0.f), 0);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToThirtyTwoBitInt (-0.5f), -1073741824);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToThirtyTwoBitInt (-1.f), -2147483647);
        REQUIRE_EQ (AudioSampleConverter<float>::sampleToThirtyTwoBitInt (std::numeric_limits<float>::lowest()), -2147483647);
        
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToThirtyTwoBitInt (std::numeric_limits<double>::max()), 2147483647);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToThirtyTwoBitInt (1.f), 2147483647);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToThirtyTwoBitInt (0.5f), 1073741823);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToThirtyTwoBitInt (0.f), 0);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToThirtyTwoBitInt (-0.5f), -1073741823);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToThirtyTwoBitInt (-1.), -2147483647);
        REQUIRE_EQ (AudioSampleConverter<double>::sampleToThirtyTwoBitInt (std::numeric_limits<double>::lowest()), -2147483647);
    }
    
    //=============================================================
    TEST_CASE ("32-bit Conversions::sampleToThirtyTwoBitInt (unsigned integers)")
    {
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToThirtyTwoBitInt (std::numeric_limits<uint32_t>::max()), 2147483647);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToThirtyTwoBitInt (4294967295), 2147483647);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToThirtyTwoBitInt (3221225472), 1073741824);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToThirtyTwoBitInt (2147483648), 0);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToThirtyTwoBitInt (1073741824), -1073741824);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToThirtyTwoBitInt (1), -2147483647);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToThirtyTwoBitInt (0), -2147483648);
        REQUIRE_EQ (AudioSampleConverter<uint32_t>::sampleToThirtyTwoBitInt (std::numeric_limits<uint32_t>::min()), -2147483648);
        
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToThirtyTwoBitInt (std::numeric_limits<uint64_t>::max()), 2147483647);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToThirtyTwoBitInt (4294967295), 2147483647);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToThirtyTwoBitInt (3221225472), 1073741824);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToThirtyTwoBitInt (2147483648), 0);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToThirtyTwoBitInt (1073741824), -1073741824);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToThirtyTwoBitInt (1), -2147483647);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToThirtyTwoBitInt (0), -2147483648);
        REQUIRE_EQ (AudioSampleConverter<uint64_t>::sampleToThirtyTwoBitInt (std::numeric_limits<uint64_t>::min()), -2147483648);
    }
    
    //=============================================================
    TEST_CASE ("32-bit Conversions::sampleToThirtyTwoBitInt (signed integers)")
    {
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToThirtyTwoBitInt (std::numeric_limits<int32_t>::max()), 2147483647);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToThirtyTwoBitInt (2147483647), 2147483647);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToThirtyTwoBitInt (1073741824), 1073741824);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToThirtyTwoBitInt (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToThirtyTwoBitInt (-1073741824), -1073741824);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToThirtyTwoBitInt (-2147483647), -2147483647);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToThirtyTwoBitInt (-2147483648), -2147483648);
        REQUIRE_EQ (AudioSampleConverter<int32_t>::sampleToThirtyTwoBitInt (std::numeric_limits<int32_t>::min()), -2147483648);
        
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToThirtyTwoBitInt (std::numeric_limits<int64_t>::max()), 2147483647);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToThirtyTwoBitInt (2147483647), 2147483647);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToThirtyTwoBitInt (1073741824), 1073741824);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToThirtyTwoBitInt (0), 0);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToThirtyTwoBitInt (-1073741824), -1073741824);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToThirtyTwoBitInt (-2147483647), -2147483647);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToThirtyTwoBitInt (-2147483648LL), -2147483648LL);
        REQUIRE_EQ (AudioSampleConverter<int64_t>::sampleToThirtyTwoBitInt (std::numeric_limits<int64_t>::min()), -2147483648);
    }
}
