//=======================================================================
/** @file AudioFile.h
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

#ifndef _AS_AudioFile_h
#define _AS_AudioFile_h

#include <iostream>
#include <vector>
#include <assert.h>


//=============================================================
template <class T>
class AudioFile
{
public:
    
    typedef std::vector<std::vector<T>> AudioBuffer;
    
    //=============================================================
    enum class AudioFileType
    {
        Error,
        Unknown,
        NotLoaded,
        Wav
    };
    
    //=============================================================
    /** Constructor */
    AudioFile();
    
    //=============================================================
    bool load (std::string filePath);
    
    bool save (std::string filePath);
    
    //=============================================================
    const std::vector<T>& getAudioChannel (int channel) const;
    
    const AudioBuffer& getAudioBuffer() const;
    
    //=============================================================
    /** @Returns the sample rate */
    int getSampleRate() const;
    
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
    double getLengthInSeconds();
    
    /** Prints a summary of the audio file to the console */
    void printSummary();
    
private:
    
    //=============================================================
    bool decodeWaveFile (std::vector<unsigned char>& fileData);
    
    //=============================================================
    bool writeToWaveFile (std::string filePath);
    
    //=============================================================
    void clearAudioBuffer();
    
    //=============================================================
    AudioFileType determineAudioFileType (std::vector<unsigned char>& fileData);
    int32_t fourBytesToInt (std::vector<unsigned char>& source, int startIndex);
    int16_t twoBytesToInt (std::vector<unsigned char>& source, int startIndex);
    int getIndexOfString (std::vector<unsigned char>& source, std::string s);
    T sixteenBitIntToSample (int16_t sample);
    T singleByteToSample (unsigned char byte);
    
    //=============================================================
    void addStringToFileData (std::vector<unsigned char>& fileData, std::string s);
    
    //=============================================================
    AudioFileType audioFileType;
    std::vector<std::vector<T>> audioSampleBuffer;
    int sampleRate;
    int numChannels;
    int bitDepth;
};



#endif /* AudioFile_h */
