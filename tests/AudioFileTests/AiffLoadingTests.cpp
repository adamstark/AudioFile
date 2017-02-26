#ifndef AIFF_LOADING_TESTS
#define AIFF_LOADING_TESTS
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>

#include "../../AudioFile.h"

// --------------------------------------------
// Test audio files: 44.1kHz Stereo
#include "test-headers/aiff_stereo_8bit_44100.h"
#include "test-headers/aiff_stereo_16bit_44100.h"
#include "test-headers/aiff_stereo_24bit_44100.h"

// --------------------------------------------
// Test audio files: 48kHz Stereo
#include "test-headers/aiff_stereo_8bit_48000.h"
#include "test-headers/aiff_stereo_16bit_48000.h"
#include "test-headers/aiff_stereo_24bit_48000.h"

//=============================================================
BOOST_AUTO_TEST_SUITE (AiffLoadingTests)

//=============================================================
BOOST_AUTO_TEST_CASE (AiffLoadingTests_Stereo_8bit_44100)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/aiff_stereo_8bit_44100.aif");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), aiff_stereo_8bit_44100::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), aiff_stereo_8bit_44100::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), aiff_stereo_8bit_44100::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), aiff_stereo_8bit_44100::numChannels);
    
    for (int i = 0; i < aiff_stereo_8bit_44100::testBuffer.size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioFile.samples[k][i], aiff_stereo_8bit_44100::testBuffer[k][i], 0.00001);
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (AiffLoadingTests_Stereo_16bit_44100)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/aiff_stereo_16bit_44100.aif");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), aiff_stereo_16bit_44100::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), aiff_stereo_16bit_44100::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), aiff_stereo_16bit_44100::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), aiff_stereo_16bit_44100::numChannels);
    
    for (int i = 0; i < aiff_stereo_16bit_44100::testBuffer.size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioFile.samples[k][i], aiff_stereo_16bit_44100::testBuffer[k][i], 0.00001);
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (AiffLoadingTests_Stereo_24bit_44100)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/aiff_stereo_24bit_44100.aif");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), aiff_stereo_24bit_44100::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), aiff_stereo_24bit_44100::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), aiff_stereo_24bit_44100::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), aiff_stereo_24bit_44100::numChannels);
    
    for (int i = 0; i < aiff_stereo_24bit_44100::testBuffer.size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioFile.samples[k][i], aiff_stereo_24bit_44100::testBuffer[k][i], 0.00001);
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (AiffLoadingTests_Stereo_8bit_48000)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/aiff_stereo_8bit_48000.aif");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), aiff_stereo_8bit_48000::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), aiff_stereo_8bit_48000::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), aiff_stereo_8bit_48000::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), aiff_stereo_8bit_48000::numChannels);
    
    for (int i = 0; i < aiff_stereo_8bit_48000::testBuffer.size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioFile.samples[k][i], aiff_stereo_8bit_48000::testBuffer[k][i], 0.00001);
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (AiffLoadingTests_Stereo_16bit_48000)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/aiff_stereo_16bit_48000.aif");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), aiff_stereo_16bit_48000::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), aiff_stereo_16bit_48000::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), aiff_stereo_16bit_48000::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), aiff_stereo_16bit_48000::numChannels);
    
    for (int i = 0; i < aiff_stereo_16bit_48000::testBuffer.size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioFile.samples[k][i], aiff_stereo_16bit_48000::testBuffer[k][i], 0.00001);
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (AiffLoadingTests_Stereo_24bit_48000)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/aiff_stereo_24bit_48000.aif");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), aiff_stereo_24bit_48000::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), aiff_stereo_24bit_48000::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), aiff_stereo_24bit_48000::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), aiff_stereo_24bit_48000::numChannels);
    
    for (int i = 0; i < aiff_stereo_24bit_48000::testBuffer.size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioFile.samples[k][i], aiff_stereo_24bit_48000::testBuffer[k][i], 0.00001);
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()

#endif
