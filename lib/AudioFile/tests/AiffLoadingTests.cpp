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
TEST_SUITE ("AiffLoadingTests")
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
                CHECK (audioFile.samples[k][i] == doctest::Approx (aiff_stereo_8bit_44100::testBuffer[k][i]).epsilon (0.00001));
            }
        }
    }

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
                CHECK (audioFile.samples[k][i] == doctest::Approx (aiff_stereo_8bit_48000::testBuffer[k][i]).epsilon (0.00001));
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
