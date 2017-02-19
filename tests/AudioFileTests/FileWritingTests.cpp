#ifndef FILE_WRITING_TESTS
#define FILE_WRITING_TESTS
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>
#include <math.h>

#include "../../AudioFile.h"

//=============================================================
BOOST_AUTO_TEST_SUITE (WritingTests)

//=============================================================
BOOST_AUTO_TEST_CASE (WritingTest1)
{
    AudioFile<float> audioFile;
    
    audioFile.setAudioBufferSize (2, 44100 * 4);
    
    for (int i = 0;i < audioFile.getNumSamplesPerChannel(); i++)
    {
        float sample = sinf (2. * M_PI * (float) i / 44100. * 440.);
        
        audioFile.samples[0][i] = sample * 0.5;
        audioFile.samples[1][i] = sample * 0.5;
    }
    
    audioFile.setBitDepth (16);
    
    BOOST_CHECK (audioFile.save ("audio-write-tests/test1.wav"));
    BOOST_CHECK (audioFile.save ("audio-write-tests/test1.aif"));
}

BOOST_AUTO_TEST_SUITE_END()

#endif
