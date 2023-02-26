#include "doctest.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <AudioFile.h>

//=============================================================
const std::string projectBuildDirectory = PROJECT_BINARY_DIR;

//=============================================================
// Writes an audio file with a given number of channels, sample rate, bit depth and format
// Returns true if it was successful
template <typename T>
bool writeTestAudioFile (int numChannels, int sampleRate, int bitDepth, AudioFileFormat format)
{
    float sampleRateAsFloat = (float) sampleRate;
    
    AudioFile<T> audioFile;
    
    audioFile.setAudioBufferSize (numChannels, sampleRate * 4);
    
    // In the case of an integer representation, this value will be
    T maxValue;
    if (std::is_floating_point<T>::value)
    {
        maxValue = 1;
    }
    else if (std::numeric_limits<T>::is_integer)
    {
        // compute the maximum positive value of T as some signed
        // integer type.
        maxValue = (T)~(1 << (sizeof(T) * 8 - 1));
    }

    for (int i = 0; i < audioFile.getNumSamplesPerChannel(); i++)
    {
        T sample = (T)(sinf (2. * M_PI * ((float) i / sampleRateAsFloat) * 440.) * maxValue);
        
        for (int k = 0; k < audioFile.getNumChannels(); k++)
            audioFile.samples[k][i] = sample * 0.5f;
    }
    
    audioFile.setSampleRate (sampleRate);
    audioFile.setBitDepth (bitDepth);

    std::string numChannelsAsString;
    if (numChannels == 1)
        numChannelsAsString = "mono";
    else if (numChannels == 2)
        numChannelsAsString = "stereo";
    else
        numChannelsAsString = std::to_string (numChannels) + " channels";

    std::string bitDepthAsString = std::to_string (bitDepth);
    std::string sampleRateAsString = std::to_string (sampleRate);

    if (format == AudioFileFormat::Wave)
    {
        return audioFile.save (projectBuildDirectory + "/audio-write-tests/" + numChannelsAsString + "_" + sampleRateAsString + "_" + bitDepthAsString + "bit" + ".wav", format);
    }
    
    else if (format == AudioFileFormat::Aiff)
    {
        return audioFile.save (projectBuildDirectory + "/audio-write-tests/" + numChannelsAsString + "_" + sampleRateAsString + "_" + bitDepthAsString + "bit" + ".aif", format);
    }
    
    return false;
}


//=============================================================
TEST_SUITE ("Writing Tests")
{
    
#if PEFORM_TEST_WRITE_TO_ALL_FORMATS
    //=============================================================
    TEST_CASE ("WritingTest::WriteSineToneToManyFormats")
    {
        std::vector<int> sampleRates = {22050, 44100, 48000, 96000};
        std::vector<int> bitDepths = {8, 16, 24, 32};
        std::vector<int> numChannels = {1, 2, 8};
        std::vector<AudioFileFormat> audioFormats = {AudioFileFormat::Wave, AudioFileFormat::Aiff};
        
        for (auto& sampleRate : sampleRates)
        {
            for (auto& bitDepth : bitDepths)
            {
                for (auto& channels : numChannels)
                {
                    for (auto& format : audioFormats)
                    {
                        auto fmt_str = format == AudioFileFormat::Wave ? "wav" : "aiff";
                        std::cerr << sampleRate << " " << bitDepth << " " << channels << " " << fmt_str << std::endl;
                        CHECK (writeTestAudioFile<float> (channels, sampleRate, bitDepth, format));
                    }
                }
            }
        }
    }

    //=============================================================
    TEST_CASE ("WritingTest::WriteSineToneToManyFormats_Integer")
    {
        std::vector<int> sampleRates = {22050, 44100, 48000, 96000};
        std::vector<int> bitDepths = {8, 16, 24, 32};
        std::vector<int> numChannels = {1, 2, 8};
        std::vector<AudioFileFormat> audioFormats = {AudioFileFormat::Wave, AudioFileFormat::Aiff};
        
        for (auto& sampleRate : sampleRates)
        {
            for (auto& bitDepth : bitDepths)
            {
                for (auto& channels : numChannels)
                {
                    for (auto& format : audioFormats)
                    {
                        CHECK (writeTestAudioFile<int16_t> (channels, sampleRate, bitDepth, format));
                    }
                }
            }
        }
    }
#endif

    //=============================================================
    TEST_CASE ("WritingTest::WriteFromCopiedSampleBuffer")
    {
        AudioFile<float> audioFile1, audioFile2;
        
        bool loadedOK = audioFile1.load (projectBuildDirectory + "/test-audio/wav_stereo_16bit_44100.wav");
        CHECK (loadedOK);
        
        audioFile2.setAudioBuffer (audioFile1.samples);
        bool savedOK = audioFile2.save (projectBuildDirectory + "/audio-write-tests/copied_audio_file.aif", AudioFileFormat::Aiff);
        CHECK (savedOK);
    }
}
