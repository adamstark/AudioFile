//=======================================================================
/** @file AudioFile.cpp
 *  @author Adam Stark
 *  @copyright Copyright (C) 2017  Adam Stark
 *
 * This file is part of the 'AudioFile' library
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//=======================================================================

#include "AudioFile.h"
#include <fstream>
#include <iterator>

//=============================================================
// Pre-defined 10-byte representations of common sample rates
std::vector<uint8_t> aiff_8000 = {64, 11, 250, 0, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_11025 = {64, 12, 172, 68, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_16000 = {64, 12, 250, 0, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_22050 = {64, 13, 172, 68, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_32000 = {64, 13, 250, 0, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_37800 = {64, 14, 147, 168, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_44056 = {64, 14, 172, 24, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_44100 = {64, 14, 172, 68, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_47250 = {64, 14, 184, 146, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_48000 = {64, 14, 187, 128, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_50000 = {64, 14, 195, 80, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_50400 = {64, 14, 196, 224, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_88200 = {64, 15, 172, 68, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_96000 = {64, 15, 187, 128, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_176400 = {64, 16, 172, 68, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_192000 = {64, 16, 187, 128, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_352800 = {64, 17, 172, 68, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_2822400 = {64, 20, 172, 68, 0, 0, 0, 0, 0, 0};
std::vector<uint8_t> aiff_5644800 = {64, 21, 172, 68, 0, 0, 0, 0, 0, 0};

//=============================================================
template <class T>
AudioFile<T>::AudioFile()
{
    bitDepth = 16;
    sampleRate = 44100;
    samples.resize (1);
    samples[0].resize (0);
    audioFileType = AudioFileType::NotLoaded;
}

//=============================================================
template <class T>
int AudioFile<T>::getSampleRate() const
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
double AudioFile<T>::getLengthInSeconds()
{
    return (double)getNumSamplesPerChannel() / (double)sampleRate;
}

//=============================================================
template <class T>
void AudioFile<T>::printSummary()
{
    std::cout << "|============================|" << std::endl;
    std::cout << "Num Channels: " << getNumChannels() << std::endl;
    std::cout << "Num Samples Per Channel: " << getNumSamplesPerChannel() << std::endl;
    std::cout << "Sample Rate: " << sampleRate << std::endl;
    std::cout << "Bit Depth: " << bitDepth << std::endl;
    std::cout << "Length in Seconds: " << getLengthInSeconds() << std::endl;
    std::cout << "|============================|" << std::endl;
}

//=============================================================
template <class T>
void AudioFile<T>::setBitDepth (int numBitsPerSample)
{
    bitDepth = numBitsPerSample;
}

//=============================================================
template <class T>
void AudioFile<T>::setSampleRate (int newSampleRate)
{
    sampleRate = newSampleRate;
}

//=============================================================
template <class T>
bool AudioFile<T>::load (std::string filePath)
{
    std::ifstream file (filePath, std::ios::binary);
    
    // check the file exists
    if (! file.good())
    {
        std::cout << "ERROR: File doesn't exist or otherwise can't load file" << std::endl;
        std::cout << filePath << std::endl;
        return false;
    }
    
    file.unsetf (std::ios::skipws);
    std::istream_iterator<uint8_t> begin (file), end;
    std::vector<uint8_t> fileData (begin, end);
    
    // get audio file type
    audioFileType = determineAudioFileType (fileData);
    
    if (audioFileType == AudioFileType::Wave)
    {
        return decodeWaveFile (fileData);
    }
    else if (audioFileType == AudioFileType::Aiff)
    {
        return decodeAiffFile (fileData);
    }
    else
    {
        std::cout << "Audio File Type: " << "Error" << std::endl;
        return false;
    }
}

//=============================================================
template <class T>
bool AudioFile<T>::decodeWaveFile (std::vector<uint8_t>& fileData)
{
    // -----------------------------------------------------------
    // HEADER CHUNK
    std::string headerChunkID (fileData.begin(), fileData.begin() + 4);
    //int32_t fileSizeInBytes = fourBytesToInt (fileData, 4) + 8;
    std::string format (fileData.begin() + 8, fileData.begin() + 12);
    
    // -----------------------------------------------------------
    // try and find the start points of key chunks
    int indexOfDataChunk = getIndexOfString (fileData, "data");
    int indexOfFormatChunk = getIndexOfString (fileData, "fmt");
    
    // if we can't find the data or format chunks, or the IDs/formats don't seem to be as expected
    // then it is unlikely we'll able to read this file, so abort
    if (indexOfDataChunk == -1 || indexOfFormatChunk == -1 || headerChunkID != "RIFF" || format != "WAVE")
    {
        std::cout << "ERROR: this doesn't seem to be a valid .WAV file" << std::endl;
        return false;
    }
    
    // -----------------------------------------------------------
    // FORMAT CHUNK
    int f = indexOfFormatChunk;
    std::string formatChunkID (fileData.begin() + f, fileData.begin() + f + 4);
    //int32_t formatChunkSize = fourBytesToInt (fileData, f + 4);
    int16_t audioFormat = twoBytesToInt (fileData, f + 8);
    int16_t numChannels = twoBytesToInt (fileData, f + 10);
    sampleRate = (int) fourBytesToInt (fileData, f + 12);
    int32_t numBytesPerSecond = fourBytesToInt (fileData, f + 16);
    int16_t numBytesPerBlock = twoBytesToInt (fileData, f + 20);
    bitDepth = (int) twoBytesToInt (fileData, f + 22);
    
    int numBytesPerSample = bitDepth / 8;
    
    // check that the audio format is PCM
    if (audioFormat != 1)
    {
        std::cout << "ERROR: this is a compressed .WAV file and this library does not support decoding them at present" << std::endl;
        return false;
    }
    
    // check the number of channels is mono or stereo
    if (numChannels < 1 ||numChannels > 2)
    {
        std::cout << "ERROR: this WAV file seems to be neither mono nor stereo (perhaps multi-track, or corrupted?)" << std::endl;
        return false;
    }
    
    // check header data is consistent
    if ((numBytesPerSecond != (numChannels * sampleRate * bitDepth) / 8) || (numBytesPerBlock != (numChannels * numBytesPerSample)))
    {
        std::cout << "ERROR: the header data in this WAV file seems to be inconsistent" << std::endl;
        return false;
    }
    
    // check bit depth is either 8, 16 or 24 bit
    if (bitDepth != 8 && bitDepth != 16 && bitDepth != 24)
    {
        std::cout << "ERROR: this file has a bit depth that is not 8, 16 or 24 bits" << std::endl;
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
            
            if (bitDepth == 8)
            {
                int32_t sampleAsInt = (int32_t) fileData[sampleIndex];
                T sample = (T)(sampleAsInt - 128) / (T)128.;
                
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = twoBytesToInt (fileData, sampleIndex);
                T sample = sixteenBitIntToSample (sampleAsInt);
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsInt = 0;
                sampleAsInt = (fileData[sampleIndex + 2] << 16) | (fileData[sampleIndex + 1] << 8) | fileData[sampleIndex];
                
                if (sampleAsInt & 0x800000) //  if the 24th bit is set, this is a negative number in 24-bit world
                    sampleAsInt = sampleAsInt | ~0xFFFFFF; // so make sure sign is extended to the 32 bit float

                T sample = (T)sampleAsInt / (T)8388608.;
                samples[channel].push_back (sample);
            }
            else
            {
                assert (false);
            }
        }
    }

    return true;
}

//=============================================================
template <class T>
bool AudioFile<T>::decodeAiffFile (std::vector<uint8_t>& fileData)
{
    // -----------------------------------------------------------
    // HEADER CHUNK
    std::string headerChunkID (fileData.begin(), fileData.begin() + 4);
    //int32_t fileSizeInBytes = fourBytesToInt (fileData, 4, Endianness::BigEndian) + 8;
    std::string format (fileData.begin() + 8, fileData.begin() + 12);
    
    // -----------------------------------------------------------
    // try and find the start points of key chunks
    int indexOfCommChunk = getIndexOfString (fileData, "COMM");
    int indexOfSoundDataChunk = getIndexOfString (fileData, "SSND");
    
    // if we can't find the data or format chunks, or the IDs/formats don't seem to be as expected
    // then it is unlikely we'll able to read this file, so abort
    if (indexOfSoundDataChunk == -1 || indexOfCommChunk == -1 || headerChunkID != "FORM" || format != "AIFF")
    {
        std::cout << "ERROR: this doesn't seem to be a valid AIFF file" << std::endl;
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
    
    // check the sample rate was properly decoded
    if (sampleRate == -1)
    {
        std::cout << "ERROR: this AIFF file has an unsupported sample rate" << std::endl;
        return false;
    }
    
    // check the number of channels is mono or stereo
    if (numChannels < 1 ||numChannels > 2)
    {
        std::cout << "ERROR: this AIFF file seems to be neither mono nor stereo (perhaps multi-track, or corrupted?)" << std::endl;
        return false;
    }
    
    // check bit depth is either 8, 16 or 24 bit
    if (bitDepth != 8 && bitDepth != 16 && bitDepth != 24)
    {
        std::cout << "ERROR: this file has a bit depth that is not 8, 16 or 24 bits" << std::endl;
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
    if ((soundDataChunkSize - 8) != totalNumAudioSampleBytes || totalNumAudioSampleBytes > (fileData.size() - samplesStartIndex))
    {
        std::cout << "ERROR: the metadatafor this file doesn't seem right" << std::endl;
        return false;
    }
    
    clearAudioBuffer();
    samples.resize (numChannels);
    
    for (int i = 0; i < numSamplesPerChannel; i++)
    {
        for (int channel = 0; channel < numChannels; channel++)
        {
            int sampleIndex = samplesStartIndex + (numBytesPerFrame * i) + channel * numBytesPerSample;
            
            if (bitDepth == 8)
            {
                int8_t sampleAsSigned8Bit = (int8_t)fileData[sampleIndex];
                T sample = (T)sampleAsSigned8Bit / (T)128.;
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = twoBytesToInt (fileData, sampleIndex, Endianness::BigEndian);
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
            else
            {
                assert (false);
            }
        }
    }
    
    return true;
}

//=============================================================
template <class T>
int AudioFile<T>::getAiffSampleRate (std::vector<uint8_t>& fileData, int sampleRateStartIndex)
{
    if (tenByteMatch (fileData, sampleRateStartIndex, aiff_8000, 0))
        return 8000;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_11025, 0))
        return 11025;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_16000, 0))
        return 16000;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_22050, 0))
        return 22050;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_32000, 0))
        return 32000;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_37800, 0))
        return 37800;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_44056, 0))
        return 44056;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_44100, 0))
        return 44100;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_47250, 0))
        return 47250;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_48000, 0))
        return 48000;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_50000, 0))
        return 50000;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_50400, 0))
        return 50400;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_88200, 0))
        return 88200;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_96000, 0))
        return 96000;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_176400, 0))
        return 176400;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_192000, 0))
        return 192000;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_352800, 0))
        return 352800;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_2822400, 0))
        return 2822400;
    else if (tenByteMatch (fileData, sampleRateStartIndex, aiff_5644800, 0))
        return 5644800;
    
    return -1;
}

//=============================================================
template <class T>
bool AudioFile<T>::tenByteMatch (std::vector<uint8_t>& v1, int startIndex1, std::vector<uint8_t>& v2, int startIndex2)
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
void AudioFile<T>::addSampleRateToAiffData (std::vector<uint8_t>& fileData, int sampleRate)
{
    if (sampleRate == 8000)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_8000[i]);
    }
    else if (sampleRate == 11025)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_11025[i]);
    }
    else if (sampleRate == 16000)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_16000[i]);
    }
    else if (sampleRate == 22050)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_22050[i]);
    }
    else if (sampleRate == 32000)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_32000[i]);
    }
    else if (sampleRate == 37800)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_37800[i]);
    }
    else if (sampleRate == 44056)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_44056[i]);
    }
    else if (sampleRate == 44100)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_44100[i]);
    }
    else if (sampleRate == 47250)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_47250[i]);
    }
    else if (sampleRate == 48000)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_48000[i]);
    }
    else if (sampleRate == 50000)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_50000[i]);
    }
    else if (sampleRate == 50400)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_50400[i]);
    }
    else if (sampleRate == 88200)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_88200[i]);
    }
    else if (sampleRate == 96000)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_96000[i]);
    }
    else if (sampleRate == 176400)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_176400[i]);
    }
    else if (sampleRate == 192000)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_192000[i]);
    }
    else if (sampleRate == 352800)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_352800[i]);
    }
    else if (sampleRate == 2822400)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_2822400[i]);
    }
    else if (sampleRate == 5644800)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiff_5644800[i]);
    }
}

//=============================================================
template <class T>
bool AudioFile<T>::save (std::string filePath, AudioFileType format)
{
    if (format == AudioFileType::Wave)
    {
        return saveToWaveFile (filePath);
    }
    else if (format == AudioFileType::Aiff)
    {
        return saveToAiffFile (filePath);
    }
    
    return false;
}

//=============================================================
template <class T>
bool AudioFile<T>::saveToWaveFile (std::string filePath)
{
    std::vector<uint8_t> fileData;
    
    int32_t dataChunkSize = getNumSamplesPerChannel() * (getNumChannels() * bitDepth / 8);
    
    // -----------------------------------------------------------
    // HEADER CHUNK
    addStringToFileData (fileData, "RIFF");
    
    // The file size in bytes is the header chunk size (4, not counting RIFF and WAVE) + the format
    // chunk size (24) + the metadata part of the data chunk plus the actual data chunk size
    int32_t fileSizeInBytes = 4 + 24 + 8 + dataChunkSize;
    addInt32ToFileData (fileData, fileSizeInBytes);
    
    addStringToFileData (fileData, "WAVE");
    
    // -----------------------------------------------------------
    // FORMAT CHUNK
    addStringToFileData (fileData, "fmt ");
    addInt32ToFileData (fileData, 16); // format chunk size (16 for PCM)
    addInt16ToFileData (fileData, 1); // audio format = 1
    addInt16ToFileData (fileData, (int16_t)getNumChannels()); // num channels
    addInt32ToFileData (fileData, (int32_t)sampleRate); // sample rate
    
    int32_t numBytesPerSecond = (int32_t) ((getNumChannels() * sampleRate * bitDepth) / 8);
    addInt32ToFileData (fileData, numBytesPerSecond);
    
    int16_t numBytesPerBlock = getNumChannels() * (bitDepth / 8);
    addInt16ToFileData (fileData, numBytesPerBlock);
    
    addInt16ToFileData (fileData, (int16_t)bitDepth);
    
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
                int32_t sampleAsInt = ((samples[channel][i] * (T)128.) + 128.);
                uint8_t byte = (uint8_t)sampleAsInt;
                fileData.push_back (byte);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = (int16_t) (samples[channel][i] * (T)32768.);
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
            else
            {
                assert (false);
            }
        }
    }
    
    // check that the various sizes we put in the metadata are correct
    if (fileSizeInBytes != (fileData.size() - 8) || dataChunkSize != (getNumSamplesPerChannel() * getNumChannels() * (bitDepth / 8)))
    {
        std::cout << "ERROR: couldn't save file to " << filePath << std::endl;
        return false;
    }
    
    // try to write the file
    return writeDataToFile (fileData, filePath);
}

//=============================================================
template <class T>
bool AudioFile<T>::saveToAiffFile (std::string filePath)
{
    std::vector<uint8_t> fileData;
    
    int32_t numBytesPerSample = bitDepth / 8;
    int32_t numBytesPerFrame = numBytesPerSample * getNumChannels();
    int32_t totalNumAudioSampleBytes = getNumSamplesPerChannel() * numBytesPerFrame;
    int32_t soundDataChunkSize = totalNumAudioSampleBytes + 8;
    
    // -----------------------------------------------------------
    // HEADER CHUNK
    addStringToFileData (fileData, "FORM");
    
    // The file size in bytes is the header chunk size (4, not counting FORM and AIFF) + the COMM
    // chunk size (26) + the metadata part of the SSND chunk plus the actual data chunk size
    int32_t fileSizeInBytes = 4 + 26 + 16 + totalNumAudioSampleBytes;
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
                int32_t sampleAsInt = (int32_t)(samples[channel][i] * (T)128.);
                uint8_t byte = (uint8_t)sampleAsInt;
                fileData.push_back (byte);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = (int16_t) (samples[channel][i] * (T)32768.);
                addInt16ToFileData (fileData, sampleAsInt, Endianness::BigEndian);
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
            else
            {
                assert (false);
            }
        }
    }
    
    // check that the various sizes we put in the metadata are correct
    if (fileSizeInBytes != (fileData.size() - 8) || soundDataChunkSize != getNumSamplesPerChannel() *  numBytesPerFrame + 8)
    {
        std::cout << "ERROR: couldn't save file to " << filePath << std::endl;
        return false;
    }
    
    // try to write the file
    return writeDataToFile (fileData, filePath);
}

//=============================================================
template <class T>
bool AudioFile<T>::writeDataToFile (std::vector<uint8_t>& fileData, std::string filePath)
{
    std::ofstream outputFile (filePath, std::ios::binary);
    
    if (outputFile.is_open())
    {
        for (int i = 0; i < fileData.size(); i++)
        {
            char value = (char) fileData[i];
            outputFile.write (&value, sizeof (char));
        }
        
        outputFile.close();
        
        return true;
    }
    
    return false;
}

//=============================================================
template <class T>
void AudioFile<T>::addStringToFileData (std::vector<uint8_t>& fileData, std::string s)
{
    for (int i = 0; i < s.length();i++)
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
    
    for (int i = 0; i < 4; i++)
        fileData.push_back (bytes[i]);
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
    for (int i = 0; i < samples.size();i++)
    {
        samples[i].clear();
    }
    
    samples.clear();
}

//=============================================================
template <class T>
AudioFileType AudioFile<T>::determineAudioFileType (std::vector<uint8_t>& fileData)
{
    std::string header (fileData.begin(), fileData.begin() + 4);
    
    if (header == "RIFF")
        return AudioFileType::Wave;
    else if (header == "FORM")
        return AudioFileType::Aiff;
    else
        return AudioFileType::Error;
}

//=============================================================
template <class T>
int32_t AudioFile<T>::fourBytesToInt (std::vector<uint8_t>& source, int startIndex, Endianness endianness)
{
    int32_t result;
    
    if (endianness == Endianness::LittleEndian)
        result = (source[startIndex + 3] << 24) | (source[startIndex + 2] << 16) | (source[startIndex + 1] << 8) | source[startIndex];
    else
        result = (source[startIndex] << 24) | (source[startIndex + 1] << 16) | (source[startIndex + 2] << 8) | source[startIndex + 3];
    
    return result;
}

//=============================================================
template <class T>
int16_t AudioFile<T>::twoBytesToInt (std::vector<uint8_t>& source, int startIndex, Endianness endianness)
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
int AudioFile<T>::getIndexOfString (std::vector<uint8_t>& source, std::string stringToSearchFor)
{
    int index = -1;
    int stringLength = (int)stringToSearchFor.length();
    
    for (int i = 0; i < source.size() - stringLength;i++)
    {
        std::string section (source.begin() + i, source.begin() + i + stringLength);
        
        if (section == stringToSearchFor)
        {
            index = i;
            break;
        }
    }
    
    return index;
}

//=============================================================
template <class T>
T AudioFile<T>::sixteenBitIntToSample (int16_t sample)
{
    return (T)sample / (T)32768.;
}

//===========================================================
template class AudioFile<float>;
template class AudioFile<double>;
