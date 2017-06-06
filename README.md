# AudioFile

<!-- Version and License Badges -->
![Version](https://img.shields.io/badge/version-1.0.2-green.svg?style=flat-square) 
![License](https://img.shields.io/badge/license-GPL-blue.svg?style=flat-square) 
![Language](https://img.shields.io/badge/language-C++-yellow.svg?style=flat-square) 

A simple C++ library for reading and writing audio files. 

Current supported formats:

* WAV
* AIFF

Author
------

AudioFile is written and maintained by Adam Stark.

[http://www.adamstark.co.uk](http://www.adamstark.co.uk)

Usage
-----

### Create an AudioFile object:

	#include "AudioFile.h"

	AudioFile<double> audioFile;
		
### Load an audio file:

	audioFile.load ("/path/to/my/audiofile.wav");
	
### Get some information about the loaded audio:

	int sampleRate = audioFile.getSampleRate();
	int bitDepth = audioFile.getBitDepth();
	
	int numSamples = audioFile.getNumSamplesPerChannel();
	double lengthInSeconds = audioFile.getLengthInSeconds();
	
	int numChannels = audioFile.getNumChannels();
	bool isMono = audioFile.isMono();
	bool isStereo = audioFile.isStereo();
	
	// or, just use this quick shortcut to print a summary to the console
	audioFile.printSummary();
	
### Access the samples directly:

	int channel = 0;
	int numSamples = audioFile.getNumSamplesPerChannel();

	for (int i = 0; i < numSamples; i++)
	{
		double currentSample = audioFile.samples[channel][i];
	}

### Replace the AudioFile audio buffer with another

	// 1. Create an AudioBuffer 
	// (BTW, AudioBuffer is just a vector of vectors)
	
	AudioFile<double>::AudioBuffer buffer;
	
	// 2. Set to (e.g.) two channels
	buffer.resize (2);
	
	// 3. Set number of samples per channel
	buffer[0].resize (100000);
	buffer[1].resize (100000);
	
	// 4. do something here to fill the buffer with samples
	
	// 5. Put into the AudioFile object
	bool ok = audioFile.setAudioBuffer (buffer);
	
	
### Resize the audio buffer	

	// Set both the number of channels and number of samples per channel
	audioFile.setAudioBufferSize (numChannels, numSamples);
	
	// Set the number of samples per channel
	audioFile.setNumSamplesPerChannel (numSamples);
	
	// Set the number of channels
	audioFile.setNumChannels (int numChannels);
	
### Set bit depth and sample rate
	
	audioFile.setBitDepth (24);
	audioFile.setSampleRate (44100);
	
### Save the audio file to disk
	
	// Wave file (implicit)
	audioFile.save ("path/to/desired/audioFile.wav");
	
	// Wave file (explicit)
	audioFile.save ("path/to/desired/audioFile.wav", AudioFileFormat::Wave);
	
	// Aiff file
	audioFile.save ("path/to/desired/audioFile.aif", AudioFileFormat::Aiff);


A Note On Types
-----------------

AudioFile is a template class and so it can be instantiated using floating point precision:

	AudioFile<float> audioFile;

...or double precision:

	AudioFile<double> audioFile;
	
This simply reflects the data type you would like to use to store the underlying audio samples. You can still read or write 8, 16 or 24-bit audio files, regardless of the type that you use (unless your system uses a precision for floats less than your desired bit depth).

Versions
-------

##### 1.0.2 - 6th June 2017

- Bug fixes

License
-------

Copyright (c) 2017 Adam Stark

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.