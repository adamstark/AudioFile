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

    /** Set the audio buffer for this AudioFile by moving samples from another buffer.
     * @Returns true if the buffer was moved successfully.
     */
    bool setAudioBuffer(AudioBuffer&& newBuffer);

    /** Sets the audio buffer to a given number of channels and number of samples per channel. This will try to preserve
     * the existing audio, adding zeros to any new channels or new samples in a given channel.
     */
    void setAudioBufferSize (int numChannels, int numSamples);
    
    /** Sets the number of samples per channel in the audio buffer. This will try to preserve
     * the existing audio, adding zeros to new samples in a given channel if the number of samples is increased.
     */
    void setNumSamplesPerChannel (int numSamples);
    
    /** Sets the number of channels. New channels will have the correct number of samples and be initialised to zero */
    void setNumChannels (int numChannels);
    
    /** Sets the bit depth for the audio file. If you use the save() function, this bit depth rate will be used */
    void setBitDepth (int numBitsPerSample);
    
    /** Sets the sample rate for the audio file. If you use the save() function, this sample rate will be used */
    void setSampleRate (uint32_t newSampleRate);
    
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
    AudioFileFormat determineAudioFileFormat (const std::vector<uint8_t>& fileData);
    bool decodeWaveFile (const std::vector<uint8_t>& fileData);
    bool decodeAiffFile (const std::vector<uint8_t>& fileData);
    
    //=============================================================
    bool saveToWaveFile (const std::string& filePath);
    bool saveToAiffFile (const std::string& filePath);
    
    //=============================================================
    void clearAudioBuffer();
    
    //=============================================================
    template<Endianness E = Endianness::LittleEndian>
    inline int32_t fourBytesToInt(const std::vector<uint8_t>& source, int startIndex)
    {
        return *reinterpret_cast<const int32_t*>(source.data() + startIndex);
    }

    template<>
    inline int32_t fourBytesToInt<Endianness::BigEndian>(const std::vector<uint8_t>& source, int startIndex)
    {
        return  (source[startIndex] << 24) | (source[startIndex + 1] << 16) | (source[startIndex + 2] << 8) | source[startIndex + 3];
    }

    template<Endianness E = Endianness::LittleEndian>
    inline int16_t twoBytesToInt(const std::vector<uint8_t>& source, int startIndex)
    {
        return *reinterpret_cast<const int16_t*>(source.data() + startIndex);
    }

    template<>
    inline int16_t twoBytesToInt<Endianness::BigEndian>(const std::vector<uint8_t>& source, int startIndex)
    {
        return (source[startIndex] << 8) | source[startIndex + 1];
    }

    template<Endianness E = Endianness::LittleEndian>
    int getIndexOfChunk (const std::vector<uint8_t>& source, const std::string& chunkHeaderID, int startIndex);
    
    //=============================================================
    T sixteenBitIntToSample (int16_t sample);
    int16_t sampleToSixteenBitInt (T sample);
    
    //=============================================================
    uint8_t sampleToSingleByte (T sample);
    T singleByteToSample (uint8_t sample);
    
    uint32_t getAiffSampleRate (const std::vector<uint8_t>& fileData, int sampleRateStartIndex);
    bool tenByteMatch (const std::vector<uint8_t>& v1, int startIndex1, const std::vector<uint8_t>& v2, int startIndex2);
    void addSampleRateToAiffData (std::vector<uint8_t>& fileData, uint32_t sampleRate);
    T clamp (T v1, T minValue, T maxValue);
    
    //=============================================================
    void addStringToFileData (std::vector<uint8_t>& fileData, const std::string& s);
    
    template<Endianness E = Endianness::LittleEndian>
    inline void addInt32ToFileData(std::vector<uint8_t>& fileData, int32_t i)
    {
        const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&i);
        fileData.insert(fileData.end(), bytes, bytes + 4);
    }

    template<>
    inline void addInt32ToFileData<Endianness::BigEndian>(std::vector<uint8_t>& fileData, int32_t i)
    {
        uint8_t bytes[4];

        bytes[0] = (i >> 24) & 0xFF;
        bytes[1] = (i >> 16) & 0xFF;
        bytes[2] = (i >> 8) & 0xFF;
        bytes[3] = i & 0xFF;
        
        fileData.insert(fileData.end(), bytes, bytes + 4);
    }

    template<Endianness E = Endianness::LittleEndian>
    inline void addInt16ToFileData (std::vector<uint8_t>& fileData, int16_t i)
    {
        const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&i);
        fileData.push_back(bytes[0]);
        fileData.push_back(bytes[1]);
    }

    template<>
    inline void addInt16ToFileData<Endianness::BigEndian>(std::vector<uint8_t>& fileData, int16_t i)
    {
        fileData.push_back((i >> 8) & 0xFF);
        fileData.push_back(i & 0xFF);
    }
    
    //=============================================================
    bool writeDataToFile (const std::vector<uint8_t>& fileData, const std::string& filePath);
    
    //=============================================================
    void reportError (const std::string& errorMessage);
    
    //=============================================================
    AudioFileFormat audioFileFormat;
    uint32_t sampleRate;
    int bitDepth;
    bool logErrorsToConsole {true};
};


//=============================================================
// Pre-defined 10-byte representations of common sample rates
static std::unordered_map <uint32_t, std::vector<uint8_t>> aiffSampleRateTable = {
    {8000, {64, 11, 250, 0, 0, 0, 0, 0, 0, 0}},
    {11025, {64, 12, 172, 68, 0, 0, 0, 0, 0, 0}},
    {16000, {64, 12, 250, 0, 0, 0, 0, 0, 0, 0}},
    {22050, {64, 13, 172, 68, 0, 0, 0, 0, 0, 0}},
    {32000, {64, 13, 250, 0, 0, 0, 0, 0, 0, 0}},
    {37800, {64, 14, 147, 168, 0, 0, 0, 0, 0, 0}},
    {44056, {64, 14, 172, 24, 0, 0, 0, 0, 0, 0}},
    {44100, {64, 14, 172, 68, 0, 0, 0, 0, 0, 0}},
    {47250, {64, 14, 184, 146, 0, 0, 0, 0, 0, 0}},
    {48000, {64, 14, 187, 128, 0, 0, 0, 0, 0, 0}},
    {50000, {64, 14, 195, 80, 0, 0, 0, 0, 0, 0}},
    {50400, {64, 14, 196, 224, 0, 0, 0, 0, 0, 0}},
    {88200, {64, 15, 172, 68, 0, 0, 0, 0, 0, 0}},
    {96000, {64, 15, 187, 128, 0, 0, 0, 0, 0, 0}},
    {176400, {64, 16, 172, 68, 0, 0, 0, 0, 0, 0}},
    {192000, {64, 16, 187, 128, 0, 0, 0, 0, 0, 0}},
    {352800, {64, 17, 172, 68, 0, 0, 0, 0, 0, 0}},
    {2822400, {64, 20, 172, 68, 0, 0, 0, 0, 0, 0}},
    {5644800, {64, 21, 172, 68, 0, 0, 0, 0, 0, 0}}
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
    static_assert(std::is_floating_point<T>::value, "ERROR: This version of AudioFile only supports floating point sample formats");

    bitDepth = 16;
    sampleRate = 44100;
    samples.resize (1);
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
    std::cout << "|======================================|" << std::endl;
    std::cout << "Num Channels: " << getNumChannels() << std::endl;
    std::cout << "Num Samples Per Channel: " << getNumSamplesPerChannel() << std::endl;
    std::cout << "Sample Rate: " << sampleRate << std::endl;
    std::cout << "Bit Depth: " << bitDepth << std::endl;
    std::cout << "Length in Seconds: " << getLengthInSeconds() << std::endl;
    std::cout << "|======================================|" << std::endl;
}

//=============================================================
template <class T>
bool AudioFile<T>::setAudioBuffer (const AudioBuffer& newBuffer)
{
    if (newBuffer.empty())
    {
        assert (false && "The buffer your are trying to use has no channels");
        return false;
    }
    
    size_t numChannels = newBuffer.size();
    size_t numSamples = newBuffer[0].size();
    
    // set the number of channels
    samples.resize (numChannels);
    
    for (size_t k = 0; k < numChannels; k++)
    {
        assert (newBuffer[k].size() == numSamples);
        
        samples[k].resize (numSamples);
        std::memcpy((void*)samples[k].data(), (const void*)newBuffer[k].data(), sizeof(T) * numSamples);
    }
    
    return true;
}


template <class T>
bool AudioFile<T>::setAudioBuffer(AudioBuffer&& newBuffer)
{
    if (newBuffer.empty())
    {
        assert(false && "The buffer your are trying to use has no channels");
        return false;
    }

    samples = std::move(newBuffer);

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
    
    return loadFromMemory (fileData);
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
    //std::string formatChunkID (fileData.begin() + f, fileData.begin() + f + 4);
    //int32_t formatChunkSize = fourBytesToInt (fileData, f + 4);
    uint16_t audioFormat = twoBytesToInt (fileData, f + 8);
    uint16_t numChannels = twoBytesToInt (fileData, f + 10);
    sampleRate = (uint32_t) fourBytesToInt (fileData, f + 12);
    uint32_t numBytesPerSecond = fourBytesToInt (fileData, f + 16);
    uint16_t numBytesPerBlock = twoBytesToInt (fileData, f + 20);
    bitDepth = (int) twoBytesToInt (fileData, f + 22);
    
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
    //std::string dataChunkID (fileData.begin() + d, fileData.begin() + d + 4);
    int32_t dataChunkSize = fourBytesToInt (fileData, d + 4);
    
    int numSamples = dataChunkSize / (numChannels * bitDepth / 8);
    int samplesStartIndex = indexOfDataChunk + 8;
    
    clearAudioBuffer();
    samples.resize (numChannels);

    for (auto& chan : samples)
        chan.resize(numSamples);

    for (int i = 0; i < numSamples; i++)
    {
        int sampleIndex = samplesStartIndex + (numBytesPerBlock * i);

        for (int channel = 0; channel < numChannels; channel++, sampleIndex += numBytesPerSample)
        {
            
            if ((sampleIndex + (bitDepth / 8) - 1) >= fileData.size())
            {
                reportError ("ERROR: read file error as the metadata indicates more samples than there are in the file data");
                return false;
            }
            
            if (bitDepth == 8)
            {
                T sample = singleByteToSample (fileData[sampleIndex]);
                samples[channel][i] = sample;
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = twoBytesToInt (fileData, sampleIndex);
                T sample = sixteenBitIntToSample (sampleAsInt);
                samples[channel][i] = sample;
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsInt = 0;
                sampleAsInt = (fileData[sampleIndex + 2] << 16) | (fileData[sampleIndex + 1] << 8) | fileData[sampleIndex];
                
                if (sampleAsInt & 0x800000) //  if the 24th bit is set, this is a negative number in 24-bit world
                    sampleAsInt = sampleAsInt | ~0xFFFFFF; // so make sure sign is extended to the 32 bit float

                T sample = (T)sampleAsInt / (T)8388608.;
                samples[channel][i] = sample;
            }
            else if (bitDepth == 32)
            {
                int32_t sampleAsInt = fourBytesToInt (fileData, sampleIndex);
                T sample;
                
                if (audioFormat == WavAudioFormat::IEEEFloat)
                    sample = (T)reinterpret_cast<float&> (sampleAsInt);
                else // assume PCM
                    sample = (T) sampleAsInt / static_cast<float> (std::numeric_limits<std::int32_t>::max());
                
                samples[channel][i] = sample;
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
    std::string format (fileData.begin() + 8, fileData.begin() + 12);
    
    int audioFormat = format == "AIFF" ? AIFFAudioFormat::Uncompressed : format == "AIFC" ? AIFFAudioFormat::Compressed : AIFFAudioFormat::Error;
    
    // -----------------------------------------------------------
    // try and find the start points of key chunks
    int indexOfCommChunk = getIndexOfChunk<Endianness::BigEndian> (fileData, "COMM", 12);
    int indexOfSoundDataChunk = getIndexOfChunk<Endianness::BigEndian> (fileData, "SSND", 12);
    int indexOfXMLChunk = getIndexOfChunk<Endianness::BigEndian> (fileData, "iXML", 12);
    
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
    int16_t numChannels = twoBytesToInt<Endianness::BigEndian> (fileData, p + 8);
    int32_t numSamplesPerChannel = fourBytesToInt<Endianness::BigEndian> (fileData, p + 10);
    bitDepth = (int) twoBytesToInt<Endianness::BigEndian>(fileData, p + 14);
    sampleRate = getAiffSampleRate (fileData, p + 16);
    
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
    int32_t soundDataChunkSize = fourBytesToInt<Endianness::BigEndian> (fileData, s + 4);
    int32_t offset = fourBytesToInt<Endianness::BigEndian> (fileData, s + 8);
    
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
                int8_t sampleAsSigned8Bit = (int8_t)fileData[sampleIndex];
                T sample = (T)sampleAsSigned8Bit / (T)128.;
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = twoBytesToInt<Endianness::BigEndian>(fileData, sampleIndex);
                T sample = sixteenBitIntToSample (sampleAsInt);
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsInt = 0;
                sampleAsInt = (fileData[sampleIndex] << 16) | (fileData[sampleIndex + 1] << 8) | fileData[sampleIndex + 2];
                
                if (sampleAsInt & 0x800000) //  if the 24th bit is set, this is a negative number in 24-bit world
                    sampleAsInt = sampleAsInt | ~0xFFFFFF; // so make sure sign is extended to the 32 bit float
                
                T sample = (T)sampleAsInt / (T)8388608.;
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 32)
            {
                int32_t sampleAsInt = fourBytesToInt<Endianness::BigEndian> (fileData, sampleIndex);
                T sample;
                
                if (audioFormat == AIFFAudioFormat::Compressed)
                    sample = (T)reinterpret_cast<float&> (sampleAsInt);
                else // assume uncompressed
                    sample = (T) sampleAsInt / static_cast<float> (std::numeric_limits<std::int32_t>::max());
                    
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
    for (auto it : aiffSampleRateTable)
    {
        if (tenByteMatch (fileData, sampleRateStartIndex, it.second, 0))
            return it.first;
    }
    
    return 0;
}

//=============================================================
template <class T>
bool AudioFile<T>::tenByteMatch (const std::vector<uint8_t>& v1, int startIndex1, const std::vector<uint8_t>& v2, int startIndex2)
{
    for (int i = 0; i < 10; i++)
    {
        if (v1[startIndex1 + i] != v2[startIndex2 + i])
            return false;
    }
    
    return true;
}

//=============================================================
template <class T>
void AudioFile<T>::addSampleRateToAiffData (std::vector<uint8_t>& fileData, uint32_t sampleRate)
{
    if (aiffSampleRateTable.count (sampleRate) > 0)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiffSampleRateTable[sampleRate][i]);
    }
}

//=============================================================
template <class T>
bool AudioFile<T>::save (const std::string& filePath, AudioFileFormat format)
{
    if (format == AudioFileFormat::Wave)
    {
        return saveToWaveFile (filePath);
    }
    else if (format == AudioFileFormat::Aiff)
    {
        return saveToAiffFile (filePath);
    }
    
    return false;
}

//=============================================================
template <class T>
bool AudioFile<T>::saveToWaveFile (const std::string& filePath)
{
    int32_t dataChunkSize = getNumSamplesPerChannel() * (getNumChannels() * bitDepth / 8);
    int16_t audioFormat = bitDepth == 32 ? WavAudioFormat::IEEEFloat : WavAudioFormat::PCM;
    int32_t formatChunkSize = audioFormat == WavAudioFormat::PCM ? 16 : 18;
    int32_t iXMLChunkSize = static_cast<int32_t> (iXMLChunk.size());
    
    // The file size in bytes is the header chunk size (4, not counting RIFF and WAVE) + the format
    // chunk size (24) + the metadata part of the data chunk plus the actual data chunk size
    int32_t fileSizeInBytes = 4 + formatChunkSize + 8 + 8 + dataChunkSize;
    if (iXMLChunkSize > 0)
    {
        fileSizeInBytes += (8 + iXMLChunkSize);
    }

    std::vector<uint8_t> fileData;
    fileData.reserve(fileSizeInBytes + 8);

    // -----------------------------------------------------------
    // HEADER CHUNK
    addStringToFileData(fileData, "RIFF");

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
                uint8_t byte = sampleToSingleByte (samples[channel][i]);
                fileData.push_back (byte);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = sampleToSixteenBitInt (samples[channel][i]);
                addInt16ToFileData (fileData, sampleAsInt);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsIntAgain = (int32_t) (samples[channel][i] * (T)8388608.);
                
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
                    sampleAsInt = (int32_t) reinterpret_cast<int32_t&> (samples[channel][i]);
                else // assume PCM
                    sampleAsInt = (int32_t) (samples[channel][i] * std::numeric_limits<int32_t>::max());
                
                addInt32ToFileData (fileData, sampleAsInt);
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
        reportError ("ERROR: couldn't save file to " + filePath);
        return false;
    }
    
    // try to write the file
    return writeDataToFile (fileData, filePath);
}

//=============================================================
template <class T>
bool AudioFile<T>::saveToAiffFile (const std::string& filePath)
{
    int32_t numBytesPerSample = bitDepth / 8;
    int32_t numBytesPerFrame = numBytesPerSample * getNumChannels();
    int32_t totalNumAudioSampleBytes = getNumSamplesPerChannel() * numBytesPerFrame;
    int32_t soundDataChunkSize = totalNumAudioSampleBytes + 8;
    int32_t iXMLChunkSize = static_cast<int32_t> (iXMLChunk.size());
    
    // The file size in bytes is the header chunk size (4, not counting FORM and AIFF) + the COMM
    // chunk size (26) + the metadata part of the SSND chunk plus the actual data chunk size
    int32_t fileSizeInBytes = 4 + 26 + 16 + totalNumAudioSampleBytes;
    if (iXMLChunkSize > 0)
    {
        fileSizeInBytes += (8 + iXMLChunkSize);
    }

    std::vector<uint8_t> fileData;
    fileData.reserve(fileSizeInBytes + 8);

    // -----------------------------------------------------------
    // HEADER CHUNK
    addStringToFileData(fileData, "FORM");

    addInt32ToFileData<Endianness::BigEndian> (fileData, fileSizeInBytes);
    
    addStringToFileData (fileData, "AIFF");
    
    // -----------------------------------------------------------
    // COMM CHUNK
    addStringToFileData (fileData, "COMM");
    addInt32ToFileData<Endianness::BigEndian> (fileData, 18); // commChunkSize
    addInt16ToFileData<Endianness::BigEndian> (fileData, getNumChannels()); // num channels
    addInt32ToFileData<Endianness::BigEndian> (fileData, getNumSamplesPerChannel()); // num samples per channel
    addInt16ToFileData<Endianness::BigEndian> (fileData, bitDepth); // bit depth
    addSampleRateToAiffData (fileData, sampleRate);
    
    // -----------------------------------------------------------
    // SSND CHUNK
    addStringToFileData (fileData, "SSND");
    addInt32ToFileData<Endianness::BigEndian> (fileData, soundDataChunkSize);
    addInt32ToFileData<Endianness::BigEndian> (fileData, 0); // offset
    addInt32ToFileData<Endianness::BigEndian> (fileData, 0); // block size
    
    for (int i = 0; i < getNumSamplesPerChannel(); i++)
    {
        for (int channel = 0; channel < getNumChannels(); channel++)
        {
            if (bitDepth == 8)
            {
                uint8_t byte = sampleToSingleByte (samples[channel][i]);
                fileData.push_back (byte);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = sampleToSixteenBitInt (samples[channel][i]);
                addInt16ToFileData<Endianness::BigEndian> (fileData, sampleAsInt);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsIntAgain = (int32_t) (samples[channel][i] * (T)8388608.);
                
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
                int32_t sampleAsInt = (int32_t) (samples[channel][i] * std::numeric_limits<int32_t>::max());
                addInt32ToFileData<Endianness::BigEndian> (fileData, sampleAsInt);
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
        addInt32ToFileData<Endianness::BigEndian> (fileData, iXMLChunkSize);
        addStringToFileData (fileData, iXMLChunk);
    }
    
    // check that the various sizes we put in the metadata are correct
    if (fileSizeInBytes != static_cast<int32_t> (fileData.size() - 8) || soundDataChunkSize != getNumSamplesPerChannel() *  numBytesPerFrame + 8)
    {
        reportError ("ERROR: couldn't save file to " + filePath);
        return false;
    }
    
    // try to write the file
    return writeDataToFile (fileData, filePath);
}

//=============================================================
template <class T>
bool AudioFile<T>::writeDataToFile (const std::vector<uint8_t>& fileData, const std::string& filePath)
{
    std::ofstream outputFile (filePath, std::ios::binary);
    
    if (outputFile.is_open())
    {
        outputFile.write((const char*)fileData.data(), fileData.size());
        outputFile.close();
        return !outputFile.fail();
    }
    
    return false;
}

//=============================================================
template <class T>
void AudioFile<T>::addStringToFileData (std::vector<uint8_t>& fileData, const std::string& s)
{
    for (size_t i = 0; i < s.length();i++)
        fileData.push_back ((uint8_t) s[i]);
}

//=============================================================
template <class T>
void AudioFile<T>::clearAudioBuffer()
{
    samples.clear();
}

//=============================================================
template <class T>
AudioFileFormat AudioFile<T>::determineAudioFileFormat (const std::vector<uint8_t>& fileData)
{
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
template<typename AudioFile<T>::Endianness E>
int AudioFile<T>::getIndexOfChunk (const std::vector<uint8_t>& source, const std::string& chunkHeaderID, int startIndex)
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
        auto chunkSize = fourBytesToInt<E> (source, i);
        i += (dataLen + chunkSize);
    }

    return -1;
}

//=============================================================
template <class T>
T AudioFile<T>::sixteenBitIntToSample (int16_t sample)
{
    return static_cast<T> (sample) / static_cast<T> (32768.);
}

//=============================================================
template <class T>
int16_t AudioFile<T>::sampleToSixteenBitInt (T sample)
{
    sample = clamp (sample, -1., 1.);
    return static_cast<int16_t> (sample * 32767.);
}

//=============================================================
template <class T>
uint8_t AudioFile<T>::sampleToSingleByte (T sample)
{
    sample = clamp (sample, -1., 1.);
    sample = (sample + 1.) / 2.;
    return static_cast<uint8_t> (sample * 255.);
}

//=============================================================
template <class T>
T AudioFile<T>::singleByteToSample (uint8_t sample)
{
    return static_cast<T> (sample - 128) / static_cast<T> (128.);
}

//=============================================================
template <class T>
T AudioFile<T>::clamp (T value, T minValue, T maxValue)
{
    value = std::min (value, maxValue);
    value = std::max (value, minValue);
    return value;
}

//=============================================================
template <class T>
void AudioFile<T>::reportError (const std::string& errorMessage)
{
    if (logErrorsToConsole)
        std::cout << errorMessage << std::endl;
}

#if defined (_MSC_VER)
    __pragma(warning (pop))
#elif defined (__GNUC__)
    _Pragma("GCC diagnostic pop")
#endif

#endif /* AudioFile_h */
