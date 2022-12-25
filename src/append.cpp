#include "4rer.h"

AudioFile<double>::AudioBuffer append (int argc, char**argv) {
	AudioFile<double>::AudioBuffer buffer;
        buffer.resize (2);
        int numSamples = 0;
        // for each argument, add it to buffer
        for (int i = 0; i < argc-2; i++) {
                AudioFile<double> appended;
                appended.load (argv[i]);
                int newNumSamples = appended.getNumSamplesPerChannel();
                buffer[0].resize (numSamples + newNumSamples);
                buffer[1].resize (numSamples + newNumSamples);
                cout << argv[i] << endl;
                for (int channel = 0; channel < 2; channel++) { // for each channel
                        for (int j = 0; j < newNumSamples; j++) {
                                double currentSample = appended.samples[channel][j];
                                buffer[channel][j+numSamples] = currentSample;
                        }
                }
                numSamples+=newNumSamples;
        }
	return buffer;
}
int main(int argc, char**argv) {
	if (argc < 4) {
		die("usage: ./append <source file path> <source file path> ... <destination file path>");
	}
	argv++;
	saveFile(argv[argc-2], append(argc, argv), 44100, 24);
	return 0;
}
