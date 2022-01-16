# AudioFile

<!-- Version and License Badges -->
![Version](https://img.shields.io/badge/version-1.1.0-green.svg?style=flat-square) 
![License](https://img.shields.io/badge/license-MIT-blue.svg?style=flat-square) 
![Language](https://img.shields.io/badge/language-C++-yellow.svg?style=flat-square) 

A simple header-only C++ library for reading and writing audio files. 

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
	
	// 4. do something here to fill the buffer with samples, e.g.
	
	#include <math.h> // somewhere earler (for M_PI and sinf())
	
	// then...
	
	int numChannels = 2;
	int numSamplesPerChannel = 100000;
	float sampleRate = 44100.f;
	float frequency = 440.f;

	for (int i = 0; i < numSamplesPerChannel; i++)
	{
        float sample = sinf (2. * M_PI * ((float) i / sampleRate) * frequency) ;
        
        for (int channel = 0; channel < numChannels; channel++)
             buffer[channel][i] = sample * 0.5;
	}
	
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


Examples
-----------------

Please see the `examples` folder for some examples on library usage. 


A Note On Types
-----------------

AudioFile is a template class and so it can be instantiated using floating point precision:

	AudioFile<float> audioFile;

...or double precision:

	AudioFile<double> audioFile;
	
This simply reflects the data type you would like to use to store the underlying audio samples. You can still read or write 8, 16 or 24-bit audio files, regardless of the type that you use (unless your system uses a precision for floats less than your desired bit depth).

I have heard of people using the library with other types, but I have not designed for those cases. Let me know if you are interested in this supporting a specific type more formally.

Error Messages
-----------------

By default, the library logs error messages to the console to provide information on what has gone wrong (e.g. a file we tried to load didn't exist). 

If you prefer not to see these messages, you can disable this error logging behaviour using:

	audioFile.shouldLogErrorsToConsole (false);


Versions
-------

##### 1.1.0 - 15th January 2022

- Moved project to MIT licence
- Added option to load an audio file already in memory
- CI Workflow improvements and bug fixes

##### 1.0.9 - 23rd January 2021

- Faster loading of audio files
- Bug fixes

##### 1.0.8 - 18th October 2020

- CMake support
- Construct instances with a file path
- Bug fixes

##### 1.0.7 - 3rd July 2020

- Support for 32-bit audio files
- Support for multi-channel audio files
- Reading/writing of [iXML data chunks](http://www.ixml.info/)

##### 1.0.6 - 29th February 2020

- Made error logging to the console optional
- Fixed lots of compiler warnings 

##### 1.0.5 - 14th October 2019

- Added include of <algorithm> to better support Visual Studio

##### 1.0.4 - 13th October 2019

- Changed to a header-only library. Now you can just include AudioFile.h
- Bug fixes

##### 1.0.3 - 28th October 2018

- Bug fixes
- Documentation updates

##### 1.0.2 - 6th June 2017

- Bug fixes

Contributions
-------

* Multichannel (i.e. >2 channels) audio file support ([Sidelobe](https://github.com/Sidelobe))
* Read/write of iXML data chunks ([mynameisjohn](https://github.com/mynameisjohn))
* Remove warnings ([Abhinav1997](https://github.com/Abhinav1997))
* Better support on Ubuntu ([BenjaminHinchliff](https://github.com/BenjaminHinchliff))
* Faster loading of audio files ([helloimmatt](https://github.com/helloimmatt/))
* Improvements to Github Actions workflow ([emiro85](https://github.com/emiro85))
* Pull request review ([MatthieuHernandez](https://github.com/MatthieuHernandez))

Want to Contribute?
-------

If you would like to submit a pull request for this library, please do! But kindly follow the following simple guidelines...

* Make the changes as concise as is possible for the change you are proposing
* Avoid unnecessarily changing a large number of lines - e.g. commits changing the number of spaces in indentations on all lines (and so on)
* Keep to the code style of this library which is the [JUCE Coding Standards](https://juce.com/discover/stories/coding-standards)

License
-------

MIT License

Copyright (c) 2017 Adam Stark

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.