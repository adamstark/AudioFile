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
void writeTestAudioFile (int numChannels, int sampleRate, int bitDepth, AudioFileFormat format)
{
    std::string sampleType;
    float sampleRateAsFloat = (float) sampleRate;
    
    AudioFile<T> audioFileWriter;
    
    audioFileWriter.setAudioBufferSize (numChannels, sampleRate * 4);
    
    // In the case of an integer representation, this value will be
    T maxValue;
    
    if constexpr (std::is_floating_point<T>::value)
    {
        maxValue = 1;
        sampleType = "floating_point";
    }
    else if constexpr (std::numeric_limits<T>::is_integer)
    {
        if constexpr (std::is_signed_v<T>)
        {
            sampleType = "integer (signed, " + std::to_string (sizeof (T) * 8) + "-bit)";
            maxValue = pow (2, bitDepth - 1) - 1;
        }
        else
        {
            sampleType = "integer (unsigned, " + std::to_string (sizeof (T) * 8) + "-bit)";
            maxValue = pow (2, bitDepth) - 1;
        }
    }

    for (int i = 0; i < audioFileWriter.getNumSamplesPerChannel(); i++)
    {
        T sample;
        
        if constexpr (std::numeric_limits<T>::is_integer && std::is_unsigned_v<T>)
            sample = (T)(((sinf (2. * M_PI * ((double) i / sampleRateAsFloat) * 440.) + 1.) / 2.) * maxValue);
        else
            sample = (T)(sinf (2. * M_PI * ((double) i / sampleRateAsFloat) * 440.) * maxValue);
        
        for (int k = 0; k < audioFileWriter.getNumChannels(); k++)
            audioFileWriter.samples[k][i] = sample * 0.5f;
    }
    
    audioFileWriter.setSampleRate (sampleRate);
    audioFileWriter.setBitDepth (bitDepth);

    std::string numChannelsAsString;
    if (numChannels == 1)
        numChannelsAsString = "mono";
    else if (numChannels == 2)
        numChannelsAsString = "stereo";
    else
        numChannelsAsString = std::to_string (numChannels) + " channels";

    std::string bitDepthAsString = std::to_string (bitDepth);
    std::string sampleRateAsString = std::to_string (sampleRate);

    std::string filePath;
    
    if (format == AudioFileFormat::Wave)
    {
        filePath = projectBuildDirectory + "/audio-write-tests/" + sampleType + "_" + numChannelsAsString + "_" + sampleRateAsString + "_" + bitDepthAsString + "bit" + ".wav";
    }
    else if (format == AudioFileFormat::Aiff)
    {
        filePath = projectBuildDirectory + "/audio-write-tests/" + sampleType + "_" + numChannelsAsString + "_" + sampleRateAsString + "_" + bitDepthAsString + "bit" + ".aif";
        
    }
    
    bool OK = audioFileWriter.save (filePath, format);
    REQUIRE (OK);
    
    //-----------------------------------------------------------------
    // for some key bit depths and mono/stereo files, read in the audio file
    // we just wrote and do a sample-by-sample comparison to confirm we are
    // writing good files
    if ((bitDepth == 8 || bitDepth == 16 || bitDepth == 24) &&  numChannels <= 2)
    {
        AudioFile<T> audioFileReader;
        audioFileReader.load (filePath);
        
        // confirm num channels
        CHECK (audioFileReader.getNumChannels() == audioFileWriter.getNumChannels());
        
        // confirm bit depth
        CHECK (audioFileReader.getBitDepth() == audioFileWriter.getBitDepth());
        
        // confirm sample rate
        CHECK (audioFileReader.getSampleRate() == audioFileWriter.getSampleRate());
        
        // confirm the number of samples per channel
        CHECK (audioFileReader.getNumSamplesPerChannel() == audioFileWriter.getNumSamplesPerChannel());
        
        for (size_t i = 0; i < 5000; i++)
        {
            for (int k = 0; k < audioFileReader.getNumChannels(); k++)
            {
                // NOTE: We can expect audio files we read back in to differ a small amount from the original due to small rounding errors
                REQUIRE (audioFileReader.samples[k][i] == doctest::Approx (audioFileWriter.samples[k][i]).epsilon (0.01));
            }
        }
    }
}

//=============================================================
TEST_SUITE ("Writing Tests")
{
    //=============================================================
    TEST_CASE ("WritingTest::WriteSineToneToManyFormats::FloatingPoint")
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
                        std::cerr << sampleRate << "Hz " << bitDepth << "-bit " << channels << " " << fmt_str << " (floating point)" << std::endl;
                        writeTestAudioFile<float> (channels, sampleRate, bitDepth, format);
                    }
                }
            }
        }
    }

    //=============================================================
    TEST_CASE ("WritingTest::WriteSineToneToManyFormats::Integer")
    {
        std::vector<int> sampleRates = {22050, 44100, 48000, 96000};
        std::vector<int> bitDepths = {8, 16, 24, 32};
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
                        auto fmt_str = format == AudioFileFormat::Wave ? "wav" : "aiff";
                        std::cerr << sampleRate << "Hz " << bitDepth << "-bit " << channels << " " << fmt_str << " (integer)" << std::endl;
                        
                        if (bitDepth == 8)
                            writeTestAudioFile<uint8_t> (channels, sampleRate, bitDepth, format);
                        else if (bitDepth == 16)
                            writeTestAudioFile<int16_t> (channels, sampleRate, bitDepth, format);
                        else if (bitDepth == 24)
                            writeTestAudioFile<int32_t> (channels, sampleRate, bitDepth, format);
                        else if (bitDepth == 32)
                            writeTestAudioFile<int32_t> (channels, sampleRate, bitDepth, format);
                    }
                }
            }
        }
    }

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
