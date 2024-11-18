#include "doctest/doctest.h"
#include <iostream>
#include <vector>
#include <AudioFile.h>

// --------------------------------------------
// Test audio files: 44.1kHz Stereo
#include "test-headers/aiff_stereo_8bit_44100.h"
#include "test-headers/aiff_stereo_16bit_44100.h"
#include "test-headers/aiff_stereo_24bit_44100.h"
#include "test-headers/aiff_stereo_32bit_44100.h"

// --------------------------------------------
// Test audio files: 48kHz Stereo
#include "test-headers/aiff_stereo_8bit_48000.h"
#include "test-headers/aiff_stereo_16bit_48000.h"
#include "test-headers/aiff_stereo_24bit_48000.h"
#include "test-headers/aiff_stereo_32bit_48000.h"

//=============================================================
const std::string projectBuildDirectory = PROJECT_BINARY_DIR;

//=============================================================
TEST_SUITE ("AiffLoadingTests - Floating Point Types - 8-bit File")
{
    //=============================================================
    TEST_CASE ("AiffLoadingTests_Stereo_8bit_44100")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/aiff_stereo_8bit_44100.aif");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), aiff_stereo_8bit_44100::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), aiff_stereo_8bit_44100::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), aiff_stereo_8bit_44100::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), aiff_stereo_8bit_44100::numChannels);
        
        for (size_t i = 0; i < aiff_stereo_8bit_44100::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (aiff_stereo_8bit_44100::testBuffer[k][i]).epsilon (0.01));
            }
        }
    }
    
    //=============================================================
    TEST_CASE ("AiffLoadingTests_Stereo_8bit_48000")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/aiff_stereo_8bit_48000.aif");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), aiff_stereo_8bit_48000::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), aiff_stereo_8bit_48000::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), aiff_stereo_8bit_48000::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), aiff_stereo_8bit_48000::numChannels);
        
        for (size_t i = 0; i < aiff_stereo_8bit_48000::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (aiff_stereo_8bit_48000::testBuffer[k][i]).epsilon (0.01));
            }
        }
    }
}

//=============================================================
TEST_SUITE ("AiffLoadingTests - Floating Point Types - 16-bit File")
{
    //=============================================================
    TEST_CASE ("AiffLoadingTests_Stereo_16bit_44100")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/aiff_stereo_16bit_44100.aif");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), aiff_stereo_16bit_44100::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), aiff_stereo_16bit_44100::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), aiff_stereo_16bit_44100::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), aiff_stereo_16bit_44100::numChannels);
        
        for (size_t i = 0; i < aiff_stereo_16bit_44100::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (aiff_stereo_16bit_44100::testBuffer[k][i]).epsilon (0.00001));
            }
        }
    }
    
    //=============================================================
    TEST_CASE ("AiffLoadingTests_Stereo_16bit_48000")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/aiff_stereo_16bit_48000.aif");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), aiff_stereo_16bit_48000::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), aiff_stereo_16bit_48000::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), aiff_stereo_16bit_48000::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), aiff_stereo_16bit_48000::numChannels);
        
        for (size_t i = 0; i < aiff_stereo_16bit_48000::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (aiff_stereo_16bit_48000::testBuffer[k][i]).epsilon (0.00001));
            }
        }
    }
}

//=============================================================
TEST_SUITE ("AiffLoadingTests - Floating Point Types - 24-bit File")
{
    //=============================================================
    TEST_CASE ("AiffLoadingTests_Stereo_24bit_44100")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/aiff_stereo_24bit_44100.aif");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), aiff_stereo_24bit_44100::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), aiff_stereo_24bit_44100::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), aiff_stereo_24bit_44100::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), aiff_stereo_24bit_44100::numChannels);
        
        for (size_t i = 0; i < aiff_stereo_24bit_44100::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (aiff_stereo_24bit_44100::testBuffer[k][i]).epsilon (0.00001));
            }
        }
    }
    
    //=============================================================
    TEST_CASE ("AiffLoadingTests_Stereo_24bit_48000")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/aiff_stereo_24bit_48000.aif");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), aiff_stereo_24bit_48000::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), aiff_stereo_24bit_48000::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), aiff_stereo_24bit_48000::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), aiff_stereo_24bit_48000::numChannels);
        
        for (size_t i = 0; i < aiff_stereo_24bit_48000::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (aiff_stereo_24bit_48000::testBuffer[k][i]).epsilon (0.00001));
            }
        }
    }
}

//=============================================================
TEST_SUITE ("AiffLoadingTests - Floating Point Types - 32-bit File")
{
    //=============================================================
    TEST_CASE ("AiffLoadingTests_Stereo_32bit_44100")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/aiff_stereo_32bit_44100.aif");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), aiff_stereo_32bit_44100::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), aiff_stereo_32bit_44100::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), aiff_stereo_32bit_44100::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), aiff_stereo_32bit_44100::numChannels);
        
        for (size_t i = 0; i < aiff_stereo_32bit_44100::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (aiff_stereo_32bit_44100::testBuffer[k][i]).epsilon (0.00001));
            }
        }
    }

    //=============================================================
    TEST_CASE ("AiffLoadingTests_Stereo_32bit_48000")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/aiff_stereo_32bit_48000.aif");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), aiff_stereo_32bit_48000::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), aiff_stereo_32bit_48000::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), aiff_stereo_32bit_48000::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), aiff_stereo_32bit_48000::numChannels);
        
        for (size_t i = 0; i < aiff_stereo_32bit_48000::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (aiff_stereo_32bit_48000::testBuffer[k][i]).epsilon (0.00001));
            }
        }
    }
}

//=============================================================
TEST_SUITE ("AiffLoadingTests - Integer Types - 8-bit File")
{
    //=============================================================
    template <typename T>
    void test8Bit44100WithInteger (bool expectFailure = false)
    {
        AudioFile<T> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/aiff_stereo_8bit_44100.aif");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), aiff_stereo_8bit_44100::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), aiff_stereo_8bit_44100::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), aiff_stereo_8bit_44100::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), aiff_stereo_8bit_44100::numChannels);
        
        int offset = std::is_signed_v<T> ? 0 : 128;
        
        for (size_t i = 0; i < aiff_stereo_8bit_44100::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (aiff_stereo_8bit_44100::testBuffer[k][i] * 127 + offset).epsilon (0.01));
            }
        }
    }
    
    //=============================================================
    TEST_CASE ("AiffLoadingTests_Stereo_8bit_44100_integers")
    {
        test8Bit44100WithInteger<int8_t>();
        test8Bit44100WithInteger<uint8_t>();
        test8Bit44100WithInteger<int16_t>();
        test8Bit44100WithInteger<uint16_t>();
        test8Bit44100WithInteger<int32_t>();
        test8Bit44100WithInteger<uint32_t>();
        test8Bit44100WithInteger<int64_t>();
        test8Bit44100WithInteger<uint64_t>();
    }
}

//=============================================================
TEST_SUITE ("AiffLoadingTests - Integer Types - 16-bit File")
{
    //=============================================================
    template <typename T>
    void test16Bit44100WithInteger (bool expectFailure = false)
    {
        AudioFile<T> audioFile;
        
        if (expectFailure)
            audioFile.shouldLogErrorsToConsole (false);
        
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/aiff_stereo_16bit_44100.aif");
        
        if (expectFailure)
        {
            CHECK_EQ (loadedOK, false);
            return;
        }
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), aiff_stereo_16bit_44100::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), aiff_stereo_16bit_44100::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), aiff_stereo_16bit_44100::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), aiff_stereo_16bit_44100::numChannels);
        
        int offset = std::is_signed_v<T> ? 0 : 32768;
        
        for (size_t i = 0; i < aiff_stereo_16bit_44100::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (aiff_stereo_16bit_44100::testBuffer[k][i] * 32767 + offset).epsilon (0.0001));
            }
        }
    }
    
    //=============================================================
    TEST_CASE ("AiffLoadingTests_Stereo_16bit_44100_integers")
    {
        test16Bit44100WithInteger<uint16_t>();
        test16Bit44100WithInteger<int16_t>();
        test16Bit44100WithInteger<uint32_t>();
        test16Bit44100WithInteger<int32_t>();
        test16Bit44100WithInteger<uint64_t>();
        test16Bit44100WithInteger<int64_t>();
        
        // check these fail...
        test16Bit44100WithInteger<uint8_t> (true);
        test16Bit44100WithInteger<int8_t> (true);
    }
}

//=============================================================
TEST_SUITE ("AiffLoadingTests - Integer Types - 24-bit File")
{
    //=============================================================
    template <typename T>
    void test24Bit44100WithInteger (bool expectFailure = false)
    {
        AudioFile<T> audioFile;
        
        if (expectFailure)
            audioFile.shouldLogErrorsToConsole (false);
        
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/aiff_stereo_24bit_44100.aif");
        
        if (expectFailure)
        {
            REQUIRE_EQ (loadedOK, false);
            return;
        }
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), aiff_stereo_24bit_44100::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), aiff_stereo_24bit_44100::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), aiff_stereo_24bit_44100::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), aiff_stereo_24bit_44100::numChannels);
        
        int offset = std::is_signed_v<T> ? 0 : 8388608;
        
        for (size_t i = 0; i < aiff_stereo_24bit_44100::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (aiff_stereo_24bit_44100::testBuffer[k][i] * 8388607 + offset).epsilon (0.00001));
            }
        }
    }
    
    //=============================================================
    TEST_CASE ("AiffLoadingTests_Stereo_24bit_44100_integers")
    {
        test24Bit44100WithInteger<int32_t>();
        test24Bit44100WithInteger<uint32_t>();
        test24Bit44100WithInteger<int64_t>();
        test24Bit44100WithInteger<uint64_t>();
        
        // check these fail...
        test24Bit44100WithInteger<int8_t> (true);
        test24Bit44100WithInteger<uint8_t> (true);
        test24Bit44100WithInteger<int16_t> (true);
        test24Bit44100WithInteger<uint16_t> (true);
    }
}

//=============================================================
TEST_SUITE ("AiffLoadingTests - Sample Rates")
{
    //=============================================================
    TEST_CASE ("AiffLoadingTests - Sample Rates - Common Sample Rates")
    {
        // Pre-defined 10-byte representations of common sample rates
        std::unordered_map <uint32_t, std::vector<uint8_t>> aiffSampleRateTable = {
            {8000, {64, 11, 250, 0, 0, 0, 0, 0, 0, 0}},
            {11025, {64, 12, 172, 68, 0, 0, 0, 0, 0, 0}},
            {16000, {64, 12, 250, 0, 0, 0, 0, 0, 0, 0}},
            {22050, {64, 13, 172, 68, 0, 0, 0, 0, 0, 0}},
            {32000, {64, 13, 250, 0, 0, 0, 0, 0, 0, 0}},
            {37800, {64, 14, 147, 168, 0, 0, 0, 0, 0, 0}},
            {44056, {64, 14, 172, 24, 0, 0, 0, 0, 0, 0}},
            {44100, {64, 14, 172, 68, 0, 0, 0, 0, 0, 0}},
            {47250, {64, 14, 184, 146, 0, 0, 0, 0, 0, 0}},
            {48000, {64, 14, 187, 128, 0, 0, 0, 0, 0, 0}},
            {50000, {64, 14, 195, 80, 0, 0, 0, 0, 0, 0}},
            {50400, {64, 14, 196, 224, 0, 0, 0, 0, 0, 0}},
            {88200, {64, 15, 172, 68, 0, 0, 0, 0, 0, 0}},
            {96000, {64, 15, 187, 128, 0, 0, 0, 0, 0, 0}},
            {176400, {64, 16, 172, 68, 0, 0, 0, 0, 0, 0}},
            {192000, {64, 16, 187, 128, 0, 0, 0, 0, 0, 0}},
            {352800, {64, 17, 172, 68, 0, 0, 0, 0, 0, 0}},
            {2822400, {64, 20, 172, 68, 0, 0, 0, 0, 0, 0}},
            {5644800, {64, 21, 172, 68, 0, 0, 0, 0, 0, 0}}
        };
            
        std::vector<uint8_t> sampleRateBytes (10);
        
        for (const auto& pair : aiffSampleRateTable)
        {
            uint32_t sampleRate = pair.first;
            double inputSampleRate = sampleRate;
            
            // encode into bytes
            AiffUtilities::encodeAiffSampleRate (static_cast<double> (sampleRate), sampleRateBytes.data());
            
            for (int i = 0; i < 10; i++)
                CHECK_EQ (sampleRateBytes[i], aiffSampleRateTable[sampleRate][i]);
            
            double outputSampleRate = AiffUtilities::decodeAiffSampleRate (aiffSampleRateTable[sampleRate].data());
            
            CHECK_EQ (inputSampleRate, outputSampleRate);
        }
    }
    
    //=============================================================
    TEST_CASE ("AiffLoadingTests - Sample Rates - Round Trip Encode/Decode Tests")
    {
        std::vector<uint8_t> sampleRateBytes (10);
        
        for (int i = -100000; i < 100000; i += 237) // + odd number to reduce cycles but check odd and even values
        {
            double input = static_cast<double> (i);
            AiffUtilities::encodeAiffSampleRate (input, sampleRateBytes.data());
            double output = AiffUtilities::decodeAiffSampleRate (sampleRateBytes.data());
            CHECK_EQ (input, output);
        }
    }
}
