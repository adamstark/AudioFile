//=======================================================================
/** @file AudioFile.h
 *  @author Adam Stark
 *  @copyright Copyright (C) 2017  Adam Stark
 *
 * This file is part of the 'AudioFile' library
 *
 * MIT License
 *
 * Copyright (c) 2017 Adam Stark
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal 
 * in the Software without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
 * of the Software, and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
//=======================================================================

#ifndef _AS_AudioFile_h
#define _AS_AudioFile_h

#if defined (_MSC_VER)
#undef max
#undef min
#define NOMINMAX
#endif

#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <cstring>
#include <fstream>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <limits>
#include <cstdint>
#include <cmath>
#include <array>

// disable some warnings on Windows
#if defined (_MSC_VER)
    __pragma(warning (push))
    __pragma(warning (disable : 4244))
    __pragma(warning (disable : 4457))
    __pragma(warning (disable : 4458))
    __pragma(warning (disable : 4389))
    __pragma(warning (disable : 4996))
#elif defined (__GNUC__)
    _Pragma("GCC diagnostic push")
    _Pragma("GCC diagnostic ignored \"-Wconversion\"")
    _Pragma("GCC diagnostic ignored \"-Wsign-compare\"")
    _Pragma("GCC diagnostic ignored \"-Wshadow\"")
#endif

//=============================================================
/** The different types of audio file, plus some other types to 
 * indicate a failure to load a file, or that one hasn't been
 * loaded yet
 */
enum class AudioFileFormat
{
    Error,
    NotLoaded,
    Wave,
    Aiff
};

//=============================================================
template <class T>
class AudioFile
{
public:
    
    //=============================================================
    typedef std::vector<std::vector<T> > AudioBuffer;
    
    //=============================================================
    /** Constructor */
    AudioFile();
    
    /** Constructor, using a given file path to load a file */
    AudioFile (const std::string& filePath);
        
    //=============================================================
    /** Loads an audio file from a given file path.
     * @Returns true if the file was successfully loaded
     */
    bool load (const std::string& filePath);
    
    /** Saves an audio file to a given file path.
     * @Returns true if the file was successfully saved
     */
    bool save (const std::string& filePath, AudioFileFormat format = AudioFileFormat::Wave);
        
    //=============================================================
    /** Loads an audio file from data in memory */
    bool loadFromMemory (const std::vector<uint8_t>& fileData);

    //=============================================================
    /** Saves an audio file to data in memory */
    bool saveToMemory (std::vector<uint8_t>& fileData, AudioFileFormat format = AudioFileFormat::Wave);

    //=============================================================
    /** @Returns the sample rate */
    uint32_t getSampleRate() const;
    
    /** @Returns the number of audio channels in the buffer */
    int getNumChannels() const;

    /** @Returns true if the audio file is mono */
    bool isMono() const;
    
    /** @Returns true if the audio file is stereo */
    bool isStereo() const;
    
    /** @Returns the bit depth of each sample */
    int getBitDepth() const;
    
    /** @Returns the number of samples per channel */
    int getNumSamplesPerChannel() const;
    
    /** @Returns the length in seconds of the audio file based on the number of samples and sample rate */
    double getLengthInSeconds() const;
    
    /** Prints a summary of the audio file to the console */
    void printSummary() const;
    
    //=============================================================
    
    /** Set the audio buffer for this AudioFile by copying samples from another buffer.
     * @Returns true if the buffer was copied successfully.
     */
    bool setAudioBuffer (const AudioBuffer& newBuffer);
    
    /** Sets the audio buffer to a given number of channels and number of samples per channel. This will try to preserve
     * the existing audio, adding zeros to any new channels or new samples in a given channel.
     */
    void setAudioBufferSize (const int numChannels, const int numSamples);
    
    /** Sets the number of samples per channel in the audio buffer. This will try to preserve
     * the existing audio, adding zeros to new samples in a given channel if the number of samples is increased.
     */
    void setNumSamplesPerChannel (const int numSamples);
    
    /** Sets the number of channels. New channels will have the correct number of samples and be initialised to zero */
    void setNumChannels (const int numChannels);
    
    /** Sets the bit depth for the audio file. If you use the save() function, this bit depth rate will be used */
    void setBitDepth (const int numBitsPerSample);
    
    /** Sets the sample rate for the audio file. If you use the save() function, this sample rate will be used */
    void setSampleRate (const uint32_t newSampleRate);
    
    //=============================================================
    /** Sets whether the library should log error messages to the console. By default this is true */
    void shouldLogErrorsToConsole (bool logErrors);
    
    //=============================================================
    /** A vector of vectors holding the audio samples for the AudioFile. You can 
     * access the samples by channel and then by sample index, i.e:
     *
     *      samples[channel][sampleIndex]
     */
    AudioBuffer samples;
    
    //=============================================================
    /** An optional iXML chunk that can be added to the AudioFile. 
     */
    std::string iXMLChunk;
    
private:
    
    //=============================================================
    enum class Endianness
    {
        LittleEndian,
        BigEndian
    };
    
    //=============================================================
    bool decodeWaveFile (const std::vector<uint8_t>& fileData);
    bool decodeAiffFile (const std::vector<uint8_t>& fileData);

    //=============================================================
    bool encodeWaveFile (std::vector<uint8_t>& fileData);
    bool encodeAiffFile (std::vector<uint8_t>& fileData);
    
    //=============================================================
    void clearAudioBuffer();
    
    //=============================================================
    static inline AudioFileFormat determineAudioFileFormat (const std::vector<uint8_t>& fileData);

    static inline int32_t fourBytesToInt (const std::vector<uint8_t>& source, int startIndex, Endianness endianness = Endianness::LittleEndian);
    static inline int16_t twoBytesToInt (const std::vector<uint8_t>& source, int startIndex, Endianness endianness = Endianness::LittleEndian);
    static inline int getIndexOfString (const std::vector<uint8_t>& source, std::string s);
    static inline int getIndexOfChunk (const std::vector<uint8_t>& source, const std::string& chunkHeaderID, int startIndex, Endianness endianness = Endianness::LittleEndian);

    //=============================================================
    static inline uint32_t getAiffSampleRate (const std::vector<uint8_t>& fileData, int sampleRateStartIndex);
    static inline void addSampleRateToAiffData (std::vector<uint8_t>& fileData, uint32_t sampleRate);
    
    //=============================================================
    static inline void addStringToFileData (std::vector<uint8_t>& fileData, std::string s);
    static inline void addInt32ToFileData (std::vector<uint8_t>& fileData, int32_t i, Endianness endianness = Endianness::LittleEndian);
    static inline void addInt16ToFileData (std::vector<uint8_t>& fileData, int16_t i, Endianness endianness = Endianness::LittleEndian);
    
    //=============================================================
    static inline bool writeDataToFile (const std::vector<uint8_t>& fileData, std::string filePath);
    
    //=============================================================
    void reportError (const std::string& errorMessage);
    
    //=============================================================
    AudioFileFormat audioFileFormat;
    uint32_t sampleRate;
    int bitDepth;
    bool logErrorsToConsole {true};
};

//=============================================================
template <typename T>
struct AudioSampleConverter
{
    //=============================================================
    /** Convert a signed 8-bit integer to an audio sample */
    static T signedByteToSample (int8_t sample);
    
    /** Convert an audio sample to an signed 8-bit representation */
    static int8_t sampleToSignedByte (T sample);
    
    //=============================================================
    /** Convert an unsigned 8-bit integer to an audio sample */
    static T unsignedByteToSample (uint8_t sample);
    
    /** Convert an audio sample to an unsigned 8-bit representation */
    static uint8_t sampleToUnsignedByte (T sample);
    
    //=============================================================
    /** Convert a 16-bit integer to an audio sample */
    static T sixteenBitIntToSample (int16_t sample);
    
    /** Convert a an audio sample to a 16-bit integer */
    static int16_t sampleToSixteenBitInt (T sample);
    
    //=============================================================
    /** Convert a 24-bit value (int a 32-bit int) to an audio sample */
    static T twentyFourBitIntToSample (int32_t sample);
    
    /** Convert a an audio sample to a 24-bit value (in a 32-bit integer) */
    static int32_t sampleToTwentyFourBitInt (T sample);
    
    //=============================================================
    /** Convert a 32-bit signed integer to an audio sample */
    static T thirtyTwoBitIntToSample (int32_t sample);
    
    /** Convert a an audio sample to a 32-bit signed integer */
    static int32_t sampleToThirtyTwoBitInt (T sample);
    
    //=============================================================
    /** Helper clamp function to enforce ranges */
    static T clamp (T v1, T minValue, T maxValue);
};

//=============================================================
struct AiffUtilities
{
    //=============================================================
    /** Decode an 80-bit (10 byte) sample rate to a double */
    static inline double decodeAiffSampleRate (const uint8_t* bytes);
    
    /** Encode a double as an 80-bit (10-byte) sample rate */
    static inline void encodeAiffSampleRate (double sampleRate, uint8_t* bytes);
};

//=============================================================
enum WavAudioFormat
{
    PCM = 0x0001,
    IEEEFloat = 0x0003,
    ALaw = 0x0006,
    MULaw = 0x0007,
    Extensible = 0xFFFE
};

//=============================================================
enum AIFFAudioFormat
{
    Uncompressed,
    Compressed,
    Error
};

//=============================================================
/* IMPLEMENTATION */
//=============================================================

//=============================================================
template <class T>
AudioFile<T>::AudioFile()
{
    bitDepth = 16;
    sampleRate = 44100;
    samples.resize (1);
    samples[0].resize (0);
    audioFileFormat = AudioFileFormat::NotLoaded;
}

//=============================================================
template <class T>
AudioFile<T>::AudioFile (const std::string& filePath)
 :  AudioFile<T>()
{
    load (filePath);
}

//=============================================================
template <class T>
uint32_t AudioFile<T>::getSampleRate() const
{
    return sampleRate;
}

//=============================================================
template <class T>
int AudioFile<T>::getNumChannels() const
{
    return (int)samples.size();
}

//=============================================================
template <class T>
bool AudioFile<T>::isMono() const
{
    return getNumChannels() == 1;
}

//=============================================================
template <class T>
bool AudioFile<T>::isStereo() const
{
    return getNumChannels() == 2;
}

//=============================================================
template <class T>
int AudioFile<T>::getBitDepth() const
{
    return bitDepth;
}

//=============================================================
template <class T>
int AudioFile<T>::getNumSamplesPerChannel() const
{
    if (samples.size() > 0)
        return (int) samples[0].size();
    else
        return 0;
}

//=============================================================
template <class T>
double AudioFile<T>::getLengthInSeconds() const
{
    return (double)getNumSamplesPerChannel() / (double)sampleRate;
}

//=============================================================
template <class T>
void AudioFile<T>::printSummary() const
{
    std::cerr << "|======================================|" << std::endl;
    std::cerr << "Num Channels: " << getNumChannels() << std::endl;
    std::cerr << "Num Samples Per Channel: " << getNumSamplesPerChannel() << std::endl;
    std::cerr << "Sample Rate: " << sampleRate << std::endl;
    std::cerr << "Bit Depth: " << bitDepth << std::endl;
    std::cerr << "Length in Seconds: " << getLengthInSeconds() << std::endl;
    std::cerr << "|======================================|" << std::endl;
}

//=============================================================
template <class T>
bool AudioFile<T>::setAudioBuffer (const AudioBuffer& newBuffer)
{
    int numChannels = (int)newBuffer.size();
    
    if (numChannels <= 0)
    {
        assert (false && "The buffer you are trying to use has no channels");
        return false;
    }
    
    size_t numSamples = newBuffer[0].size();
    
    // set the number of channels
    samples.resize (newBuffer.size());
    
    for (int k = 0; k < getNumChannels(); k++)
    {
        assert (newBuffer[k].size() == numSamples);
        
        samples[k].resize (numSamples);
        
        for (size_t i = 0; i < numSamples; i++)
        {
            samples[k][i] = newBuffer[k][i];
        }
    }
    
    return true;
}

//=============================================================
template <class T>
void AudioFile<T>::setAudioBufferSize (int numChannels, int numSamples)
{
    samples.resize (numChannels);
    setNumSamplesPerChannel (numSamples);
}

//=============================================================
template <class T>
void AudioFile<T>::setNumSamplesPerChannel (int numSamples)
{
    int originalSize = getNumSamplesPerChannel();
    
    for (int i = 0; i < getNumChannels();i++)
    {
        samples[i].resize (numSamples);
        
        // set any new samples to zero
        if (numSamples > originalSize)
            std::fill (samples[i].begin() + originalSize, samples[i].end(), (T)0.);
    }
}

//=============================================================
template <class T>
void AudioFile<T>::setNumChannels (int numChannels)
{
    int originalNumChannels = getNumChannels();
    int originalNumSamplesPerChannel = getNumSamplesPerChannel();
    
    samples.resize (numChannels);
    
    // make sure any new channels are set to the right size
    // and filled with zeros
    if (numChannels > originalNumChannels)
    {
        for (int i = originalNumChannels; i < numChannels; i++)
        {
            samples[i].resize (originalNumSamplesPerChannel);
            std::fill (samples[i].begin(), samples[i].end(), (T)0.);
        }
    }
}

//=============================================================
template <class T>
void AudioFile<T>::setBitDepth (int numBitsPerSample)
{
    bitDepth = numBitsPerSample;
}

//=============================================================
template <class T>
void AudioFile<T>::setSampleRate (uint32_t newSampleRate)
{
    sampleRate = newSampleRate;
}

//=============================================================
template <class T>
void AudioFile<T>::shouldLogErrorsToConsole (bool logErrors)
{
    logErrorsToConsole = logErrors;
}

//=============================================================
template <class T>
bool AudioFile<T>::load (const std::string& filePath)
{
    std::ifstream file (filePath, std::ios::binary);
    
    // check the file exists
    if (! file.good())
    {
        reportError ("ERROR: File doesn't exist or otherwise can't load file\n"  + filePath);
        return false;
    }
    
    std::vector<uint8_t> fileData;

	file.unsetf (std::ios::skipws);

	file.seekg (0, std::ios::end);
	size_t length = file.tellg();
	file.seekg (0, std::ios::beg);

	// allocate
	fileData.resize (length);

	file.read(reinterpret_cast<char*> (fileData.data()), length);
	file.close();

	if (file.gcount() != length)
	{
		reportError ("ERROR: Couldn't read entire file\n" + filePath);
		return false;
	}
    
    // Handle very small files that will break our attempt to read the
    // first header info from them
    if (fileData.size() < 12)
    {
        reportError ("ERROR: File is not a valid audio file\n" + filePath);
        return false;
    }
    else
    {
        return loadFromMemory (fileData);
    }
}

//=============================================================
template <class T>
bool AudioFile<T>::loadFromMemory (const std::vector<uint8_t>& fileData)
{
    // get audio file format
    audioFileFormat = determineAudioFileFormat (fileData);
    
    if (audioFileFormat == AudioFileFormat::Wave)
    {
        return decodeWaveFile (fileData);
    }
    else if (audioFileFormat == AudioFileFormat::Aiff)
    {
        return decodeAiffFile (fileData);
    }
    else
    {
        reportError ("Audio File Type: Error");
        return false;
    }
}

//=============================================================
template <class T>
bool AudioFile<T>::decodeWaveFile (const std::vector<uint8_t>& fileData)
{
    // -----------------------------------------------------------
    // HEADER CHUNK
    std::string headerChunkID (fileData.begin(), fileData.begin() + 4);
    //int32_t fileSizeInBytes = fourBytesToInt (fileData, 4) + 8;
    std::string format (fileData.begin() + 8, fileData.begin() + 12);
    
    // -----------------------------------------------------------
    // try and find the start points of key chunks
    int indexOfDataChunk = getIndexOfChunk (fileData, "data", 12);
    int indexOfFormatChunk = getIndexOfChunk (fileData, "fmt ", 12);
    int indexOfXMLChunk = getIndexOfChunk (fileData, "iXML", 12);
    
    // if we can't find the data or format chunks, or the IDs/formats don't seem to be as expected
    // then it is unlikely we'll able to read this file, so abort
    if (indexOfDataChunk == -1 || indexOfFormatChunk == -1 || headerChunkID != "RIFF" || format != "WAVE")
    {
        reportError ("ERROR: this doesn't seem to be a valid .WAV file");
        return false;
    }
    
    // -----------------------------------------------------------
    // FORMAT CHUNK
    int f = indexOfFormatChunk;
    std::string formatChunkID (fileData.begin() + f, fileData.begin() + f + 4);
    //int32_t formatChunkSize = fourBytesToInt (fileData, f + 4);
    uint16_t audioFormat = twoBytesToInt (fileData, f + 8);
    uint16_t numChannels = twoBytesToInt (fileData, f + 10);
    sampleRate = (uint32_t) fourBytesToInt (fileData, f + 12);
    uint32_t numBytesPerSecond = fourBytesToInt (fileData, f + 16);
    uint16_t numBytesPerBlock = twoBytesToInt (fileData, f + 20);
    bitDepth = (int) twoBytesToInt (fileData, f + 22);
    
    if (bitDepth > sizeof (T) * 8)
    {
        std::string message = "ERROR: you are trying to read a ";
        message += std::to_string (bitDepth);
        message += "-bit file using a ";
        message += std::to_string (sizeof (T) * 8);
        message += "-bit sample type";
        reportError (message);
        return false;
    }
    
    uint16_t numBytesPerSample = static_cast<uint16_t> (bitDepth) / 8;
    
    // check that the audio format is PCM or Float or extensible
    if (audioFormat != WavAudioFormat::PCM && audioFormat != WavAudioFormat::IEEEFloat && audioFormat != WavAudioFormat::Extensible)
    {
        reportError ("ERROR: this .WAV file is encoded in a format that this library does not support at present");
        return false;
    }
    
    // check the number of channels is mono or stereo
    if (numChannels < 1 || numChannels > 128)
    {
        reportError ("ERROR: this WAV file seems to be an invalid number of channels (or corrupted?)");
        return false;
    }
    
    // check header data is consistent
    if (numBytesPerSecond != static_cast<uint32_t> ((numChannels * sampleRate * bitDepth) / 8) || numBytesPerBlock != (numChannels * numBytesPerSample))
    {
        reportError ("ERROR: the header data in this WAV file seems to be inconsistent");
        return false;
    }
    
    // check bit depth is either 8, 16, 24 or 32 bit
    if (bitDepth != 8 && bitDepth != 16 && bitDepth != 24 && bitDepth != 32)
    {
        reportError ("ERROR: this file has a bit depth that is not 8, 16, 24 or 32 bits");
        return false;
    }
    
    // -----------------------------------------------------------
    // DATA CHUNK
    int d = indexOfDataChunk;
    std::string dataChunkID (fileData.begin() + d, fileData.begin() + d + 4);
    int32_t dataChunkSize = fourBytesToInt (fileData, d + 4);
    
    int numSamples = dataChunkSize / (numChannels * bitDepth / 8);
    int samplesStartIndex = indexOfDataChunk + 8;
    
    clearAudioBuffer();
    samples.resize (numChannels);
    
    for (int i = 0; i < numSamples; i++)
    {
        for (int channel = 0; channel < numChannels; channel++)
        {
            int sampleIndex = samplesStartIndex + (numBytesPerBlock * i) + channel * numBytesPerSample;
            
            if ((sampleIndex + (bitDepth / 8) - 1) >= fileData.size())
            {
                reportError ("ERROR: read file error as the metadata indicates more samples than there are in the file data");
                return false;
            }
            
            if (bitDepth == 8)
            {
                T sample = AudioSampleConverter<T>::unsignedByteToSample (fileData[sampleIndex]);
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = twoBytesToInt (fileData, sampleIndex);
                T sample = AudioSampleConverter<T>::sixteenBitIntToSample (sampleAsInt);
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsInt = 0;
                sampleAsInt = (fileData[sampleIndex + 2] << 16) | (fileData[sampleIndex + 1] << 8) | fileData[sampleIndex];
                
                if (sampleAsInt & 0x800000) //  if the 24th bit is set, this is a negative number in 24-bit world
                    sampleAsInt = sampleAsInt | ~0xFFFFFF; // so make sure sign is extended to the 32 bit float

                T sample = AudioSampleConverter<T>::twentyFourBitIntToSample (sampleAsInt);
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 32)
            {
                int32_t sampleAsInt = fourBytesToInt (fileData, sampleIndex);
                T sample;
                
                if (audioFormat == WavAudioFormat::IEEEFloat && std::is_floating_point_v<T>) 
                {
                    float f;
                    memcpy (&f, &sampleAsInt, sizeof(int32_t));
                    sample = (T)f;
                }
                else // assume PCM
                {
                    sample = AudioSampleConverter<T>::thirtyTwoBitIntToSample (sampleAsInt);
                }
                
                samples[channel].push_back (sample);
            }
            else
            {
                assert (false);
            }
        }
    }

    // -----------------------------------------------------------
    // iXML CHUNK
    if (indexOfXMLChunk != -1)
    {
        int32_t chunkSize = fourBytesToInt (fileData, indexOfXMLChunk + 4);
        iXMLChunk = std::string ((const char*) &fileData[indexOfXMLChunk + 8], chunkSize);
    }

    return true;
}

//=============================================================
template <class T>
bool AudioFile<T>::decodeAiffFile (const std::vector<uint8_t>& fileData)
{
    // -----------------------------------------------------------
    // HEADER CHUNK
    std::string headerChunkID (fileData.begin(), fileData.begin() + 4);
    //int32_t fileSizeInBytes = fourBytesToInt (fileData, 4, Endianness::BigEndian) + 8;
    std::string format (fileData.begin() + 8, fileData.begin() + 12);
    
    int audioFormat = format == "AIFF" ? AIFFAudioFormat::Uncompressed : format == "AIFC" ? AIFFAudioFormat::Compressed : AIFFAudioFormat::Error;
    
    // -----------------------------------------------------------
    // try and find the start points of key chunks
    int indexOfCommChunk = getIndexOfChunk (fileData, "COMM", 12, Endianness::BigEndian);
    int indexOfSoundDataChunk = getIndexOfChunk (fileData, "SSND", 12, Endianness::BigEndian);
    int indexOfXMLChunk = getIndexOfChunk (fileData, "iXML", 12, Endianness::BigEndian);
    
    // if we can't find the data or format chunks, or the IDs/formats don't seem to be as expected
    // then it is unlikely we'll able to read this file, so abort
    if (indexOfSoundDataChunk == -1 || indexOfCommChunk == -1 || headerChunkID != "FORM" || audioFormat == AIFFAudioFormat::Error)
    {
        reportError ("ERROR: this doesn't seem to be a valid AIFF file");
        return false;
    }

    // -----------------------------------------------------------
    // COMM CHUNK
    int p = indexOfCommChunk;
    std::string commChunkID (fileData.begin() + p, fileData.begin() + p + 4);
    //int32_t commChunkSize = fourBytesToInt (fileData, p + 4, Endianness::BigEndian);
    int16_t numChannels = twoBytesToInt (fileData, p + 8, Endianness::BigEndian);
    int32_t numSamplesPerChannel = fourBytesToInt (fileData, p + 10, Endianness::BigEndian);
    bitDepth = (int) twoBytesToInt (fileData, p + 14, Endianness::BigEndian);
    sampleRate = getAiffSampleRate (fileData, p + 16);
    
    if (bitDepth > sizeof (T) * 8)
    {
        std::string message = "ERROR: you are trying to read a ";
        message += std::to_string (bitDepth);
        message += "-bit file using a ";
        message += std::to_string (sizeof (T) * 8);
        message += "-bit sample type";
        reportError (message);
        return false;
    }
    
    // check the sample rate was properly decoded
    if (sampleRate == 0)
    {
        reportError ("ERROR: this AIFF file has an unsupported sample rate");
        return false;
    }
    
    // check the number of channels is mono or stereo
    if (numChannels < 1 ||numChannels > 2)
    {
        reportError ("ERROR: this AIFF file seems to be neither mono nor stereo (perhaps multi-track, or corrupted?)");
        return false;
    }
    
    // check bit depth is either 8, 16, 24 or 32-bit
    if (bitDepth != 8 && bitDepth != 16 && bitDepth != 24 && bitDepth != 32)
    {
        reportError ("ERROR: this file has a bit depth that is not 8, 16, 24 or 32 bits");
        return false;
    }
    
    // -----------------------------------------------------------
    // SSND CHUNK
    int s = indexOfSoundDataChunk;
    std::string soundDataChunkID (fileData.begin() + s, fileData.begin() + s + 4);
    int32_t soundDataChunkSize = fourBytesToInt (fileData, s + 4, Endianness::BigEndian);
    int32_t offset = fourBytesToInt (fileData, s + 8, Endianness::BigEndian);
    //int32_t blockSize = fourBytesToInt (fileData, s + 12, Endianness::BigEndian);
    
    int numBytesPerSample = bitDepth / 8;
    int numBytesPerFrame = numBytesPerSample * numChannels;
    int totalNumAudioSampleBytes = numSamplesPerChannel * numBytesPerFrame;
    int samplesStartIndex = s + 16 + (int)offset;
        
    // sanity check the data
    if ((soundDataChunkSize - 8) != totalNumAudioSampleBytes || totalNumAudioSampleBytes > static_cast<long>(fileData.size() - samplesStartIndex))
    {
        reportError ("ERROR: the metadatafor this file doesn't seem right");
        return false;
    }
    
    clearAudioBuffer();
    samples.resize (numChannels);
    
    for (int i = 0; i < numSamplesPerChannel; i++)
    {
        for (int channel = 0; channel < numChannels; channel++)
        {
            int sampleIndex = samplesStartIndex + (numBytesPerFrame * i) + channel * numBytesPerSample;
            
            if ((sampleIndex + (bitDepth / 8) - 1) >= fileData.size())
            {
                reportError ("ERROR: read file error as the metadata indicates more samples than there are in the file data");
                return false;
            }
            
            if (bitDepth == 8)
            {
                T sample = AudioSampleConverter<T>::signedByteToSample (static_cast<int8_t> (fileData[sampleIndex]));
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = twoBytesToInt (fileData, sampleIndex, Endianness::BigEndian);
                T sample = AudioSampleConverter<T>::sixteenBitIntToSample (sampleAsInt);
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsInt = 0;
                sampleAsInt = (fileData[sampleIndex] << 16) | (fileData[sampleIndex + 1] << 8) | fileData[sampleIndex + 2];
                
                if (sampleAsInt & 0x800000) //  if the 24th bit is set, this is a negative number in 24-bit world
                    sampleAsInt = sampleAsInt | ~0xFFFFFF; // so make sure sign is extended to the 32 bit float

                T sample = AudioSampleConverter<T>::twentyFourBitIntToSample (sampleAsInt);
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 32)
            {
                int32_t sampleAsInt = fourBytesToInt (fileData, sampleIndex, Endianness::BigEndian);
                T sample;
                
                if (audioFormat == AIFFAudioFormat::Compressed)
                    sample = (T)reinterpret_cast<float&> (sampleAsInt);
                else // assume PCM
                    sample = AudioSampleConverter<T>::thirtyTwoBitIntToSample (sampleAsInt);
                
                samples[channel].push_back (sample);
            }
            else
            {
                assert (false);
            }
        }
    }

    // -----------------------------------------------------------
    // iXML CHUNK
    if (indexOfXMLChunk != -1)
    {
        int32_t chunkSize = fourBytesToInt (fileData, indexOfXMLChunk + 4);
        iXMLChunk = std::string ((const char*) &fileData[indexOfXMLChunk + 8], chunkSize);
    }
    
    return true;
}

//=============================================================
template <class T>
uint32_t AudioFile<T>::getAiffSampleRate (const std::vector<uint8_t>& fileData, int sampleRateStartIndex)
{
    double sampleRate = AiffUtilities::decodeAiffSampleRate (&fileData[sampleRateStartIndex]);
    return static_cast<uint32_t> (sampleRate);
}

//=============================================================
template <class T>
void AudioFile<T>::addSampleRateToAiffData (std::vector<uint8_t>& fileData, uint32_t sampleRateToAdd)
{
    std::array<uint8_t, 10> sampleRateData;
    AiffUtilities::encodeAiffSampleRate (static_cast<double> (sampleRateToAdd), sampleRateData.data());
    fileData.insert (fileData.end(), sampleRateData.begin(), sampleRateData.end());
}

//=============================================================
template <class T>
bool AudioFile<T>::save (const std::string& filePath, AudioFileFormat format)
{
        std::vector<uint8_t> fileData;
        return saveToMemory (fileData, format) && writeDataToFile (fileData, filePath);
}

//=============================================================
template <class T>
bool AudioFile<T>::saveToMemory (std::vector<uint8_t>& fileData, AudioFileFormat format)
{
    if (format == AudioFileFormat::Wave)
    {
        return encodeWaveFile (fileData);
    }
    else if (format == AudioFileFormat::Aiff)
    {
        return encodeAiffFile (fileData);
    }
    
    return false;
}

//=============================================================
template <class T>
bool AudioFile<T>::encodeWaveFile (std::vector<uint8_t>& fileData)
{    
    int32_t dataChunkSize = getNumSamplesPerChannel() * (getNumChannels() * bitDepth / 8);
    int16_t audioFormat = bitDepth == 32 && std::is_floating_point_v<T> ? WavAudioFormat::IEEEFloat : WavAudioFormat::PCM;
    int32_t formatChunkSize = audioFormat == WavAudioFormat::PCM ? 16 : 18;
    int32_t iXMLChunkSize = static_cast<int32_t> (iXMLChunk.size());
    
    // -----------------------------------------------------------
    // HEADER CHUNK
    addStringToFileData (fileData, "RIFF");
    
    // The file size in bytes is the header chunk size (4, not counting RIFF and WAVE) + the format
    // chunk size (24) + the metadata part of the data chunk plus the actual data chunk size
    int32_t fileSizeInBytes = 4 + formatChunkSize + 8 + 8 + dataChunkSize;
    if (iXMLChunkSize > 0)
    {
        fileSizeInBytes += (8 + iXMLChunkSize);
    }

    addInt32ToFileData (fileData, fileSizeInBytes);
    
    addStringToFileData (fileData, "WAVE");
    
    // -----------------------------------------------------------
    // FORMAT CHUNK
    addStringToFileData (fileData, "fmt ");
    addInt32ToFileData (fileData, formatChunkSize); // format chunk size (16 for PCM)
    addInt16ToFileData (fileData, audioFormat); // audio format
    addInt16ToFileData (fileData, (int16_t)getNumChannels()); // num channels
    addInt32ToFileData (fileData, (int32_t)sampleRate); // sample rate
    
    int32_t numBytesPerSecond = (int32_t) ((getNumChannels() * sampleRate * bitDepth) / 8);
    addInt32ToFileData (fileData, numBytesPerSecond);
    
    int16_t numBytesPerBlock = getNumChannels() * (bitDepth / 8);
    addInt16ToFileData (fileData, numBytesPerBlock);
    
    addInt16ToFileData (fileData, (int16_t)bitDepth);
    
    if (audioFormat == WavAudioFormat::IEEEFloat)
        addInt16ToFileData (fileData, 0); // extension size
    
    // -----------------------------------------------------------
    // DATA CHUNK
    addStringToFileData (fileData, "data");
    addInt32ToFileData (fileData, dataChunkSize);
    
    for (int i = 0; i < getNumSamplesPerChannel(); i++)
    {
        for (int channel = 0; channel < getNumChannels(); channel++)
        {
            if (bitDepth == 8)
            {
                uint8_t byte = AudioSampleConverter<T>::sampleToUnsignedByte (samples[channel][i]);
                fileData.push_back (byte);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = AudioSampleConverter<T>::sampleToSixteenBitInt (samples[channel][i]);
                addInt16ToFileData (fileData, sampleAsInt);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsIntAgain = AudioSampleConverter<T>::sampleToTwentyFourBitInt (samples[channel][i]);
                
                uint8_t bytes[3];
                bytes[2] = (uint8_t) (sampleAsIntAgain >> 16) & 0xFF;
                bytes[1] = (uint8_t) (sampleAsIntAgain >>  8) & 0xFF;
                bytes[0] = (uint8_t) sampleAsIntAgain & 0xFF;
                
                fileData.push_back (bytes[0]);
                fileData.push_back (bytes[1]);
                fileData.push_back (bytes[2]);
            }
            else if (bitDepth == 32)
            {
                int32_t sampleAsInt;
                
                if (audioFormat == WavAudioFormat::IEEEFloat)
                {
                    if constexpr (std::is_same_v<T, float>)
                    {
                        sampleAsInt = (int32_t) reinterpret_cast<int32_t&> (samples[channel][i]);
                    }
                    else if constexpr (std::is_same_v<T, double>)
                    {
                        auto sampleAsFloat = (float) samples[channel][i];
                        float& referenceToSample = sampleAsFloat;
                        sampleAsInt = (int32_t) reinterpret_cast<int32_t&> (referenceToSample);
                    }
                }
                else // assume PCM
                {
                    sampleAsInt = AudioSampleConverter<T>::sampleToThirtyTwoBitInt (samples[channel][i]);
                }
                
                addInt32ToFileData (fileData, sampleAsInt, Endianness::LittleEndian);
            }
            else
            {
                assert (false && "Trying to write a file with unsupported bit depth");
                return false;
            }
        }
    }
    
    // -----------------------------------------------------------
    // iXML CHUNK
    if (iXMLChunkSize > 0) 
    {
        addStringToFileData (fileData, "iXML");
        addInt32ToFileData (fileData, iXMLChunkSize);
        addStringToFileData (fileData, iXMLChunk);
    }
    
    // check that the various sizes we put in the metadata are correct
    if (fileSizeInBytes != static_cast<int32_t> (fileData.size() - 8) || dataChunkSize != (getNumSamplesPerChannel() * getNumChannels() * (bitDepth / 8)))
    {
        reportError ("ERROR: Incorrect file or data chunk size.");
        return false;
    }
    
    return true;
}

//=============================================================
template <class T>
bool AudioFile<T>::encodeAiffFile (std::vector<uint8_t>& fileData)
{    
    int32_t numBytesPerSample = bitDepth / 8;
    int32_t numBytesPerFrame = numBytesPerSample * getNumChannels();
    int32_t totalNumAudioSampleBytes = getNumSamplesPerChannel() * numBytesPerFrame;
    int32_t soundDataChunkSize = totalNumAudioSampleBytes + 8;
    int32_t iXMLChunkSize = static_cast<int32_t> (iXMLChunk.size());
    
    // -----------------------------------------------------------
    // HEADER CHUNK
    addStringToFileData (fileData, "FORM");
    
    // The file size in bytes is the header chunk size (4, not counting FORM and AIFF) + the COMM
    // chunk size (26) + the metadata part of the SSND chunk plus the actual data chunk size
    int32_t fileSizeInBytes = 4 + 26 + 16 + totalNumAudioSampleBytes;
    if (iXMLChunkSize > 0)
    {
        fileSizeInBytes += (8 + iXMLChunkSize);
    }

    addInt32ToFileData (fileData, fileSizeInBytes, Endianness::BigEndian);
    
    addStringToFileData (fileData, "AIFF");
    
    // -----------------------------------------------------------
    // COMM CHUNK
    addStringToFileData (fileData, "COMM");
    addInt32ToFileData (fileData, 18, Endianness::BigEndian); // commChunkSize
    addInt16ToFileData (fileData, getNumChannels(), Endianness::BigEndian); // num channels
    addInt32ToFileData (fileData, getNumSamplesPerChannel(), Endianness::BigEndian); // num samples per channel
    addInt16ToFileData (fileData, bitDepth, Endianness::BigEndian); // bit depth
    addSampleRateToAiffData (fileData, sampleRate);
    
    // -----------------------------------------------------------
    // SSND CHUNK
    addStringToFileData (fileData, "SSND");
    addInt32ToFileData (fileData, soundDataChunkSize, Endianness::BigEndian);
    addInt32ToFileData (fileData, 0, Endianness::BigEndian); // offset
    addInt32ToFileData (fileData, 0, Endianness::BigEndian); // block size
    
    for (int i = 0; i < getNumSamplesPerChannel(); i++)
    {
        for (int channel = 0; channel < getNumChannels(); channel++)
        {
            if (bitDepth == 8)
            {
                uint8_t byte = static_cast<uint8_t> (AudioSampleConverter<T>::sampleToSignedByte (samples[channel][i]));
                fileData.push_back (byte);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = AudioSampleConverter<T>::sampleToSixteenBitInt (samples[channel][i]);
                addInt16ToFileData (fileData, sampleAsInt, Endianness::BigEndian);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsIntAgain = AudioSampleConverter<T>::sampleToTwentyFourBitInt (samples[channel][i]);
                
                uint8_t bytes[3];
                bytes[0] = (uint8_t) (sampleAsIntAgain >> 16) & 0xFF;
                bytes[1] = (uint8_t) (sampleAsIntAgain >>  8) & 0xFF;
                bytes[2] = (uint8_t) sampleAsIntAgain & 0xFF;
                
                fileData.push_back (bytes[0]);
                fileData.push_back (bytes[1]);
                fileData.push_back (bytes[2]);
            }
            else if (bitDepth == 32)
            {
                // write samples as signed integers (no implementation yet for floating point, but looking at WAV implementation should help)
                int32_t sampleAsInt = AudioSampleConverter<T>::sampleToThirtyTwoBitInt (samples[channel][i]);
                addInt32ToFileData (fileData, sampleAsInt, Endianness::BigEndian);
            }
            else
            {
                assert (false && "Trying to write a file with unsupported bit depth");
                return false;
            }
        }
    }

    // -----------------------------------------------------------
    // iXML CHUNK
    if (iXMLChunkSize > 0)
    {
        addStringToFileData (fileData, "iXML");
        addInt32ToFileData (fileData, iXMLChunkSize, Endianness::BigEndian);
        addStringToFileData (fileData, iXMLChunk);
    }
    
    // check that the various sizes we put in the metadata are correct
    if (fileSizeInBytes != static_cast<int32_t> (fileData.size() - 8) || soundDataChunkSize != getNumSamplesPerChannel() *  numBytesPerFrame + 8)
    {
        reportError ("ERROR: Incorrect file or data chunk size.");
        return false;
    }
    
    return true;
}

//=============================================================
template <class T>
bool AudioFile<T>::writeDataToFile (const std::vector<uint8_t>& fileData, std::string filePath)
{
    std::ofstream outputFile (filePath, std::ios::binary);

    if (!outputFile.is_open())
    {
        return false;
    }

    outputFile.write ((const char*)fileData.data(), fileData.size());
    outputFile.close();
    return true;
}

//=============================================================
template <class T>
void AudioFile<T>::addStringToFileData (std::vector<uint8_t>& fileData, std::string s)
{
    for (size_t i = 0; i < s.length();i++)
        fileData.push_back ((uint8_t) s[i]);
}

//=============================================================
template <class T>
void AudioFile<T>::addInt32ToFileData (std::vector<uint8_t>& fileData, int32_t i, Endianness endianness)
{
    uint8_t bytes[4];
    
    if (endianness == Endianness::LittleEndian)
    {
        bytes[3] = (i >> 24) & 0xFF;
        bytes[2] = (i >> 16) & 0xFF;
        bytes[1] = (i >> 8) & 0xFF;
        bytes[0] = i & 0xFF;
    }
    else
    {
        bytes[0] = (i >> 24) & 0xFF;
        bytes[1] = (i >> 16) & 0xFF;
        bytes[2] = (i >> 8) & 0xFF;
        bytes[3] = i & 0xFF;
    }
    
    for (int j = 0; j < 4; j++)
        fileData.push_back (bytes[j]);
}

//=============================================================
template <class T>
void AudioFile<T>::addInt16ToFileData (std::vector<uint8_t>& fileData, int16_t i, Endianness endianness)
{
    uint8_t bytes[2];
    
    if (endianness == Endianness::LittleEndian)
    {
        bytes[1] = (i >> 8) & 0xFF;
        bytes[0] = i & 0xFF;
    }
    else
    {
        bytes[0] = (i >> 8) & 0xFF;
        bytes[1] = i & 0xFF;
    }
    
    fileData.push_back (bytes[0]);
    fileData.push_back (bytes[1]);
}

//=============================================================
template <class T>
void AudioFile<T>::clearAudioBuffer()
{
    for (size_t i = 0; i < samples.size();i++)
    {
        samples[i].clear();
    }
    
    samples.clear();
}

//=============================================================
template <class T>
AudioFileFormat AudioFile<T>::determineAudioFileFormat (const std::vector<uint8_t>& fileData)
{
    if (fileData.size() < 4)
        return AudioFileFormat::Error;
    
    std::string header (fileData.begin(), fileData.begin() + 4);
    
    if (header == "RIFF")
        return AudioFileFormat::Wave;
    else if (header == "FORM")
        return AudioFileFormat::Aiff;
    else
        return AudioFileFormat::Error;
}

//=============================================================
template <class T>
int32_t AudioFile<T>::fourBytesToInt (const std::vector<uint8_t>& source, int startIndex, Endianness endianness)
{
    if (source.size() >= (startIndex + 4))
    {
        int32_t result;
        
        if (endianness == Endianness::LittleEndian)
            result = (source[startIndex + 3] << 24) | (source[startIndex + 2] << 16) | (source[startIndex + 1] << 8) | source[startIndex];
        else
            result = (source[startIndex] << 24) | (source[startIndex + 1] << 16) | (source[startIndex + 2] << 8) | source[startIndex + 3];
        
        return result;
    }
    else
    {
        assert (false && "Attempted to read four bytes from vector at position where out of bounds access would occur");
        return 0; // this is a dummy value as we don't have one to return
    }
}

//=============================================================
template <class T>
int16_t AudioFile<T>::twoBytesToInt (const std::vector<uint8_t>& source, int startIndex, Endianness endianness)
{
    int16_t result;
    
    if (endianness == Endianness::LittleEndian)
        result = (source[startIndex + 1] << 8) | source[startIndex];
    else
        result = (source[startIndex] << 8) | source[startIndex + 1];
    
    return result;
}

//=============================================================
template <class T>
int AudioFile<T>::getIndexOfChunk (const std::vector<uint8_t>& source, const std::string& chunkHeaderID, int startIndex, Endianness endianness)
{
    constexpr int dataLen = 4;
    
    if (chunkHeaderID.size() != dataLen)
    {
        assert (false && "Invalid chunk header ID string");
        return -1;
    }

    int i = startIndex;
    while (i < source.size() - dataLen)
    {
        if (memcmp (&source[i], chunkHeaderID.data(), dataLen) == 0)
        {
            return i;
        }

        i += dataLen;
        
        // If somehow we don't have 4 bytes left to read, then exit with -1
        if ((i + 4) >= source.size())
            return -1;
        
        int32_t chunkSize = fourBytesToInt (source, i, endianness);
        // Assume chunk size is invalid if it's greater than the number of bytes remaining in source
        if (chunkSize > (source.size() - i - dataLen) || (chunkSize < 0))
        {
            assert (false && "Invalid chunk size");
            return -1;
        }
        i += (dataLen + chunkSize);
    }

    return -1;
}

//=============================================================
template <class T>
void AudioFile<T>::reportError (const std::string& errorMessage)
{
    if (logErrorsToConsole)
        std::cerr << errorMessage << std::endl;
}

//=============================================================
template <typename SignedType>
typename std::make_unsigned<SignedType>::type convertSignedToUnsigned (SignedType signedValue)
{
    static_assert (std::is_signed<SignedType>::value, "The input value must be signed");
    
    typename std::make_unsigned<SignedType>::type unsignedValue = static_cast<typename std::make_unsigned<SignedType>::type> (1) + std::numeric_limits<SignedType>::max();
    
    unsignedValue += signedValue;
    return unsignedValue;
}

//=============================================================
enum SampleLimit
{
    SignedInt16_Min = -32768,
    SignedInt16_Max = 32767,
    UnsignedInt16_Min = 0,
    UnsignedInt16_Max = 65535,
    SignedInt24_Min = -8388608,
    SignedInt24_Max = 8388607,
    UnsignedInt24_Min = 0,
    UnsignedInt24_Max = 16777215
};

//=============================================================
template <class T>
T AudioSampleConverter<T>::thirtyTwoBitIntToSample (int32_t sample)
{
    if constexpr (std::is_floating_point<T>::value)
    {
        return static_cast<T> (sample) / static_cast<T> (std::numeric_limits<int32_t>::max());
    }
    else if (std::numeric_limits<T>::is_integer)
    {
        if constexpr (std::is_signed_v<T>)
			return static_cast<T> (sample);
        else
            return static_cast<T> (clamp (static_cast<T> (sample + 2147483648), 0, 4294967295));
    }
}

//=============================================================
template <class T>
int32_t AudioSampleConverter<T>::sampleToThirtyTwoBitInt (T sample)
{
    if constexpr (std::is_floating_point<T>::value)
    {
        // multiplying a float by a the max int32_t is problematic because
        // of roundng errors which can cause wrong values to come out, so
        // we use a different implementation here compared to other types
        if constexpr (std::is_same_v<T, float>)
        {
            if (sample >= 1.f)
                return std::numeric_limits<int32_t>::max();
            else if (sample <= -1.f)
                return std::numeric_limits<int32_t>::lowest() + 1; // starting at 1 preserves symmetry
            else
                return static_cast<int32_t> (sample * std::numeric_limits<int32_t>::max());
        }
        else
        {
            return static_cast<int32_t> (clamp (sample, -1., 1.) * std::numeric_limits<int32_t>::max());
        }
    }
    else
    {
        if constexpr (std::is_signed_v<T>)
            return static_cast<int32_t> (clamp (sample, -2147483648LL, 2147483647LL));
        else
            return static_cast<int32_t> (clamp (sample, 0, 4294967295) - 2147483648);
    }
}

//=============================================================
template <class T>
T AudioSampleConverter<T>::twentyFourBitIntToSample (int32_t sample)
{
    if constexpr (std::is_floating_point<T>::value)
    {
        return static_cast<T> (sample) / static_cast<T> (8388607.);
    }
    else if (std::numeric_limits<T>::is_integer)
    {
        if constexpr (std::is_signed_v<T>)
            return static_cast<T> (clamp (sample, SignedInt24_Min, SignedInt24_Max));
        else
            return static_cast<T> (clamp (sample + 8388608, UnsignedInt24_Min, UnsignedInt24_Max));
    }
}

//=============================================================
template <class T>
int32_t AudioSampleConverter<T>::sampleToTwentyFourBitInt (T sample)
{
    if constexpr (std::is_floating_point<T>::value)
    {
        sample = clamp (sample, -1., 1.);
        return static_cast<int32_t> (sample * 8388607.);
    }
    else
    {
        if constexpr (std::is_signed_v<T>)
            return static_cast<int32_t> (clamp (sample, SignedInt24_Min, SignedInt24_Max));
        else
            return static_cast<int32_t> (clamp (sample, UnsignedInt24_Min, UnsignedInt24_Max) + SignedInt24_Min);
    }
}

//=============================================================
template <class T>
T AudioSampleConverter<T>::sixteenBitIntToSample (int16_t sample)
{
    if constexpr (std::is_floating_point<T>::value)
    {
        return static_cast<T> (sample) / static_cast<T> (32767.);
    }
    else if constexpr (std::numeric_limits<T>::is_integer)
    {
        if constexpr (std::is_signed_v<T>)
            return static_cast<T> (sample);
        else
            return static_cast<T> (convertSignedToUnsigned<int16_t> (sample));
    }
}

//=============================================================
template <class T>
int16_t AudioSampleConverter<T>::sampleToSixteenBitInt (T sample)
{
    if constexpr (std::is_floating_point<T>::value)
    {
        sample = clamp (sample, -1., 1.);
        return static_cast<int16_t> (sample * 32767.);
    }
    else
    {
        if constexpr (std::is_signed_v<T>)
            return static_cast<int16_t> (clamp (sample, SignedInt16_Min, SignedInt16_Max));
        else
            return static_cast<int16_t> (clamp (sample, UnsignedInt16_Min, UnsignedInt16_Max) + SignedInt16_Min);
    }
}

//=============================================================
template <class T>
uint8_t AudioSampleConverter<T>::sampleToUnsignedByte (T sample)
{
    if constexpr (std::is_floating_point<T>::value)
    {
        sample = clamp (sample, -1., 1.);
        sample = (sample + 1.) / 2.;
        return static_cast<uint8_t> (1 + (sample * 254));
    }
    else
    {
        if constexpr (std::is_signed_v<T>)
            return static_cast<uint8_t> (clamp (sample, -128, 127) + 128);
        else
            return static_cast<uint8_t> (clamp (sample, 0, 255));
    }
}

//=============================================================
template <class T>
int8_t AudioSampleConverter<T>::sampleToSignedByte (T sample)
{
    if constexpr (std::is_floating_point<T>::value)
    {
        sample = clamp (sample, -1., 1.);
        return static_cast<int8_t> (sample * (T)0x7F);
    }
    else
    {
        if constexpr (std::is_signed_v<T>)
            return static_cast<int8_t> (clamp (sample, -128, 127));
        else
            return static_cast<int8_t> (clamp (sample, 0, 255) - 128);
    }
}

//=============================================================
template <class T>
T AudioSampleConverter<T>::unsignedByteToSample (uint8_t sample)
{
    if constexpr (std::is_floating_point<T>::value)
    {
        return static_cast<T> (sample - 128) / static_cast<T> (127.);
    }
    else if (std::numeric_limits<T>::is_integer)
    {
        if constexpr (std::is_unsigned_v<T>)
            return static_cast<T> (sample);
        else
            return static_cast<T> (sample - 128);
    }
}

//=============================================================
template <class T>
T AudioSampleConverter<T>::signedByteToSample (int8_t sample)
{
    if constexpr (std::is_floating_point<T>::value)
    {
        return static_cast<T> (sample) / static_cast<T> (127.);
    }
    else if constexpr (std::numeric_limits<T>::is_integer)
    {
        if constexpr (std::is_signed_v<T>)
            return static_cast<T> (sample);
        else
            return static_cast<T> (convertSignedToUnsigned<int8_t> (sample));
    }
}

//=============================================================
template <class T>
T AudioSampleConverter<T>::clamp (T value, T minValue, T maxValue)
{
    value = std::min (value, maxValue);
    value = std::max (value, minValue);
    return value;
}

//=============================================================
inline double AiffUtilities::decodeAiffSampleRate (const uint8_t* bytes)
{
    // Note: Sample rate is 80 bits made up of
    // * 1 sign bit
    // * 15 exponent bits
    // * 64 mantissa bits
    
    // ----------------------------------------------
    // Sign
    
    // Extract the sign (most significant bit of byte 0)
    int sign = (bytes[0] & 0x80) ? -1 : 1;
    
    // ----------------------------------------------
    // Exponent
    
    // byte 0: ignore the sign and shift the most significant bits to the left by one byte
    uint16_t msbShifted = (static_cast<uint16_t> (bytes[0] & 0x7F) << 8);
    
    // calculate exponent by combining byte 0 and byte 1 and subtract bias
    uint16_t exponent = (msbShifted | static_cast<uint16_t> (bytes[1])) - 16383;
    
    // ----------------------------------------------
    // Mantissa
    
    // Extract the mantissa (remaining 64 bits) by looping over the remaining
    // bytes and combining them while shifting the result to the left by
    // 8 bits each time
    uint64_t mantissa = 0;
    
    for (int i = 2; i < 10; ++i)
        mantissa = (mantissa << 8) | bytes[i];
    
    // Normalize the mantissa (implicit leading 1 for normalized values)
    double normalisedMantissa = static_cast<double> (mantissa) / (1ULL << 63);
    
    // ----------------------------------------------
    // Combine sign, exponent, and mantissa into a double
    
    return sign * std::ldexp (normalisedMantissa, exponent);
}

//=============================================================
inline void AiffUtilities::encodeAiffSampleRate (double sampleRate, uint8_t* bytes)
{
    // Determine the sign
    int sign = (sampleRate < 0) ? -1 : 1;
    
    if (sign == -1)
        sampleRate = -sampleRate;
    
    // Set most significant bit of byte 0 for the sign
    bytes[0] = (sign == -1) ? 0x80 : 0x00;
    
    // Calculate the exponent using logarithm (log base 2)
    int exponent = (log (sampleRate) / log (2.0));
    
    // Add bias to exponent for AIFF
    uint16_t biasedExponent = static_cast<uint16_t> (exponent + 16383);
    
    // Normalize the sample rate
    double normalizedSampleRate = sampleRate / pow (2.0, exponent);
    
    // Calculate the mantissa
    uint64_t mantissa = static_cast<uint64_t> (normalizedSampleRate * (1ULL << 63));
    
    // Pack the exponent into first two bytes of 10-byte AIFF format
    bytes[0] |= (biasedExponent >> 8) & 0x7F;   // Upper 7 bits of exponent
    bytes[1] = biasedExponent & 0xFF;           // Lower 8 bits of exponent
    
    // Put the mantissa into byte array
    for (int i = 0; i < 8; ++i)
        bytes[2 + i] = (mantissa >> (8 * (7 - i))) & 0xFF;
}

#if defined (_MSC_VER)
    __pragma(warning (pop))
#elif defined (__GNUC__)
    _Pragma("GCC diagnostic pop")
#endif

#endif /* AudioFile_h */
