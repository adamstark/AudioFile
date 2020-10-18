#include "doctest.h"
#include <iostream>
#include <vector>
#include <AudioFile.h>

// --------------------------------------------
// Test audio files: 44.1kHz Stereo
#include "test-headers/wav_stereo_8bit_44100.h"
#include "test-headers/wav_stereo_16bit_44100.h"
#include "test-headers/wav_stereo_24bit_44100.h"
#include "test-headers/wav_stereo_32bit_44100.h"

// --------------------------------------------
// Test audio files: 48kHz Stereo
#include "test-headers/wav_stereo_8bit_48000.h"
#include "test-headers/wav_stereo_16bit_48000.h"
#include "test-headers/wav_stereo_24bit_48000.h"
#include "test-headers/wav_stereo_32bit_48000.h"

// --------------------------------------------
// Test audio files: 44.1kHz Mono
//#include "test-headers/wav_mono_8bit_44100.h"
#include "test-headers/wav_mono_16bit_44100.h"

// --------------------------------------------
// Test audio files: 48kHz Mono
//#include "test-headers/wav_mono_8bit_48000.h"
#include "test-headers/wav_mono_16bit_48000.h"

// --------------------------------------------
// Test audio files: 48kHz 8-channel
#include "test-headers/wav_8chan_24bit_48000.h"

//=============================================================
const std::string projectBuildDirectory = PROJECT_BINARY_DIR;

//=============================================================
TEST_SUITE ("WavLoadingTests")
{
    //=============================================================
    TEST_CASE ("WavLoadingTests_Stereo_8bit_44100")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/wav_stereo_8bit_44100.wav");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), wav_stereo_8bit_44100::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), wav_stereo_8bit_44100::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), wav_stereo_8bit_44100::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), static_cast<int> (wav_stereo_8bit_44100::testBuffer.size()));
        
        for (size_t i = 0; i < wav_stereo_8bit_44100::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (wav_stereo_8bit_44100::testBuffer[k][i]).epsilon (0.00001));
            }
        }
    }

    //=============================================================
    TEST_CASE ("WavLoadingTests_Stereo_16bit_44100")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/wav_stereo_16bit_44100.wav");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), wav_stereo_16bit_44100::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), wav_stereo_16bit_44100::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), wav_stereo_16bit_44100::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), static_cast<int> (wav_stereo_16bit_44100::testBuffer.size()));
        
        for (size_t i = 0; i < wav_stereo_16bit_44100::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (wav_stereo_16bit_44100::testBuffer[k][i]).epsilon (0.00001));
            }
        }
    }

    //=============================================================
    TEST_CASE ("WavLoadingTests_Stereo_24bit_44100")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/wav_stereo_24bit_44100.wav");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), wav_stereo_24bit_44100::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), wav_stereo_24bit_44100::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), wav_stereo_24bit_44100::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), static_cast<int> (wav_stereo_24bit_44100::testBuffer.size()));
        
        for (size_t i = 0; i < wav_stereo_24bit_44100::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (wav_stereo_24bit_44100::testBuffer[k][i]).epsilon (0.00001));
            }
        }
    }

    //=============================================================
    TEST_CASE ("WavLoadingTests_Stereo_32bit_44100")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/wav_stereo_32bit_44100.wav");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), wav_stereo_32bit_44100::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), wav_stereo_32bit_44100::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), wav_stereo_32bit_44100::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), static_cast<int> (wav_stereo_32bit_44100::testBuffer.size()));
        
        for (size_t i = 0; i < wav_stereo_32bit_44100::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (wav_stereo_32bit_44100::testBuffer[k][i]).epsilon (0.00001));
            }
        }
    }

    //=============================================================
    TEST_CASE ("WavLoadingTests_Mono_8bit_44100")
    {
        //TODO
    }

    //=============================================================
    TEST_CASE ("WavLoadingTests_Mono_16bit_44100")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/wav_mono_16bit_44100.wav");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), wav_mono_16bit_44100::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), wav_mono_16bit_44100::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), wav_mono_16bit_44100::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), static_cast<int> (wav_mono_16bit_44100::numChannels));
        
        for (size_t i = 0; i < wav_mono_16bit_44100::testBuffer.size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (wav_mono_16bit_44100::testBuffer[i]).epsilon (0.00001));
            }
        }
    }

    //=============================================================
    TEST_CASE ("WavLoadingTests_Mono_24bit_44100")
    {
        //TODO
    }

    //=============================================================
    TEST_CASE ("WavLoadingTests_Stereo_8bit_48000")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/wav_stereo_8bit_48000.wav");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), wav_stereo_8bit_48000::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), wav_stereo_8bit_48000::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), wav_stereo_8bit_48000::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), static_cast<int> (wav_stereo_8bit_48000::testBuffer.size()));
        
        for (size_t i = 0; i < wav_stereo_8bit_48000::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (wav_stereo_8bit_48000::testBuffer[k][i]).epsilon (0.001));
            }
        }
    }

    //=============================================================
    TEST_CASE ("WavLoadingTests_Stereo_16bit_48000")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/wav_stereo_16bit_48000.wav");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), wav_stereo_16bit_48000::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), wav_stereo_16bit_48000::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), wav_stereo_16bit_48000::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), static_cast<int> (wav_stereo_16bit_48000::testBuffer.size()));
        
        for (size_t i = 0; i < wav_stereo_16bit_48000::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (wav_stereo_16bit_48000::testBuffer[k][i]).epsilon (0.001));
            }
        }
    }

    //=============================================================
    TEST_CASE ("WavLoadingTests_Stereo_24bit_48000")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/wav_stereo_24bit_48000.wav");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), wav_stereo_24bit_48000::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), wav_stereo_24bit_48000::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), wav_stereo_24bit_48000::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), static_cast<int> (wav_stereo_24bit_48000::testBuffer.size()));
        
        for (size_t i = 0; i < wav_stereo_24bit_48000::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (wav_stereo_24bit_48000::testBuffer[k][i]).epsilon (0.00001));
            }
        }
    }

    //=============================================================
    TEST_CASE ("WavLoadingTests_Stereo_32bit_48000")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/wav_stereo_32bit_48000.wav");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), wav_stereo_32bit_48000::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), wav_stereo_32bit_48000::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), wav_stereo_32bit_48000::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), static_cast<int> (wav_stereo_32bit_48000::testBuffer.size()));
        
        for (size_t i = 0; i < wav_stereo_32bit_48000::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (wav_stereo_32bit_48000::testBuffer[k][i]).epsilon (0.00001));
            }
        }
    }

    //=============================================================
    TEST_CASE ("WavLoadingTests_Mono_8bit_48000")
    {
        //TODO
    }

    //=============================================================
    TEST_CASE ("WavLoadingTests_Mono_16bit_48000")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/wav_mono_16bit_48000.wav");
        
        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), wav_mono_16bit_48000::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), wav_mono_16bit_48000::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), wav_mono_16bit_48000::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), static_cast<int> (wav_mono_16bit_48000::numChannels));
        
        for (size_t i = 0; i < wav_mono_16bit_48000::testBuffer.size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (wav_mono_16bit_48000::testBuffer[i]).epsilon (0.00001));
            }
        }
    }

    //=============================================================
    TEST_CASE ("WavLoadingTests_Mono_24bit_48000")
    {
        //TODO
    }

    //=============================================================
    TEST_CASE ("WavLoadingTests_8chan_24bit_48000")
    {
        AudioFile<double> audioFile;
        bool loadedOK = audioFile.load (projectBuildDirectory + "/test-audio/wav_8chan_24bit_48000.wav");

        CHECK (loadedOK);
        CHECK_EQ (audioFile.getNumSamplesPerChannel(), wav_8chan_24bit_48000::numSamplesPerChannel);
        CHECK_EQ (audioFile.getBitDepth(), wav_8chan_24bit_48000::bitDepth);
        CHECK_EQ (audioFile.getSampleRate(), wav_8chan_24bit_48000::sampleRate);
        CHECK_EQ (audioFile.getNumChannels(), wav_8chan_24bit_48000::numChannels);

        for (size_t i = 0; i < wav_8chan_24bit_48000::testBuffer[0].size(); i++)
        {
            for (int k = 0; k < audioFile.getNumChannels(); k++)
            {
                CHECK (audioFile.samples[k][i] == doctest::Approx (wav_8chan_24bit_48000::testBuffer[k][i]).epsilon (0.00001));
            }
        }
    }
}
