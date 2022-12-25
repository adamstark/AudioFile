#include "4rer.h"

AudioFile<double>::AudioBuffer layer (int argc, char**argv) {
	AudioFile<double>::AudioBuffer buffer;
        buffer.resize (2);
        buffer[0].resize (0);
        buffer[1].resize (0);
        int numSamples = 0;
        // for each argument, add it to buffer
        for (int i = 0; i < argc-2; i++) {
                AudioFile<double> layered;
                if (!(layered.load (argv[i])))
                        die("Failed to load file");
                int newNumSamples = layered.getNumSamplesPerChannel();
                int larger = (numSamples >  newNumSamples ? numSamples:newNumSamples);
                int smaller = (numSamples > newNumSamples ? newNumSamples:numSamples);
                buffer[0].resize (larger);
                buffer[1].resize (larger);
                cout << argv[i] << endl;
                for (int channel = 0; channel < 2; channel++) { // for each channel
                        for (int j = 0; j < larger; j++) {
                                if (j < smaller) {
                                        double currentSample = layered.samples[channel][j];
                                        buffer[channel][j]+=currentSample;
                                        buffer[channel][j]/=2;
                                }
                                else if (larger > numSamples) {
                                        buffer[channel][j] = layered.samples[channel][j];
                                }
                        }
                }
                numSamples=larger;
        }
	return buffer;
}

int main(int argc, char**argv) {
	if (argc < 4) {
		die("usage: ./layer <source path> <source path> ... <destination path>");
	}
	argv++;
	saveFile(argv[argc-2], layer(argc, argv), 44100, 24);
	return 0;
}
