#include <iostream>
#include "../lib/AudioFile/AudioFile.h"
#include <math.h>
#include <cstring>
using namespace std;

void die (const char*msg) {
        cout << msg << endl;
        exit(1);
}

/*
AudioFile<double>::AudioBuffer ** openPaths (int numPaths, char** filePaths) {
	AudioFile<double>::AudioBuffer buffer;	
	for (int i = 0; i < numPaths; i++) {
	}
	return &&buffer;
} */

void saveFile(char*path, AudioFile<double>::AudioBuffer buffer, float sampleRate, int bitDepth) {
	AudioFile<double> audioFile;
        if (!(audioFile.setAudioBuffer (buffer)))
		die("Error: couldn't set audio buffer");
        // Set both the number of channels and number of samples per channel
        audioFile.setAudioBufferSize (buffer.size(), buffer[0].size());

        audioFile.setBitDepth (bitDepth);
        audioFile.setSampleRate (sampleRate);
        audioFile.save(path, AudioFileFormat::Wave);
        cout << path << endl;
        return;	
}

void writeBuffer(AudioFile<double>::AudioBuffer *buffer, int numSamples) {
	fwrite(&numSamples, sizeof(int), 1, stdout);
        fprintf(stderr, "num samples: %d\n size of sample: %ld\n", numSamples, sizeof(double));
        for (int channel = 0; channel < 2; channel++) { // for each channel
                for (int j = 0; j < numSamples; j++) {
                        fwrite(&(*buffer)[channel][j], sizeof(double), 1, stdout);
                }
        }
        return;	

}

int readSamplesFromFile(AudioFile<double>::AudioBuffer *buffer, AudioFile<double> file) {
	int numSamples = file.getNumSamplesPerChannel();
	(*buffer).resize(2);
	(*buffer)[0].resize (numSamples);
        (*buffer)[1].resize (numSamples);
	for (int channel = 0; channel < 2; channel++) 
		for (int i = 0; i < numSamples; i++) 
			(*buffer)[channel][i] = file.samples[channel][i];
	return numSamples;
}

int readSamplesFromInput(AudioFile<double>::AudioBuffer *buffer) {
	int numSamples;
	if (fread(&numSamples, sizeof(int), 1, stdin)==0)
		die("fread failed");
	(*buffer).resize (2);
        (*buffer)[0].resize (numSamples);
        (*buffer)[1].resize (numSamples);
	fprintf(stderr, "num samples read: %d\n size of sample: %ld\n", numSamples, sizeof(double));
        for (int channel = 0; channel < 2; channel++) { // for each channel
        	for (int j = 0; j < numSamples; j++) {
                	fread(&((*buffer)[channel][j]), sizeof((*buffer)[0][0]), 1, stdin);
		}
        }
	return numSamples;
}



AudioFile<double>::AudioBuffer layer (int argc, char**argv);

AudioFile<double>::AudioBuffer append (int argc, char**argv);












