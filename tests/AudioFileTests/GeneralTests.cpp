#ifndef GENERAL_TESTS
#define GENERAL_TESTS
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>
#include <math.h>

#include "../../AudioFile.h"

//=============================================================
BOOST_AUTO_TEST_SUITE (GeneralTests)

//=============================================================
void checkFilesAreExactlyTheSame (AudioFile<float>* a, AudioFile<float>* b)
{
    BOOST_CHECK (a->getSampleRate() == b->getSampleRate());
    BOOST_CHECK (a->getBitDepth() == b->getBitDepth());
    BOOST_CHECK (a->getNumChannels() == b->getNumChannels());
    BOOST_CHECK (a->getNumSamplesPerChannel() == b->getNumSamplesPerChannel());
    BOOST_CHECK (a->getLengthInSeconds() == b->getLengthInSeconds());
    
    for (size_t channel = 0; channel < a->samples.size(); channel++)
    {
        for (size_t i = 0; i < a->samples.size(); i++)
            BOOST_CHECK_EQUAL (a->samples[channel][i], b->samples[channel][i]);
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (GeneralTests_CopyConstructor)
{
    AudioFile<float> a;
    a.load ("test-audio/aiff_stereo_32bit_48000.aif");

    AudioFile<float> b (a);
    
    checkFilesAreExactlyTheSame (&a, &b);
}

//=============================================================
BOOST_AUTO_TEST_CASE (GeneralTests_CopyAssignmentOperator)
{
    AudioFile<float> a;
    a.load ("test-audio/aiff_stereo_32bit_48000.aif");

    AudioFile<float> b;
    b = a;
    
    checkFilesAreExactlyTheSame (&a, &b);
}

//=============================================================
BOOST_AUTO_TEST_CASE (GeneralTests_MoveAssignmentOperator)
{
    AudioFile<float> a;
    a.load ("test-audio/aiff_stereo_32bit_48000.aif");

    AudioFile<float> b;
    AudioFile<float> c;
    b = a;
    c = std::move (a);
    
    checkFilesAreExactlyTheSame (&b, &c);
}

//=============================================================
BOOST_AUTO_TEST_CASE (GeneralTests_MoveConstructor)
{
    AudioFile<float> a;
    a.load ("test-audio/aiff_stereo_32bit_48000.aif");

    AudioFile<float> b;
    b = a;
    
    AudioFile<float> c (std::move (a));
    
    checkFilesAreExactlyTheSame (&b, &c);
}

//=============================================================
BOOST_AUTO_TEST_CASE (GeneralTests_ConstructFromPath)
{
    std::string filePath = "test-audio/aiff_stereo_32bit_48000.aif";
    
    AudioFile<float> a;
    a.load (filePath);

    AudioFile<float> b (filePath);
        
    checkFilesAreExactlyTheSame (&a, &b);
}

BOOST_AUTO_TEST_SUITE_END()

#endif
