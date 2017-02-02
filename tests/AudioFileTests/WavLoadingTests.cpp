#ifndef WAV_LOADING_TESTS
#define WAV_LOADING_TESTS
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>

#include "../../AudioFile.h"

// test audio files
#include "test-headers/wav_stereo_8bit_44100.h"
#include "test-headers/wav_stereo_16bit_44100.h"
#include "test-headers/wav_stereo_24bit_44100.h"
#include "test-headers/wav_stereo_8bit_48000.h"
#include "test-headers/wav_stereo_16bit_48000.h"
#include "test-headers/wav_stereo_24bit_48000.h"

//=============================================================
BOOST_AUTO_TEST_SUITE (WavLoadingTests)

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Stereo_16bit_44100)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/wav_stereo_16bit_44100.wav");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), wav_stereo_16bit_44100::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), wav_stereo_16bit_44100::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), wav_stereo_16bit_44100::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), wav_stereo_16bit_44100::testBuffer.size());
    
    const std::vector<std::vector<double>>& audioBuffer = audioFile.getAudioBuffer();
    
    for (int i = 0; i < wav_stereo_16bit_44100::testBuffer[0].size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioBuffer[k][i], wav_stereo_16bit_44100::testBuffer[k][i], 0.00001);
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Stereo_24bit_44100)
{
    /*
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/wav_stereo_24bit_44100.wav");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), wav_stereo_24bit_44100::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), wav_stereo_24bit_44100::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), wav_stereo_24bit_44100::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), wav_stereo_24bit_44100::testBuffer.size());
    
    const std::vector<std::vector<double>>& audioBuffer = audioFile.getAudioBuffer();
    
    for (int i = 0; i < wav_stereo_24bit_44100::testBuffer[0].size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioBuffer[k][i], wav_stereo_24bit_44100::testBuffer[k][i], 0.00001);
        }
    }*/
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Stereo_8bit_44100)
{

}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Mono_16bit_44100)
{
    
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Mono_24bit_44100)
{
    
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Mono_8bit_44100)
{
    
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Stereo_16bit_48000)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/wav_stereo_16bit_48000.wav");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), wav_stereo_16bit_48000::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), wav_stereo_16bit_48000::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), wav_stereo_16bit_48000::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), wav_stereo_16bit_48000::testBuffer.size());
    
    const std::vector<std::vector<double>>& audioBuffer = audioFile.getAudioBuffer();
    
    for (int i = 0; i < wav_stereo_16bit_48000::testBuffer[0].size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioBuffer[k][i], wav_stereo_16bit_48000::testBuffer[k][i], 0.001);
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Stereo_24bit_48000)
{
    /*
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/wav_stereo_24bit_48000.wav");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), wav_stereo_24bit_48000::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), wav_stereo_24bit_48000::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), wav_stereo_24bit_48000::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), wav_stereo_24bit_48000::testBuffer.size());
    
    const std::vector<std::vector<double>>& audioBuffer = audioFile.getAudioBuffer();
    
    for (int i = 0; i < wav_stereo_24bit_48000::testBuffer[0].size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioBuffer[k][i], wav_stereo_24bit_48000::testBuffer[k][i], 0.00001);
        }
    }*/
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Stereo_8bit_48000)
{
    
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Mono_16bit_48000)
{
    
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Mono_24bit_48000)
{
    
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Mono_8bit_48000)
{
    
}



BOOST_AUTO_TEST_SUITE_END()

#endif
