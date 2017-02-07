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
template <class T>
AudioFile<T>::AudioFile()
{
    bitDepth = 16;
    sampleRate = 44100;
    numChannels = 1;
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
    return numChannels;
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
    std::cout << "Num Channels: " << numChannels << std::endl;
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
    std::istream_iterator<unsigned char> begin (file), end;
    std::vector<unsigned char> fileData (begin, end);
    
    // get audio file type
    audioFileType = determineAudioFileType (fileData);
    
    if (audioFileType == AudioFileType::Wave)
    {
        return decodeWaveFile (fileData);
    }
    else
    {
        std::cout << "Audio File Type: " << "Error" << std::endl;
        return false;
    }
}

//=============================================================
template <class T>
bool AudioFile<T>::decodeWaveFile (std::vector<unsigned char>& fileData)
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
    numChannels = (int) twoBytesToInt (fileData, f + 10);
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
                T sample = singleByteToSample (fileData[sampleIndex]);
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
bool AudioFile<T>::save (std::string filePath)
{
    return saveToWaveFile (filePath);
    
    return false;
}

//=============================================================
template <class T>
bool AudioFile<T>::saveToWaveFile (std::string filePath)
{
    std::vector<unsigned char> fileData;
    
    int32_t dataChunkSize = getNumSamplesPerChannel() * (numChannels * bitDepth / 8);
    
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
    addInt16ToFileData (fileData, (int16_t)numChannels); // num channels
    addInt32ToFileData (fileData, (int32_t)sampleRate); // sample rate
    
    int32_t numBytesPerSecond = (int32_t) ((numChannels * sampleRate * bitDepth) / 8);
    addInt32ToFileData (fileData, numBytesPerSecond);
    
    int16_t numBytesPerBlock = numChannels * (bitDepth / 8);
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
                unsigned char byte = (unsigned char)sampleAsInt;
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
                
                unsigned char bytes[3];
                bytes[2] = (unsigned char) (sampleAsIntAgain >> 16) & 0xFF;
                bytes[1] = (unsigned char) (sampleAsIntAgain >>  8) & 0xFF;
                bytes[0] = (unsigned char) sampleAsIntAgain & 0xFF;
                
                fileData.push_back (bytes[0]);
                fileData.push_back (bytes[1]);
                fileData.push_back (bytes[2]);
            }
        }
    }
    
    // check that the various sizes we put in the metadata are correct
    if (fileSizeInBytes != (fileData.size() - 8) || dataChunkSize != (getNumSamplesPerChannel() * numChannels * (bitDepth / 8)))
    {
        std::cout << "ERROR: couldn't save file to " << filePath << std::endl;
        return false;
    }
    
    // try to write the file
    return writeDataToFile (fileData, filePath);
}

//=============================================================
template <class T>
bool AudioFile<T>::writeDataToFile (std::vector<unsigned char>& fileData, std::string filePath)
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
void AudioFile<T>::addStringToFileData (std::vector<unsigned char>& fileData, std::string s)
{
    for (int i = 0; i < s.length();i++)
        fileData.push_back ((unsigned char) s[i]);
}

//=============================================================
template <class T>
void AudioFile<T>::addInt32ToFileData (std::vector<unsigned char>& fileData, int32_t i)
{
    unsigned char bytes[4];
    
    bytes[3] = (i >> 24) & 0xFF;
    bytes[2] = (i >> 16) & 0xFF;
    bytes[1] = (i >> 8) & 0xFF;
    bytes[0] = i & 0xFF;
    
    for (int i = 0; i < 4; i++)
        fileData.push_back (bytes[i]);
}

//=============================================================
template <class T>
void AudioFile<T>::addInt16ToFileData (std::vector<unsigned char>& fileData, int16_t i)
{
    unsigned char bytes[2];
    
    bytes[1] = (i >> 8) & 0xFF;
    bytes[0] = i & 0xFF;
    
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
typename AudioFile<T>::AudioFileType AudioFile<T>::determineAudioFileType (std::vector<unsigned char>& fileData)
{
    std::string header (fileData.begin(), fileData.begin() + 4);
    
    if (header == "RIFF")
        return AudioFileType::Wave;
    else
        return AudioFileType::Error;
}

//=============================================================
template <class T>
int32_t AudioFile<T>::fourBytesToInt (std::vector<unsigned char>& source, int startIndex)
{
    int32_t result = (source[startIndex + 3] << 24) | (source[startIndex + 2] << 16) | (source[startIndex + 1] << 8) | source[startIndex];
    return result;
}

//=============================================================
template <class T>
int16_t AudioFile<T>::twoBytesToInt (std::vector<unsigned char>& source, int startIndex)
{
    int16_t result = (source[startIndex + 1] << 8) | source[startIndex];
    return result;
}

//=============================================================
template <class T>
int AudioFile<T>::getIndexOfString (std::vector<unsigned char>& source, std::string stringToSearchFor)
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

//=============================================================
template <class T>
T AudioFile<T>::singleByteToSample (unsigned char byte)
{
    int32_t sampleAsInt = (int32_t) byte;
    return (T)(sampleAsInt - 128) / (T)128.;
}

//===========================================================
template class AudioFile<float>;
template class AudioFile<double>;
