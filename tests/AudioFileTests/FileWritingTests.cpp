#ifndef FILE_WRITING_TESTS
#define FILE_WRITING_TESTS
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>
#include <math.h>

#include "../../AudioFile.h"

//=============================================================
// Writes an audio file with a given number of channels, sample rate, bit deoth and format
// Returns true if it was successful
bool writeTestAudioFile (int numChannels, int sampleRate, int bitDepth, AudioFileFormat format)
{
    float sampleRateAsFloat = (float) sampleRate;
    
    AudioFile<float> audioFile;
    
    audioFile.setAudioBufferSize (numChannels, sampleRate * 4);
    
    for (int i = 0; i < audioFile.getNumSamplesPerChannel(); i++)
    {
        float sample = sinf (2. * M_PI * ((float) i / sampleRateAsFloat) * 440.) ;
        
        for (int k = 0; k < audioFile.getNumChannels(); k++)
            audioFile.samples[k][i] = sample * 0.5;
    }
    
    audioFile.setSampleRate (sampleRate);
    audioFile.setBitDepth (bitDepth);
    
    std::string numChannelsAsString = numChannels == 1 ? "mono" : "stereo";
    std::string bitDepthAsString = std::to_string (bitDepth);
    std::string sampleRateAsString = std::to_string (sampleRate);

    if (format == AudioFileFormat::Wave)
    {
        return audioFile.save ("audio-write-tests/" + numChannelsAsString + "_" + sampleRateAsString + "_" + bitDepthAsString + "bit" + ".wav");
    }
    
    else if (format == AudioFileFormat::Aiff)
    {
        return audioFile.save ("audio-write-tests/" + numChannelsAsString + "_" + sampleRateAsString + "_" + bitDepthAsString + "bit" + ".aif");
    }
    
    return false;
}


//=============================================================
BOOST_AUTO_TEST_SUITE (WritingTests)

//=============================================================
BOOST_AUTO_TEST_CASE (WritingTest_WriteSineToneToManyFormats)
{
    std::vector<int> sampleRates = {22050, 44100, 48000, 96000};
    std::vector<int> bitDepths = {8, 16, 24};
    std::vector<int> numChannels = {1, 2};
    std::vector<AudioFileFormat> audioFormats = {AudioFileFormat::Wave, AudioFileFormat::Aiff};
    
    for (auto& sampleRate : sampleRates)
    {
        for (auto& bitDepth : bitDepths)
        {
            for (auto& channels : numChannels)
            {
                for (auto& format : audioFormats)
                {
                    BOOST_CHECK (writeTestAudioFile (channels, sampleRate, bitDepth, format));
                }
            }
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (WritingTest_WriteFromCopiedSampleBuffer)
{
    AudioFile<float> audioFile1, audioFile2;
    
    bool loadedOK = audioFile1.load ("test-audio/wav_stereo_16bit_44100.wav");
    BOOST_CHECK (loadedOK);
    
    audioFile2.setAudioBuffer (audioFile1.samples);
    audioFile2.save("audio-write-tests/copied_audio_file.aif", AudioFileFormat::Aiff);
}
                      

BOOST_AUTO_TEST_SUITE_END()

#endif
