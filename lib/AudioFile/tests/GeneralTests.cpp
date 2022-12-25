#include "doctest.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <AudioFile.h>

//=============================================================
TEST_SUITE ("General Tests")
{
    //=============================================================
    const std::string projectBuildDirectory = PROJECT_BINARY_DIR;

    //=============================================================
    void checkFilesAreExactlyTheSame (AudioFile<float>& a, AudioFile<float>& b)
    {
        CHECK (a.getSampleRate() == b.getSampleRate());
        CHECK (a.getBitDepth() == b.getBitDepth());
        CHECK (a.getNumChannels() == b.getNumChannels());
        CHECK (a.getNumSamplesPerChannel() == b.getNumSamplesPerChannel());
        CHECK (a.getLengthInSeconds() == b.getLengthInSeconds());
        
        size_t numSamplesToTest = std::min (static_cast<size_t> (20000), a.samples[0].size());
        
        for (size_t channel = 0; channel < a.samples.size(); channel++)
        {
            for (size_t i = 0; i < numSamplesToTest; i++)
            {
                CHECK_EQ (a.samples[channel][i], b.samples[channel][i]);
            }
        }
    }

    //=============================================================
    TEST_CASE ("GeneralTests::CopyConstructor")
    {
        AudioFile<float> a;
        a.load (projectBuildDirectory + "/test-audio/aiff_stereo_16bit_44100.aif");

        AudioFile<float> b (a);
        
        checkFilesAreExactlyTheSame (a, b);
    }

    //=============================================================
    TEST_CASE ("GeneralTests::CopyAssignmentOperator")
    {
        AudioFile<float> a;
        a.load (projectBuildDirectory + "/test-audio/aiff_stereo_16bit_44100.aif");

        AudioFile<float> b;
        b = a;
        
        checkFilesAreExactlyTheSame (a, b);
    }

    //=============================================================
    TEST_CASE ("GeneralTests::MoveAssignmentOperator")
    {
        AudioFile<float> a;
        a.load (projectBuildDirectory + "/test-audio/aiff_stereo_16bit_44100.aif");

        AudioFile<float> b;
        AudioFile<float> c;
        b = a;
        c = std::move (a);
        
        checkFilesAreExactlyTheSame (b, c);
    }

    //=============================================================
    TEST_CASE ("GeneralTests::MoveConstructor")
    {
        AudioFile<float> a;
        a.load (projectBuildDirectory + "/test-audio/aiff_stereo_16bit_44100.aif");

        AudioFile<float> b;
        b = a;
        
        AudioFile<float> c (std::move (a));
        
        checkFilesAreExactlyTheSame (b, c);
    }

    //=============================================================
    TEST_CASE ("GeneralTests::ConstructFromPath")
    {
        std::string filePath = projectBuildDirectory + "/test-audio/aiff_stereo_16bit_44100.aif";
        
        AudioFile<float> a;
        a.load (filePath);

        AudioFile<float> b (filePath);
            
        checkFilesAreExactlyTheSame (a, b);
    }
}
