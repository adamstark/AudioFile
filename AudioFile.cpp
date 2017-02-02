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

// http://soundfile.sapp.org/doc/WaveFormat/
// https://blogs.msdn.microsoft.com/dawate/2009/06/23/intro-to-audio-programming-part-2-demystifying-the-wav-format/

//=============================================================
template <class T>
AudioFile<T>::AudioFile()
{
    bitDepth = 16;
    sampleRate = 44100;
    numChannels = 1;
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
bool AudioFile<T>::isMono()
{
    return getNumChannels() == 1;
}

//=============================================================
template <class T>
bool AudioFile<T>::isStereo()
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
    if (audioSampleBuffer.size() > 0)
        return (int) audioSampleBuffer[0].size();
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
const std::vector<T>& AudioFile<T>::getAudioChannel (int channel) const
{
    // If you've hit this, it seems you are requesting an audio channel
    // that does not exist... Perhaps check using getNumChannels()
    assert (channel >= 0 && channel < getNumChannels());
    
    return audioSampleBuffer[channel];
}

//=============================================================
template <class T>
const typename AudioFile<T>::AudioBuffer& AudioFile<T>::getAudioBuffer() const
{
    return audioSampleBuffer;
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
    
    if (audioFileType == AudioFileType::Wav)
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
    //int32_t subChunk1Size = fourBytesToInt (fileData, f + 4);
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
    audioSampleBuffer.resize (numChannels);
    
    for (int i = 0; i < numSamples; i++)
    {
        for (int channel = 0; channel < numChannels; channel++)
        {
            int sampleIndex = samplesStartIndex + (numBytesPerBlock * i) + channel * numBytesPerSample;
            
            if (bitDepth == 16)
            {
                int16_t sampleAsInt = twoBytesToInt (fileData, sampleIndex);
                T sample = sixteenBitIntToSample (sampleAsInt);
                audioSampleBuffer[channel].push_back (sample);
            }
            else if (bitDepth == 24)
            {
                // to do
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
void AudioFile<T>::clearAudioBuffer()
{
    for (int i = 0; i < audioSampleBuffer.size();i++)
    {
        audioSampleBuffer[i].clear();
    }
    
    audioSampleBuffer.clear();
}

//=============================================================
template <class T>
typename AudioFile<T>::AudioFileType AudioFile<T>::determineAudioFileType (std::vector<unsigned char>& fileData)
{
    std::string header (fileData.begin(), fileData.begin() + 4);
    
    if (header == "RIFF")
        return AudioFileType::Wav;
    else
        return AudioFileType::Unknown;
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

//===========================================================
template class AudioFile<float>;
template class AudioFile<double>;
