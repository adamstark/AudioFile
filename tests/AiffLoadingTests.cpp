#include "doctest.h"
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
