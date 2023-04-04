# AudioFile

<!-- Version and License Badges -->
![Version](https://img.shields.io/badge/version-1.1.1-green.svg?style=flat-square) 
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
	audioFile.setNumChannels (numChannels);
	
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

For example

	AudioFile<float> audioFile;

...or double precision...

	AudioFile<double> audioFile;
	
...or an integer type:

	AudioFile<int> audioFile;	
	
This simply reflects the data type you would like to use to store the underlying audio samples. 

When you use an integer type to store the samples (e.g. `int` or `int8_t` or `int16_t` or `uint32_t`), the library will read in the integer sample values directly from the audio file. A couple of notes on integer types:

* The range of samples is designed to be symmetric. This means that for (e.g.) an signed 8-bit integer (`int8_t`) we will use the range `[-127, 127]` for storing samples representing the `[-1., 1.]` range. The value `-128` is possible here given the `int8_t` type, but this is interpreted as a value slightly lower than `-1` (specifically `-1.007874015748`).

* In the case of unsigned types, we obviously can't store samples as negative values. Therefore, we used the equivalent range of the unsigned type in use. E.g. if with a 8-bit signed integer (`int8_t`) the range would be `[-127, 127]`, for an 8-bit unsigned integer we would use the range `[1, 255]`. Note that we don't use `-128` for `int8_t` or `0` in `uint8_t`.

* If you try to read an audio file with a larger bit-depth than the type you are using to store samples, the attempt to read the file will fail. Put more simply, you can't read a 16-bit audio file into an 8-bit integer.

* If you are writing audio samples in integer formats, you should use the correct sample range for both a) the type you are using to store samples; and b) the bit depth of the audio you want to write.

The following table details the sample range for each bit-depth:

| Type  | 8-bit Audio | 16-bit Audio | 24-bit Audio | 32-bit Audio |
| ------------- | ------------- | ------------- | ------------- | ------------- |
| `float` | `[-1.0, 1.0]` | `[-1.0, 1.0]` | `[-1.0, 1.0]` | `[-1.0, 1.0]` |
| `double` | `[-1.0, 1.0]` | `[-1.0, 1.0]` | `[-1.0, 1.0]` | `[-1.0, 1.0]` |
| `int8_t` | `[-127, 127]` | :x: (type too small) | :x: (type too small) | :x: (type too small) |
| `uint8_t` | `[1, 255]` | :x: (type too small) | :x: (type too small) | :x: (type too small) |
| `int16_t` | `[-127, 127]` | `[-32767, 32767]` | :x: (type too small) | :x: (type too small) |
| `uint16_t` | `[1, 255]` | `[1, 65535]` | :x: (type too small) | :x: (type too small) |
| `int32_t` | `[-127, 127]` | `[-32767, 32767]` | [`-8388607, 8388607]`  | `[-2147483647, 2147483647]` |
| `uint32_t` | `[1, 255]` | `[1, 65535]` | `[1, 16777215]` | `[1, 4294967295]` |
| `int64_t` | `[-127, 127]` | `[-32767, 32767]` | [`-8388607, 8388607]`  | `[-2147483647, 2147483647]` |
| `uint64_t` | `[1, 255]` | `[1, 65535]` | `[1, 16777215]` | `[1, 4294967295]` |

Error Messages
-----------------

By default, the library logs error messages to the console to provide information on what has gone wrong (e.g. a file we tried to load didn't exist). 

If you prefer not to see these messages, you can disable this error logging behaviour using:

	audioFile.shouldLogErrorsToConsole (false);


Versions
-------

##### 1.1.1 - 4th April 2023

- Support for integer formats
- Improved unit testing
- Many bug fixes

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

Many thanks to the following people for their contributions to this library:

* [Abhinav1997](https://github.com/Abhinav1997)
* [alxarsenault](https://github.com/alxarsenault)
* [BenjaminHinchliff](https://github.com/BenjaminHinchliff)
* [emiro85](https://github.com/emiro85)
* [heartofrain](https://github.com/heartofrain)
* [helloimmatt](https://github.com/helloimmatt/)
* [MatthieuHernandez](https://github.com/MatthieuHernandez)
* [mrpossoms](https://github.com/mrpossoms)
* [mynameisjohn](https://github.com/mynameisjohn)
* [Sidelobe](https://github.com/Sidelobe)
* [sschaetz](https://github.com/sschaetz)
* [Yhcrown](https://github.com/Yhcrown)

Want to Contribute?
-------

If you would like to submit a pull request for this library, please do! But kindly follow the following simple guidelines...

* Make the changes as concise as is possible for the change you are proposing
* Avoid unnecessarily changing a large number of lines - e.g. commits changing the number of spaces in indentations on all lines (and so on)
* Keep to the code style of this library which is the [JUCE Coding Standards](https://juce.com/discover/stories/coding-standards)
* Make the changes relative to the develop branch of the library (as this may have advanced beyond the master branch)

License
-------

MIT License

Copyright (c) 2017 Adam Stark

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
