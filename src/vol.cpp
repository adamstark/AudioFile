#include <iostream>
#include "../lib/AudioFile/AudioFile.h"
#include <math.h>
using namespace std;

void die (const char*msg) {
	cout << msg << endl;
	exit(1);
}

int main(int argc, char**argv) {
	if (argc != 4) {
		die("usage: ./vol <volume multiplier> <source file path> <destination file path>");
	}
	double mult = stod(argv[1]);

	AudioFile<float> file;
        file.load(argv[2]);
	int numSamples = file.getNumSamplesPerChannel();
	for (int channel = 0; channel < 2; channel++) { // for each channel
		for (int j = 0; j < numSamples; j++) {
			file.samples[channel][j] =( file.samples[channel][j] * mult);
		}
	}
        file.save(argv[3], AudioFileFormat::Wave);
	cout << "end" << endl;
	return 0;
}
