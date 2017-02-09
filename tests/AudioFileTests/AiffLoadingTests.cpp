#ifndef AIFF_LOADING_TESTS
#define AIFF_LOADING_TESTS
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>

#include "../../AudioFile.h"

// --------------------------------------------
// Test audio files: 44.1kHz Stereo
//#include "test-headers/test123.h"

//=============================================================
BOOST_AUTO_TEST_SUITE (AiffLoadingTests)

//=============================================================
BOOST_AUTO_TEST_CASE (AiffLoadingTests_Mono_24bit_44100)
{
    /*
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/test123.aif");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), test123::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), test123::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), test123::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), test123::numChannels);
    
    for (int i = 0; i < test123::testBuffer.size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioFile.samples[k][i], test123::testBuffer[i], 0.00001);
        }
    }*/
}

BOOST_AUTO_TEST_SUITE_END()

#endif
